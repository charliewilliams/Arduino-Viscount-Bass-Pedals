
static int intensity = 64;

const static long debounceDelay = 50; // the debounce time; increase if the output flickers

uint16_t pressedPedals = 0x00;
uint16_t previousPedals = 0x00;
uint16_t debounceTimes = 0x00;

void midiTick() {

  readPedals();
  readIntensity();
  playNotes();
}

void readPedals() {

  for (int i = 0; i < NUM_KEYS; i++) {

    if (digitalRead(i) == HIGH) {
      bitWrite(pressedPedals, i, 1);
      delay(50);
    }
    else {
      bitWrite(pressedPedals, i, 0);
    }
  }
}

// TODO future expansion
void readIntensity() {
  
  //  int val = analogRead(intensityPot);
  //  intensity = (uint8_t) (map(val, 0, 1023, 0, 127));
}

void playNotes() {

  for (int i = 0; i < NUM_KEYS; i++) {

    if (bitRead(pressedPedals, i) != bitRead(previousPedals, i)) {

      int note = notePitches[i] + octave * 12;

      if (bitRead(pressedPedals, i)) {

        bitWrite(previousPedals, i , 1);
        usbMIDI.sendNoteOn(note, intensity, 1);
        MIDI.sendNoteOn(note, intensity, 0);
        Serial.print("Note on: "); Serial.print(i); Serial.print(" / "); Serial.println(notePitches[i]);
        writeLED(i, true);
      }
      else {

        bitWrite(previousPedals, i , 0);
        usbMIDI.sendNoteOff(note, intensity, 1);
        MIDI.sendNoteOff(note, intensity, 0);
        Serial.print("Note off: "); Serial.print(i); Serial.print(" / "); Serial.println(notePitches[i]);
        writeLED(i, false);
      }
    }
  }
}

