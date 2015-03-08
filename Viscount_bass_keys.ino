
//#define AUDIO_MODE HIFI

#include <MozziGuts.h>

#define CONTROL_RATE 64

const static int NUM_KEYS = 13;
static int debugCounter = 0;
const static int debugMod = 1000;

void setup() {

  Serial.begin(9600);
  setupControl();
  setupAudio();
  startMozzi(CONTROL_RATE);
}

void loop() {

  audioHook();
  debugSerial();
}

