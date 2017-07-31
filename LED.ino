
#define PIN_R 21
#define PIN_G 22
#define PIN_B 23

#define noteColor0 {90, 0, 0} // C
#define noteColor1 {9, 0, 20}
#define noteColor2 {255, 15, 0} // D
#define noteColor3 {10, 0, 10}
#define noteColor4 {211, 84, 0} // E
#define noteColor5 {0, 10, 1} // F
#define noteColor6 {40, 40, 40}
#define noteColor7 {4, 50, 40} // G
#define noteColor8 {0, 7, 100}
#define noteColor9 {0, 0, 34} // A
#define noteColor10 {20, 0, 0}
#define noteColor11 {200, 0, 18} // B

//const static int whiteKeys[7][3] = {noteColor0, noteColor2, noteColor4, noteColor5, noteColor7, noteColor9, noteColor11};
const static int noteColors[12][3] = {noteColor0, noteColor1, noteColor2, noteColor3, noteColor4, noteColor5, noteColor6,
                                      noteColor7, noteColor8, noteColor9, noteColor10, noteColor11
                                     };
const static float brightness = 2.0;
const static float breathingBrightness = 30.0;
const static float breathingSpeed = 10000.0;
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
    //    breathingCounter = 0;
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
}

void updateLED() {

  if (noteIsOn) {
    return;
  }

  breathingCounter++;

  float val = (exp(sin(breathingCounter / breathingSpeed * PI)) - 0.36787944) * breathingBrightness;
  analogWrite(PIN_R, val);
  analogWrite(PIN_G, val);
  analogWrite(PIN_B, val);
}

