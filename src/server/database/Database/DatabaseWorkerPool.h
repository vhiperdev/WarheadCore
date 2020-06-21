/*
 * This file is part of the WarheadCore Project. See AUTHORS file for Copyright information
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation; either version 2 of the License, or (at your
 * option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for
 * more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program. If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef _DATABASEWORKERPOOL_H
#define _DATABASEWORKERPOOL_H

#include "Common.h"
#include "QueryCallback.h"
#include "MySQLConnection.h"
#include "Transaction.h"
#include "DatabaseWorker.h"
#include "PreparedStatement.h"
#include "Log.h"
#include "QueryResult.h"
#include "QueryHolder.h"
#include "AdhocStatement.h"
#include "StringFormat.h"
#include <ace/Thread_Mutex.h>

class PingOperation : public SQLOperation
{
    //! Operation for idle delaythreads
    bool Execute()
    {
        m_conn->Ping();
        return true;
    }
};

template <class T>
class DatabaseWorkerPool
{
    public:
        /* Activity state */
        DatabaseWorkerPool();

        ~DatabaseWorkerPool() { }

        void SetConnectionInfo(std::string const& infoString, uint8 const asyncThreads, uint8 const synchThreads);

        uint32 Open();

        void Close();

        //! Prepares all prepared statements
        bool PrepareStatements();

        inline MySQLConnectionInfo const* GetConnectionInfo() const
        {
            return _connectionInfo.get();
        }

        /**
            Delayed one-way statement methods.
        */

        //! Enqueues a one-way SQL operation in string format that will be executed asynchronously.
        //! This method should only be used for queries that are only executed once, e.g during startup.
        void Execute(const char* sql);

        //! Enqueues a one-way SQL operation in string format -with variable args- that will be executed asynchronously.
        //! This method should only be used for queries that are only executed once, e.g during startup.
        template<typename Format, typename... Args>
        void PExecute(Format&& sql, Args&&... args)
        {
            if (warhead::IsFormatEmptyOrNull(sql))
                return;

            Execute(warhead::StringFormat(std::forward<Format>(sql), std::forward<Args>(args)...).c_str());
        }

        //! Enqueues a one-way SQL operation in prepared statement format that will be executed asynchronously.
        //! Statement must be prepared with CONNECTION_ASYNC flag.
        void Execute(PreparedStatement* stmt);

        /**
            Direct synchronous one-way statement methods.
        */

        //! Directly executes a one-way SQL operation in string format, that will block the calling thread until finished.
        //! This method should only be used for queries that are only executed once, e.g during startup.
        void DirectExecute(const char* sql);

        //! Directly executes a one-way SQL operation in string format -with variable args-, that will block the calling thread until finished.
        //! This method should only be used for queries that are only executed once, e.g during startup.
        template<typename Format, typename... Args>
        void DirectPExecute(Format&& sql, Args&&... args)
        {
            if (warhead::IsFormatEmptyOrNull(sql))
                return;

            DirectExecute(warhead::StringFormat(std::forward<Format>(sql), std::forward<Args>(args)...).c_str());
        }

        //! Directly executes a one-way SQL operation in prepared statement format, that will block the calling thread until finished.
        //! Statement must be prepared with the CONNECTION_SYNCH flag.
        void DirectExecute(PreparedStatement* stmt);

        /**
            Synchronous query (with resultset) methods.
        */

        //! Directly executes an SQL query in string format that will block the calling thread until finished.
        //! Returns reference counted auto pointer, no need for manual memory management in upper level code.
        QueryResult Query(const char* sql, T* conn = nullptr);

        //! Directly executes an SQL query in string format -with variable args- that will block the calling thread until finished.
        //! Returns reference counted auto pointer, no need for manual memory management in upper level code.
        template<typename Format, typename... Args>
        QueryResult PQuery(Format&& sql, T* conn, Args&&... args)
        {
            if (warhead::IsFormatEmptyOrNull(sql))
                return QueryResult(nullptr);

            return Query(warhead::StringFormat(std::forward<Format>(sql), std::forward<Args>(args)...).c_str(), conn);
        }

        //! Directly executes an SQL query in string format -with variable args- that will block the calling thread until finished.
        //! Returns reference counted auto pointer, no need for manual memory management in upper level code.
        template<typename Format, typename... Args>
        QueryResult PQuery(Format&& sql, Args&&... args)
        {
            if (warhead::IsFormatEmptyOrNull(sql))
                return QueryResult(nullptr);

            return Query(warhead::StringFormat(std::forward<Format>(sql), std::forward<Args>(args)...).c_str());
        }

        //! Directly executes an SQL query in prepared format that will block the calling thread until finished.
        //! Returns reference counted auto pointer, no need for manual memory management in upper level code.
        //! Statement must be prepared with CONNECTION_SYNCH flag.
        PreparedQueryResult Query(PreparedStatement* stmt);

        /**
            Asynchronous query (with resultset) methods.
        */

        //! Enqueues a query in string format that will set the value of the QueryResultFuture return object as soon as the query is executed.
        //! The return value is then processed in ProcessQueryCallback methods.
        QueryResultFuture AsyncQuery(const char* sql);

        //! Enqueues a query in string format -with variable args- that will set the value of the QueryResultFuture return object as soon as the query is executed.
        //! The return value is then processed in ProcessQueryCallback methods.
        template<typename Format, typename... Args>
        QueryResultFuture AsyncPQuery(Format&& sql, Args&&... args)
        {
            if (warhead::IsFormatEmptyOrNull(sql))
                return QueryResult(nullptr);

            return AsyncQuery(warhead::StringFormat(std::forward<Format>(sql), std::forward<Args>(args)...).c_str());
        }

        //! Enqueues a query in prepared format that will set the value of the PreparedQueryResultFuture return object as soon as the query is executed.
        //! The return value is then processed in ProcessQueryCallback methods.
        //! Statement must be prepared with CONNECTION_ASYNC flag.
        PreparedQueryResultFuture AsyncQuery(PreparedStatement* stmt);

        //! Enqueues a vector of SQL operations (can be both adhoc and prepared) that will set the value of the QueryResultHolderFuture
        //! return object as soon as the query is executed.
        //! The return value is then processed in ProcessQueryCallback methods.
        //! Any prepared statements added to this holder need to be prepared with the CONNECTION_ASYNC flag.
        QueryResultHolderFuture DelayQueryHolder(SQLQueryHolder* holder);

        /**
            Transaction context methods.
        */

        //! Begins an automanaged transaction pointer that will automatically rollback if not commited. (Autocommit=0)
        SQLTransaction BeginTransaction();

        //! Enqueues a collection of one-way SQL operations (can be both adhoc and prepared). The order in which these operations
        //! were appended to the transaction will be respected during execution.
        void CommitTransaction(SQLTransaction transaction);

        //! Directly executes a collection of one-way SQL operations (can be both adhoc and prepared). The order in which these operations
        //! were appended to the transaction will be respected during execution.
        void DirectCommitTransaction(SQLTransaction& transaction);

        //! Method used to execute prepared statements in a diverse context.
        //! Will be wrapped in a transaction if valid object is present, otherwise executed standalone.
        void ExecuteOrAppend(SQLTransaction& trans, PreparedStatement* stmt);

        //! Method used to execute ad-hoc statements in a diverse context.
        //! Will be wrapped in a transaction if valid object is present, otherwise executed standalone.
        void ExecuteOrAppend(SQLTransaction& trans, const char* sql);

        /**
            Other
        */

        //! Automanaged (internally) pointer to a prepared statement object for usage in upper level code.
        //! Pointer is deleted in this->DirectExecute(PreparedStatement*), this->Query(PreparedStatement*) or PreparedStatementTask::~PreparedStatementTask.
        //! This object is not tied to the prepared statement on the MySQL context yet until execution.
        PreparedStatement* GetPreparedStatement(uint32 index);

        //! Apply escape string'ing for current collation. (utf8)
        unsigned long EscapeString(char* to, const char* from, unsigned long length)
        {
            if (!to || !from || !length)
                return 0;

            return mysql_real_escape_string(_connections[IDX_SYNCH][0]->GetHandle(), to, from, length);
        }

        //! Keeps all our MySQL connections alive, prevent the server from disconnecting us.
        void KeepAlive();
        
        void EscapeString(std::string& str)
        {
            if (str.empty())
                return;

            char* buf = new char[str.size() * 2 + 1];
            EscapeString(buf, str.c_str(), str.size());
            str = buf;
            delete[] buf;
        }

    private:
        enum InternalIndex
        {
            IDX_ASYNC,
            IDX_SYNCH,
            IDX_SIZE
        };

        uint32 OpenConnections(InternalIndex type, uint8 numConnections);

        void Enqueue(SQLOperation* op)
        {
            _queue->enqueue(op);
        }

        //! Gets a free connection in the synchronous connection pool.
        //! Caller MUST call t->Unlock() after touching the MySQL context to prevent deadlocks.
        T* GetFreeConnection();

        char const* GetDatabaseName() const;

        ACE_Message_Queue<ACE_SYNCH>*  _mqueue;
        //! Queue shared by async worker threads.
        ACE_Activation_Queue* _queue;             
        std::vector<std::vector<T*>> _connections;
        //! Counter of MySQL connections;
        uint32 _connectionCount[IDX_SIZE];
        std::unique_ptr<MySQLConnectionInfo> _connectionInfo;
        std::vector<uint8> _preparedStatementSize;
        uint8 _async_threads, _synch_threads;
};

#endif
