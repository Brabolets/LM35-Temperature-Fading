
// LM35 temp sensor connected to Analogue-in 1, 5volt and ground
// ~2 to ~102 degrees C
//
#include <LiquidCrystal.h>
LiquidCrystal lcd(12, 11, 5, 4, 3, 2); // your LCD pins could be different
int ledPin = 9; // backlight pin
unsigned long total; // readings
float tempC; // Celcius
float tempF; // Fahrenheit
//
void setup() {
  analogReference(INTERNAL); // use the internal ~1.1volt reference, change (INTERNAL) to (INTERNAL1V1) for a Mega
  Serial.begin(115200); // ---set serial monitor to this value---
  //analogWrite(ledPin, 255); // optional dimming
  lcd.begin(16, 2); // shield with 2x16 characters
  lcd.setCursor(0, 0); // first row
  lcd.print("Initializing..."); //info text
  lcd.setCursor(0, 1); // second row
  lcd.print("OK");
  delay(1000); // info display time
}
//
void loop() {

  for (int fadeValue = 0 ; fadeValue <= 220; fadeValue += 5) {
    // sets the value (range from 0 to 255):
    analogWrite(ledPin, fadeValue);
    // wait for 30 milliseconds to see the dimming effect
    delay(70);
    }

// fade out from max to min in increments of 5 points:
  for (int fadeValue = 220 ; fadeValue >= 0; fadeValue -= 5) {
    // sets the value (range from 0 to 255):
    analogWrite(ledPin, fadeValue);
    // wait for 30 milliseconds to see the dimming effect
    delay(10);
  }

    
  analogRead(1); // one unused reading
  for (int x = 0; x < 50; x++) { // 50 readings for averaging
    total = total + analogRead(1); // add each value to a total
  }
  // convert value to temp
  tempC = total * 0.00207617; // calibration maths, depends on actual Vref, (0.001953125 * Vref in volts)
  tempF = tempC * 1.8 + 32; // Fahrenheit conversion
  // print to LCD
  if (total == 51150) { // 50*1023
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("---TOO HOT---");
  }
  else {
    lcd.clear();
    lcd.setCursor(0, 0); // first row
    lcd.print(tempC, 1); // two decimal places
    lcd.setCursor(4, 0); // position 6, first row
    lcd.print("C");
    lcd.setCursor(11, 0); // second row
    lcd.print(tempF, 1); // one decimal place
    lcd.setCursor(15, 0); // position 6, second row
    lcd.print("F");
    lcd.setCursor(1, 1); // position 6, first row
    lcd.print("Temp Ambiente");
  }
  // print to serial monitor
  Serial.print("Raw average = ");
  Serial.print(total * 0.02, 1); // 1/50 of 50 readings, one decimal place
  if (total == 51150) { // max value with 50 readings
    Serial.println("  ----too hot----");
  }
  else {
    Serial.print("   The temperature is  ");
    Serial.print(tempC, 2); // two decimal places
    Serial.print(" Celcius  ");
    Serial.print(tempF, 1); // one decimal place
    Serial.println(" Fahrenheit");
  }
  delay(1000); // slows readings
  total = 0; // reset value
}
 
  
