
const int channel = 1;
const int note = 64;
const int velocity = 100;

const int durationMillis = 500;


static boolean onUSB = true;
static boolean testNoteIsOn = false;
static int lastEventMillis = 0;

// Alernates sending a note to usb & midi interface.
// The notes are a half-step apart
void midiTest() {

  if (millis() - lastEventMillis > durationMillis) {

    lastEventMillis = millis();
    testNoteIsOn = !testNoteIsOn;

    if (testNoteIsOn) {

      if (onUSB) {
        midiTestUSB(true);
      } else {
        midiTestInterface(true);
      }

    } else {

      if (onUSB) {
        midiTestUSB(false);
      } else {
        midiTestInterface(false);
      }

      onUSB = !onUSB;
    }
  }
}

void midiTestUSB(boolean turnOn) {

//  while (usbMIDI.read()) {};
//
//  if (turnOn) {
//
//    Serial.println("NoteOn USB");
//    usbMIDI.sendNoteOn(note, velocity, channel);
//    digitalWrite(board_led, HIGH);
//
//  } else {
//
//    Serial.println("NoteOff USB");
//    usbMIDI.sendNoteOff(note, velocity, channel);
//    digitalWrite(board_led, LOW);
//  }
}


void midiTestInterface(boolean turnOn) {

  while (MIDI.read()) {};

  if (turnOn) {

    Serial.println("NoteOn MIDI");
    MIDI.sendNoteOn(note + 1, velocity, channel);
    digitalWrite(board_led, HIGH);

  } else {

    Serial.println("NoteOff MIDI");
    MIDI.sendNoteOff(note + 1, velocity, channel);
    digitalWrite(board_led, LOW);
  }
}

