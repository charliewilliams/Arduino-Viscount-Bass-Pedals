/*
Viscount bass keys
1 octave digital control in on 13 digital pins + Ground
White keys: Digital 0-7
Black keys: Analog 0-5
Mono audio out as PWM on 1 digital pin (10)
Status RGB LED PWM on 9-10-11
Wireless TX/RX on 0-1
*/

#include <MozziGuts.h>
#include <Oscil.h>
#include <Sample.h> // Sample template
#include <samples/burroughs1_18649_int8.h> // a converted audio sample
#include <tables/sin2048_int8.h> // sine table for oscillator

// use: Oscil <table_size, update_rate> oscilName (wavetable), look in .h file of table #included above
Oscil <SIN2048_NUM_CELLS, AUDIO_RATE> aSin(SIN2048_DATA);

float freqs[13] = {32.703, 34.648, 36.708, 38.891, 41.203, 43.654, 46.249, 48.999, 51.913, 55.000, 58.270, 61.735, 64.406};
int octave = 2;
float freq;

const int LED_R = 9;
const int LED_G = 10;
const int LED_B = 11;
const int WI_TX = 1;
const int WI_RX = 0;

// Duemilanove pins are simple
void readPins() {

  int noteNum = 0;
  // white keys
  for (int i = 0; i < 8; i++) {
    int pinValue = digitalRead(i);
    if (pinValue) {
      noteNum = noteNumFromPin(i);
      break;
    }
  }

  if (!noteNum) {
    // black keys
    for (int i = 0; i < 6; i++) {
      int pinValue = mozziAnalogRead(i);
      pinValue = stateFromAnalogValue(pinValue);
      if (pinValue) {
        noteNum = noteNumFromAnalogPin(i);
        break;
      }
    }
  }

  aSin.setFreq(freqFromNoteNum(noteNum));
}

// conversions

bool stateFromAnalogValue(int analog) {
  return analog > 512;
}

int freqFromNoteNum(int noteNum) {
  return freqs[noteNum] * octave;
}

// Duemilanove pin setup (i.e. no wireless)

int noteNumFromPin(int pin) {
  if (pin < 3) { //0 1 2 = C D E
    return pin * 2;
  }
  else if (pin < 7) { // 3 4 5 6 = F G A B
    return pin * 2 + 1;
  }
  else return 12; // 7 = C
}

int noteNumFromAnalogPin(int pin) {
  if (pin < 2) { // 0 1 = Db Eb
    return pin * 2 + 1;
  } else {
    return pin * 2 + 2; // 2 3 4 = Gb Ab Bb
  }
}

// runloop

void setup() {
  Serial.begin(115200); // Debug only
  startMozzi();
}

void updateControl() {
  readPins();
}

int updateAudio() {
  return aSin.next();
}

void loop() {
  audioHook();
}
