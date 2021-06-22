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
  currentColour = 0;
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
    else if (results.value == 0xFF5AA5) {
      Serial.println("6");
      state = 6;
      pushUpdate = true;
    }
    else if (results.value == 0xFF42BD) {
      Serial.println("7");
      state = 7;
      pushUpdate = true;
    }
    else if (results.value == 0xFF4AB5) {
      Serial.println("8");
      state = 8;
      pushUpdate = true;
    }
    else if (results.value == 0xFF52AD) {
      Serial.println("9");
      state = 9;
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
    Serial.println(results.value, HEX);
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
    case 6:
      //Serial.println("State 7: Ben");
      if (pushUpdate) {
        ben();
        pushUpdate = false;
      }
      break;
    case 7:
      //Serial.println("State 8: Exclamation");
      if (pushUpdate) {
        exclamation();
        pushUpdate = false;
      }
      break;
    case 8:
      //Serial.println("State 9: ???");
      if (pushUpdate) {
        // TODO
        pushUpdate = false;
      }
      break;
    case 9:
      //Serial.println("State 10: ???");
      if (pushUpdate) {
        // TODO
        pushUpdate = false;
      }
      break;
    default:
      //Serial.println("Invalid State");
      break;
  }
}

void setLED(int row, int index) {
  switch (row) {
    case 1:
      leds_1[index] = colours[currentColour];
      break;
    case 2:
      leds_2[index] = colours[currentColour];
      break;
    case 3:
      leds_3[index] = colours[currentColour];
      break;
    case 4:
      leds_4[index] = colours[currentColour];
      break;
    default:
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

void neutral_0 () {
  wipe();
  // Row 1
  setLED(1, 10);
  setLED(1, 11);
  setLED(1, 21);
  setLED(1, 22);
  // Row 2
  setLED(2, 7);
  setLED(2, 10);
  setLED(2, 18);
  setLED(2, 21);
  // Row 3
  setLED(3, 8);
  setLED(3, 11);
  setLED(3, 19);
  setLED(3, 22);
  // Row 4
  setLED(4, 8);
  setLED(4, 9);
  setLED(4, 19);
  setLED(4, 20);
  FastLED.show();
}

void neutral_1 () {
  wipe();
  // Row 2
  setLED(2, 7);
  setLED(2, 8);
  setLED(2, 9);
  setLED(2, 10);
  setLED(2, 18);
  setLED(2, 19);
  setLED(2, 20);
  setLED(2, 21);
  // Row 3
  setLED(3, 8);
  setLED(3, 9);
  setLED(3, 10);
  setLED(3, 11);
  setLED(3, 19);
  setLED(3, 20);
  setLED(3, 21);
  setLED(3, 22);
  FastLED.show();
}

void neutral_2 () {
  wipe();
  // Row 3
  setLED(3, 8);
  setLED(3, 9);
  setLED(3, 10);
  setLED(3, 11);
  setLED(3, 19);
  setLED(3, 20);
  setLED(3, 21);
  setLED(3, 22);
  FastLED.show();
}

void happy () {
  wipe();
  // Row 1
  setLED(1, 11);
  setLED(1, 21);
  // Row 2
  setLED(2, 8);
  setLED(2, 10);
  setLED(2, 18);
  setLED(2, 20);
  // Row 3
  setLED(3, 8);
  setLED(3, 12);
  setLED(3, 18);
  setLED(3, 22);
  // Row 4
  setLED(4, 6);
  setLED(4, 12);
  setLED(4, 16);
  setLED(4, 22);
  FastLED.show();
}

void sad () {
  wipe();
  // Row 1
  setLED(1, 12);
  setLED(1, 20);
  // Row 2
  setLED(2, 9);
  setLED(2, 19);
  // Row 3
  setLED(3, 9);
  setLED(3, 21);
  // Row 4
  setLED(4, 7);
  setLED(4, 21);
  FastLED.show();
}

void angry () {
  wipe();
  // Row 1
  setLED(1, 9);
  setLED(1, 23);
  // Row 2
  setLED(2, 8);
  setLED(2, 20);
  // Row 3
  setLED(3, 10);
  setLED(3, 20);
  // Row 4
  setLED(4, 10);
  setLED(4, 18);
  FastLED.show();
}

void dead () {
  wipe();
  // Row 1
  setLED(1, 9);
  setLED(1, 12);
  setLED(1, 20);
  setLED(1, 23);
  // Row 2
  setLED(2, 8);
  setLED(2, 9);
  setLED(2, 19);
  setLED(2, 20);
  // Row 3
  setLED(3, 9);
  setLED(3, 10);
  setLED(3, 20);
  setLED(3, 21);
  // Row 4
  setLED(4, 7);
  setLED(4, 10);
  setLED(4, 18);
  setLED(4, 21);
  FastLED.show();
}

void ben () {
  Serial.println("Ben");
  wipe();
  // For my loving friend, Ben 
  // Row 1
  setLED(1, 8);
  setLED(1, 10);
  setLED(1, 14);
  setLED(1, 18);
  setLED(1, 21);
  setLED(1, 22);
  setLED(1, 23);
  setLED(1, 24);
  // Row 2
  setLED(2, 5);
  setLED(2, 7);
  setLED(2, 9);
  setLED(2, 12);
  setLED(2, 16);
  setLED(2, 23);
  // Row 3
  setLED(3, 6);
  setLED(3, 8);
  setLED(3, 10);
  setLED(3, 13);
  setLED(3, 17);
  setLED(3, 24);
  // Row 4
  setLED(4, 5);
  setLED(4, 7);
  setLED(4, 9);
  setLED(4, 13);
  setLED(4, 14);
  setLED(4, 15);
  setLED(4, 19);
  setLED(4, 20);
  setLED(4, 21);
  setLED(4, 22);
  FastLED.show();
}

void exclamation () {
  wipe();
  // Row 1
  setLED(1, 10);
  setLED(1, 11);
  setLED(1, 21);
  setLED(1, 22);
  // Row 2
  setLED(2, 8);
  setLED(2, 9);
  setLED(2, 19);
  setLED(2, 20);
  // Row 4
  setLED(4, 8);
  setLED(4, 9);
  setLED(4, 19);
  setLED(4, 20);
  FastLED.show();
}
