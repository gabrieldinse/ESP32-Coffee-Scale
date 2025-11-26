#include "HX711.h"
#include <Arduino.h>

// HX711 circuit wiring
#define LOADCELL_DOUT_PIN 21  // D21 pin on board
#define LOADCELL_SCK_PIN 22   // D22 pin on board

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
}
 
void loop() {
  Serial.print("Reading: ");
  Serial.println(loadcell.get_units(10), 0);
  delay(100);
}
