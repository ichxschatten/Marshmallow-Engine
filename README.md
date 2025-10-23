# Marshmallow-Engine v0.0.0.2 (Bare Win32 + DX9)

Полноэкранный Win32 без `<windows.h>` и без CRT. Две части: `App` (окно) и `Render` (CPU или Direct3D 9). Top-most, плавная отрисовка, выход по **Esc**.

## Сборка
```bash
clang -O3 -m64 -ffunction-sections -fdata-sections \
  -fno-stack-protector -fno-unwind-tables -fno-asynchronous-unwind-tables -fno-exceptions \
  -nostartfiles -Wl,-s -Wl,--gc-sections -Wl,-subsystem,windows -Wl,-e,WinMainCRTStartup \
  src/main.c -luser32 -lgdi32 -ld3d9 -o Marshmallow-Engine.exe
