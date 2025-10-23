#ifndef ME_APP_H
#define ME_APP_H
#include "Render.h"
#if defined(_WIN32)
#include "app_win.h"
#elif defined(__linux__)
#include "app_linux.h"
#else
#include "app_macos.h"
#endif
#endif