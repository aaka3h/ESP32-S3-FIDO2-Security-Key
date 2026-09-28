#include <stdint.h>
#include "esp_log.h"
#include "tinyusb.h"
#include "tinyusb_default_config.h"
#include "class/hid/hid_device.h"

static const char *TAG = "FIDO2";

/* FIDO Alliance HID usage page: 0xF1D0 */
static const uint8_t fido_report_desc[] = {
    0x06, 0xD0, 0xF1,       // Usage Page: FIDO
    0x09, 0x01,             // Usage: CTAPHID
    0xA1, 0x01,             // Application Collection

    0x09, 0x20,             // Input Report
    0x15, 0x00,
    0x26, 0xFF, 0x00,
    0x75, 0x08,
    0x95, 0x40,             // 64 bytes
    0x81, 0x02,

    0x09, 0x21,             // Output Report
    0x15, 0x00,
    0x26, 0xFF, 0x00,
    0x75, 0x08,
    0x95, 0x40,             // 64 bytes
    0x91, 0x02,

    0xC0
};

#define USB_TOTAL_LEN \
    (TUD_CONFIG_DESC_LEN + TUD_HID_INOUT_DESC_LEN)

static const uint8_t usb_config_desc[] = {
    TUD_CONFIG_DESCRIPTOR(
        1, 1, 0, USB_TOTAL_LEN, 0, 100
    ),

    TUD_HID_INOUT_DESCRIPTOR(
        0, 4, HID_ITF_PROTOCOL_NONE,
        sizeof(fido_report_desc),
        0x01, 0x81, 64, 5
    )
};

static const char *usb_strings[] = {
    (const char[]){0x09, 0x04},
    "ESP32 FIDO Lab",
    "Experimental FIDO HID",
    "000001",
    "FIDO Interface"
};

uint8_t const *tud_hid_descriptor_report_cb(
    uint8_t instance
) {
    (void)instance;
    return fido_report_desc;
}

uint16_t tud_hid_get_report_cb(
    uint8_t instance,
    uint8_t report_id,
    hid_report_type_t report_type,
    uint8_t *buffer,
    uint16_t reqlen
) {
    (void)instance;
    (void)report_id;
    (void)report_type;
    (void)buffer;
    (void)reqlen;
    return 0;
}

void tud_hid_set_report_cb(
    uint8_t instance,
    uint8_t report_id,
    hid_report_type_t report_type,
    uint8_t const *buffer,
    uint16_t bufsize
) {
    (void)instance;
    (void)report_id;
    (void)report_type;
    (void)buffer;

    ESP_LOGI(TAG, "Received HID report: %u bytes",
             (unsigned)bufsize);
}

void app_main(void)
{
    ESP_LOGI(TAG, "Starting FIDO HID prototype");

    tinyusb_config_t cfg = TINYUSB_DEFAULT_CONFIG();

    cfg.descriptor.full_speed_config = usb_config_desc;
    cfg.descriptor.string = usb_strings;
    cfg.descriptor.string_count =
        sizeof(usb_strings) / sizeof(usb_strings[0]);

    ESP_ERROR_CHECK(tinyusb_driver_install(&cfg));

    ESP_LOGI(TAG, "USB HID initialized");
}
