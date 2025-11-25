// Copyright (c) 2025 Andrew Carroll Games, LLC
// All rights reserved.

#include "extension.h"
#include "platform.h"
#include "engine.h"
#include "platform_api.h"
#include "platform_api_types.h"
#include "platform_timing.h"
#include "sdl3_extension_api.h"
#include <SDL3/SDL.h>
#include <stdio.h>

// Window Management
typedef struct PlatformWindow {
  SDL_Window *sdl_window;
} PlatformWindow;

typedef struct PlatformRenderer {
  SDL_Renderer *sdl_renderer;
} PlatformRenderer;

// After generating, make sure to set up the specific API here.
static SDL3API g_sdl3_api = {
  .CreateWindow = SDL3_CreateWindow,
  .DestroyWindow = SDL3_DestroyWindow,
  .GetWindowSize = SDL3_GetWindowSize,
  .SetWindowFullscreen = SDL3_SetWindowFullscreen,
  .SetWindowBordered = SDL3_SetWindowBordered,
  .SetWindowResizeable = SDL3_SetWindowResizeable,
  .SetWindowSurfaceVSync = SDL3_SetWindowSurfaceVSync,
  .GetWindowSurfaceVSync = SDL3_GetWindowSurfaceVSync,
  .CreateRenderer = SDL3_CreateRenderer,
  .DestroyRenderer = SDL3_DestroyRenderer,
  .SetRendererLogicalPresentation = SDL3_SetRendererLogicalPresentation,
  .SetRendererHint = SDL3_SetRendererHint,
  .RendererClear = SDL3_RendererClear,
  .RendererPresent = SDL3_RendererPresent,
  .RendererGetVSync = SDL3_RendererGetVSync,
  .RendererSetVSync = SDL3_RendererSetVSync,
  .GetBasePath = SDL3_GetBasePath,
  .GetPrefPath = SDL3_GetPrefPath
};

#pragma region SDL3_Window
EXTENSION_API PlatformWindow* SDL3_CreateWindow(const char* title, const int32_t width, const int32_t height, const PlatformRendererType rendererType) {
  PlatformWindow *window = SDL_calloc(1, sizeof(PlatformWindow));
  SDL_WindowFlags windowFlags = 0;
  switch (rendererType) {
    case PLATFORM_RENDERER_VULKAN:
      windowFlags = SDL_WINDOW_VULKAN;
      break;
    case PLATFORM_RENDERER_METAL:
      windowFlags = SDL_WINDOW_METAL;
      break;
    case PLATFORM_RENDERER_OPENGL:
    default:
      windowFlags = SDL_WINDOW_OPENGL;
      break;
  }

  window->sdl_window = SDL_CreateWindow(title, width, height, windowFlags);
  if (!window->sdl_window) {
    SDL_free(window);
    return NULL;
  }

  return window;
}

EXTENSION_API void SDL3_DestroyWindow(const PlatformWindow* window) {
  if (window && window->sdl_window) {
    SDL_DestroyWindow(window->sdl_window);
  }
}

EXTENSION_API bool SDL3_GetWindowSize(const PlatformWindow* window, int32_t *width, int32_t *height) {
  const SDL_Surface *windowSurface = SDL_GetWindowSurface(window->sdl_window);
  if (windowSurface) {
    *width = windowSurface->w;
    *height = windowSurface->h;
    return true;
  }
  return false;
}

EXTENSION_API void SDL3_SetWindowFullscreen(const PlatformWindow* window, const bool fullscreen) {
  SDL_SetWindowFullscreen(window->sdl_window, fullscreen);
}

EXTENSION_API void SDL3_SetWindowBordered(const PlatformWindow* window, const bool bordered) {
  SDL_SetWindowBordered(window->sdl_window, bordered);
}

EXTENSION_API void SDL3_SetWindowResizeable(const PlatformWindow* window, const bool resizeable) {
  SDL_SetWindowResizable(window->sdl_window, resizeable);
}

EXTENSION_API void SDL3_SetWindowSurfaceVSync(const PlatformWindow* window, const int32_t vsync) {
  SDL_SetWindowSurfaceVSync(window->sdl_window, 0);
}

