
static int debugCounter = 0;
const static int debugMod = 1000;

String noteNameFromPin(int pin) {
  char names[12][3] = {"C ", "C#", "D ", "Eb", "E ", "F ", "F#", "G ", "Ab", "A ", "Bb", "B "};
  return names[pin % 12];

}

void debugSerial() {

  if (debugCounter % debugMod == 0) {

    for (int i = 0; i < NUM_KEYS; i++) {

      int val = pedalIsDownForNote[i];
      //      int time = debounceTimes[i];

//      String s = " " + noteNameFromPin(i) + ": " + !val + " " + (envelope[i].playing() ? "YES" : "no ");
//      Serial.print(s);
    }

    Serial.println("");
  }

  debugCounter++;
}
