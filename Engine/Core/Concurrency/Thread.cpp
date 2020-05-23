/*****************************************************************************************************************************
 * Copyright 2020 Gabriel Gheorghe. All rights reserved.
 * This code is licensed under the BSD 3-Clause "New" or "Revised" License
 * License url: https://github.com/GabyForceQ/PolluxEngine/blob/master/LICENSE
 *****************************************************************************************************************************/

#include "Engine/enginepch.hpp"

#include "Thread.hpp"

namespace Pollux::Core
{
    Thread::Thread()
        :
        m_Worker{ std::thread(&Thread::QueueLoop, this) }
    {
    }

    Thread::~Thread()
    {
        if (m_Worker.IsJoinable())
        {
            Wait();
            m_QueueMutex.lock();
            m_Destroying = true;
            m_Condition.notify_one();
            m_QueueMutex.unlock();
            m_Worker.Join();
        }
    }

    void Thread::AddJob(std::function<void()> JobCallback)
    {
        std::lock_guard lock{ m_QueueMutex };
        m_JobQueue.push(std::move(JobCallback));
        m_Condition.notify_one();
    }

    void Thread::Wait()
    {
        std::unique_lock lock{ m_QueueMutex };
        m_Condition.wait(lock, [this]() { return m_JobQueue.empty(); });
    }

    const WorkerThread& Thread::GetWorker() const noexcept
    {
        return m_Worker;
    }

    void Thread::QueueLoop()
    {
        while (true)
        {
            std::function<void()> JobCallback;
            {
                std::unique_lock lock{ m_QueueMutex };
                m_Condition.wait(lock, [this] { return !m_JobQueue.empty() || m_Destroying; });
                
                if (m_Destroying)
                {
                    break;
                }
                
                JobCallback = m_JobQueue.front();
            }

            JobCallback();

            {
                std::lock_guard lock{ m_QueueMutex };
                m_JobQueue.pop();
                m_Condition.notify_one();
            }
        }
    }
}