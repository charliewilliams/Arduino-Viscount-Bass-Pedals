// Bass synth controlled by organ-donor Viscount pedals.
// by Charlie Williams (@buildsucceeded)
// and Rick Hewes (@rickhewes)
// 2015-2017

// Have fun with this code, it's under a
// Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License.
// Built on Mozzi by Tim Barrass
// which is licensed under a Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License.

// Notes:
// This is written to run on the Teensyduino 3.1.
// For DAC DC offset removal on the Teensy, use a 1 to 10 uF capacitor.
// Connect the + side to DAC/A14 and the - side to your mixer's input.

// Mozzi stuff
//#include <ADC.h>
#include <Line.h>
#include <MozziGuts.h>
#include <Oscil.h>
#include <tables/sin8192_int8.h>
#include <tables/smoothsquare8192_int8.h>
#include <tables/saw8192_int8.h>

#define CONTROL_RATE 64

static const bool DEBUG = 0;
static const bool DEBUG_AUTO_PLAY_NOTES = 0;
static const bool AUDIO = 0;
static const bool MIDI = 1;

const static int NUM_KEYS = 13;

void setup() {

  if (DEBUG) {
    Serial.begin(9600);
  }

  setupControl();

//  if (AUDIO) {
//    setupAudio();
//    startMozzi(CONTROL_RATE);
//  }
}

void loop() {

  if (AUDIO) {
    audioHook();
  }

  if (MIDI) {
    midiTick();
  }

  updateLED();

  if (DEBUG) {
    debugSerial();
  }
}

