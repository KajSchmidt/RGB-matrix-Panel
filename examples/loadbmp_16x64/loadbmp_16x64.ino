/******************************************

Script to load image from SD-card for two 
chained 16x32 RGB Led Matrix.

Image must be a 16x64 BMP (24 bit) image saved
on SD-card.

This functions have only been tested on 
Arduino Mega ADK due to the matrix need of 
full registers and the ethernet+sd-shields
need of SS-pins.

Author: Kaj Schmidt (https://github.com/KajSchmidt)

*******************************************/

#include <SPI.h>
#include <SD.h>
#include <RGB_matrix_Panel/Adafruit_GFX.h>   // Core graphics library
#include <RGBmatrixPanel.h> // Hardware-specific library


#define CLK 11  // MUST be on PORTB!
#define LAT A3
#define OE  12
#define A   A0
#define B   A1
#define C   A2

// Last parameter = 'true' enables double-buffering, for flicker-free,
// buttery smooth animation.  Note that NOTHING WILL SHOW ON THE DISPLAY
// until the first call to swapBuffers().  This is normal.
RGBmatrixPanel matrix(A, B, C, CLK, LAT, OE, true);

PImage myimage;

void setup() {
  Serial.begin(9600);
  
  pinMode(10, OUTPUT);
  digitalWrite(10, HIGH); //Disable ethernetshield
  
  pinMode(4, OUTPUT);
  if (!SD.begin(4)) Serial.println("SD failed!");
  else Serial.println("SD Connected!");
 
  matrix.begin();

  myimage = matrix.loadImage("image.bmp");
  if (!myimage.isValid()) Serial.println("error while loading image");
  else Serial.println("Image loaded!");
}

void loop() {
  matrix.image(myimage, 0,0);
  matrix.swapBuffers(false);
}
