#ifndef ME_RENDER_MACOS_H
#define ME_RENDER_MACOS_H
typedef void* HWND;
static void* ME_Render_Init(HWND h,int w,int hh,unsigned int c,int m){(void)h;(void)w;(void)hh;(void)c;(void)m;return 0;}
static void ME_Render_Frame(void* ctx,unsigned int c,int m){(void)ctx;(void)c;(void)m;}
static void ME_Render_Shutdown(void* ctx,int m){(void)ctx;(void)m;}
#endif