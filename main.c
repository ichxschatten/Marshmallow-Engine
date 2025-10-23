typedef unsigned long       DWORD;
typedef unsigned int        UINT;
typedef long long           LRESULT;
typedef void*               HINSTANCE;
typedef void*               HICON;
typedef void*               HCURSOR;
typedef void*               HBRUSH;
typedef void*               HWND;
typedef const unsigned short* LPCWSTR;
typedef unsigned long long  WPARAM;
typedef long long           LPARAM;

typedef struct {
    UINT   cbSize;
    UINT   style;
    LRESULT (__stdcall *lpfnWndProc)(HWND, UINT, WPARAM, LPARAM);
    int    cbClsExtra;
    int    cbWndExtra;
    HINSTANCE hInstance;
    HICON  hIcon;
    HCURSOR hCursor;
    HBRUSH hbrBackground;
    LPCWSTR lpszMenuName;
    LPCWSTR lpszClassName;
    HICON  hIconSm;
} WNDCLASSEXW;

typedef struct {
    HWND   hwnd;
    UINT   message;
    WPARAM wParam;
    LPARAM lParam;
    unsigned long time;
    struct { long x, y; } pt;
    unsigned long lPrivate;
} MSG;

#define CS_HREDRAW            0x0002
#define CS_VREDRAW            0x0001
#define WS_POPUP              0x80000000U
#define WS_VISIBLE            0x10000000U
#define SW_SHOW               5
#define SM_CXSCREEN           0
#define SM_CYSCREEN           1
#define PM_REMOVE             0x0001
#define WM_KEYDOWN            0x0100
#define WM_SYSKEYDOWN         0x0104
#define WM_SYSCOMMAND         0x0112
#define WM_CLOSE              0x0010
#define WM_DESTROY            0x0002
#define VK_ESCAPE             0x1B
#define SC_CLOSE              0xF060
#define HWND_TOPMOST          ((HWND)(-1))
#define SWP_NOSIZE            0x0001
#define SWP_NOMOVE            0x0002
#define SWP_NOACTIVATE        0x0010
#define SWP_SHOWWINDOW        0x0040
#define SWP_FRAMECHANGED      0x0020

__declspec(dllimport) HINSTANCE __stdcall GetModuleHandleW(LPCWSTR);
__declspec(dllimport) int       __stdcall RegisterClassExW(const WNDCLASSEXW*);
__declspec(dllimport) HWND      __stdcall CreateWindowExW(DWORD, LPCWSTR, LPCWSTR, DWORD, int, int, int, int, HWND, void*, HINSTANCE, void*);
__declspec(dllimport) int       __stdcall ShowWindow(HWND, int);
__declspec(dllimport) int       __stdcall UpdateWindow(HWND);
__declspec(dllimport) int       __stdcall GetSystemMetrics(int);
__declspec(dllimport) int       __stdcall PeekMessageW(MSG*, HWND, UINT, UINT, UINT);
__declspec(dllimport) int       __stdcall TranslateMessage(const MSG*);
__declspec(dllimport) LRESULT   __stdcall DispatchMessageW(const MSG*);
__declspec(dllimport) LRESULT   __stdcall DefWindowProcW(HWND, UINT, WPARAM, LPARAM);
__declspec(dllimport) void      __stdcall PostQuitMessage(int);
__declspec(dllimport) int       __stdcall SetProcessDPIAware(void);
__declspec(dllimport) int       __stdcall SetWindowPos(HWND, HWND, int, int, int, int, UINT);

static const unsigned short CN[] = {
    'M','a','r','s','h','m','a','l','l','o','w','-','E','n','g','i','n','e','-','v','0','.','0','.','0','.','0',0
};

static LRESULT __stdcall WndProc(HWND h, UINT m, WPARAM w, LPARAM l) {
    if ((m == WM_KEYDOWN || m == WM_SYSKEYDOWN) && (UINT)w == VK_ESCAPE) { PostQuitMessage(0); return 0; }
    if (m == WM_SYSCOMMAND && ((w & 0xFFF0) == SC_CLOSE)) return 0;
    if (m == WM_CLOSE) return 0;
    if (m == WM_DESTROY) { PostQuitMessage(0); return 0; }
    return DefWindowProcW(h, m, w, l);
}

void __stdcall WinMainCRTStartup(void) {
    SetProcessDPIAware();
    HINSTANCE inst = GetModuleHandleW(0);
    WNDCLASSEXW wc;
    wc.cbSize=sizeof(wc);
    wc.style=CS_HREDRAW|CS_VREDRAW;
    wc.lpfnWndProc=WndProc;
    wc.cbClsExtra=0;
    wc.cbWndExtra=0;
    wc.hInstance=inst;
    wc.hIcon=(HICON)0;
    wc.hCursor=(HCURSOR)0;
    wc.hbrBackground=(HBRUSH)0;
    wc.lpszMenuName=(LPCWSTR)0;
    wc.lpszClassName=CN;
    wc.hIconSm=(HICON)0;
    RegisterClassExW(&wc);
    int W=GetSystemMetrics(SM_CXSCREEN);
    int H=GetSystemMetrics(SM_CYSCREEN);
    HWND win=CreateWindowExW(0, CN, CN, WS_POPUP|WS_VISIBLE, 0,0,W,H, (HWND)0,0,inst,0);
    SetWindowPos(win, HWND_TOPMOST, 0,0,0,0, SWP_NOMOVE|SWP_NOSIZE|SWP_NOACTIVATE|SWP_SHOWWINDOW|SWP_FRAMECHANGED);
    ShowWindow(win, SW_SHOW);
    UpdateWindow(win);
    MSG msg;
    for (;;) {
        while (PeekMessageW(&msg, (HWND)0, 0,0, PM_REMOVE)) {
            if ((int)msg.message==0x0012) goto exit;
            TranslateMessage(&msg);
            DispatchMessageW(&msg);
        }
    }
exit:
    return;
}
