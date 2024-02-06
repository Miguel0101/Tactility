#include "app.h"
#include "lvgl.h"
#include "ui/toolbar.h"

static void app_show(App app, lv_obj_t* parent) {
    lv_obj_set_flex_flow(parent, LV_FLEX_FLOW_COLUMN);

    tt_toolbar_create_for_app(parent, app);

    lv_obj_t* wrapper = lv_obj_create(parent);
    lv_obj_set_width(wrapper, LV_PCT(100));
    lv_obj_set_flex_grow(wrapper, 1);

    lv_obj_t* heap_info = lv_label_create(wrapper);
    lv_label_set_recolor(heap_info, true);
    lv_obj_set_width(heap_info, 200);
    lv_obj_set_style_text_align(heap_info, LV_TEXT_ALIGN_CENTER, 0);
#ifdef ESP_PLATFORM
    lv_label_set_text_fmt(
        heap_info,
        "Heap available:\n%d / %d",
        heap_caps_get_free_size(MALLOC_CAP_INTERNAL),
        heap_caps_get_total_size(MALLOC_CAP_INTERNAL)
    );
#else
    lv_label_set_text(heap_info, "Heap available: ?");
#endif
    lv_obj_align(heap_info, LV_ALIGN_CENTER, 0, -20);

    lv_obj_t* spi_info = lv_label_create(wrapper);
    lv_label_set_recolor(spi_info, true);
    lv_obj_set_width(spi_info, 200);
    lv_obj_set_style_text_align(spi_info, LV_TEXT_ALIGN_CENTER, 0);
#ifdef ESP_PLATFORM
    lv_label_set_text_fmt(
        spi_info,
        "SPI available\n%d / %d",
        heap_caps_get_free_size(MALLOC_CAP_SPIRAM),
        heap_caps_get_total_size(MALLOC_CAP_SPIRAM)
    );
#else
    lv_label_set_text(spi_info, "SPI available: none");
#endif
    lv_obj_align(spi_info, LV_ALIGN_CENTER, 0, 20);
}

AppManifest system_info_app = {
    .id = "systeminfo",
    .name = "System Info",
    .icon = NULL,
    .type = AppTypeSystem,
    .on_start = NULL,
    .on_stop = NULL,
    .on_show = &app_show
};
