// Copyright (c) 2025 Andrew Carroll Games, LLC
// All rights reserved.
#include <stdio.h>
#include "platform_timing.h"
#include "platform.h"

// Functions defined in the platform that we wish to provide SDL definitions for.
void Platform_Log(const char* fmt, ...){
  printf("This came from SDL's extension. (%s)", fmt);
}

uint64_t Platform_GetTimeNS() {
  Platform_Log("TIME TIME TIME.\n");
  return 0;
}
