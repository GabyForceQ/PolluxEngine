/*****************************************************************************************************************************
 * Copyright 2020 Gabriel Gheorghe. All rights reserved.
 * This code is licensed under the BSD 3-Clause "New" or "Revised" License
 * License url: https://github.com/GabyForceQ/PolluxEngine/blob/master/LICENSE
 *****************************************************************************************************************************/

#pragma once

#include "FileStatus.hpp"

namespace Pollux::Core
{
    class WorkerThread;

    class FileWatcher
    {
    public:
        using delay_t = std::chrono::duration<int32_t, std::milli>;

        FileWatcher(std::string pathToWatch, delay_t delay);
        
        virtual ~FileWatcher();

        void Start(const std::function<void(std::string_view, FileStatus)>& action, std::string_view threadName = "");
        
        bool Running() const noexcept;

    private:
        WorkerThread* m_pWorkerThread = nullptr;
        std::unordered_map<std::string, std::filesystem::file_time_type> m_Paths;
        bool m_bRunning = true;
        std::string m_PathToWatch;
        delay_t m_Delay;
    };
}