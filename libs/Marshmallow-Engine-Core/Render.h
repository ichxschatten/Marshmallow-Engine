#ifndef ME_RENDER_H
#define ME_RENDER_H
#if defined(_WIN32)
#include "render_win_d3d9.h"
#elif defined(__linux__)
#include "render_linux.h"
#else
#include "render_macos.h"
#endif
#endif