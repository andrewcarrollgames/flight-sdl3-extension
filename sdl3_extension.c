// Copyright (c) 2025 Andrew Carroll Games, LLC
// All rights reserved.

#include "extension.h"
#include "platform_api.h"
#include "platform_timing.h"
#include "sdl3_extension_api.h"
#include "sdl3_platform_overrides.h"
#include <stdio.h>

static PlatformAPI* g_platform = NULL;

EXTENSION_API void SDL3_LogHello(void) {
  if (g_platform) {
    Platform_Log("Hello!\n");
  }
}

EXTENSION_API void SDL3_LogWorld(void) {
  if (g_platform) {
    Platform_Log("XOXO\n--SDL3_Extension\n");
  }
}

// TODO: Implement PlatformAPI's missing calls and plug them in.

static SDL3API g_sdl3_api = {
  .LogHello = SDL3_LogHello,
  .LogWorld = SDL3_LogWorld
};

// --- The Extension Interface ---
bool SDL3_Init(EngineAPI* engine, PlatformAPI* platform) {
  g_platform = platform;
  Platform_Log("SDL3 Extension Initialized.\n");

  PlatformAPI* platform_api = Platform_GetAPI();
  platform_api->Log = Platform_Log;
  platform_api->GetTimeNS = Platform_GetTimeNS;
  /*
  .CreateWindow = Platform_CreateWindow,
  .DestroyWindow = Platform_DestroyWindow,
  .GetWindowSize = Platform_GetWindowSize,
  .SetWindowFullscreen = Platform_SetWindowFullscreen,
  .SetWindowBordered = Platform_SetWindowBordered,
  .SetWindowResizeable = Platform_SetWindowResizeable,
  .SetWindowSurfaceVSync = Platform_SetWindowSurfaceVSync,
  .GetWindowSurfaceVSync = Platform_GetWindowSurfaceVSync,

  .CreateRenderer = Platform_CreateRenderer,
  .DestroyRenderer = Platform_DestroyRenderer,
  .RendererClear = Platform_RendererClear,
  .RendererPresent = Platform_RendererPresent,
  .RendererSetVSync = Platform_RendererSetVSync,
  .RendererGetVSync = Platform_RendererGetVSync,
  .SetRenderLogicalPresentation = Platform_SetRenderLogicalPresentation,
  */

  // Call SDL_Init()
  // Assign our logging into PlatformAPI's functions here.
  // Maybe consider the same for timing...no, do it at the core.

  return true;
}

void SDL3_Update(float dt) {
}

void SDL3_Shutdown(void) {
  Platform_Log("SDL3 Extension Shutdown.\n");

  // Call SDL_Shutdown
}

void* SDL3_GetSpecificAPI(void) {
  return &g_sdl3_api;
}

// Exported Symbol
ExtensionInterface g_extension_sdl3 = {
  .name = "SDL3",
  .Init = SDL3_Init,
  .Update = SDL3_Update,
  .Shutdown = SDL3_Shutdown,
  .GetSpecificAPI = SDL3_GetSpecificAPI
};
