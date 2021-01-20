/**
 * Author:    UseMyTools.Net
 * Created:   2021.01.20
 *
 * (c) Copyright by UseMyTools.Net.
 *  MIT license
 *
 **/

#include <Adafruit_GFX.h>
/*
 * Adafruit_GFX Core graphics library
 * Written by Limor Fried/Ladyada & Phil Burgess/PaintYourDragon
 * for Adafruit Industries.
 *  BSD license, all text above must be included in any redistribution.
*/

/*
 * code snippet from Time_Message_ESP8266_Matrix-P4
 * https://arduino-projects-free.blogspot.com/2020/08/time-message-esp8266-matrix-p4-weather.html
 *
 */


#include <RGBmatrixPanel.h> // Hardware-specific library
#include <FreeMonoBold12pt7b.h>
#include <kongtext4pt7b.h>


// Similar to F(), but for PROGMEM string pointers rather than literals
#define F2(progmem_ptr) (const __FlashStringHelper *)progmem_ptr


#define CLK 11   // USE THIS ON ARDUINO MEGA
#define OE   9
#define LAT 10
#define A   A0
#define B   A1
#define C   A2
#define D   A3




// Last parameter = 'true' enables double-buffering, for flicker-free,
// buttery smooth animation.  Note that NOTHING WILL SHOW ON THE DISPLAY
// until the first call to swapBuffers().  This is normal.
//RGBmatrixPanel matrix(A, B, C, CLK, LAT, OE, true);
RGBmatrixPanel matrix(A, B, C, D, CLK, LAT, OE, true, 64);



uint16_t myRED = matrix.Color333(7,0,0);
uint16_t myGREEN = matrix.Color333(0,7,0);
uint16_t myBLUE = matrix.Color333(0,0,7);
uint16_t myWHITE = matrix.Color333(7, 7,7);
uint16_t myYELLOW = matrix.Color333(7,7,0);
uint16_t myCYAN = matrix.Color333(0,7,7);
uint16_t myMAGENTA = matrix.Color333(7,0,7);
uint16_t myShadow = matrix.Color333(4,0,7);
uint16_t myROSE = matrix.Color333(7,0,4);
uint16_t myBLACK = matrix.Color333(0,0,0);
uint16_t myCOLORS[9] = {myRED, myGREEN, myWHITE, myMAGENTA, myBLUE, myYELLOW, myCYAN, myShadow, myROSE};


const char str[] PROGMEM = "Happy Birthday Amina WE ALL LOVE YOU";
//int    textX   = matrix.width(),
int    textX   = 14,

       //textMin = sizeof(str) * -12,
       textMin = sizeof(str) * -6,

       hue     = 0;
int8_t ball[3][4] = {
  {  3,  0,  1,  1 }, // Initial X,Y pos & velocity for 3 bouncy balls
  { 17, 15,  1, -1 },
  { 27,  4, -1,  1 }
};
static const uint16_t PROGMEM ballcolor[3] = {
  0x0080, // Green=1
  0x0002, // Blue=1
  0x1000  // Red=1
};

  void setup() {
  Serial.begin(115200); //opens serial port, sets data rate to 115200 bps
  matrix.begin();
  matrix.setTextWrap(false); // Allow text to run off right edge
  matrix.setTextSize(1);

}



void display_footer()
{
  matrix.setCursor(1, 29);
  matrix.setFont(&kongtext4pt7b);
  matrix.setTextColor(myCYAN);
  matrix.print("21");
  matrix.setTextColor(myMAGENTA);
  matrix.print("JAN");
  matrix.setTextColor(myBLUE);
  matrix.print("2021");
  matrix.setFont();
}



void display_header()
{
String  text = "*AMINA*";
  uint16_t text_length = text.length();
  int xpo = (64 - text_length * 7) / 2;

  matrix.setCursor(xpo, 1);
  matrix.setFont(&kongtext4pt7b);
  for (int y = 0; y < 9; y++) {
  uint8_t  r = random(0,8);
    matrix.setTextColor(myCOLORS[r]);
    matrix.print(text[y]);
  }
  matrix.setFont();
}

void display_middle(){


int ypos = 12;

  // Draw big scrolly text on top
matrix.setTextColor(matrix.ColorHSV(hue, 255, 255, true));
matrix.setCursor(textX, ypos);
matrix.print(F2(str));
matrix.setFont(&kongtext4pt7b);

  // Move text left (w/wrap), increase hue
  if((--textX) < textMin) textX = 14;
  hue += 7;
  if(hue >= 1536) hue -= 1536;

}

void loop() {

  matrix.fillScreen(matrix.Color333(0, 0, 0));

  display_header();
  display_middle();
  display_footer();

  // Update display
  matrix.swapBuffers(false);

}
