
// Figure out which pedals are down
// including debouncing

#include <ADSR.h>

long debounceDelay = 50;    // the debounce time; increase if the output flickers
bool pedalIsDownForNote[NUM_KEYS] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
bool debounceTimes[NUM_KEYS] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
ADSR <CONTROL_RATE> envelope[NUM_KEYS];


void setupControl() {

  for (int i = 0; i < NUM_KEYS; i++) {

    ADSR <CONTROL_RATE> env;// = ADSR<CONTROL_RATE>();

    env.setAttackLevel(255);
    env.setDecayLevel(127);
    env.setSustainLevel(127);
    env.setReleaseLevel(0);

    env.setAttackTime(10);
    env.setDecayTime(127);
    env.setSustainTime(65535);
    env.setReleaseTime(500);

    envelope[i] = env;
  }
}

void updateControl() {

  for (int i = 0; i < NUM_KEYS; i++) {

    ADSR <CONTROL_RATE> env = envelope[i];
    env.update(); // should this be inside the 'else' below?

    bool oldValue = pedalIsDownForNote[i];

    int rawValue = digitalRead(i);
    bool value = debouncePin(i, rawValue, oldValue);

    if (oldValue != value) {
      pedalIsDownForNote[i] = value;

      if (value) {
        env.noteOn();
      } else {
        env.noteOff();
      }
    }
  }
}

bool debouncePin(int pin, bool rawValue, bool oldValue) {

  long ms = millis();

  if (rawValue != oldValue) {
    debounceTimes[pin] = ms;
  }

  if (ms - debounceTimes[pin] > debounceDelay) {
    return rawValue;
  }
  return oldValue;
}

void debugSerial() {

  if (debugCounter % debugMod == 0) {

    for (int i = 0; i < NUM_KEYS; i++) {

      int val = pedalIsDownForNote[i];
      int time = debounceTimes[i];
      Serial.print("      " + val);
      Serial.print(": " + time);
    }

    Serial.println("");
  }

  debugCounter++;
}
