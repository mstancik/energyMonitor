
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
#include <ArduinoJson.h>

LiquidCrystal_I2C lcd(0x27,20,4);  // set the LCD address to 0x27 for a 16 chars and 2 line display

#include "EmonLib.h"                   // Include Emon Library
EnergyMonitor emon1;                   // Create an instance
EnergyMonitor emon2;
EnergyMonitor emon3;

DynamicJsonDocument jbuffer(256);

void setup()
{
  lcd.init();                      // initialize the lcd 
  lcd.init();
  // Print a message to the LCD.
  lcd.backlight();
  lcd.setCursor(0,0);
  lcd.print("Initializing LCD");
  lcd.setCursor(0,1);
  lcd.print("L1");
  lcd.setCursor(0,2);
  lcd.print("L2");
  lcd.setCursor(0,3);
  lcd.print("L3");
  
  Serial.begin(9600);
  emon1.current(0, 14.80);     // L1        // Current: input pin, calibration.
  emon2.current(1, 18.80);     // L2
  emon3.current(2, 14.70);     // L3 

}


void loop()
{
  double Irms1 = emon1.calcIrms(10000);  // Calculate Irms only
  double Irms2 = emon2.calcIrms(10000);
  double Irms3 = emon3.calcIrms(10000);
  double Pow1 = Irms1 * 230;
  double Pow2 = Irms2 * 230;
  double Pow3 = Irms3 * 230;
  lcd.clear();
  lcd.setCursor(0,1);
  lcd.print("L1 ");
  lcd.print(Pow1);
  lcd.setCursor(0,2);
  lcd.print("L2 ");
  lcd.print(Pow2);
  lcd.setCursor(0,3);
  lcd.print("L3 ");
  lcd.print(Pow3);


  jbuffer["power1"] = Pow1;
  jbuffer["power2"] = Pow2;
  jbuffer["power3"] = Pow3;
  serializeJson(jbuffer, Serial); 
  jbuffer.clear();
  Serial.println();
}
