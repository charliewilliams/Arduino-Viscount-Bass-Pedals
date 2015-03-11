
// Figure out which pedals are down
// including debouncing

#include <ADSR.h>

const static long debounceDelay = 50; // the debounce time; increase if the output flickers
bool pedalIsDownForNote[NUM_KEYS] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
bool debounceTimes[NUM_KEYS] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
ADSR <CONTROL_RATE, AUDIO_RATE> envelope[NUM_KEYS];
ADSR <CONTROL_RATE, AUDIO_RATE> env = ADSR <CONTROL_RATE, AUDIO_RATE>();


void setupControl() {

  for (int i = 0; i < NUM_KEYS; i++) {

    pinMode(i, INPUT);

    envelope[i] = ADSR <CONTROL_RATE, AUDIO_RATE>();

    envelope[i].setADLevels(255, 127);
//    envelope[i].setSustainLevel(255);
//    envelope[i].setReleaseLevel(255);
    envelope[i].setTimes(10, 250, 1000, 500);

    envelope[i].noteOn();
  }
}

void updateControl() {

  bool noteOnFound = false;
  bool noteOffFound = false;

  for (int i = 0; i < NUM_KEYS; i++) {

    bool oldValue = pedalIsDownForNote[i];

    int rawValue = digitalRead(i);
    bool value = debouncePin(i, rawValue, oldValue);

    if (oldValue != value) {

      pedalIsDownForNote[i] = value;

      if (!value) {
        envelope[i].noteOn();
        noteOnFound = true;
        writeLED(i, true);
      } else {
        envelope[i].noteOff();
        noteOffFound = true;
        writeLED(0, false);
      }
    }

    envelope[i].update();
  }

  env.update();
  if (noteOnFound) {
    env.noteOn();
  } else if (noteOffFound) {
    env.noteOff();
  }
  
  updateLED();
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

