#include <utility>

#include "service/ServiceInstance.h"

namespace tt::service {

ServiceInstance::ServiceInstance(const service::ServiceManifest&manifest) : manifest(manifest) {}

const service::ServiceManifest& ServiceInstance::getManifest() const { return manifest; }

std::shared_ptr<void> ServiceInstance::getData() const {
    mutex.acquire(TtWaitForever);
    std::shared_ptr<void> result = data;
    mutex.release();
    return result;
}

void ServiceInstance::setData(std::shared_ptr<void> newData) {
    mutex.acquire(TtWaitForever);
    data = std::move(newData);
    mutex.release();
}

}