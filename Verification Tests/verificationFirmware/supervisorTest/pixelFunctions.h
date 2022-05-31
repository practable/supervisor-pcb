
#ifndef pixelFunctions_h
#define pixelFunctions_h



#include <FastLED.h>

#include <autoDelay.h>





#define LED_PIN     5
#define NUM_LEDS    9
#define BRIGHTNESS  70
#define LED_TYPE    WS2811
#define COLOR_ORDER GRB
CRGBArray <NUM_LEDS> leds;

#define UPDATES_PER_SECOND 30
#define HUE_STEPS 5                // Number of steps to advance through palette between each for loop. Origionally 3

// This example shows several ways to set up and use 'palettes' of colors
// with FastLED.
//
// These compact palettes provide an easy way to re-colorize your
// animation on the fly, quickly, easily, and with low overhead.
//
// USING palettes is MUCH simpler in practice than in theory, so first just
// run this sketch, and watch the pretty lights as you then read through
// the code.  Although this sketch has eight (or more) different color schemes,
// the entire sketch compiles down to about 6.5K on AVR.
//
// FastLED provides a few pre-configured color palettes, and makes it
// extremely easy to make up your own color schemes with palettes.
//
// Some notes on the more abstract 'theory and practice' of
// FastLED compact palettes are at the bottom of this file.







CRGBPalette16 currentPalette;
TBlendType    currentBlending;


CRGBPalette16 nextPalette;
//TBlendType    currentBlending;

#include "pixelPalettes.h"

#define START_PALETTE hotpink_blue    // Sterile while palette to start with
//#define START_PALETTE select_palette(random(0, NUM_FX));

#define PRINT_INDEX false
#define DEBUG_DELAY false
#define DEBUG_DELAY_TIME 300

#define FADE_THROUGH_DELAY 1   // delay time between brightness changes during crossfade through black effect (millis)
#define PAUSE_BLACK_DELAY 100    // delay time to pause at black between crossfade for cleaner scene change effect

#define PROGRAM_DELAY 10   // Delay to switch progams in minuites

uint32_t transition_timer = 45;    // effect transitions are in seconds

uint16_t minutes_running;   // think this can be deleted






void fastled_setup() {
  //Serial.begin(115200);
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
  currentPalette = START_PALETTE;
  // currentPalette = select_palette(random(0, 5));
  currentBlending = LINEARBLEND;
  // nextPalette = select_palette(random(0, NUM_FX));
  nextPalette = START_PALETTE;
}




autoDelay shift_effect;


// Cycles through banks of palettes based on program type
void switchPalette() {
  if (shift_effect.secondsDelay(transition_timer)) {
    //    Serial.println("Fading into New Palette");
    currentPalette = nextPalette;
    nextPalette = select_palette(random(0, NUM_FX));
  }
}

int hue_steps = 3;

void FillLEDsFromPaletteColors( uint8_t colorIndex) {
  for ( int i = 0; i < NUM_LEDS; i++) {
    leds[i] = ColorFromPalette( currentPalette, colorIndex, BRIGHTNESS, currentBlending);
    colorIndex += hue_steps;
  }
  if (PRINT_INDEX) {
    //    Serial.print("Colour Index: [");
    //   Serial.print(colorIndex);
    //   Serial.println("]");
  }
}


uint8_t startIndex = 0;
int16_t index_addr = 1;

// Fills led buffer from palette
void apply_palette() {
  startIndex = startIndex + 1;        /* motion speed */
  FillLEDsFromPaletteColors(startIndex);
}


void pixelLoop(bool active = false) {
  if (active) {
    switchPalette();                // Switches colour palette periodically (actually only changes nextPalette, which is blended into currentPalette u
    nblendPaletteTowardPalette(currentPalette, nextPalette, 12);    // slow blend between palettes
    apply_palette();               //applies palette to LED buffer
    FastLED.show();
    FastLED.delay(1000 / UPDATES_PER_SECOND);
  }
}


#endif
