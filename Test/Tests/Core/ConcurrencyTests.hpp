/*****************************************************************************************************************************
 * Copyright 2020 Gabriel Gheorghe. All rights reserved.
 * This code is licensed under the BSD 3-Clause "New" or "Revised" License
 * License url: https://github.com/GabyForceQ/PolluxEngine/blob/master/LICENSE
 *****************************************************************************************************************************/

#pragma once

namespace Pollux::Test
{
	/**************************************************************************************************************************
	 * \brief Check if a WorkerThread can be created or destroyed successfully
	 * \return Test Result
	 *************************************************************************************************************************/
	UnitTestResult CreateDestroyWorkerThread();

	/**************************************************************************************************************************
	 * \brief Check if a name can be set to a WorkerThread
	 * \return Test Result
	 *************************************************************************************************************************/
	UnitTestResult SetNameToWorkerThread();
}