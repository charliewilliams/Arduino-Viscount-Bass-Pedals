
// Figure out which pedals are down
// including debouncing

#include <ADSR.h>

long debounceDelay = 50; // the debounce time; increase if the output flickers
bool pedalIsDownForNote[NUM_KEYS] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
bool debounceTimes[NUM_KEYS] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
ADSR <CONTROL_RATE, AUDIO_RATE> envelope[NUM_KEYS];


void setupControl() {

  for (int i = 0; i < NUM_KEYS; i++) {

    pinMode(i, INPUT);

    envelope[i] = ADSR <CONTROL_RATE, AUDIO_RATE>();

    envelope[i].setADLevels(255, 127);

    //    env.setAttackLevel(255);
    //    env.setDecayLevel(127);
    envelope[i].setSustainLevel(255);
    envelope[i].setReleaseLevel(255);

    envelope[i].setTimes(10, 250, 1000, 500);
    //        env.setTimes(0, 0, 0, 0);
    //    env.setAttackTime(10);
    //    env.setDecayTime(127);
    //    env.setSustainTime(65535);
    //    env.setReleaseTime(500);

    //    envelope[i] = env;
    envelope[i].noteOn();
  }
}

void updateControl() {

  for (int i = 0; i < NUM_KEYS; i++) {

    bool oldValue = pedalIsDownForNote[i];

    int rawValue = digitalRead(i);
    bool value = debouncePin(i, rawValue, oldValue);

    if (oldValue != value) {

      pedalIsDownForNote[i] = value;

      if (!value) {
        envelope[i].noteOn();
      } else {
        envelope[i].noteOff();
      }
    }

    envelope[i].update();
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
      //      int time = debounceTimes[i];

      String s = " " + noteNameFromPin(i) + ": " + (envelope[i].playing() ? "YES" : "no ");//!val;
      Serial.print(s);
    }

    Serial.println("");
  }

  debugCounter++;
}
