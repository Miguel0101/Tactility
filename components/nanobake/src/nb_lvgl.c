#include "nb_lvgli.h"
#include "nb_hardwarei.h"
#include <esp_lvgl_port.h>
#include <check.h>

static const char* TAG = "nb_lvgl";

nb_lvgl_t nb_lvgl_init(nb_hardware_t _Nonnull* hardware) {
    const lvgl_port_cfg_t lvgl_cfg = {
        .task_priority = 4,
        .task_stack = 4096,
        .task_affinity = -1, // core pinning
        .task_max_sleep_ms = 500,
        .timer_period_ms = 5
    };

    furi_check(lvgl_port_init(&lvgl_cfg) == ESP_OK, "lvgl port init failed");
    nb_display_t _Nonnull* display = hardware->display;

    // Add display
    ESP_LOGD(TAG, "lvgl add display");
    const lvgl_port_display_cfg_t disp_cfg = {
        .io_handle = display->io_handle,
        .panel_handle = display->display_handle,
        .buffer_size = display->horizontal_resolution * display->draw_buffer_height * (display->bits_per_pixel / 8),
        .double_buffer = 0,
        .hres = display->horizontal_resolution,
        .vres = display->vertical_resolution,
        .monochrome = false,
        .rotation = {
            .swap_xy = false,
            .mirror_x = display->mirror_x,
            .mirror_y = display->mirror_y,
        },
        .flags = {
            .buff_dma = true,
        }
    };

    lv_disp_t _Nonnull* disp = lvgl_port_add_disp(&disp_cfg);
    lv_indev_t _Nullable* touch_indev = NULL;

    // Add touch
    if (hardware->touch != NULL) {
        const lvgl_port_touch_cfg_t touch_cfg = {
            .disp = disp,
            .handle = hardware->touch->touch_handle,
        };
        touch_indev = lvgl_port_add_touch(&touch_cfg);
        furi_check(touch_indev != NULL, "failed to add touch to lvgl");
    }

    return (nb_lvgl_t) {
        .disp = disp,
        .touch_indev = touch_indev
    };
}