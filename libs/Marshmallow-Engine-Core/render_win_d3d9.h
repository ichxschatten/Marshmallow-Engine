#ifndef ME_RENDER_WIN_D3D9_H
#define ME_RENDER_WIN_D3D9_H
typedef unsigned int UINT;typedef unsigned long DWORD32;typedef long LONG;typedef void* HWND;typedef void* HDC;
typedef unsigned long DWORD;typedef unsigned short WORD;
__declspec(dllimport)HDC __stdcall GetDC(HWND);
__declspec(dllimport)int __stdcall ReleaseDC(HWND,HDC);
__declspec(dllimport)int __stdcall StretchDIBits(HDC,int,int,int,int,int,int,int,int,const void*,const void*,unsigned int,DWORD);
__declspec(dllimport)void* __stdcall VirtualAlloc(void*,unsigned long,unsigned long,unsigned long);
#define DIB_RGB_COLORS 0
#define SRCCOPY 0x00CC0020
typedef struct{DWORD biSize;LONG biWidth;LONG biHeight;WORD biPlanes;WORD biBitCount;DWORD biCompression;DWORD biSizeImage;LONG biXPelsPerMeter;LONG biYPelsPerMeter;DWORD biClrUsed;DWORD biClrImportant;}BITMAPINFOHEADER;
typedef struct{BITMAPINFOHEADER bmiHeader;}BITMAPINFO;
__declspec(dllimport)void* __stdcall Direct3DCreate9(unsigned int);
#define D3D_SDK_VERSION 32
#define D3DDEVTYPE_HAL 1
#define D3DSWAPEFFECT_DISCARD 1
#define D3DFMT_X8R8G8B8 22
#define D3DPRESENT_INTERVAL_IMMEDIATE 0x80000000u
#define D3DCLEAR_TARGET 1u
#define D3DCREATE_HARDWARE_VERTEXPROCESSING 0x40u
#define D3DCREATE_PUREDEVICE 0x10u
typedef struct IDirect3D9 IDirect3D9;typedef struct IDirect3DDevice9 IDirect3DDevice9;
typedef struct{UINT BackBufferWidth,BackBufferHeight,BackBufferFormat,BackBufferCount,MultiSampleType;DWORD32 MultiSampleQuality;UINT SwapEffect;HWND hDeviceWindow;int Windowed,EnableAutoDepthStencil;UINT AutoDepthStencilFormat;DWORD32 Flags;UINT FullScreen_RefreshRateInHz,PresentationInterval;}D3DPRESENT_PARAMETERS;
typedef struct{void*q0;void*q1;unsigned long(__stdcall*Release)(IDirect3D9*);void*q3;void*q4;void*q5;void*q6;void*q7;void*q8;void*q9;void*q10;void*q11;void*q12;void*q13;void*q14;void*q15;long(__stdcall*CreateDevice)(IDirect3D9*,UINT,UINT,HWND,DWORD32,D3DPRESENT_PARAMETERS*,IDirect3DDevice9**);}IDirect3D9Vtbl;struct IDirect3D9{IDirect3D9Vtbl*lpVtbl;};
typedef struct{void*r0;void*r1;unsigned long(__stdcall*Release)(IDirect3DDevice9*);void*r3;void*r4;void*r5;void*r6;void*r7;void*r8;void*r9;void*r10;void*r11;void*r12;void*r13;void*r14;void*r15;long(__stdcall*Reset)(IDirect3DDevice9*,D3DPRESENT_PARAMETERS*);long(__stdcall*Present)(IDirect3DDevice9*,void*,void*,HWND,void*);void*r18;void*r19;void*r20;void*r21;void*r22;void*r23;void*r24;void*r25;void*r26;void*r27;void*r28;void*r29;void*r30;void*r31;void*r32;void*r33;void*r34;void*r35;void*r36;void*r37;void*r38;void*r39;void*r40;long(__stdcall*BeginScene)(IDirect3DDevice9*);long(__stdcall*EndScene)(IDirect3DDevice9*);long(__stdcall*Clear)(IDirect3DDevice9*,DWORD32,void*,DWORD32,unsigned int,float,DWORD32);}IDirect3DDevice9Vtbl;struct IDirect3DDevice9{IDirect3DDevice9Vtbl*lpVtbl;};
typedef struct{HWND hwnd;HDC dc;void* px;int w,h;BITMAPINFO bi;}ME_SW_CTX;
typedef struct{IDirect3D9*d3d9;IDirect3DDevice9*dev9;}ME_D3D9_CTX;
static void _me_fill32(void* p,unsigned int v,unsigned long n){unsigned long i=n>>1;unsigned long long q=((unsigned long long)v<<32)|v;unsigned long long* d=(unsigned long long*)p;while(i--)*d++=q;if(n&1){unsigned int* t=(unsigned int*)d;*t=v;}}
static void* ME_Render_Init(HWND hwnd,int w,int h,unsigned int color,int mode){if(mode==0){ME_SW_CTX*c=(ME_SW_CTX*)VirtualAlloc(0,sizeof(ME_SW_CTX),0x3000,0x04);c->hwnd=hwnd;c->dc=GetDC(hwnd);c->w=w;c->h=h;c->bi.bmiHeader.biSize=40;c->bi.bmiHeader.biWidth=w;c->bi.bmiHeader.biHeight=-h;c->bi.bmiHeader.biPlanes=1;c->bi.bmiHeader.biBitCount=32;c->bi.bmiHeader.biCompression=0;c->bi.bmiHeader.biSizeImage=0;c->px=VirtualAlloc(0,(unsigned long)(w*h*4ull),0x3000,0x04);_me_fill32(c->px,(color&0x00FFFFFFu),(unsigned long)(w*h));return c;}else{IDirect3D9*d=(IDirect3D9*)Direct3DCreate9(D3D_SDK_VERSION);IDirect3DDevice9*dv;D3DPRESENT_PARAMETERS pp;pp.BackBufferWidth=w;pp.BackBufferHeight=h;pp.BackBufferFormat=D3DFMT_X8R8G8B8;pp.BackBufferCount=2;pp.MultiSampleType=0;pp.MultiSampleQuality=0;pp.SwapEffect=D3DSWAPEFFECT_DISCARD;pp.hDeviceWindow=hwnd;pp.Windowed=0;pp.EnableAutoDepthStencil=0;pp.AutoDepthStencilFormat=0;pp.Flags=0;pp.FullScreen_RefreshRateInHz=0;pp.PresentationInterval=D3DPRESENT_INTERVAL_IMMEDIATE;d->lpVtbl->CreateDevice(d,0,D3DDEVTYPE_HAL,hwnd,(DWORD32)(D3DCREATE_HARDWARE_VERTEXPROCESSING|D3DCREATE_PUREDEVICE),&pp,&dv);ME_D3D9_CTX*c=(ME_D3D9_CTX*)VirtualAlloc(0,sizeof(ME_D3D9_CTX),0x3000,0x04);c->d3d9=d;c->dev9=dv;return c;}}
static void ME_Render_Frame(void* ctx,unsigned int color,int mode){if(mode==0){ME_SW_CTX*c=(ME_SW_CTX*)ctx;StretchDIBits(c->dc,0,0,c->w,c->h,0,0,c->w,c->h,c->px,&c->bi,DIB_RGB_COLORS,SRCCOPY);}else{ME_D3D9_CTX*c=(ME_D3D9_CTX*)ctx;c->dev9->lpVtbl->Clear(c->dev9,0,0,D3DCLEAR_TARGET,color,1.0f,0);c->dev9->lpVtbl->Present(c->dev9,0,0,0,0);}}
static void ME_Render_Shutdown(void* ctx,int mode){if(mode==0){ME_SW_CTX*c=(ME_SW_CTX*)ctx;ReleaseDC(c->hwnd,c->dc);}else{ME_D3D9_CTX*c=(ME_D3D9_CTX*)ctx;c->dev9->lpVtbl->Release(c->dev9);c->d3d9->lpVtbl->Release(c->d3d9);}}
#endif