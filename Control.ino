#include <AnalogMultiButton.h>

const int BUTTONS_PIN = 14;
const int BUTTONS_TOTAL = 4;

// find out what the value of analogRead is when you press each of your buttons and put them in this array
// you can find this out by putting Serial.println(analogRead(BUTTONS_PIN)); in your loop() and opening the serial monitor to see the values
// make sure they are in order of smallest to largest
const int BUTTONS_VALUES[BUTTONS_TOTAL] = {0, 320, 495, 597};

// you can also define constants for each of your buttons, which makes your code easier to read
// define these in the same order as the numbers in your BUTTONS_VALUES array, so whichever button has the smallest analogRead() number should come first
const int OCTAVE_DOWN_BTN = 0;
const int OCTAVE_UP_BTN = 1;
const int ARROW_UP = 2;
const int ARROW_DOWN = 3;

// make an AnalogMultiButton object, pass in the pin, total and values array
AnalogMultiButton buttons(BUTTONS_PIN, BUTTONS_TOTAL, BUTTONS_VALUES);

// pass a fourth parameter to set the debounce time in milliseconds
// this defaults to 20 and can be increased if you're working with particularly bouncy buttons

//int lastMillis = 0;

void updateControls() {

//  if (millis() - lastMillis > 1000) {
//    lastMillis = millis();
//    Serial.println(analogRead(BUTTONS_PIN));
//  }

    buttons.update();
  
    if (buttons.onPress(OCTAVE_DOWN_BTN)) {
      Serial.println("Octave DOWN");
      octave--;
    }
    else if (buttons.onPress(OCTAVE_UP_BTN)) {
      Serial.println("Octave UP");
      octave++;
    }
    else if (buttons.onPress(ARROW_UP)) {
      Serial.println("UP arrow");
      Keyboard.press(KEY_UP_ARROW);
      Keyboard.release(KEY_UP_ARROW);
    }
    else if (buttons.onPress(ARROW_DOWN)) {
      Serial.println("DOWN arrow");
      Keyboard.press(KEY_DOWN_ARROW);
      Keyboard.release(KEY_DOWN_ARROW);
    }
}

