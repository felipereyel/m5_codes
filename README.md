# m5_codes

## Requirements

- Arduino CLI
    - m5stack core (`arduino-cli core install m5stack:esp32@2.1.4`)
    - M5 grafics lib (`arduino-cli lib install M5GFX`)
    - M5 lib (`arduino-cli lib install M5Unified`)
    - enable git libs (`arduino-cli config set library.enable_unsafe_install true`)
    - BLE lib (`arduino-cli lib install --git-url https://github.com/felipereyel/QRCode_esp32_compat.git`)

## Compile and upload

```
    make firmware-compile
    make firmware-upload

    # Or both
    make firmware
```

## TODOs

- Add web server to configure code content