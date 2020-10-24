
#include <MCUFRIEND_kbv.h>
#include <Adafruit_GFX.h>
#include <Adafruit_TFTLCD.h>
#include <TouchScreen.h> //touch library

                             /*  r     g    b */
#define BLACK        0x0000  /*   0,   0,   0 */
#define BLUE         0x001F  /*   0,   0, 255 */
#define RED          0xF800  /* 255,   0,   0 */
#define GREEN        0x07E0  /*   0, 255,   0 */
#define CYAN         0x07FF  /*   0, 255, 255 */
#define YELLOW       0xFFE0  /* 255, 255,   0 */
#define WHITE        0xFFFF  /* 255, 255, 255 */
#define NAVY         0x000F  /*   0,   0, 128 */
#define DARKGREEN    0x03E0  /*   0, 128,   0 */
#define DARKCYAN     0x03EF  /*   0, 128, 128 */
#define MAROON       0x7800  /* 128,   0,   0 */
#define PURPLE       0x780F  /* 128,   0, 128 */
#define OLIVE        0x7BE0  /* 128, 128,   0 */
#define LIGHTGREY    0xC618  /* 192, 192, 192 */
#define DARKGREY     0x7BEF  /* 128, 128, 128 */
#define ORANGE       0xFD20  /* 255, 165,   0 */
#define GREENYELLOW  0xAFE5  /* 173, 255,  47 */
#define PINK         0xF81F  /* 255,   0, 255 */

#define BUTTON_X 40
#define BUTTON_Y 160
#define BUTTON_W 67
#define BUTTON_H 40
#define BUTTON_SPACING_X 10
#define BUTTON_SPACING_Y 15
#define BUTTON_TEXTSIZE 2


#define YP A3  // must be an analog pin, use "An" notation!
#define XM A2  // must be an analog pin, use "An" notation!
#define YM 9   // can be a digital pin
#define XP 8   // can be a digital pin

#define MINPRESSURE 10
#define MAXPRESSURE 1000

//touch sensitivity for X
#define TS_MINX 124
#define TS_MAXX 906

//touch sensitivity for Y
#define TS_MINY 83
#define TS_MAXY 893


#define RED_LED 44
#define GRE_LED 45
#define BLU_LED 46

boolean red_on = 0;
boolean gre_on = 0;
boolean blu_on = 0;

Adafruit_GFX_Button buttons[3];
char button_labels[3][5] = {"R", "G", "B"};
uint16_t button_colors[6] = {RED, GREEN, BLUE};

MCUFRIEND_kbv tft;

TouchScreen ts = TouchScreen(XP, YP, XM, YM, 300);

void setup() {

  Serial.begin(9600);
  pinMode(RED_LED, OUTPUT);
  pinMode(GRE_LED, OUTPUT);
  pinMode(BLU_LED, OUTPUT);

  tft.reset();

  uint16_t identifier = tft.readID();
  if (identifier == 0x9325) {
    Serial.println(F("Found ILI9325 LCD driver"));
  } else if (identifier == 0x9328) {
    Serial.println(F("Found ILI9328 LCD driver"));
  } else if (identifier == 0x4535) {
    Serial.println(F("Found LGDP4535 LCD driver"));
  } else if (identifier == 0x7575) {
    Serial.println(F("Found HX8347G LCD driver"));
  } else if (identifier == 0x9341) {
    Serial.println(F("*Found ILI9341 LCD driver"));
  } else if (identifier == 0x7783) {
    Serial.println(F("Found ST7781 LCD driver"));
  } else if (identifier == 0x8230) {
    Serial.println(F("Found UC8230 LCD driver"));
  }
  else if (identifier == 0x8357) {
    Serial.println(F("Found HX8357D LCD driver"));
  } else if (identifier == 0x0101)
  {
    identifier = 0x9341;
    Serial.println(F("Found 0x9341 LCD driver"));
  } else if (identifier == 0x9481)
  {
    Serial.println(F("Found 0x9481 LCD driver"));
  }
  else if (identifier == 0x9486)
  {
    Serial.println(F("Found 0x9486 LCD driver"));
  }
  else {
    Serial.print(F("Unknown LCD driver chip: "));
    Serial.println(identifier, HEX);
    identifier = 0x9486;
  }

  tft.begin(identifier);
  Serial.print("TFT size is "); Serial.print(tft.width()); Serial.print("x"); Serial.println(tft.height());
  tft.setRotation(0);
  tft.fillScreen(BLACK);

  for (uint8_t row = 0; row < 1; row++) {
    for (uint8_t col = 0; col < 3; col++) {
      buttons[col + row * 3].initButton(&tft, BUTTON_X + col * (BUTTON_W + BUTTON_SPACING_X),
                                        BUTTON_Y + row * (BUTTON_H + BUTTON_SPACING_Y), // x, y, w, h, outline, fill, text
                                        BUTTON_W, BUTTON_H, WHITE, button_colors[col + row * 3], WHITE,
                                        button_labels[col + row * 3], BUTTON_TEXTSIZE);
      buttons[col + row * 3].drawButton();
    }
  }
}

void loop() {
  digitalWrite(13, HIGH);
  TSPoint p = ts.getPoint();
  digitalWrite(13, LOW);

  pinMode(XM, OUTPUT);
  pinMode(YP, OUTPUT);

  if (p.z > MINPRESSURE && p.z < MAXPRESSURE)
  {

    //THESE NEED TO BE UNCOMMENTED IFF you see "tft.setRotation(1);" in setup function
    //p.x = p.x + p.y;
    //p.y = p.x - p.y;
    //p.x = p.x - p.y;
    p.x = map(p.x, TS_MINX, TS_MAXX, 0, tft.width());
    p.y = tft.height() - (map(p.y, TS_MINY, TS_MAXY, tft.height(), 0));
 
  }

  // Go thru all the buttons, checking if they were pressed
  for (uint8_t b = 0; b < 3; b++) {
    if ((buttons[b].contains(p.x, p.y)) && p.x > 10)
    {
      Serial.print("Pressing: "); Serial.println(b); 
      Serial.print("X, Y coords: "); Serial.print(p.x); Serial.print(" "); Serial.println(p.y);
      buttons[b].press(true);  // tell the button it is pressed
 
      //Button has been pressed
      if (b == 0) {
        // Toggle Red status
        red_on = !red_on;
      }
      if (b == 1) {
        // Toggle Green status
        gre_on = !gre_on;
      }
      if (b == 2) {
        // Toggle Blue status
        blu_on = !blu_on;
      }
 
      // Button Display
      if (red_on) {
        digitalWrite(RED_LED, HIGH);
      } else {
        digitalWrite(RED_LED, LOW);
      }
      if (gre_on) {
        digitalWrite(GRE_LED, HIGH);
      } else {
        digitalWrite(GRE_LED, LOW);
      }
      if (blu_on) {
        digitalWrite(BLU_LED, HIGH);
      } else {
        digitalWrite(BLU_LED, LOW);
      }
 
    } else {
      buttons[b].press(false);  // tell the button it is NOT pressed
    }
  }
 
  // now we can ask the buttons if their state has changed
  for (uint8_t b = 0; b < 3; b++) {
    if (buttons[b].justReleased()) {
      Serial.print("Released: "); Serial.println(b);
      buttons[b].drawButton();  // draw normal
    }
 
    if (buttons[b].justPressed()) {
      buttons[b].drawButton(true);  // draw invert!
 
 
      delay(100); // UI debouncing
    }
  }

  
}
