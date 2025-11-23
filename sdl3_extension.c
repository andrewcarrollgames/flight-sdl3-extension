// Copyright (c) 2025 Andrew Carroll Games, LLC
// All rights reserved.

#include "extension.h"
#include "platform.h"
#include "platform_api.h"
#include "platform_timing.h"
#include "sdl3_extension_api.h"
#include <SDL3/SDL.h>
#include <stdio.h>

// Window Management

EXTENSION_API void SDL3_LogHello(void) {
  Platform_Log("Hello!\n");
}

EXTENSION_API void SDL3_LogWorld(void) {
  Platform_Log("XOXO\n--SDL3_Extension\n");
}

// After generating, make sure to set up the specific API here.
static SDL3API g_sdl3_api = {
  .LogHello = SDL3_LogHello,
  .LogWorld = SDL3_LogWorld,
  .CreateWindow = SDL3_CreateWindow,
  .DestroyWindow = SDL3_DestroyWindow
};

EXTENSION_API PlatformWindow* SDL3_CreateWindow(const char *title, int w, int h) {
  return NULL;
}

EXTENSION_API void SDL3_DestroyWindow(PlatformWindow* window) {

}

// --- The Extension Interface ---
bool SDL3_Init(EngineAPI* engine, PlatformAPI* platform) {
  Platform_Log("SDL3 Extension Initializing.\n");

  if (!SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_EVENTS)) {
    Platform_Log("Unable to initialize SDL: %s", SDL_GetError());
    return false;
  }

  PlatformAPI* platform_api = Platform_GetAPI();
  platform_api->Log = Platform_Log;
  platform_api->LogWarning = Platform_LogWarning;
  platform_api->LogError = Platform_LogError;
  platform_api->GetTimeNS = Platform_GetTimeNS;
  /*
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

  return true;
}

void SDL3_Shutdown(void) {
  Platform_Log("SDL3 Extension Shutdown.\n");
  SDL_Quit();
}

void* SDL3_GetSpecificAPI(void) {
  return &g_sdl3_api;
}

// Exported Symbol
ExtensionInterface g_extension_sdl3 = {
  .name = "SDL3",
  .Init = SDL3_Init,
  .Update = NULL,
  .Shutdown = SDL3_Shutdown,
  .GetSpecificAPI = SDL3_GetSpecificAPI
};
