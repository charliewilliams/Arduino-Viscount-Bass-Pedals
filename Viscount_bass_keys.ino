// Bass synth controlled by organ-donor Viscount pedals.
// by Charlie Williams (@buildsucceeded)
// and Rick Hewes (@rickhewes)
// 2015-2017

// Have fun with this code, it's under a
// Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License.

const static int NUM_KEYS = 13;
const static int baseNote = 36; // C2
static int octave = 0;
byte notePitches[NUM_KEYS];

void setup() {

  Serial.begin(9600); // 31250

  Serial.println("STARTUP CHIME: BONNNNNNNNG");

  Keyboard.begin();

  for (int i = 0; i < NUM_KEYS; i++) {
    pinMode(i, INPUT); // INPUT_PULLUP
    notePitches[i] = baseNote - i;
  }
}

void loop() {

  midiTick();
  updateControls();
  updateLED();
}

