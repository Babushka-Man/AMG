// My memory game
// Lets see how it goes... ;)

class Game {
  int patternLength = 0;
  int* pattern = nullptr;

public:
  void reset(){
    patternLength = 0;
    free(pattern);
    pattern = nullptr;
  }

  void setConstantPatternLength(int length){
    patternLength = length;
  }

  int* getPattern(){
    if(pattern != nullptr)
    {
      pattern = malloc(patternLength * sizeof(int));
    }
    for(int i = 0; i < patternLength; i++)
    {
      pattern[i] = rand() % 4;
    }
    return pattern;
  }

  int getCurrPaternLength(){
    return patternLength;
  }

};

int LED_COUNT = 4;
int BUTTON_COUNT = LED_COUNT;
int ledPins[] = {1, 2, 3, 4}; 
int buttonPins[] = {9, 10, 12, 13};

Game theGame = Game();
int* pattern;

void setup() {
  Serial.begin(9600);
  
  for(int i = 0; i < LED_COUNT; i++){
    pinMode(ledPins[i], OUTPUT);
  }

  for(int i = 0; i < LED_COUNT; i++){
    pinMode(buttonPins[i], INPUT);
  }

  theGame.setConstantPatternLength(4);
  pattern = theGame.getPattern();
}

void loop() {
  for(int i = 0; i < theGame.getCurrPaternLength(); i++)
  {
    digitalWrite(ledPins[pattern[i]], HIGH);
    delay(200);
    digitalWrite(ledPins[pattern[i]], LOW);
    delay(200);
  }
  
  while (true) {
    for(int i = 0; i < BUTTON_COUNT; i++)
    {
      if(digitalRead(buttonPins[i]) == HIGH)
      {
        String logMsg = "Button " + String(buttonPins[i]) + " was pressed";
        Serial.println(logMsg);
        delay(100);
      }

    }    
  }

}


