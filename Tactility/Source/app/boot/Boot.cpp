#include <Check.h>
#include <Thread.h>
#include <Kernel.h>
#include "Assets.h"
#include "app/AppContext.h"
#include "lvgl.h"
#include "hal/Display.h"
#include "service/loader/Loader.h"
#include "lvgl/Style.h"
#include "app/display/DisplaySettings.h"

#ifdef ESP_PLATFORM
#include "sdkconfig.h"
#else
#define CONFIG_TT_SPLASH_DURATION 0
#endif

namespace tt::app::boot {

static int32_t threadCallback(void* context);

struct Data {
    Data() : thread("boot", 4096, threadCallback, this) {}

    Thread thread;
};

static int32_t threadCallback(TT_UNUSED void* context) {
    TickType_t start_time = tt::get_ticks();

    auto* lvgl_display = lv_display_get_default();
    tt_assert(lvgl_display != nullptr);
    auto* hal_display = (tt::hal::Display*)lv_display_get_user_data(lvgl_display);
    tt_assert(hal_display != nullptr);
    if (hal_display->supportsBacklightDuty()) {
        int32_t backlight_duty = app::display::getBacklightDuty();
        hal_display->setBacklightDuty(backlight_duty);
    }

    TickType_t end_time = tt::get_ticks();
    TickType_t ticks_passed = end_time - start_time;
    TickType_t minimum_ticks = (CONFIG_TT_SPLASH_DURATION / portTICK_PERIOD_MS);
    if (minimum_ticks > ticks_passed) {
        tt::delay_ticks(minimum_ticks - ticks_passed);
    }
    tt::service::loader::stopApp();
    tt::service::loader::startApp("Desktop");
    return 0;
}

static void onShow(TT_UNUSED AppContext& app, lv_obj_t* parent) {
    auto data = std::static_pointer_cast<Data>(app.getData());

    lv_obj_t* image = lv_image_create(parent);
    lv_obj_set_size(image, LV_PCT(100), LV_PCT(100));
    lv_image_set_src(image, TT_ASSETS_BOOT_LOGO);
    lvgl::obj_set_style_bg_blacken(parent);

    data->thread.start();
}

static void onStart(AppContext& app) {
    auto data = std::make_shared<Data>();
    app.setData(data);
}

static void onStop(AppContext& app) {
    auto data = std::static_pointer_cast<Data>(app.getData());
    data->thread.join();
}

extern const AppManifest manifest = {
    .id = "Boot",
    .name = "Boot",
    .type = TypeBoot,
    .onStart = onStart,
    .onStop = onStop,
    .onShow = onShow,
};

} // namespace