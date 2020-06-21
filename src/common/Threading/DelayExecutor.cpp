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

#include <ace/Thread_Mutex.h>
#include <ace/Log_Msg.h>
#include "Threading.h"
#include "DelayExecutor.h"

DelayExecutor* DelayExecutor::instance()
{
    static DelayExecutor instance;
    return &instance;
}

DelayExecutor::DelayExecutor()
    : pre_svc_hook_(0), post_svc_hook_(0), activated_(false), mqueue_(1*1024*1024, 1*1024*1024), queue_(&mqueue_)
{
}

DelayExecutor::~DelayExecutor()
{
    if (pre_svc_hook_)
        delete pre_svc_hook_;

    if (post_svc_hook_)
        delete post_svc_hook_;

    deactivate();
}

int DelayExecutor::deactivate()
{
    if (!activated())
        return -1;

    activated(false);
    queue_.queue()->deactivate();
    wait();

    return 0;
}

int DelayExecutor::svc()
{
    if (pre_svc_hook_)
        pre_svc_hook_->call();

    for (;;)
    {
        ACE_Method_Request* rq = queue_.dequeue();

        if (!rq)
            break;

        rq->call();
        delete rq;
    }

    if (post_svc_hook_)
        post_svc_hook_->call();

    return 0;
}

int DelayExecutor::start(int num_threads, ACE_Method_Request* pre_svc_hook, ACE_Method_Request* post_svc_hook)
{
    if (activated())
        return -1;

    if (num_threads < 1)
        return -1;

    if (pre_svc_hook_)
        delete pre_svc_hook_;

    if (post_svc_hook_)
        delete post_svc_hook_;

    pre_svc_hook_ = pre_svc_hook;
    post_svc_hook_ = post_svc_hook;

    queue_.queue()->activate();

    // pussywizard:
    //warhead::ThreadPriority tp;
    //int _priority = tp.getPriority(warhead::Priority_Highest);
    //if (ACE_Task_Base::activate(THR_NEW_LWP | THR_JOINABLE, num_threads, 0, _priority) == -1)
    //    return -1;

    if (ACE_Task_Base::activate(THR_NEW_LWP | THR_JOINABLE | THR_INHERIT_SCHED, num_threads) == -1)
        return -1;

    activated(true);

    return true;
}

int DelayExecutor::execute(ACE_Method_Request* new_req)
{
    if (new_req == NULL)
        return -1;

    // pussywizard: NULL as param for enqueue - wait until the action is possible!
    // new tasks are added to the queue during map update (schedule_update in MapInstanced::Update)
    // the queue can be momentarily blocked by map threads constantly waiting for tasks (for (;;) { queue_.dequeue();... } in DelayExecutor::svc())
    // so just wait a moment, don't drop the task xDddd
    if (queue_.enqueue(new_req, /*(ACE_Time_Value*)&ACE_Time_Value::zero*/ NULL) == -1)
    {
        delete new_req;
        ACE_ERROR_RETURN((LM_ERROR, ACE_TEXT("(%t) %p\n"), ACE_TEXT("DelayExecutor::execute enqueue")), -1);
    }

    return 0;
}

bool DelayExecutor::activated()
{
    return activated_;
}

void DelayExecutor::activated(bool s)
{
    activated_ = s;
}
