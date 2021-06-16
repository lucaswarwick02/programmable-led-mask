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
CRGB red = CRGB(16, 0, 0);
CRGB green = CRGB(0, 16, 0);
CRGB blue = CRGB(0, 0, 16);
CRGB colours[4] = {white, red, green, blue};

uint8_t hue = 0;
int state;
int previousSubstate;
int period;
unsigned long startMillis;
unsigned long currentMillis;
bool pushUpdate = true;
int currentColour;

void setup() {
  // Set up LED strips
  FastLED.addLeds<WS2812, LED_PIN_1, GRB>(leds_1, NUM_LEDS);
  FastLED.addLeds<WS2812, LED_PIN_2, GRB>(leds_2, NUM_LEDS);
  FastLED.addLeds<WS2812, LED_PIN_3, GRB>(leds_3, NUM_LEDS);
  FastLED.addLeds<WS2812, LED_PIN_4, GRB>(leds_4, NUM_LEDS);
  FastLED.setBrightness(  BRIGHTNESS );
  // Sets up the IR Reciever
  Serial.begin(9600);
  irrecv.enableIRIn();
  // Set up global variables
  state = 0;
  currentColour = 1;
}

void loop () {
  // Check for state change
  if (irrecv.decode(&results)) { // have we received an IR signal?
    if (results.value == 0xFF6897) {
      Serial.println("0");
      state = 0;
      pushUpdate = true;
    }
    else if (results.value == 0xFF30CF) {
      Serial.println("1");
      state = 1;
      pushUpdate = true;
    }
    else if (results.value == 0xFF18E7) {
      Serial.println("2");
      state = 2;
      pushUpdate = true;
    }
    else if (results.value == 0xFF7A85) {
      Serial.println("3");
      state = 3;
      pushUpdate = true;
    }
    else if (results.value == 0xFF10EF) {
      Serial.println("4");
      state = 4;
      pushUpdate = true;
    }
    else if (results.value == 0xFF38C7) {
      Serial.println("5");
      state = 5;
      pushUpdate = true;
    }
    else if (results.value == 0xFFE01F) {
      Serial.println("Down Colour");
      if (currentColour - 1 < 0) {
        currentColour = 3;
      }
      else {
        currentColour -= 1;
      }
      pushUpdate = true;
    }
    else if (results.value == 0xFF906F) {
      Serial.println("Up Colour");
      if (currentColour + 1 > 4) {
        currentColour = 0;
      }
      else {
        currentColour += 1;
      }
      pushUpdate = true;
    }
    else if (results.value == 0xFFFFFF) {
      // If buttons are held down, it sends this signal
    }
    //Serial.println(results.value, HEX);
    irrecv.resume();
  }
  // Perform function
  currentMillis = millis();
  switch (state){
    case 0:
      //Serial.println("State 0: Neutral");
      period = currentMillis - startMillis;
      if (period <= 5000) {
        if (previousSubstate == 3) {
          pushUpdate = true;
        }
        if (pushUpdate) {
          neutral_0();
          pushUpdate = false;
          previousSubstate = 0;
        }
      }
      else if (period > 5000 && period <= 5100) {
        if (previousSubstate == 0) {
          pushUpdate = true;
        }
        if (pushUpdate) {
          neutral_1();
          pushUpdate = false;
          previousSubstate = 1;
        }
      }
      else if (period > 5100 && period <= 5200) {
        if (previousSubstate == 1) {
          pushUpdate = true;
        }
        if (pushUpdate) {
          neutral_2();
          pushUpdate = false;
          previousSubstate = 2;
        }
      }
      else if (period > 5200 && period <= 5300) {
        if (previousSubstate == 2) {
          pushUpdate = true;
        }
        if (pushUpdate) {
          neutral_1();
          pushUpdate = false;
          previousSubstate = 3;
        }
      }
      else {
        // Reset state 0 chain
        startMillis = millis();
      }
      break;
    case 1:
      //Serial.println("State 1: Happy");
      if (pushUpdate) {
        happy();
        pushUpdate = false;
      }
      break;
    case 2:
      //Serial.println("State 2: Sad");
      if (pushUpdate) {
        sad();
        pushUpdate = false;
      }
      break;
    case 3:
      //Serial.println("State 3: Angry");
      if (pushUpdate) {
        angry();
        pushUpdate = false;
      }
      break;
    case 4:
      //Serial.println("State 1: Dead");
      if (pushUpdate) {
        dead();
        pushUpdate = false;
      }
      break;
    case 5:
      //Serial.println("State 1: Dead");
      if (pushUpdate) {
        wipe();
        pushUpdate = false;
      }
      for (int i = 5; i < 28; i++) {
        leds_1[i] = CHSV(hue + (i * 10), 255 , 255 * 0.5);
      }
      for (int i = 3; i < 26; i++) {
        leds_2[i] = CHSV(hue + (i * 10), 255, 255 * 0.5);
      }
      for (int i = 4; i < 27; i++) {
        leds_3[i] = CHSV(hue + (i * 10), 255, 255 * 0.5);
      }
      for (int i = 3; i < 26; i++) {
        leds_4[i] = CHSV(hue + (i * 10), 255, 255 * 0.5);
      }
      EVERY_N_MILLISECONDS(2){
        hue++;
      }
      FastLED.show();
      break;
    default:
      //Serial.println("Invalid State");
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

// Middle indexes:
// leds_1 = 16
// leds_1 = 14
// leds_1 = 15
// leds_1 = 14

void neutral_0 ()  {
  wipe();
  // Row 1
  leds_1[21] = colours[currentColour];
  leds_1[22] = colours[currentColour];
  leds_1[11] = colours[currentColour];
  leds_1[10] = colours[currentColour];
  // Row 2
  leds_2[18] = colours[currentColour];
  leds_2[21] = colours[currentColour];
  leds_2[10] = colours[currentColour];
  leds_2[7] = colours[currentColour];
  // Row 3
  leds_3[19] = colours[currentColour];
  leds_3[22] = colours[currentColour];
  leds_3[11] = colours[currentColour];
  leds_3[8] = colours[currentColour];
  // Row 4
  leds_4[19] = colours[currentColour];
  leds_4[20] = colours[currentColour];
  leds_4[9] = colours[currentColour];
  leds_4[8] = colours[currentColour];
  FastLED.show();
}

void neutral_1 () {
  wipe();
  // Row 2
  leds_2[18] = colours[currentColour];
  leds_2[19] = colours[currentColour];
  leds_2[20] = colours[currentColour];
  leds_2[21] = colours[currentColour];
  leds_2[10] = colours[currentColour];
  leds_2[9] = colours[currentColour];
  leds_2[8] = colours[currentColour];
  leds_2[7] = colours[currentColour];
  // Row 3
  leds_3[19] = colours[currentColour];
  leds_3[20] = colours[currentColour];
  leds_3[21] = colours[currentColour];
  leds_3[22] = colours[currentColour];
  leds_3[11] = colours[currentColour];
  leds_3[10] = colours[currentColour];
  leds_3[9] = colours[currentColour];
  leds_3[8] = colours[currentColour];
  FastLED.show();
}

void neutral_2 () {
  wipe();
  // Row 3
  leds_3[19] = colours[currentColour];
  leds_3[20] = colours[currentColour];
  leds_3[21] = colours[currentColour];
  leds_3[22] = colours[currentColour];
  leds_3[11] = colours[currentColour];
  leds_3[10] = colours[currentColour];
  leds_3[9] = colours[currentColour];
  leds_3[8] = colours[currentColour];
  FastLED.show();
}

void happy ()  {
  Serial.println("Happy");
  wipe();
  // Row 1
  leds_1[21] = colours[currentColour];
  leds_1[11] = colours[currentColour];
  // Row 2
  leds_2[20] = colours[currentColour];
  leds_2[18] = colours[currentColour];
  leds_2[10] = colours[currentColour];
  leds_2[8] = colours[currentColour];
  // Row 3
  leds_3[22] = colours[currentColour];
  leds_3[18] = colours[currentColour];
  leds_3[12] = colours[currentColour];
  leds_3[8] = colours[currentColour];
  // Row 4
  leds_4[22] = colours[currentColour];
  leds_4[16] = colours[currentColour];
  leds_4[12] = colours[currentColour];
  leds_4[6] = colours[currentColour];
  FastLED.show();
}

void sad ()  {
  Serial.println("Sad");
  wipe();
  // Row 1
  leds_1[20] = colours[currentColour];
  leds_1[12] = colours[currentColour];
  // Row 2
  leds_2[19] = colours[currentColour];
  leds_2[9] = colours[currentColour];
  // Row 3
  leds_3[21] = colours[currentColour];
  leds_3[9] = colours[currentColour];
  // Row 4
  leds_4[21] = colours[currentColour];
  leds_4[7] = colours[currentColour];
  FastLED.show();
}

void angry ()  {
  Serial.println("Angry");
  wipe();
  // Row 1
  leds_1[22] = colours[currentColour];
  leds_1[10] = colours[currentColour];
  // Row 2
  leds_2[19] = colours[currentColour];
  leds_2[9] = colours[currentColour];
  // Row 3
  leds_3[19] = colours[currentColour];
  leds_3[11] = colours[currentColour];
  // Row 4
  leds_4[17] = colours[currentColour];
  leds_4[11] = colours[currentColour];
  FastLED.show();
}

void dead ()  {
  Serial.println("Dead");
  wipe();
  // Row 1
  leds_1[20] = colours[currentColour];
  leds_1[23] = colours[currentColour];
  leds_1[12] = colours[currentColour];
  leds_1[9] = colours[currentColour];
  // Row 2
  leds_2[19] = colours[currentColour];
  leds_2[20] = colours[currentColour];
  leds_2[9] = colours[currentColour];
  leds_2[8] = colours[currentColour];
  // Row 3
  leds_3[20] = colours[currentColour];
  leds_3[21] = colours[currentColour];
  leds_3[10] = colours[currentColour];
  leds_3[9] = colours[currentColour];
  // Row 4
  leds_4[18] = colours[currentColour];
  leds_4[21] = colours[currentColour];
  leds_4[10] = colours[currentColour];
  leds_4[7] = colours[currentColour];
  FastLED.show();
}
