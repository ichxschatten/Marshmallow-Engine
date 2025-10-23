
---

# RELEASE-v0.0.0.1.md
# Marshmallow-Engine v0.0.0.1 — Minimal ESC Exit

## Состав
- Класс/заголовок: `Marshmallow-Engine-v0.0.0.1`
- Точка входа: `WinMainCRTStartup`
- Полноэкранное top-most окно
- Закрытие по Esc
- Остальное обрабатывает `DefWindowProcW`

## Ограничения
- Нет обработки ошибок
- Нет рендера и тайминга
- Выход только по Esc или внешним завершением процесса
