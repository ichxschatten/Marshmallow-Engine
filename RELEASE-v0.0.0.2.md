
---

# RELEASE-v0.0.0.2.md
# Marshmallow-Engine v0.0.0.2

## Новое
- Разделение на `App` (окно) и `Render` (CPU/D3D9).
- DX9 модуль: `render_win_d3d9.h` (fullscreen, immediate present).
- CPU модуль: буфер + `StretchDIBits` без мерцаний.
- Макросы запуска: `ME_RUN_SW`, `ME_RUN_D3D9`; цвет: `ME_COLOR(r,g,b)`.

## Поведение
- Полноэкранное top-most окно.
- Плавная заливка кадра без миганий.
- Выход по Esc.

## Ограничения
- Без обработки ошибок.
- Без тайминга/ввода, только цикл и заливка фона.
