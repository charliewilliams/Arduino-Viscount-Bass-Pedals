
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
#include <Oscil.h>
#include <tables/sin8192_int8.h>
#include <tables/smoothsquare8192_int8.h>
#include <tables/saw8192_int8.h>

static const int NUM_CELLS = 8192;
static const int8_t* SIN_DATA = SIN8192_DATA; //SIN8192_DATA; //SMOOTHSQUARE8192_DATA; //SIN8192_DATA; //SAW8192_DATA
static const int8_t* SAW_DATA = SAW8192_DATA;

#define CONTROL_RATE 64

const static int NUM_KEYS = 13;
const static int debugMod = 1000;
Oscil <NUM_CELLS, AUDIO_RATE> oscil1, oscil2;
float freqs[NUM_KEYS] = {261.626, 277.183, 293.665, 311.127, 329.628, 349.228, 369.994, 391.995, 415.305, 440.000, 466.164, 493.883, 523.251};
float octaveDetune = 1.005;
float octave = 48.0; // bigger numbers are lower, must be a power of 2 for concert tuning

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

