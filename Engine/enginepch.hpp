/*****************************************************************************************************************************
 * Copyright 2020 Gabriel Gheorghe. All rights reserved.
 * This code is licensed under the BSD 3-Clause "New" or "Revised" License
 * License url: https://github.com/GabyForceQ/PolluxEngine/blob/master/LICENSE
 *****************************************************************************************************************************/

#pragma once

#define NOMINMAX
#define STRICT
#define _USE_MATH_DEFINES

#pragma region CPP_STL_HEADERS
#include <atomic>
#include <iostream>
#include <string>
#include <unordered_map>
#include <deque>
#include <queue>
#include <sstream>
#include <algorithm>
#include <functional>
#include <chrono>
#include <iomanip>
#include <limits>
#include <cstdlib>
#include <clocale>
#include <cmath>
#include <cstring>
#include <type_traits>
#include <vector>
#include <map>
#include <cstddef>
#include <array>
#include <set>
#include <unordered_set>
#include <fstream>
#include <optional>
#include <thread>
#include <mutex>
#include <variant>
#include <utility>
#include <varargs.h>
#include <locale>
#include <filesystem>
#include <future>
#pragma endregion CPP_STL_HEADERS

#ifdef POLLUX_TARGET_DEBUG
void* operator new(size_t size);
void operator delete(void* p);
#endif

#define SAFE_DELETE(PTR) if (PTR != nullptr) { delete PTR; PTR = nullptr; }

#pragma region OS_HEADERS
#ifdef POLLUX_SYSTEM_WINDOWS
#define WINVER 0x0A00 // Windows 10 only
#define _WIN32_WINNT 0x0A00 // Windows 10 only
#pragma comment(lib, "xinput.lib")
#pragma comment(lib, "dinput8.lib")
#pragma comment(lib, "dxguid.lib")
#include <sdkddkver.h>
#include <Windows.h>
#include <windowsx.h>
#include <wrl/client.h>
#include <comdef.h>
#include <ShellScalingApi.h>
#define DIRECTINPUT_VERSION 0x0800
#include <dinput.h>
#include <Xinput.h>
#include <hidusage.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <WbemIdl.h>
#include <OleAuto.h>
#include <shellapi.h>
#undef IsMinimized
#endif
#pragma endregion OS_HEADERS

#ifdef POLLUX_DRIVER_VULKAN
#include "vulkan/vulkan.hpp"
#endif

namespace Pollux
{
    using byte_t = uint8_t;
    using type_t = uint16_t;
    using id_t = uint64_t;
    using resource_t = uint64_t;
    using tag_t = uint16_t;
    using pixel_t = uint32_t;
    using port_t = uint16_t;
    using address_t = uint32_t;

#ifdef POLLUX_SYSTEM_WINDOWS
    using soket_t = SOCKET;
#endif

    extern const char* g_pEmptyString;

#ifdef POLLUX_TARGET_UNITTEST
    struct UnitTestResult
    {
        bool succeeded = true;
        const char* message = g_pEmptyString;
    };

#define RUN_TEST(NAME) if (UnitTestResult res = NAME(); !res.succeeded) \
    { std::cout << res.message << "\n"; errors++; }
#endif
}

#ifdef POLLUX_PLATFORM_X64
size_t operator "" _sz(uint64_t x);
#endif

#ifdef ENGINE_HEADERS
#include "Core/CoreModule.hpp"
#endif