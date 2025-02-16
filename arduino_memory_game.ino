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
int ledPins[] = {1, 2, 3, 4}; 

Game theGame = Game();
int* pattern;

void setup() {
  pinMode(ledPins[0], OUTPUT);
  pinMode(ledPins[1], OUTPUT);
  pinMode(ledPins[2], OUTPUT);
  pinMode(ledPins[3], OUTPUT);

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
  delay(1000);
}


