/* pixelFunctions.h

    Just a place to store Ws23818 LED Pixel functions

    Pixel Pin
    #define PIXEL_DATA          5

*/


#ifndef pixelFunctions_h
#define pixelFunctions_h


#include <FastLED.h>


#define LED_PIN     PIXEL_DATA
#define NUM_LEDS    8
#define BRIGHTNESS  150
#define LED_TYPE    WS2811
#define COLOR_ORDER GRB
//CRGB leds[NUM_LEDS];
CRGBArray <NUM_LEDS> leds;

#define UPDATES_PER_SECOND 30
#define HUE_STEPS 5                // Number of steps to advance through palette between each for loop. Origionally 3



CRGBPalette16 currentPalette;
TBlendType    currentBlending;


DEFINE_GRADIENT_PALETTE( transform) {
  0,        0, 40, 255,    /* Baby Blue */
  8,        200, 20, 150,   /* Baby Pink */
  10,       255,  255, 255,    /* White */
  13,       200, 20, 150,    /* Baby Pink*/
  255,      0, 40, 255     /* Baby Blue */
};


DEFINE_GRADIENT_PALETTE( hotpink_blue ) {
  0,        0,  100, 255,    /* at index 0, orange(0,0,0) */
  50,       0,  255, 255,    /* at index 0, orange(0,0,0) */
  60,        255, 0, 150,
  100,       255, 0, 150,
  150,         0, 0, 255,
  170,       0,  255,  255,    /* at index 0, orange(0,0,0) */
  222,       255,  0,  150, /* at index 255, white(255,255,255) */
  255,    120,  0,   255   /* at index 0, orange(0,0,0) */       // last entry must be for index 255
};


DEFINE_GRADIENT_PALETTE( raggaPalette ) {
  0,      255,  255,  0,    /* at index 0, yellow(0,0,0) */
  100,     100,  255,  0,    /* at index 0, greenyellow(0,0,0) */
  150,      0,  255, 0,    /* at index 192, green(255,0,0) */
  200,     255,  0, 0, /* at index 255, red(255,255,255) */
  255,    255,  255,  0    /* at index 0, yellow(0,0,0) */       // last entry must be for index 255
};













void fastled_setup() {
  // Serial.println("Gathering Spectrum...");
  delay( 1000 ); // power-up safety delay
  FastLED.addLeds<LED_TYPE, LED_PIN, COLOR_ORDER>(leds, NUM_LEDS).setCorrection( TypicalLEDStrip );
  // Serial.println("...Processing Light Threads...");
  FastLED.setBrightness(  BRIGHTNESS );
  randomSeed(analogRead(0));   // psudo random number generator for randomness & chaos
  leds(0, 9) = CHSV(255, 255, 0);
  // Serial.println("               Weaving Colours...  \n     ...Selecting Pigments\n");
  delay(500);
  //  Serial.println("Chroma Paintbrush Initialised:  Luminescence Matrix Applied.\n Starting Visual Light Imbument\n ");
  FastLED.show();

}

void pixelBegin() {
  fastled_setup();
  currentBlending = LINEARBLEND;
}



void pixelChangePalette(CRGBPalette16 newPalette) {
  currentPalette = newPalette;
}



void FillLEDsFromPaletteColors( uint8_t colorIndex) {
  uint8_t brightness = 255;
  for ( int i = 0; i < NUM_LEDS; ++i) {
    leds[i] = ColorFromPalette( currentPalette, colorIndex, brightness, currentBlending);
    colorIndex += 3;
  }
}


void pixelLoop() {
  static uint8_t startIndex = 0;
  startIndex = startIndex + 1; /* motion speed */
  FillLEDsFromPaletteColors( startIndex);
  FastLED.show();
  FastLED.delay(1000 / UPDATES_PER_SECOND);
}





#endif
