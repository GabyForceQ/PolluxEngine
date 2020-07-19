/*****************************************************************************************************************************
 * Copyright 2020 Gabriel Gheorghe. All rights reserved.
 * This code is licensed under the BSD 3-Clause "New" or "Revised" License
 * License url: https://github.com/GabyForceQ/PolluxEngine/blob/master/LICENSE
 *****************************************************************************************************************************/

#pragma once

namespace Pollux::Core
{
    /*************************************************************************************************************************
     * \class This Thread
     *
     * Contains static methods to handle the current thread
     *************************************************************************************************************************/
    class ThisThread final
    {
    public:
        /**********************************************************************************************************************
         * \brief Set Worker Thread name
         * \param name of the Worker Thread
         *********************************************************************************************************************/
        static void SetName(const char* name);

        /**********************************************************************************************************************
         * \brief Set Worker Thread name
         * \param name of the Worker Thread
         *********************************************************************************************************************/
        static void SetName(std::string_view name);

        /**********************************************************************************************************************
         * \brief Sleep Worker Thread for N millisconds
         * \param milliseconds Worker Thread should sleep for
         *********************************************************************************************************************/
        static void SleepForMilliseconds(const uint32_t& milliseconds);

        /**********************************************************************************************************************
         * \brief Sleep Worker Thread for N seconds
         * \param seconds Worker Thread should sleep for
         *********************************************************************************************************************/
        static void SleepForSeconds(const uint32_t& seconds);
    };
}