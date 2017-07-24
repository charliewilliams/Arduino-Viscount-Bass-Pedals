
// Figure out which pedals are down
// including debouncing

const static unsigned int UINT_MAX = 65535;
const static long debounceDelay = 50; // the debounce time; increase if the output flickers
bool pedalIsDownForNote[NUM_KEYS] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
bool debounceTimes[NUM_KEYS] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

void setupControl() {

  for (int i = 0; i < NUM_KEYS; i++) {
    pinMode(i, INPUT_PULLUP);
  }
}

void updateControl() {

  if (DEBUG_AUTO_PLAY_NOTES) {
    updateDebugNote();
    return;
  }

  for (int i = 0; i < NUM_KEYS; i++) {

    bool oldValue = pedalIsDownForNote[i];

    int rawValue = digitalRead(i);
    bool value = debouncePin(i, rawValue, oldValue);

    if (oldValue != value) {

      pedalIsDownForNote[i] = value;

      if (!value) {

        // Audio
//        oscil1.setFreq(freqs[NUM_KEYS - i - 1] / octave);
//        oscil2.setFreq((freqs[NUM_KEYS - i - 1] / (octave - 1)) * octaveDetune);
//        envelope[i].noteOn();
//        noiseEnvelope.noteOn();

        // MIDI
        noteOn(i);

        // LED
        writeLED(i, true);

      } else {

        // Audio
//        envelope[i].noteOff();
//        noiseEnvelope.noteOff();

        // MIDI
        noteOff(i);

        // LED
        writeLED(0, false);
      }
    }

//    if (envelope[i].playing()) {
//      envelope[i].update();
//    }
  }

//  noiseEnvelope.update();
  //  Serial.println(envelope[0].next());
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

