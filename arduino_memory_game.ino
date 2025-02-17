// My memory game
// Lets see how it goes... ;)

class Node {
public:
  int val;
  Node* next;
};

class Led {
  int _pin;

public:
  Led(int pin){
    _pin = pin;
  }

  void on(){
    digitalWrite(_pin, HIGH);
  }

  void off(){
    digitalWrite(_pin, LOW);
  }
};

class Game {
  int _patternLength = 0;
  Node* _patternStart = nullptr;
  Node* _patternEnd = nullptr;
  int _numOfLeds;
  Led** _leds;

  Node* getNewNode() {
      Node* node = new Node();
      node->val = rand() % _numOfLeds;
      node->next = nullptr;
  }

  void increaseGameLength(){
    _patternLength++;
    if (_patternStart == nullptr) {
      _patternStart = getNewNode();
      _patternEnd = _patternStart;
    }
    else {
      _patternEnd->next = getNewNode();
      _patternEnd = _patternEnd->next;
    }
  }

  void showPattern(){
    Node* node = _patternStart;
    for(int i = 0; i < _patternLength; i++)
    {
      _leds[node->val]->on();
      delay(200);
      _leds[node->val]->off();
      delay(200);
    }
  }

public:
  Game(int numOfLeds, Led** leds){
    _patternLength = 0;
    _numOfLeds = numOfLeds;
    _leds = leds;
  }

  void start(){
    increaseGameLength();
    showPattern();
  }

  void reset(){
    _patternLength = 0;
    
    Node* temp;
    while (_patternStart != nullptr) {
      temp = _patternStart->next;
      free(_patternStart);
      _patternStart = temp;
    }
    _patternEnd = nullptr;
  }

  void setConstantPatternLength(int length){
    _patternLength = length;
  }

  Node* getPattern(){
    return _patternStart;
  }

  int getCurrPaternLength(){
    return _patternLength;
  }
};

class Player{
  Game* _myGame;

public:
  Player(Game* game){
    _myGame = game;
  }

  void startGame(){
      _myGame->start();
  }
};

int LED_COUNT = 4;
int BUTTON_COUNT = LED_COUNT;
int ledPins[] = {2, 3, 4, 5}; 
int buttonPins[] = {9, 10, 12, 13};

Player* thePlayer;

void setup() {
  Serial.begin(9600);
  
  for(int i = 0; i < LED_COUNT; i++){
    pinMode(ledPins[i], OUTPUT);
  }

  for(int i = 0; i < LED_COUNT; i++){
    pinMode(buttonPins[i], INPUT);
  }

  Led** leds = malloc(LED_COUNT * sizeof(Led*));

  for(int i = 0; i < LED_COUNT; i++){
    leds[i] = new Led(ledPins[i]);
  }

  Game* theGame = new Game(LED_COUNT, leds);
  thePlayer = new Player(theGame);
  thePlayer->startGame();
}

void loop() {
  
  while (true) {
    for(int i = 0; i < BUTTON_COUNT; i++)
    {
      if(digitalRead(buttonPins[i]) == HIGH)
      {
        
      }
    }    
  }

}


