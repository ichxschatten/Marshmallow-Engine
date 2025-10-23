# Marshmallow-Engine v0.0.0.1 (Bare Win32)

Полноэкранное приложение без `<windows.h>` и без CRT. Только полноэкранный режим поверх всех окон и выход по Esc.

## Сборка
```bash
clang -O3 -m64 -ffunction-sections -fdata-sections \
  -fno-stack-protector -fno-unwind-tables -fno-asynchronous-unwind-tables -fno-exceptions \
  -nostartfiles -Wl,-s -Wl,--gc-sections -Wl,-subsystem,windows -Wl,-e,WinMainCRTStartup \
  src/main.c -luser32 -o Marshmallow-Engine.exe
