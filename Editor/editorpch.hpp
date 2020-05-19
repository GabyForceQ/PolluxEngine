/**
 * Copyright 2020 Gabriel Gheorghe. All rights reserved.
 * This code is licensed under the BSD 3-Clause "New" or "Revised" License
 * License url: https://github.com/GabyForceQ/PolluxEngine/blob/master/LICENSE
 */

#pragma once

#define ENGINE_HEADERS
#include "Engine/enginepch.hpp"

using namespace Pollux;

#define META_OBJECT()

#define PROJECT_NAME "Editor"

#if POLLUX_TARGET_DEBUG
#define BUILD_TARGET "Debug"
#elif POLLUX_TARGET_RELEASE
#define BUILD_TARGET "Release"
#elif POLLUX_TARGET_RETAIL
#define BUILD_TARGET "Retail"
#endif