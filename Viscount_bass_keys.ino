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
Oscil <SIN2048_NUM_CELLS, AUDIO_RATE> s0(SIN2048_DATA), s1(SIN2048_DATA), s2(SIN2048_DATA), s3(SIN2048_DATA), s4(SIN2048_DATA), s5(SIN2048_DATA), s6(SIN2048_DATA), s7(SIN2048_DATA), s8(SIN2048_DATA), s9(SIN2048_DATA), s10(SIN2048_DATA), s11(SIN2048_DATA), s12(SIN2048_DATA);
Oscil <SIN2048_NUM_CELLS, AUDIO_RATE>sins[13] = {s0, s1, s2, s3, s4, s5, s6, s7, s8};
float freqs[13] = {32.703, 34.648, 36.708, 38.891, 41.203, 43.654, 46.249, 48.999, 51.913, 55.000, 58.270, 61.735, 64.406};
int octave = 2;
Oscil <SIN2048_NUM_CELLS, AUDIO_RATE> monoSin(SIN2048_DATA);

const int LED_R = 9;
const int LED_G = 10;
const int LED_B = 11;
const int WI_TX = 1;
const int WI_RX = 0;

// Duemilanove pins are simple
void readPins() {

  int noteNum = 0;
  // white keys

  static int i = 1;

  int pinValue = analogRead(i);
  String string = "";
  string += i;
  string += ":";
  string += pinValue;
  string += "    ";
  string += "   ";

  if (pinValue < 500) {
    Serial.print(string);
  } else {
    Serial.print("        ");
  }

  if (i++ >= 8) {
    Serial.println("");
    i = 1;
  }

  //    if (pinValue == HIGH) {
  //      noteNum = noteNumFromPin(i);
  //      break;
  //    }

  //  if (!noteNum) {
  //    // black keys
  //    for (int i = 0; i < 6; i++) {
  //      int pinValue = mozziAnalogRead(i);
  //      pinValue = stateFromAnalogValue(pinValue);
  //      if (pinValue) {
  //        noteNum = noteNumFromAnalogPin(i);
  //        break;
  //      }
  //    }
  //  }
  //
  //  if (noteNum) {
  //   Serial.println(noteNum);
  //  }

  monoSin.setFreq(freqFromNoteNum(noteNum));
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
  else if (pin == 7) {
    return 12; // 7 = C
  }
  return 0;
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

  for (int i = 0; i < 7; i++) {
    pinMode(i, INPUT);
  }

  pinMode(7, OUTPUT);

  int value = 1024;

  analogWrite(A0, value);
  analogWrite(A1, value);
  analogWrite(A2, value);
  analogWrite(A3, value);
  analogWrite(A4, value);
  analogWrite(A5, value);
  analogWrite(A6, value);
  analogWrite(A7, 1024 - value);

  for (int i = 0; i < 13; i++) {
    sins[i].setFreq(freqs[i]);
  }
  Serial.begin(115200); // Debug only
  startMozzi();
}

void updateControl() {
  updateLED();
  readPins();
}

int updateAudio() {
  return monoSin.next();
}

void loop() {
  audioHook();
}

// RGB LED madness

int r, g, b; // LED
void updateLED() {
  r++;
  g += 2;
  b -= 3;
  analogWrite(LED_R, r);
  analogWrite(LED_G, g);
  analogWrite(LED_B, b);
  //  Serial.write("RGB: ");
  //  Serial.write(r);
  //  Serial.write("\n");// + r + " " + g + " " + b);
}
