//Jacob Pawlak
//October 22nd 2020
//DHT11 messin
//gooo blue team

#include <DHT.h>
#include <DHT_U.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

#define dht_input 2
#define DHTTYPE DHT11
DHT dht(dht_input, DHTTYPE);

const byte lcdRows = 4;
const byte lcdCols = 16;
//making the LCD screen
LiquidCrystal_I2C lcdScreen(0x27, lcdCols, lcdRows);

//WHEN LOOKING AT BLUE BOX
// Connect pin 1 (on the left) of the sensor to +5V
// Connect pin 2 of the sensor to whatever your DHTPIN is
// Connect pin 3 (on the right) of the sensor to GROUND
// Connect a 10K resistor from pin 2 (data) to pin 1 (power) of the sensor (I GUESS YOU NEED TO DO THIS?)


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  dht.begin();
  Wire.begin();
  //setting up the screen
  lcdScreen.init();
  lcdScreen.backlight();
  lcdScreen.clear();
  lcdScreen.setCursor(0,0);
  lcdScreen.print("Temp and humidity");
  delay(500);

}

void loop() {
  // put your main code here, to run repeatedly:

  // Reading temperature or humidity takes about 250 milliseconds!
  // Sensor readings may also be up to 2 seconds 'old' (its a very slow sensor)
  float h = dht.readHumidity();
  // Read temperature as Fahrenheit (isFahrenheit = true)
  float f = dht.readTemperature(true);

  // Check if any reads failed and exit early (to try again).
  if (isnan(h) || isnan(f)) {
    Serial.println(F("Failed to read from DHT sensor!"));
    return;
  }

  // Compute heat index in Fahrenheit (the default)
  float hif = dht.computeHeatIndex(f, h);

  lcdScreen.setCursor(1,1);
  lcdScreen.print(F("Humidity: "));
  lcdScreen.print(h);
  lcdScreen.setCursor(1,2);
  lcdScreen.print(F("Temperature: "));
  lcdScreen.print(f);
  lcdScreen.setCursor(1,3);
  lcdScreen.print(F("Heat Index: "));
  lcdScreen.print(hif);
  
  Serial.print(F("humidity: "));
  Serial.print(h);
  Serial.print(F("%  Temperature: "));
  Serial.print(f);
  Serial.print(F("°F  Heat index: "));
  Serial.print(hif);
  Serial.println(F("°F"));
}
