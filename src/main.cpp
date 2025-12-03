#include <Arduino.h>
#include <WiFi.h>

#include "HX711.h"

#include "WifiSecrets.hpp" // See WifiSecretsExample.hpp

// HX711 circuit wiring
#define LOADCELL_DOUT_PIN 16  // D16 pin on board
#define LOADCELL_SCK_PIN 4    // D4 pin on board

// 2. Adjustment settings
// Coke: 380g grams
// Reading: ~152950
// 152950 / 380 = 424.86111111111111111111111111111
const float LOADCELL_DIVIDER = static_cast<float>(152950) / 380;

HX711 loadcell;
 
void setup() {

  Serial.begin(9600);
  Serial.println("HX711 Demo");

  loadcell.begin(LOADCELL_DOUT_PIN, LOADCELL_SCK_PIN);  // ✅ REQUIRED !!!
  loadcell.set_scale(LOADCELL_DIVIDER);
  loadcell.tare(20);
  Serial.println("Insert the item to be weighed"); 

  // Wifi
  WiFi.mode(WIFI_STA);  // Station mode
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);

    // Wait for connection
  int max_retries = 20;
  while (WiFi.status() != WL_CONNECTED && max_retries-- > 0) {
    Serial.print(".");
    delay(500);
  }

  if (WiFi.status() == WL_CONNECTED) {
    Serial.println("\nWiFi connected!");
    Serial.print("IP address: ");
    Serial.println(WiFi.localIP());
  } else {
    Serial.println("\nFailed to connect to WiFi");
  }
}
 
void loop() {
  Serial.print("Reading: ");
  Serial.println(loadcell.get_units(10), 0);
  delay(100);

  static uint64_t last = 0;
  if (millis() - last > 5000) {
    last = millis();
    Serial.println(WiFi.status() == WL_CONNECTED ? "Still connected" : "Disconnected");
  }
}
