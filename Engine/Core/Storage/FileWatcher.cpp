/******************************************************************************************************************************
 * Copyright 2020 Gabriel Gheorghe. All rights reserved.
 * This code is licensed under the BSD 3-Clause "New" or "Revised" License
 * License url: https://github.com/GabyForceQ/PolluxEngine/blob/master/LICENSE
 *****************************************************************************************************************************/

#include "Engine/enginepch.hpp"

#include "FileWatcher.hpp"
#include "Engine/Core/Concurrency/WorkerThread.hpp"
#include "Engine/Core/Concurrency/ThisThread.hpp"

namespace Pollux::Core
{
    FileWatcher::FileWatcher(std::string pathToWatch, delay_t delay)
        :
        m_PathToWatch{ std::move(pathToWatch) },
        m_Delay{ std::move(delay) }
    {
    }

    FileWatcher::~FileWatcher()
    {
        SAFE_DELETE(m_pWorkerThread);
    }

    void FileWatcher::Start(const std::function<void(std::string_view, FileStatus)>& action, std::string_view threadName)
    {
        SAFE_DELETE(m_pWorkerThread);

        m_pWorkerThread = new WorkerThread([=]
        {
            if (threadName != "")
            {
                ThisThread::SetName(threadName);
            }

            while (m_bRunning)
            {
                std::this_thread::sleep_for(m_Delay);

                auto it = m_Paths.begin();
                
                while (it != m_Paths.end())
                {
                    if (!std::filesystem::exists(it->first))
                    {
                        action(it->first, FileStatus::Erased);
                        it = m_Paths.erase(it);
                    }
                    else
                    {
                        ++it;
                    }
                }

                for (auto& file : std::filesystem::recursive_directory_iterator(m_PathToWatch))
                {
                    auto fileLastWriteTime = std::filesystem::last_write_time(file);

                    if (!m_Paths.contains(file.path().string()))
                    {
                        m_Paths[file.path().string()] = fileLastWriteTime;
                        action(file.path().string(), FileStatus::Created);
                    }
                    else
                    {
                        if (m_Paths[file.path().string()] != fileLastWriteTime)
                        {
                            m_Paths[file.path().string()] = fileLastWriteTime;
                            action(file.path().string(), FileStatus::Modified);
                        }
                    }
                }
            }
        });
    }

    bool FileWatcher::Running() const noexcept
    {
        return m_bRunning;
    }
}