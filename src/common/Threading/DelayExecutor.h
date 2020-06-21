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

#ifndef _M_DELAY_EXECUTOR_H
#define _M_DELAY_EXECUTOR_H

#include "Define.h"
#include <ace/Task.h>
#include <ace/Activation_Queue.h>
#include <ace/Method_Request.h>

class WH_COMMON_API DelayExecutor : protected ACE_Task_Base
{
    public:

        DelayExecutor();
        virtual ~DelayExecutor();

        static DelayExecutor* instance();

        int execute(ACE_Method_Request* new_req);

        int start(int num_threads = 1, ACE_Method_Request* pre_svc_hook = NULL, ACE_Method_Request* post_svc_hook = NULL);

        int deactivate();

        bool activated();

        virtual int svc();

    private:

        ACE_Method_Request* pre_svc_hook_;
        ACE_Method_Request* post_svc_hook_;
        bool activated_;
        ACE_Message_Queue<ACE_SYNCH> mqueue_;
        ACE_Activation_Queue queue_;


        void activated(bool s);
};

#endif // _M_DELAY_EXECUTOR_H
