/*****************************************************************************************************************************
 * Copyright 2020 Gabriel Gheorghe. All rights reserved.
 * This code is licensed under the BSD 3-Clause "New" or "Revised" License
 * License url: https://github.com/GabyForceQ/PolluxEngine/blob/master/LICENSE
 *****************************************************************************************************************************/

#pragma once

namespace Pollux::Core
{
    /*************************************************************************************************************************
     * \class Worker Thread
     *************************************************************************************************************************/
    class WorkerThread final
    {
    public:
        /**********************************************************************************************************************
         * \brief Default constructor
         *********************************************************************************************************************/
        WorkerThread() = default;
        
        /**********************************************************************************************************************
         * \brief Construct a Worker Thread using a known std::thread
         * \param thread known std::thread
         *********************************************************************************************************************/
        explicit WorkerThread(std::thread thread) noexcept;
        
        /**********************************************************************************************************************
         * \brief Move constructor
         * \param other Worker Thread
         *********************************************************************************************************************/
        WorkerThread(WorkerThread&& other) noexcept;
        
        /**********************************************************************************************************************
         * \brief Move assignment
         * \param other Worker Thread
         *********************************************************************************************************************/
        WorkerThread& operator=(WorkerThread&& other) noexcept;
        
        /**********************************************************************************************************************
         * \brief Assignment
         * \param other known std::thread
         *********************************************************************************************************************/
        WorkerThread& operator=(std::thread other) noexcept;
        
        /**********************************************************************************************************************
         * \brief Destructor
         *********************************************************************************************************************/
        ~WorkerThread() noexcept;

        /**********************************************************************************************************************
         * \brief Constructor
         * \param Callback callback for std::thread creation
         * \param args arguments for std::thread initialization
         *********************************************************************************************************************/
        template <typename CALLABLE, typename ...ARGS>
        explicit WorkerThread(CALLABLE&& Callback, ARGS&&... args)
            :
            m_Handle{ std::forward<CALLABLE>(Callback), std::forward<ARGS>(args)... }
        {
        }

        /**********************************************************************************************************************
         * \brief Swap a Worker Thread with another
         * \param other known Worker Thread
         *********************************************************************************************************************/
        void Swap(WorkerThread& other) noexcept;
        
        /**********************************************************************************************************************
         * \brief Join Worker Thread
         *********************************************************************************************************************/
        void Join();
        
        /**********************************************************************************************************************
         * \brief Detach Worker Thread
         *********************************************************************************************************************/
        void Detach();

        /**********************************************************************************************************************
         * \brief Set Worker Thread priority
         * \param priotity of the Worker Thread
         *********************************************************************************************************************/
        void SetPriority(const float& priority);

        /**********************************************************************************************************************
         * \return True if the Worker Thread is joinable
         *********************************************************************************************************************/
        bool IsJoinable() const noexcept;

        /**********************************************************************************************************************
         * \return Worker Thread unique identifier
         *********************************************************************************************************************/
        std::thread::id GetID() const noexcept;
        
        /**********************************************************************************************************************
         * \return Handle to std::thread
         *********************************************************************************************************************/
        std::thread& GetHandle() noexcept;

        /**********************************************************************************************************************
         * \return Constant handle to std::thread
         *********************************************************************************************************************/
        const std::thread& GetHandle() const noexcept;
        
        /**********************************************************************************************************************
         * \return Handle to std::thread native handle
         *********************************************************************************************************************/
        std::thread::native_handle_type GetNativeHandle() noexcept;

    private:
        std::thread m_Handle;
    };
}