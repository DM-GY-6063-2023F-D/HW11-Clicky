#include "Clicky.h"

int NO_STATE = 0;
int RED_STATE = 1;
int BLUE_STATE = 2;

Clicky mButton0;
Clicky mButton1;

int cState = NO_STATE;

void setup() {
  // inputs
  mButton0.setup(2);
  mButton1.setup(3);

  // outputs
  pinMode(6, OUTPUT);
  pinMode(7, OUTPUT);
}

void loop() {
  // read input clicks
  bool b0c = mButton0.wasClicked();
  bool b1c = mButton1.wasClicked();

  // state transitions
  if (cState == NO_STATE) {
    if (b0c) {
      cState = BLUE_STATE;
    } else if (b1c) {
      cState = RED_STATE;
    }
  }

  else if (cState == RED_STATE) {
    if (b0c) {
      cState = BLUE_STATE;
    } else if (b1c) {
      cState = NO_STATE;
    }
  }

  else if (cState == BLUE_STATE) {
    if (b0c) {
      cState = NO_STATE;
    } else if (b1c) {
      cState = RED_STATE;
    }
  }

  // output logic
  int blinkVal = (millis() / 200) % 2;

  if (cState == RED_STATE) {
    digitalWrite(6, blinkVal);
    digitalWrite(7, LOW);
  } else if (cState == BLUE_STATE) {
    digitalWrite(6, LOW);
    digitalWrite(7, blinkVal);
  } else {
    digitalWrite(6, LOW);
    digitalWrite(7, LOW);
  }

  delay(10);
}
