// My memory game
// Lets see how it goes... ;)

int LED_COUNT = 4;
int ledPins[] = {1, 2, 3, 4}; 

void setup() {
  pinMode(ledPins[0], OUTPUT);
  pinMode(ledPins[1], OUTPUT);
  pinMode(ledPins[2], OUTPUT);
  pinMode(ledPins[3], OUTPUT);
}

void loop() {
  for(int i = 0; i < LED_COUNT; i++)
  {
      digitalWrite(ledPins[i], HIGH);
      delay(200);
      digitalWrite(ledPins[i], LOW);
      delay(200);
  }
  delay(1000);
}
