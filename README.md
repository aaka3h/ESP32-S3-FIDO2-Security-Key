# ESP32-S3 Experimental FIDO2 Security Key

An experimental USB FIDO HID authenticator project using
the Heltec WiFi Kit 32 V3.2.

## Technology
- ESP32-S3
- ESP-IDF 5.5.2
- TinyUSB
- USB HID (FIDO usage page 0xF1D0)

## Current progress
- [x] ESP-IDF configured
- [x] Firmware compiled and flashed
- [x] TinyUSB initialized
- [x] Experimental FIDO HID descriptor
- [ ] Native USB enumeration verified
- [ ] CTAPHID_INIT and CTAPHID_PING
- [ ] CTAP2 implementation
- [ ] Passkey registration and authentication
- [ ] Security review

## Hardware
Heltec WiFi Kit 32 V3.2.

Native USB:
- GPIO19: D-
- GPIO20: D+

Verify PCB wiring before connecting USB data lines.

## Warning
Experimental development firmware only.
Not FIDO certified and not suitable for protecting
important accounts or serving as a sole recovery method.
