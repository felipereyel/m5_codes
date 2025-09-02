#include "M5Unified.h"
#include "QRCode_esp32_compat.h"

#define QRCODE_VERSION 3
#define screen_width 128
#define screen_height 128

// this is a test key
char content[52] = "otpauth://totp/A?secret=I65VU7K5ZQL7WB4E";

void setup()
{
    // M5
    auto cfg = M5.config();
    cfg.serial_baudrate = 115200;
    M5.begin(cfg);

    // Setup display
    M5.Display.init();
    M5.Display.setBrightness(10);
    M5.Display.fillScreen(TFT_WHITE);

    // Create the QR code
    QRCode qrcode;
    uint8_t qrcodeData[qrcode_getBufferSize(QRCODE_VERSION)];
    qrcode_initText(&qrcode, qrcodeData, QRCODE_VERSION, ECC_LOW, content);

    auto scale = screen_width / qrcode.size;
    auto padding = (screen_width - (qrcode.size * scale)) / 2;

    // Draw code
    for (uint8_t y = 0; y < qrcode.size; y++)
    {
        for (uint8_t x = 0; x < qrcode.size; x++)
        {
            if (qrcode_getModule(&qrcode, x, y))
            {
                M5.Display.fillRect(padding + x * scale, padding + y * scale, scale, scale, TFT_BLACK);
            }
        }
        Serial.print("\n");
    }
}

void loop()
{
    M5.delay(10);
    M5.update();
}

// void draw_totp_screen()
// {
//     if (current_seed.isEmpty() || current_provider.isEmpty() || current_totp.isEmpty())
//     {
//         return;
//     }

//     int current = (ltime) % STEP;
//     float progress = (float)current / STEP;

//     int width = M5.Display.width();
//     int height = M5.Display.height();
//     int bar_height = PROGRESS_BAR_HEIGHT;
//     int bar_width = width - 2 * PROGRESS_BAR_MARGIN;

//     int bg_color = M5.Display.color565(200, 200, 200);
//     int bar_color = M5.Display.color565(0, 255, 0);
//     if (progress > 0.8)
//     {
//         bar_color = M5.Display.color565(255, 0, 0);
//     }
//     else if (progress > 0.5)
//     {
//         bar_color = M5.Display.color565(255, 165, 0);
//     }

//     M5.Display.fillRect(10, height - bar_height - 10, bar_width, bar_height, bg_color);
//     int filled_width = (current * bar_width) / STEP;
//     M5.Display.fillRect(10, height - bar_height - 10, filled_width, bar_height, bar_color);

//     M5.Display.setTextSize(FONT_SIZE_XLARGE);
//     M5.Display.setCursor(85, 100);
//     M5.Display.printf("%s\n", current_totp.c_str());
// }

// void draw_text_ui()
// {
//     M5.Display.clear();
//     M5.Display.setCursor(0, 0);

//     M5.Display.setTextSize(FONT_SIZE_MEDIUM);
//     M5.Display.printf("slot %d/%d: ", current_index + 1, MAX_KEYS);

//     auto isEmpty = current_provider.isEmpty() || current_seed.isEmpty();
//     auto slotname = isEmpty ? "EMPTY" : current_provider;
//     M5.Display.setTextSize(FONT_SIZE_MEDIUM);
//     M5.Display.printf("%s\n", slotname);
// }

// Arduino Setup and Loop

// Draw initial UI
// M5.Display.init();
// M5.Display.setBrightness(100);
// M5.Display.fillScreen(TFT_BLACK);
// draw_text_ui();