EXTENSION_API bool SDL3_GetWindowSurfaceVSync(const PlatformWindow* window, int32_t *vsync) {
  return SDL_GetWindowSurfaceVSync(window->sdl_window, vsync);
}
#pragma endregion SDL3_Window
#pragma region SDL3_Renderer
EXTENSION_API PlatformRenderer* SDL3_CreateRenderer(const PlatformWindow* window, const char* name) {
  PlatformRenderer *renderer = SDL_calloc(1, sizeof(PlatformRenderer));

  SDL_Window *sdl_window = window->sdl_window;

  renderer->sdl_renderer = SDL_CreateRenderer(sdl_window, name);
  if (!renderer->sdl_renderer) {
    SDL_free(renderer);
    return NULL;
  }

  return renderer;
}

EXTENSION_API void SDL3_DestroyRenderer(PlatformRenderer* renderer) {
  if (renderer) {
    if (renderer->sdl_renderer) {
      SDL_DestroyRenderer(renderer->sdl_renderer);
    }
    SDL_free(renderer);
  }
}

EXTENSION_API void SDL3_RendererClear(const PlatformRenderer* renderer) {
  SDL_RenderClear(renderer->sdl_renderer);
}

EXTENSION_API void SDL3_RendererPresent(const PlatformRenderer* renderer) {
  SDL_RenderPresent(renderer->sdl_renderer);
}

EXTENSION_API void SDL3_RendererSetVSync(const PlatformRenderer *renderer, int32_t vsync) {
  SDL_SetRenderVSync(renderer->sdl_renderer, vsync);
}

EXTENSION_API bool SDL3_RendererGetVSync(const PlatformRenderer* renderer, int32_t *vsync) {
  return SDL_GetRenderVSync(renderer->sdl_renderer, vsync);
}

EXTENSION_API void SDL3_SetRendererLogicalPresentation(const PlatformRenderer* renderer, const int32_t w, const int32_t h) {
  SDL_SetRenderLogicalPresentation(renderer->sdl_renderer, w, h, SDL_LOGICAL_PRESENTATION_INTEGER_SCALE);
}

EXTENSION_API void SDL3_SetRendererHint(const char* hint) {
  SDL_SetHint(SDL_HINT_RENDER_DRIVER, hint);
}
#pragma endregion SDL3_Renderer
#pragma region SDL3_FilePath
EXTENSION_API const char* SDL3_GetBasePath(void) {
  return SDL_GetBasePath();
}

EXTENSION_API const char* SDL3_GetPrefPath(const char *org, const char *app) {
  return SDL_GetPrefPath(org, app);
}
#pragma endregion SDL3_FilePath

// --- The Extension Interface ---
bool SDL3_Init(EngineAPI* engine, PlatformAPI* platform) {
  Platform_Log("SDL3 Extension Initializing.\n");

  if (!SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_EVENTS)) {
    Platform_Log("Unable to initialize SDL: %s", SDL_GetError());
    return false;
  }

  // TODO: (ARC) Initialize SDL to use arena allocators.
  PlatformAPI* platform_api = Platform_GetAPI();
  platform_api->Log = Platform_Log;
  platform_api->LogWarning = Platform_LogWarning;
  platform_api->LogError = Platform_LogError;
  platform_api->GetTimeNS = Platform_GetTimeNS;

  return true;
}

void SDL3_Update(double deltaTime) {
  // TODO: (ARC) Choose what do with these events (translate and buffer them?)
  SDL_Event event;
  while (SDL_PollEvent(&event)) {
    switch (event.type) {
      case SDL_EVENT_KEY_DOWN: {
        if (event.key.key == SDLK_ESCAPE) {
          Platform_Log("Escape key pressed. Quitting.\n");
          Engine_Quit();
        }
        break;
      }
      case SDL_EVENT_WINDOW_CLOSE_REQUESTED:
      case SDL_EVENT_QUIT: {
        Platform_Log("Quit/Close requested.\n");
        Engine_Quit();
        break;
      }
      default: {
        break;
      }
    }
  }
}

void SDL3_Shutdown(void) {
  // TODO: (ARC) Release arena memory/Destroy Arenas here
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
  .Update = SDL3_Update,
  .Shutdown = SDL3_Shutdown,
  .GetSpecificAPI = SDL3_GetSpecificAPI
};
