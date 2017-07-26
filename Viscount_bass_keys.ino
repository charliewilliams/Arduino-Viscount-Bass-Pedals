// Bass synth controlled by organ-donor Viscount pedals.
// by Charlie Williams (@buildsucceeded)
// and Rick Hewes (@rickhewes)
// 2015-2017

// Have fun with this code, it's under a
// Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License.

#include <MIDI.h>
MIDI_CREATE_DEFAULT_INSTANCE();

const static int NUM_KEYS = 13;
const static int baseNote = 36; // C2
byte notePitches[NUM_KEYS];

void setup() {

  MIDI.begin();
  Serial.begin(9600);

  Serial.println("HELLO WORLD");

  for (int i = 0; i < NUM_KEYS; i++) {
    pinMode(i, INPUT); // INPUT_PULLUP
    notePitches[i] = baseNote + i;
  }
}

void loop() {

  midiTick();
  updateLED();
}

