/* DEBUG NOTE AUTO-PLAY */

int debugTimer = 0;
bool debugNoteOn = false;
int debugNoteDuration = 50;
int debugNote = 0;

void updateDebugNote() {

  debugTimer++;

  if (debugTimer > debugNoteDuration) {

    debugTimer = 0;
    debugNoteOn = !debugNoteOn;

    if (debugNoteOn) {

//      envelope[debugNote].noteOn();
      //      oscil1.setFreq(freqs[NUM_KEYS - debugNote - 1] / octave);
      //      oscil2.setFreq(freqs[NUM_KEYS - debugNote - 1] / octave * octaveDetune);
      //      noiseEnvelope.noteOn();
      Serial.print(debugNote);
      Serial.println(" ON");

    } else {

//      envelope[debugNote].noteOff();
//      noiseEnvelope.noteOff();
//      Serial.print(debugNote);
//      Serial.println(" OFF");
      debugNote++;
      if (debugNote >= NUM_KEYS) {
        debugNote = 0;
      }

    }
  }

//  if (debugNoteOn) {
//    envelope[debugNote].update();
//    noiseEnvelope.update();
//  }

//  for (int i = 0; i < NUM_KEYS; i++) {
//    if (envelope[i].playing()) {
//      envelope[i].update();
//    }
//  }

//  if (noiseEnvelope.playing()) {
//    noiseEnvelope.update();
//  }
}
