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
      return node;
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
      node = node->next;
    }
  }

  void resetBlink(){
    for(int j = 0; j < 2; j++)
    {
      for(int i = 0; i < _numOfLeds; i++)
      {
        _leds[i]->on();
      }
      delay(300);
      for(int i = 0; i < _numOfLeds; i++)
      {
        _leds[i]->off();
      }
      delay(300);
    }
  }

public:
  Game(int numOfLeds, Led** leds){
    _patternLength = 0;
    _numOfLeds = numOfLeds;
    _leds = leds;

    _patternStart = nullptr;
    _patternEnd = nullptr;
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

    resetBlink();
  }

  void restart(){
    reset();
    start();
  }

  Node* getPattern(){
    return _patternStart;
  }

  int getPatternLength(){
    return _patternLength;
  }

  void nextLevel(){
    increaseGameLength();
    showPattern();
  }
};

class Player{
  Game* _myGame;
  Node* _firstLed;  
  Node* _currLed;  

  void restartGame(){
    _myGame->restart();
    _firstLed = _myGame->getPattern();
    _currLed = _firstLed;
  }

public:
  Player(Game* game){
    _myGame = game;
  }

  void startGame(){
      _myGame->start();
      _firstLed = _myGame->getPattern();
      _currLed = _firstLed;
  }

  void pressedButton(int buttonLedNum){
    if(buttonLedNum == _currLed->val) {
      _currLed = _currLed->next;
      if(_currLed == nullptr)
      {
        _currLed = _firstLed;
        delay(500);
        _myGame->nextLevel();
      }
    }
    else {
      String scoreMsg = "********************  Your score is: " + String(_myGame->getPatternLength()) + "  ********************";
      restartGame();
      for(int i = 0; i < 5; i++) Serial.println();
      Serial.println("************************************************************");
      Serial.println(scoreMsg);
      Serial.println("************************************************************");
    }
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
        thePlayer->pressedButton(i);
        while(digitalRead(buttonPins[i]) == HIGH);
      }
    }    
  }

}


