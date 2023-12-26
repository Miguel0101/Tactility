## Overview

NanoBake is a front-end application platform for ESP32. It provides an application framework that is based code from the [Flipper Zero](https://github.com/flipperdevices/flipperzero-firmware/) project.

Nanobake provides:
- A hardware abstraction layer
- UI capabilities (via LVGL)
- An application platform that can run apps and services

**Status: pre-alpha**

## Technologies

LCD and input drivers are based on [esp_lcd](https://docs.espressif.com/projects/esp-idf/en/latest/esp32/api-reference/peripherals/lcd.html)
and [esp_lcd_touch](https://components.espressif.com/components/espressif/esp_lcd_touch).

UI is created with [lvgl](https://github.com/lvgl/lvgl) via [esp_lvgl_port](https://github.com/espressif/esp-bsp/tree/master/components/esp_lvgl_port).

## Supported Hardware

### Devices

In theory, all hardware from the [Board Support Packages](https://github.com/espressif/esp-bsp/) project is supported.

In practice, there are pre-configured drivers available for these boards:
- Yellow Board / 2432S024

### Drivers

**Displays** (see [esp-bsp](https://github.com/espressif/esp-bsp/blob/master/LCD.md) and [Espressif Registry](https://components.espressif.com/components?q=esp_lcd)):
- GC9503
- GC9A01
- ILI9341
- RA8875
- RM68120
- SH1107
- SSD1306
- SSD1963
- ST7262E43
- ST7789
 
**Touch** (see [Espressif Registry](https://components.espressif.com/components?q=esp_lcd_touch)):
- CST8xx
- FT5X06
- GT1151
- GT911
- STMPE610
- TT2100

## Guide

Until there is proper documentation, here are some pointers:
- [Sample application](main/src/main.c)
- [NanoBake](./components/nanobake/inc)
- [Furi](./components/furi/src)

## License

[GNU General Public License Version 3](LICENSE.md)

