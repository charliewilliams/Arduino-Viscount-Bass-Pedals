
#include <frequencyToNote.h>
#include <MIDIUSB.h>
#include <pitchToNote.h>

static int intensity = 64;
const byte notePitches[NUM_KEYS] = {pitchC3, pitchD3b, pitchD3, pitchE3b, pitchE3, pitchF3, pitchG3b, pitchG3, pitchA3b, pitchA3, pitchB3b, pitchB3, pitchC4};

void midiTick() {

  readPedals();
  readIntensity();
  playNotes();
}

void readPedals() {
  
  for (int i = 0; i < NUM_KEYS; i++) {
    
    if (digitalRead(i) == LOW) {
      bitWrite(pressedButtons, i, 1);
      delay(50);
    }
    else {
      bitWrite(pressedButtons, i, 0);
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

    if (bitRead(pressedButtons, i) != bitRead(previousButtons, i)) {

      if (bitRead(pressedButtons, i)) {

        bitWrite(previousButtons, i , 1);
        noteOn(0, notePitches[i], intensity);
        MidiUSB.flush();
      }
      else {

        bitWrite(previousButtons, i , 0);
        noteOff(0, notePitches[i], 0);
        MidiUSB.flush();
      }
    }
  }
}

// First parameter is the event type (0x09 = note on, 0x08 = note off).
// Second parameter is note-on/note-off, combined with the channel.
// Channel can be anything between 0-15. Typically reported to the user as 1-16.
// Third parameter is the note number (48 = middle C).
// Fourth parameter is the velocity (64 = normal, 127 = fastest).

void noteOn(byte pedalNum) {
  noteOn(0, , intensity);
}

void noteOff(byte pedalNum) {
  noteOff(0, , intensity);
}

void noteOn(byte channel, byte pitch, byte velocity) {
  midiEventPacket_t noteOn = {0x09, 0x90 | channel, pitch, velocity};
  MidiUSB.sendMIDI(noteOn);
}

void noteOff(byte channel, byte pitch, byte velocity) {
  midiEventPacket_t noteOff = {0x08, 0x80 | channel, pitch, velocity};
  MidiUSB.sendMIDI(noteOff);
}
