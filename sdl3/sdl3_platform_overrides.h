// Copyright (c) 2025 Andrew Carroll Games, LLC
// All rights reserved.

#ifndef SDL3_PLATFORM_OVERRIDES_H
#define SDL3_PLATFORM_OVERRIDES_H

#ifdef __cplusplus
extern "C" {
#endif

// Functions defined in the platform that we wish to provide SDL definitions for.
void Platform_Log(const char* fmt, ...);

#ifdef __cplusplus
}
#endif

#endif
