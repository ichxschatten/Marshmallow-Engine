#ifndef ME_APP_LINUX_H
#define ME_APP_LINUX_H
typedef const void* LPCWSTR;
static void ME_App_Run(LPCWSTR c,LPCWSTR t,int m,unsigned int col){(void)c;(void)t;(void)m;(void)col;}
#define ME_Run(CLS,TTL,MODE,COL) int main(void){ME_App_Run((LPCWSTR)(CLS),(LPCWSTR)(TTL),(int)(MODE),(unsigned int)(COL));return 0;}
#endif