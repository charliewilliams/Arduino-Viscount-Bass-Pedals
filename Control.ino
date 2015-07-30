
// Figure out which pedals are down
// including debouncing

#include <ADSR.h>
#include <mozzi_rand.h>

const static unsigned int UINT_MAX = 65535;
const static long debounceDelay = 50; // the debounce time; increase if the output flickers
bool pedalIsDownForNote[NUM_KEYS] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
bool debounceTimes[NUM_KEYS] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
ADSR <CONTROL_RATE, AUDIO_RATE> envelope[NUM_KEYS];
ADSR <CONTROL_RATE, AUDIO_RATE> noiseEnvelope;

void setupControl() {

  for (int i = 0; i < NUM_KEYS; i++) {

    pinMode(i, INPUT);

    envelope[i] = ADSR <CONTROL_RATE, AUDIO_RATE>();

    envelope[i].setAttackLevel(255);
    envelope[i].setDecayLevel(127);
    envelope[i].setSustainLevel(64);
    envelope[i].setReleaseLevel(0);
    envelope[i].setTimes(50, 100, UINT_MAX, 750);
    envelope[i].noteOff(); // or else you start with a bang
  }

  noiseEnvelope = ADSR <CONTROL_RATE, AUDIO_RATE>();

  noiseEnvelope.setAttackLevel(255);
  noiseEnvelope.setDecayLevel(10);
  noiseEnvelope.setSustainLevel(0);
  noiseEnvelope.setReleaseLevel(0);
  noiseEnvelope.setTimes(50, 50, 50, 50);
  noiseEnvelope.noteOff(); // or else you start with a bang
}

void updateControl() {

#if DEBUG
  updateDebugNote();
  return;
#endif

//  bool noteOnFound = false;
//  bool noteOffFound = false;

  for (int i = 0; i < NUM_KEYS; i++) {

    bool oldValue = pedalIsDownForNote[i];

    int rawValue = digitalRead(i);
    bool value = debouncePin(i, rawValue, oldValue);

    if (oldValue != value || envelope[i].playing()) {

      pedalIsDownForNote[i] = value;

      if (!value) {
        oscil1.setFreq(freqs[NUM_KEYS - i - 1] / octave);
        oscil2.setFreq((freqs[NUM_KEYS - i - 1] / (octave - 1)) * octaveDetune);
        envelope[i].noteOn();
        noiseEnvelope.noteOn();
        writeLED(i, true);
      } else {
        envelope[i].noteOff();
        noiseEnvelope.noteOff();
        writeLED(0, false);
      }
    }

    envelope[i].update();
  }

  noiseEnvelope.update();
  //  Serial.println(envelope[0].next());
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

/* DEBUG NOTE AUTO-PLAY */

int debugTimer = 0;
bool debugNoteOn = false;
int debugNoteDuration = 50;
int debugNote = 0;

void updateDebugNote() {

  debugTimer++;

  if (debugTimer > debugNoteDuration) {

    debugTimer = 0;
    debugNoteOn = !debugNoteOn;

    if (debugNoteOn) {

      envelope[debugNote].noteOn();
      oscil1.setFreq(freqs[NUM_KEYS - debugNote - 1] / octave);
      oscil2.setFreq(freqs[NUM_KEYS - debugNote - 1] / octave * octaveDetune);
      noiseEnvelope.noteOn();
      Serial.print(debugNote);
      Serial.println(" ON");

    } else {

      envelope[debugNote].noteOff();
      noiseEnvelope.noteOff();
      Serial.print(debugNote);
      Serial.println(" OFF");
      debugNote++;
      if (debugNote >= NUM_KEYS) {
        debugNote = 0;
      }

    }
  }

  if (debugNoteOn) {
    envelope[debugNote].update();
    noiseEnvelope.update();
  }

  for (int i = 0; i < NUM_KEYS; i++) {
    if (envelope[i].playing()) {
      envelope[i].update();
    }

  }

  if (noiseEnvelope.playing()) {
    noiseEnvelope.update();
  }
}
