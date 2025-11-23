// Copyright (c) 2025 Andrew Carroll Games, LLC
// All rights reserved.
#include <stdio.h>
#include "platform_timing.h"
#include "platform.h"
#include <SDL3/SDL.h>

// Functions defined in the platform that we wish to provide SDL definitions for.
void Platform_Log(const char* fmt, ...){
  va_list args;
  va_start(args, fmt);
  SDL_LogMessageV(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_INFO, fmt, args);
  va_end(args);
}

void Platform_LogWarning(const char* fmt, ...){
  va_list args;
  va_start(args, fmt);
  SDL_LogMessageV(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_WARN, fmt, args);
  va_end(args);
}

void Platform_LogError(const char* fmt, ...){
  va_list args;
  va_start(args, fmt);
  SDL_LogMessageV(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_ERROR, fmt, args);
  va_end(args);
}

uint64_t Platform_GetTimeNS() {
  return SDL_GetTicksNS();
}

/*
const char *Platform_GetBasePath(void) {
  return SDL_GetBasePath();
}

const char *Platform_GetPrefPath(const char *org, const char *app) {
  return SDL_GetPrefPath(org, app);
}
*/