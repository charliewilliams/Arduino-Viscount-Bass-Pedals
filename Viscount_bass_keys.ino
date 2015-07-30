
// Bass synth controlled by organ-donor Viscount pedals.
// by Charlie Williams (@buildsucceeded)
// and Rick Hewes (@rickhewes)

// Have fun with this code, it's under a
// Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License.
// Built on Mozzi by Tim Barrass
// which is licensed under a Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License.

// Notes:
// This is written to run on the Teensyduino 3.1.
// For DAC DC offset removal on the Teensy, use a 1 to 10 uF capacitor.
// Connect the + side to DAC/A14 and the - side to your mixer's input.

#define DEBUG 1

#include <ADC.h>
#include <MozziGuts.h>

#define CONTROL_RATE 64

const static int NUM_KEYS = 13;
const static int debugMod = 1000;

void setup() {

#if DEBUG
  Serial.begin(9600);
#endif

  setupControl();
  setupAudio();
  startMozzi(CONTROL_RATE);
}

void loop() {

  audioHook();

#if DEBUG
//  debugSerial();
#endif
}

