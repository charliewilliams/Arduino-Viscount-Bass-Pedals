// Bass synth controlled by organ-donor Viscount pedals.
// by Charlie Williams (@buildsucceeded)
// and Rick Hewes (@rickhewes)
// 2015-2018

// Have fun with this code, it's under a
// Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License.

#include <MIDI.h>
MIDI_CREATE_DEFAULT_INSTANCE();


const static int NUM_KEYS = 13;
const static int pinMap[NUM_KEYS] = {12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0};
static byte notePitches[NUM_KEYS];
const static int baseNote = 36; // C2
static int octave = 0;

void setup() {

  MIDI.begin();
  Serial.begin(31250);
  Serial.println("STARTUP CHIME: BONNNNNNNNG");
//  Keyboard.begin();

  for (int i = 0; i < NUM_KEYS; i++) {
    int pin = pinMap[i];
    pinMode(pin, INPUT_PULLDOWN);
    notePitches[i] = baseNote - i;
  }

  setupControls();
  setupLED();
}

void loop() {

  midiTick();
  updateControls();
  updateLED();

//  midiTest();
}

