project(sdl3_extension LANGUAGES C)

# Include the real SDL
set(BUILD_SHARED_LIBS OFF)
set(SDL_TEST_LIBRARY OFF CACHE INTERNAL "")
set(SDL_SHARED OFF CACHE INTERNAL "")
add_subdirectory(extern/sdl3)

# Build test extension library
add_library(sdl3_extension STATIC
    sdl3_extension.c
    sdl3_platform_overrides.c
)

target_include_directories(sdl3_extension
    PUBLIC
    ${CMAKE_SOURCE_DIR}/shared/include
    PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/extern/sdl3/include
)

# Trying out a way to override generic functions in platform 
# The standard function implementation will be replaced by this extension
set_property(GLOBAL PROPERTY EXTENSION_OVERRIDE_LOG TRUE)
set_property(GLOBAL PROPERTY EXTENSION_OVERRIDE_TIMER TRUE)

target_link_libraries(sdl3_extension PRIVATE shared SDL3::SDL3-static)

# Depend on generated API header (created by parent CMakeLists.txt)
add_custom_target(sdl3_extension_api DEPENDS ${CMAKE_SOURCE_DIR}/shared/include/sdl3_extension_api.h
)
add_dependencies(sdl3_extension sdl3_extension_api)
