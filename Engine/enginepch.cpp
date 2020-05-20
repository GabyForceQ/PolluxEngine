/*****************************************************************************************************************************
 * Copyright 2020 Gabriel Gheorghe. All rights reserved.
 * This code is licensed under the BSD 3-Clause "New" or "Revised" License
 * License url: https://github.com/GabyForceQ/PolluxEngine/blob/master/LICENSE
 *****************************************************************************************************************************/

#include "Engine/enginepch.hpp"

#ifdef POLLUX_TARGET_DEBUG

void* operator new(size_t size)
{
    return malloc(size);
}

void operator delete(void* p)
{
    free(p);
}

#endif

namespace Pollux
{
    const char* g_pEmptyString = "";
}