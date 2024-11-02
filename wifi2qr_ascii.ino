#include <qrcodegen.h>

const char* ssid = "YourNetworkName";
const char* password = "YourPassword";

void setup() {
    Serial.begin(115200);

    // Wait for Serial to initialize
    while (!Serial) delay(10);

    // Generate the QR code
    generateWiFiQRCode(ssid, password);
}

void loop() {
    // Nothing to do in loop
}

void generateWiFiQRCode(const char* ssid, const char* password) {
    // WiFi QR Code format: WIFI:S:<SSID>;T:WPA;P:<password>;;
    String wifiData = "WIFI:S:" + String(ssid) + ";T:WPA;P:" + String(password) + ";;";

    // Buffer for QR code
    uint8_t qrcode[qrcodegen_BUFFER_LEN_MAX];
    uint8_t tempBuffer[qrcodegen_BUFFER_LEN_MAX];

    // Generate QR code
    bool ok = qrcodegen_encodeText(wifiData.c_str(), tempBuffer, qrcode, qrcodegen_Ecc_LOW,
                                   qrcodegen_VERSION_MIN, qrcodegen_VERSION_MAX, 
                                   qrcodegen_Mask_AUTO, true);
    if (ok) {
        printQRCode(qrcode);
    } else {
        Serial.println("Failed to generate QR code");
    }
}

void printQRCode(const uint8_t qrcode[]) {
    int size = qrcodegen_getSize(qrcode);
    int border = 2;

    for (int y = -border; y < size + border; y++) {
        for (int x = -border; x < size + border; x++) {
            Serial.print(qrcodegen_getModule(qrcode, x, y) ? "##" : "  ");
        }
        Serial.println();
    }
}
