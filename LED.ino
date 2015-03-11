
#define PIN_R 9
#define PIN_G 10
#define PIN_B 11

#define noteColor0 {255, 0, 0} // C.
#define noteColor1 {230, 126, 34}
#define noteColor2 {230, 126, 34} // D.
#define noteColor3 {142, 68, 173} //.
#define noteColor4 {241, 196, 15} // E.
#define noteColor5 {251, 191, 149} // F
#define noteColor6 {127, 127, 127}
#define noteColor7 {141, 203, 149} // G
#define noteColor8 {156, 120, 191}
#define noteColor9 {189, 184, 194} // A
#define noteColor10 {144, 91, 24}
#define noteColor11 {192, 139, 72} // B

const static int noteColors[12][3] = {noteColor0, noteColor1, noteColor2, noteColor3, noteColor4, noteColor5, noteColor6, noteColor7, noteColor8, noteColor9, noteColor10, noteColor11};
const static float brightness = 0.25;
bool noteIsOn = false;
int breathingCounter = 0;

void setupLED() {
  analogWrite(PIN_R, 0);
  analogWrite(PIN_G, 0);
  analogWrite(PIN_B, 0);
}

void writeLED(int noteNum, bool on) {

  if (!on) {
    noteIsOn = false;
    breathingCounter = 0;
    analogWrite(PIN_R, 0);
    analogWrite(PIN_G, 0);
    analogWrite(PIN_B, 0);
    return;
  }

  noteIsOn = true;
  const int *color = noteColors[noteNum % 12];

  int r = color[0];
  int g = color[1];
  int b = color[2];

  analogWrite(PIN_R, r * brightness);
  analogWrite(PIN_G, g * brightness);
  analogWrite(PIN_B, b * brightness);

#if DEBUG
  Serial.print(" r: ");
  Serial.print(r);
  Serial.print(" g: ");
  Serial.print(g);
  Serial.print(" b: ");
  Serial.println(b);
#endif

}

void updateLED() {

  if (noteIsOn) {
    return;
  }

  breathingCounter++;

  if (breathingCounter > 255) {
    breathingCounter = 0;
  }

  int level = sin(breathingCounter / 255.0);

  analogWrite(PIN_R, level);
  analogWrite(PIN_G, level);
  analogWrite(PIN_B, level);

#if DEBUG
  digitalWrite(13, level);
#endif
}

