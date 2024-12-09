#pragma once

#include "AppManifest.h"

#ifdef ESP_PLATFORM

namespace tt::app {

bool startElfApp(const char* filePath);

void setElfAppManifest(const AppManifest& manifest);

}


#endif // ESP_PLATFORM