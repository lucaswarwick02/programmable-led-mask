// Libraries
#include <FastLED.h>
#include "IR.h"
#include "IRremote.h"

#define LED_PIN_1     10
#define LED_PIN_2     9
#define LED_PIN_3     4
#define LED_PIN_4     3
#define NUM_LEDS    28
#define BRIGHTNESS  20

IRrecv irrecv(RECEIVER);     // create instance of 'irrecv'
decode_results results;      // create instance of 'decode_results'

CRGB leds_1[NUM_LEDS];
CRGB leds_2[NUM_LEDS];
CRGB leds_3[NUM_LEDS];
CRGB leds_4[NUM_LEDS];
CRGB leds_5[3];
CRGB white = CRGB(16, 16, 16);

boolean isOn;
int state;

void setup() {
  FastLED.addLeds<WS2812, LED_PIN_1, GRB>(leds_1, NUM_LEDS);
  FastLED.addLeds<WS2812, LED_PIN_2, GRB>(leds_2, NUM_LEDS);
  FastLED.addLeds<WS2812, LED_PIN_3, GRB>(leds_3, NUM_LEDS);
  FastLED.addLeds<WS2812, LED_PIN_4, GRB>(leds_4, NUM_LEDS);
  FastLED.setBrightness(  BRIGHTNESS );

  // Sets up the IR Reciever
  Serial.begin(9600);
  irrecv.enableIRIn();
  isOn = false;
  state = 0;
}

void loop () {
  switch (state){
    case 0:
      Serial.println("State 0: Neutral");
      neutral_0();
      delay(5000);
      neutral_1();
      delay(100);
      neutral_2();
      delay(100);
      neutral_1();
      delay(100);
      break;
    case 1:
      Serial.println("State 1: Happy");
      break;
    default:
      Serial.println("Invalid State");
      break;
  }
}

void wipe () {
  for (int i = 0; i < NUM_LEDS; i++) {
    leds_1[i] = CRGB(0, 0, 0);
    leds_2[i] = CRGB(0, 0, 0);
    leds_3[i] = CRGB(0, 0, 0);
    leds_4[i] = CRGB(0, 0, 0);
  }
  FastLED.show();
}

void turnOn ()  {
  wipe();
  isOn = true;
  neutral_0();
}

void turnOff ()  {
  wipe();
  isOn = false;
}

// Middle indexes:
// leds_1 = 16
// leds_1 = 14
// leds_1 = 15
// leds_1 = 14

void neutral_0 ()  {
  wipe();
  // Row 1
  leds_1[21] = white;
  leds_1[22] = white;
  leds_1[11] = white;
  leds_1[10] = white;
  // Row 2
  leds_2[18] = white;
  leds_2[21] = white;
  leds_2[10] = white;
  leds_2[7] = white;
  // Row 3
  leds_3[19] = white;
  leds_3[22] = white;
  leds_3[11] = white;
  leds_3[8] = white;
  // Row 4
  leds_4[19] = white;
  leds_4[20] = white;
  leds_4[9] = white;
  leds_4[8] = white;
  FastLED.show();
}

void neutral_1 () {
  wipe();
  // Row 2
  leds_2[18] = white;
  leds_2[19] = white;
  leds_2[20] = white;
  leds_2[21] = white;
  leds_2[10] = white;
  leds_2[9] = white;
  leds_2[8] = white;
  leds_2[7] = white;
  // Row 3
  leds_3[19] = white;
  leds_3[20] = white;
  leds_3[21] = white;
  leds_3[22] = white;
  leds_3[11] = white;
  leds_3[10] = white;
  leds_3[9] = white;
  leds_3[8] = white;
  FastLED.show();
}

void neutral_2 () {
  wipe();
  // Row 3
  leds_3[19] = white;
  leds_3[20] = white;
  leds_3[21] = white;
  leds_3[22] = white;
  leds_3[11] = white;
  leds_3[10] = white;
  leds_3[9] = white;
  leds_3[8] = white;
  FastLED.show();
}
