#include <FastLED.h>
#include "IR.h"
#include "IRremote.h"

#define LED_PIN_1     10
#define LED_PIN_2     9
#define LED_PIN_3     4
#define LED_PIN_4     3
#define NUM_LEDS    28
#define BRIGHTNESS  20
#define NUM_STRIPS 2

IRrecv irrecv(RECEIVER);     // create instance of 'irrecv'
decode_results results;      // create instance of 'decode_results'

CRGB leds_1[NUM_LEDS];
CRGB leds_2[NUM_LEDS];
CRGB leds_3[NUM_LEDS];
CRGB leds_4[NUM_LEDS];
CRGB leds_5[3];

boolean isOn;
CRGB white = CRGB(128, 128, 128);
CRGB green = CRGB(0, 128, 0);
CRGB blue = CRGB(0, 0, 128);
CRGB red = CRGB(128, 0, 0);
CRGB yellow = CRGB(128, 128, 0);
CRGB gray = CRGB(32, 32, 32);

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
  neutral();
}

/*
void loop() {
  if (irrecv.decode(&results)) { // have we received an IR signal?
    if (isOn) {
      switch(results.value) {
        case 0xFFA25D: 
          turnOff();
          break;
        case 0xFF6897:
          neutral();
        break;
        case 0xFF30CF:
          happy();
          break;
        case 0xFF18E7:
          sad();
          break;
        case 0xFF7A85:
          angry();
          break;
        case 0xFF10EF:
          dead();
          break;
        default:
          break;
      }
    }
    else {
      // Off, only allow turnOn()
      switch(results.value) {
        case 0xFFA25D: 
          turnOn();
          break;
      }
    }
    irrecv.resume();
  }
}
*/

void loop () {
  neutral();
  delay(2500);
  happy();
  delay(2500);
  sad();
  delay(2500);
  angry();
  delay(2500);
  dead();
  delay(2500);
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
  Serial.println("Turn on");
  wipe();
  isOn = true;
  neutral();
}

void turnOff ()  {
  Serial.println("Turn off");
  wipe();
  isOn = false;
}

// Middle indexes:
// leds_1 = 16
// leds_1 = 14
// leds_1 = 15
// leds_1 = 14

void neutral ()  {
  Serial.println("Neutral");
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

void happy ()  {
  Serial.println("Happy");
  wipe();
  // Row 1
  leds_1[21] = green;
  leds_1[11] = green;
  // Row 2
  leds_2[20] = green;
  leds_2[18] = green;
  leds_2[10] = green;
  leds_2[8] = green;
  // Row 3
  leds_3[22] = green;
  leds_3[18] = green;
  leds_3[12] = green;
  leds_3[8] = green;
  // Row 4
  leds_4[22] = green;
  leds_4[16] = green;
  leds_4[12] = green;
  leds_4[6] = green;
  FastLED.show();
}

void sad ()  {
  Serial.println("Sad");
  wipe();
  // Row 1
  leds_1[20] = blue;
  leds_1[12] = blue;
  // Row 2
  leds_2[19] = blue;
  leds_2[9] = blue;
  // Row 3
  leds_3[21] = blue;
  leds_3[9] = blue;
  // Row 4
  leds_4[21] = blue;
  leds_4[7] = blue;
  FastLED.show();
}

void angry ()  {
  Serial.println("Angry");
  wipe();
  // Row 1
  leds_1[22] = red;
  leds_1[10] = red;
  // Row 2
  leds_2[19] = red;
  leds_2[9] = red;
  // Row 3
  leds_3[19] = red;
  leds_3[11] = red;
  // Row 4
  leds_4[17] = red;
  leds_4[11] = red;
  FastLED.show();
}

void dead ()  {
  Serial.println("Dead");
  wipe();
  // Row 1
  leds_1[20] = gray;
  leds_1[23] = gray;
  leds_1[12] = gray;
  leds_1[9] = gray;
  // Row 2
  leds_2[19] = gray;
  leds_2[20] = gray;
  leds_2[9] = gray;
  leds_2[8] = gray;
  // Row 3
  leds_3[20] = gray;
  leds_3[21] = gray;
  leds_3[10] = gray;
  leds_3[9] = gray;
  // Row 4
  leds_4[18] = gray;
  leds_4[21] = gray;
  leds_4[10] = gray;
  leds_4[7] = gray;
  FastLED.show();
}
