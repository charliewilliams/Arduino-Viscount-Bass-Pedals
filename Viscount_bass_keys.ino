
#include <ADC.h>
#include <MozziGuts.h>

#define CONTROL_RATE 64

const static int NUM_KEYS = 13;
static int debugCounter = 0;
const static int debugMod = 1000;

void setup() {

  /* IF DEBUG */
  Serial.begin(9600);
  /* ENDIF */
  
  setupControl();
  setupAudio();
  startMozzi(CONTROL_RATE);
}

void loop() {

  audioHook();

  /* IF DEBUG */
  debugSerial();
  /* ENDIF */
}

