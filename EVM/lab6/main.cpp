#include <iostream>
#include <libusb-1.0/libusb.h>
#include <vector>
#include <memory>
#include <iomanip>

class USBDevice {
public:
    USBDevice(libusb_device* dev);
    void printInfo() const;

private:
    libusb_device* device;
    libusb_device_descriptor desc;
    libusb_config_descriptor* config;
    std::string serialNumber;
    void fetchSerialNumber();
};

USBDevice::USBDevice(libusb_device* dev) : device(dev) {
    int r = libusb_get_device_descriptor(dev, &desc);
    if (r < 0) {
        throw std::runtime_error("Failed to get device descriptor.");
    }
    r = libusb_get_config_descriptor(dev, 0, &config);
    if (r < 0) {
        throw std::runtime_error("Failed to get configuration descriptor.");
    }
    fetchSerialNumber();
}

void USBDevice::fetchSerialNumber() {
    libusb_device_handle* handle = nullptr;
    if (libusb_open(device, &handle) == 0) {
        unsigned char serial[256];
        int ret = libusb_get_string_descriptor_ascii(handle, desc.iSerialNumber, serial, sizeof(serial));
        if (ret >= 0) {
            serialNumber = std::string(reinterpret_cast<char*>(serial), ret);
        } else {
            serialNumber = "N/A";
        }
        libusb_close(handle);
    } else {
        serialNumber = "N/A";
    }
}

void USBDevice::printInfo() const {
    std::cout << "Vendor ID: " << std::setw(4) << std::hex << desc.idVendor << " "
              << "Product ID: " << std::setw(4) << desc.idProduct << std::dec << std::endl;

    std::cout << "Device Class: " << (int)desc.bDeviceClass << std::endl;
    std::cout << "Serial Number: " << serialNumber << std::endl;

    std::cout << "Configurations: " << (int)desc.bNumConfigurations << std::endl;
    std::cout << "---------------------------------" << std::endl;

    // Вывод информации о конфигурации устройства
    for (int i = 0; i < (int)config->bNumInterfaces; ++i) {
        const libusb_interface& inter = config->interface[i];
        std::cout << "| Interface Number: " << std::setw(2) << (int)inter.num_altsetting << std::endl;

        for (int j = 0; j < inter.num_altsetting; ++j) {
            const libusb_interface_descriptor& interdesc = inter.altsetting[j];
            std::cout << "|   | Interface: " << std::setw(2) << (int)interdesc.bInterfaceNumber
                      << ", Endpoints: " << std::setw(2) << (int)interdesc.bNumEndpoints << std::endl;

            for (int k = 0; k < (int)interdesc.bNumEndpoints; ++k) {
                const libusb_endpoint_descriptor& epdesc = interdesc.endpoint[k];
                std::cout << "|   |   | Endpoint: " << std::setw(2) << (int)epdesc.bDescriptorType
                          << " Address: " << std::setw(9) << (int)epdesc.bEndpointAddress << std::endl;
            }
        }
    }

    libusb_free_config_descriptor(config);
}

class USBEnumerator {
public:
    USBEnumerator();
    ~USBEnumerator();
    void enumerateDevices();

private:
    libusb_context* ctx;
    std::vector<std::unique_ptr<USBDevice>> devices;
};

USBEnumerator::USBEnumerator() : ctx(nullptr) {
    int r = libusb_init(&ctx);
    if (r < 0) {
        throw std::runtime_error("Failed to initialize libusb.");
    }

    // Установка уровня логирования через libusb_set_option
    libusb_set_option(ctx, LIBUSB_OPTION_LOG_LEVEL, 3);  // Set debug level
}

USBEnumerator::~USBEnumerator() {
    libusb_exit(ctx);
}

void USBEnumerator::enumerateDevices() {
    libusb_device** devs = nullptr;
    ssize_t cnt = libusb_get_device_list(ctx, &devs);
    if (cnt < 0) {
        throw std::runtime_error("Failed to get device list.");
    }

    std::cout << "Found " << cnt << " devices" << std::endl;
    std::cout << "=============================="
                 "=============================" << std::endl;

    // Перебор устройств и вывод информации о каждом
    for (ssize_t i = 0; i < cnt; ++i) {
        devices.push_back(std::make_unique<USBDevice>(devs[i]));
        devices.back()->printInfo();
    }

    libusb_free_device_list(devs, 1);
}


int main() {
    try {
        USBEnumerator enumerator;
        enumerator.enumerateDevices();
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }
    return 0;
}
