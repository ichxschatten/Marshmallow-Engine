# Marshmallow-Engine v0.0.0.0 (Bare Win32)

Полноэкранное приложение без `<windows.h>` и без CRT. Обрабатывает только самое важное: полноэкранный режим сверху всех окон и закрытие по **Esc**.

## Сборка
```bash
clang -O3 -m64 -nostartfiles -fno-asynchronous-unwind-tables -fno-exceptions \
  -Wl,-s -Wl,-subsystem,windows \
  main.c -luser32 -o MarshmallowEngine.exe
