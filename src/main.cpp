#include "HX711.h"
#include <LCD_I2C.h>
#include <Arduino.h>

// HX711 circuit wiring
#define LOADCELL_DOUT_PIN 16  // D16 pin on board
#define LOADCELL_SCK_PIN 4   // D4 pin on board

// 2. Adjustment settings
// Coke: 380g grams
// Reading: ~152950
// 152950 / 380 = 424.86111111111111111111111111111
const float LOADCELL_DIVIDER = static_cast<float>(152950) / 380;

HX711 loadcell;
LCD_I2C lcd(0x27, 16, 2);

void setup() {

  Serial.begin(9600);
  Serial.println("HX711 Demo");

  loadcell.begin(LOADCELL_DOUT_PIN, LOADCELL_SCK_PIN);  // ✅ REQUIRED !!!
  loadcell.set_scale(LOADCELL_DIVIDER);
  loadcell.tare(20);
  Serial.println("Insert the item to be weighed");

  // Display testing
  lcd.begin();
  lcd.backlight();
}
 
void loop() {
  int reading = loadcell.get_units(10);
  Serial.print("Reading: ");
  Serial.println(reading, 0);
  // LCD Display
  lcd.clear();
  lcd.print("Coffee Scale");
  lcd.setCursor(0, 1);
  lcd.print("Weight: ");
  lcd.print(reading, 0);
  delay(100);
}
