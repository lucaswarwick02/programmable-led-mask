#include "IRremote.h"
#include "IR.h"

IRrecv irrecv(RECEIVER);     // create instance of 'irrecv'
decode_results results;      // create instance of 'decode_results'

int expression[] = {13, 12, 11, 10, 9}; // 0 = Neutral, 1 = Happy, 2 = Sad, 3 = Angry, 4 = Shock

void setup() {
  // Sets up the IR Reciever
  Serial.begin(9600);
  Serial.println("IR Receiver Button Decode");
  irrecv.enableIRIn();
  
  for (int i = 0; i < 5; i++) {
    pinMode(expression[i], OUTPUT);
  }
}

void loop() {
  if (irrecv.decode(&results)) { // have we received an IR signal?
    switch(results.value)
    {
      case 0xFFA25D: Serial.println("POWER"); break;
      case 0xFF6897: Serial.println("0"); singleLight(0); break;
      case 0xFF30CF: Serial.println("1"); singleLight(1); break;
      case 0xFF18E7: Serial.println("2"); singleLight(2); break;
      case 0xFF7A85: Serial.println("3"); singleLight(3); break;
      case 0xFF10EF: Serial.println("4"); singleLight(4); break;
      default: break;
    } 
    irrecv.resume();
  }
}

void singleLight (int index) {
  for (int i = 0; i < 5; i++) {
    if (i == index) {
      digitalWrite(expression[i], HIGH);
    }
    else {
      digitalWrite(expression[i], LOW);
    }
  }
}
