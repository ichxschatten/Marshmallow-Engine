#ifndef ME_H
#define ME_H
#include "App.h"
#define ME_COLOR(R,G,B) (0xFF000000u|(((unsigned)(R))&255u)<<16|(((unsigned)(G))&255u)<<8|(((unsigned)(B))&255u))
#define ME_RUN_SW(CLS,TTL,COL) ME_Run((CLS),(TTL),0,(COL))
#define ME_RUN_D3D9(CLS,TTL,COL) ME_Run((CLS),(TTL),1,(COL))
#endif