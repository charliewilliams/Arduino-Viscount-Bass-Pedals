
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

    if (digitalRead(i) == LOW) {
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

      if (bitRead(pressedPedals, i)) {

        bitWrite(previousPedals, i , 1);
        noteOn(0, notePitches[i], intensity);
        writeLED(i, true);
      }
      else {

        bitWrite(previousPedals, i , 0);
        noteOff(0, notePitches[i], 0);
        writeLED(i, false);
      }
    }
  }
}

// First parameter is the event type (0x09 = note on, 0x08 = note off).
// Second parameter is note-on/note-off, combined with the channel.
// Channel can be anything between 0-15. Typically reported to the user as 1-16.
// Third parameter is the note number (48 = middle C).
// Fourth parameter is the velocity (64 = normal, 127 = fastest).

void noteOn(byte channel, byte pitch, byte velocity) {
  MIDI.sendNoteOn(pitch, velocity, channel);
  Serial.println("Note on: " + pitch);
}

void noteOff(byte channel, byte pitch, byte velocity) {
  MIDI.sendNoteOff(pitch, velocity, channel);
  Serial.println("Note off: " + pitch);
}
