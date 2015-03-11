

//probably just use a 1 to 10 uF capacitor. Connect the + side to DAC/A14 and the - side to your mixer's input.

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
  debugSerial();
#endif
}

