#ifndef ME_APP_WIN_H
#define ME_APP_WIN_H
typedef unsigned long DWORD;typedef unsigned int UINT;typedef long long LRESULT;typedef void* HINSTANCE;typedef void* HICON;typedef void* HCURSOR;typedef void* HBRUSH;typedef void* HWND;typedef const unsigned short* LPCWSTR;typedef unsigned long long WPARAM;typedef long long LPARAM;
typedef struct{UINT cbSize,style;LRESULT(__stdcall*lpfnWndProc)(HWND,UINT,WPARAM,LPARAM);int cbClsExtra,cbWndExtra;HINSTANCE hInstance;HICON hIcon;HCURSOR hCursor;HBRUSH hbrBackground;LPCWSTR lpszMenuName,lpszClassName;HICON hIconSm;}WNDCLASSEXW;
typedef struct{long x,y;}ME_PT;typedef struct{HWND hwnd;UINT message;WPARAM wParam;LPARAM lParam;unsigned long time;ME_PT pt;unsigned long lPrivate;}MSG;
#define CS_HREDRAW 0x0002
#define CS_VREDRAW 0x0001
#define WS_POPUP 0x80000000U
#define WS_VISIBLE 0x10000000U
#define SW_SHOW 5
#define SM_CXSCREEN 0
#define SM_CYSCREEN 1
#define PM_REMOVE 0x0001
#define WM_KEYDOWN 0x0100
#define WM_SYSKEYDOWN 0x0104
#define WM_SYSCOMMAND 0x0112
#define WM_CLOSE 0x0010
#define WM_DESTROY 0x0002
#define VK_ESCAPE 0x1B
#define SC_CLOSE 0xF060
#define HWND_TOPMOST ((HWND)(-1))
#define SWP_NOSIZE 0x0001
#define SWP_NOMOVE 0x0002
#define SWP_NOACTIVATE 0x0010
#define SWP_SHOWWINDOW 0x0040
#define SWP_FRAMECHANGED 0x0020
__declspec(dllimport)HINSTANCE __stdcall GetModuleHandleW(LPCWSTR);
__declspec(dllimport)int __stdcall RegisterClassExW(const WNDCLASSEXW*);
__declspec(dllimport)HWND __stdcall CreateWindowExW(DWORD,LPCWSTR,LPCWSTR,DWORD,int,int,int,int,HWND,void*,HINSTANCE,void*);
__declspec(dllimport)int __stdcall ShowWindow(HWND,int);
__declspec(dllimport)int __stdcall UpdateWindow(HWND);
__declspec(dllimport)int __stdcall GetSystemMetrics(int);
__declspec(dllimport)int __stdcall PeekMessageW(MSG*,HWND,UINT,UINT,UINT);
__declspec(dllimport)int __stdcall TranslateMessage(const MSG*);
__declspec(dllimport)LRESULT __stdcall DispatchMessageW(const MSG*);
__declspec(dllimport)LRESULT __stdcall DefWindowProcW(HWND,UINT,WPARAM,LPARAM);
__declspec(dllimport)void __stdcall PostQuitMessage(int);
__declspec(dllimport)int __stdcall SetProcessDPIAware(void);
__declspec(dllimport)int __stdcall SetWindowPos(HWND,HWND,int,int,int,int,UINT);
static int _me_mode;static unsigned int _me_color;static void*_me_rctx;static int _me_w,_me_h;static HWND _me_hwnd;
static LRESULT __stdcall _ME_WndProc(HWND h,UINT m,WPARAM w,LPARAM l){if((m==WM_KEYDOWN||m==WM_SYSKEYDOWN)&&(UINT)w==VK_ESCAPE){PostQuitMessage(0);return 0;}if(m==WM_SYSCOMMAND&&((w&0xFFF0)==SC_CLOSE))return 0;if(m==WM_CLOSE)return 0;if(m==WM_DESTROY){PostQuitMessage(0);return 0;}return DefWindowProcW(h,m,w,l);}
static void ME_App_Run(LPCWSTR cls,LPCWSTR ttl,int mode,unsigned int color){_me_mode=mode;_me_color=color;SetProcessDPIAware();HINSTANCE i=GetModuleHandleW(0);WNDCLASSEXW w;w.cbSize=sizeof(w);w.style=CS_HREDRAW|CS_VREDRAW;w.lpfnWndProc=_ME_WndProc;w.cbClsExtra=0;w.cbWndExtra=0;w.hInstance=i;w.hIcon=(HICON)0;w.hCursor=(HCURSOR)0;w.hbrBackground=(HBRUSH)0;w.lpszMenuName=(LPCWSTR)0;w.lpszClassName=cls;w.hIconSm=(HICON)0;RegisterClassExW(&w);_me_w=GetSystemMetrics(SM_CXSCREEN);_me_h=GetSystemMetrics(SM_CYSCREEN);_me_hwnd=CreateWindowExW(0,cls,ttl,WS_POPUP|WS_VISIBLE,0,0,_me_w,_me_h,(HWND)0,0,i,0);SetWindowPos(_me_hwnd,HWND_TOPMOST,0,0,0,0,SWP_NOMOVE|SWP_NOSIZE|SWP_NOACTIVATE|SWP_SHOWWINDOW|SWP_FRAMECHANGED);ShowWindow(_me_hwnd,SW_SHOW);UpdateWindow(_me_hwnd);_me_rctx=ME_Render_Init(_me_hwnd,_me_w,_me_h,_me_color,_me_mode);MSG m;for(;;){while(PeekMessageW(&m,(HWND)0,0,0,PM_REMOVE)){if((int)m.message==0x0012)goto q;TranslateMessage(&m);DispatchMessageW(&m);}ME_Render_Frame(_me_rctx,_me_color,_me_mode);}q:ME_Render_Shutdown(_me_rctx,_me_mode);}
#define ME_Run(CLS,TTL,MODE,COL) void __stdcall WinMainCRTStartup(void){ME_App_Run((LPCWSTR)(CLS),(LPCWSTR)(TTL),(int)(MODE),(unsigned int)(COL));}
#endif