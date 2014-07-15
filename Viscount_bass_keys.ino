
void setup() {

  for (int i = 0; i < 7; i++) {
    pinMode(i, INPUT);
  }

  pinMode(7, OUTPUT);

  int value = 1024;

  analogWrite(A0, value);
  analogWrite(A1, value);
  analogWrite(A2, value);
  analogWrite(A3, value);
  analogWrite(A4, value);
  analogWrite(A5, value);
  analogWrite(A6, value);
  analogWrite(A7, 1024 - value);

  Serial.begin(9600);
}

void loop() {
  const static int threshold = 750;
  static int i = 0;
  int pinValue = analogRead(i);

  String string = "";
  string += i;
  string += ":";
  string += pinValue;
  string += "    ";
  string += "   ";

//  if (pinValue < threshold) {
    Serial.print(string);
//  } else {
//    Serial.print("        ");
//  }

  if (i++ >= 8) {
    Serial.println("");
    i = 0;
  }
}

int noteNumFromPin(int pin) {

  static const int whiteKeys[] = {0, 2, 4, 5, 7, 9, 12};
  return whiteKeys[pin];
}
