/*****************************************************************************************************************************
 * Copyright 2020 Gabriel Gheorghe. All rights reserved.
 * This code is licensed under the BSD 3-Clause "New" or "Revised" License
 * License url: https://github.com/GabyForceQ/PolluxEngine/blob/master/LICENSE
 *****************************************************************************************************************************/

#include "Test/testpch.hpp"

#include "ConcurrencyTests.hpp"
#include "Engine/Core/Concurrency/ConcurrencyModule.hpp"

using namespace Pollux::Core;

namespace Pollux::Test
{
	UnitTestResult CreateDestroyWorkerThread()
	{
		UnitTestResult res;
		static const char* pErrorMessageCreate = "WorkerThread creation FAILED";
		static const char* pErrorMessageDestroy = "WorkerThread destruction FAILED";

		WorkerThread* pWorkerThread0 = nullptr;
		WorkerThread* pWorkerThread1 = nullptr;
		//WorkerThread* pWorkerThread2 = nullptr;
		WorkerThread* pWorkerThread3 = nullptr;

		try
		{
			pWorkerThread0 = new WorkerThread();
			pWorkerThread1 = new WorkerThread(std::thread());
			//pWorkerThread2 = new WorkerThread(pWorkerThread1); move ctor
			pWorkerThread3 = new WorkerThread([](int, float) {}, 1, 2.f);
		}
		catch (...)
		{
			res.succeeded = false;
			res.message = pErrorMessageCreate;
		}

		try
		{
			SAFE_DELETE(pWorkerThread0);
			SAFE_DELETE(pWorkerThread1);
			//SAFE_DELETE(pWorkerThread2);
			SAFE_DELETE(pWorkerThread3);
		}
		catch (...)
		{
			res.succeeded = false;
			res.message = pErrorMessageDestroy;
		}

		return std::move(res);
	}

	UnitTestResult SetNameToWorkerThread()
	{
		UnitTestResult res;
		static const char* pErrorMessageCreateDestroy = "WorkerThread creation/destruction FAILED";
		static const char* pErrorMessage = "WorkerThread set name FAILED";
		static const char* threadName = "AIThread";

		try
		{
			WorkerThread* pWorkerThread = new WorkerThread(
				[&]()
				{
					try
					{
						ThisThread::SetName(threadName);
					}
					catch (...)
					{
						res.succeeded = false;
						res.message = pErrorMessage;
					}
				}
			);

			SAFE_DELETE(pWorkerThread);
		}
		catch (...)
		{
			res.succeeded = false;
			res.message = pErrorMessageCreateDestroy;
		}

		return std::move(res);
	}
}