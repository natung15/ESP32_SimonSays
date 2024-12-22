#define BUTTONINPUTRed 23
#define BUTTONINPUTWhite 22
#define BUTTONINPUTBlue 21
#define BUTTONINPUTSTART 14
#define BUZZEROUTPUT 26

#define BUTTONOUTPUTRGBRed 19
#define BUTTONOUTPUTRGBYellow 18
#define BUTTONOUTPUTRGBGreen 5

#define MAX_SEQUENCE_LENGTH 3
//Red Button == RED LED
//BLUE Button == Green LED
//White Button == Yellow LED

//GLOBAL VARIABLES
bool REDBUTTON = false;
bool BLUEBUTTON = false;
bool WHITEBUTTON = false;
bool STARTBUTTON = false;

bool LEDRed;
bool LEDYellow;
bool LEDGreen;

enum GameState {
  IDLE,
  SEQUENCE,
  PLAYER,
  WINNER,
  GAMEOVER
};

GameState currentState = IDLE;

int level = 0;
int playerGuessCount = 0;

int lightSequence[MAX_SEQUENCE_LENGTH];
int playerSequence[MAX_SEQUENCE_LENGTH];

void setup() {
  // put your setup code here, to run once:
  pinMode(BUTTONINPUTRed, INPUT_PULLUP);
  pinMode(BUTTONINPUTBlue, INPUT_PULLUP);
  pinMode(BUTTONINPUTWhite, INPUT_PULLUP);
  pinMode(BUTTONINPUTSTART, INPUT_PULLUP);

  pinMode(BUTTONOUTPUTRGBRed, OUTPUT);
  pinMode(BUTTONOUTPUTRGBGreen, OUTPUT);
  pinMode(BUTTONOUTPUTRGBYellow, OUTPUT);

  pinMode(BUZZEROUTPUT,OUTPUT);

  Serial.begin(9600);
}

void buttonRead() {
  if (digitalRead(BUTTONINPUTRed) == LOW) {
    if (REDBUTTON == false) {
      delay(50);
      REDBUTTON = true;
      tone(BUZZEROUTPUT,392,300);
    }
  } else {
    noTone(BUZZEROUTPUT);
    if (REDBUTTON == true) {
      delay(50);
      REDBUTTON = false;
      if(currentState == PLAYER){
        playerSequence[playerGuessCount] = 0;
        playerGuessCount++;
        noTone(BUZZEROUTPUT);
        return;
      }
    }
  }

  if (digitalRead(BUTTONINPUTBlue) == LOW) {
    if (BLUEBUTTON == false) {
      delay(50);
      BLUEBUTTON = true;
      tone(BUZZEROUTPUT,659,300);
    }
  } else {
    noTone(BUZZEROUTPUT);
    if (BLUEBUTTON == true) {
      delay(50);
      BLUEBUTTON = false;
      if(currentState == PLAYER){
        playerSequence[playerGuessCount] = 2;
        playerGuessCount++;
        noTone(BUZZEROUTPUT);
        return;
      }
    }
  }

  if (digitalRead(BUTTONINPUTWhite) == LOW) {
    if (WHITEBUTTON == false) {
      delay(50);
      WHITEBUTTON = true;
      tone(BUZZEROUTPUT,523,300);
    }
  } else {
    noTone(BUZZEROUTPUT);
    if (WHITEBUTTON == true) {
      delay(50);
      WHITEBUTTON = false;
      if(currentState == PLAYER){
        playerSequence[playerGuessCount] = 1;
        playerGuessCount++;
        noTone(BUZZEROUTPUT);
        return;
      }
    }
  }

  if(digitalRead(BUTTONINPUTSTART) == LOW){
    if (STARTBUTTON == false) {
      delay(50);
      STARTBUTTON = true;
    }
  } else {
    if (STARTBUTTON == true) {
      delay(50);
      STARTBUTTON = false;
    }
  }
}

void updateLEDs(){
  if (REDBUTTON == true) {
    digitalWrite(BUTTONOUTPUTRGBRed, HIGH);
    LEDRed = true;   // Turn Red LED ON

  } else {
    digitalWrite(BUTTONOUTPUTRGBRed, LOW);
    LEDRed = false;  // Turn Red LED OFF
  }

  if (BLUEBUTTON == true) {
    digitalWrite(BUTTONOUTPUTRGBGreen, HIGH);
    LEDGreen = true;  // Turn Blue LED ON
  } else {
    digitalWrite(BUTTONOUTPUTRGBGreen, LOW);
    LEDGreen = false; // Turn Blue LED OFF
  }

  if (WHITEBUTTON == true) {
    digitalWrite(BUTTONOUTPUTRGBYellow, HIGH);
    LEDYellow = true;  // Turn White LED ON
  } else {
    digitalWrite(BUTTONOUTPUTRGBYellow, LOW);
    LEDYellow = false; // Turn White LED OFF
  }
}

void generateRandomNumber(){
  if(level == MAX_SEQUENCE_LENGTH){
    return;
  }
  int randomNumber = random(0,3);
  Serial.print("RandomNumber:");
  lightSequence[level] = randomNumber;
  Serial.println(randomNumber);
  Serial.print("Sequence Length:");
  Serial.println(level+1);
  level++;
  for (int i = 0; i < level; i++) {  // Loop through each array element
    Serial.print(lightSequence[i]);  // Print value
    Serial.print(",");
  }
  Serial.println(" ");
  return;
}

void turnLEDON(int color){
  switch(color){
    case(0)://red
      digitalWrite(BUTTONOUTPUTRGBRed, HIGH);
      return;
    case(1)://yellow
      digitalWrite(BUTTONOUTPUTRGBYellow, HIGH);
      return;
    case(2)://green
      digitalWrite(BUTTONOUTPUTRGBGreen, HIGH);
      return;

  }
}

void turnLEDOFF(int color){
  switch(color){
    case(0)://red
      digitalWrite(BUTTONOUTPUTRGBRed, LOW);
      return;
    case(1)://yellow
      digitalWrite(BUTTONOUTPUTRGBYellow, LOW);
      return;
    case(2)://green
      digitalWrite(BUTTONOUTPUTRGBGreen, LOW);
      return;

  }
}

void toggleLeds(bool toggleOn){
  if(toggleOn){
    turnLEDON(0);//red
    turnLEDON(1);//yellow
    turnLEDON(2);//green
  }
  else{
    turnLEDOFF(0);//red
    turnLEDOFF(1);//yellow
    turnLEDOFF(2);//green
  }
}

void playNewRoundSequence(){
  delay(300);
  tone(BUZZEROUTPUT, 523, 300);
  toggleLeds(true);
  delay(300);
  toggleLeds(false);
  delay(300);
  toggleLeds(true);
  delay(300);
  tone(BUZZEROUTPUT, 659, 300);
  toggleLeds(false);
  delay(300); 
  toggleLeds(true);
  delay(300);
  toggleLeds(false);
  delay(500); 
  noTone(BUZZEROUTPUT);
  
}

void gameExec(){
  switch(currentState){
    case(IDLE):
      if(STARTBUTTON == true){
        tone(BUZZEROUTPUT,392,200);
        delay(200);
        tone(BUZZEROUTPUT,523,200);
        delay(200);
        tone(BUZZEROUTPUT,659,200);
        delay(200);
        noTone(BUZZEROUTPUT);
        currentState = SEQUENCE;
        level = 0;
        playerGuessCount = 0;
      }
      return;

    case(SEQUENCE):
      generateRandomNumber();
      playNewRoundSequence();
      for(int i = 0; i < level; i++){
        turnLEDON(lightSequence[i]);
        if(lightSequence[i] == 0){
          tone(BUZZEROUTPUT,392,200);
        }
        else if(lightSequence[i]== 1){
          tone(BUZZEROUTPUT,523,200);
        }
        else{
          tone(BUZZEROUTPUT,659,200);
        }
        delay(200);
        noTone(BUZZEROUTPUT);
        turnLEDOFF(lightSequence[i]);
        delay(500);
      }
      currentState = PLAYER;
      noTone(BUZZEROUTPUT);
      playerGuessCount = 0;
      return;

    case(PLAYER):
      if(playerGuessCount == level){
          Serial.println("GOOD NEXT SEQUENCE!");
          currentState = SEQUENCE;
          noTone(BUZZEROUTPUT);
        }
      if(playerGuessCount >= 1){
        if(lightSequence[playerGuessCount-1] != playerSequence[playerGuessCount-1]){
          currentState = GAMEOVER;
          noTone(BUZZEROUTPUT);
          Serial.println("GAMEOVER");
          
          
          return;
        }
        if(playerGuessCount >= MAX_SEQUENCE_LENGTH){
            currentState = WINNER;
            noTone(BUZZEROUTPUT);
            return;
        }
      }
      return;

    case(GAMEOVER):
      for(int i =0;i<5;i++){
        delay(50);
        tone(BUZZEROUTPUT, 659, 200); 
        turnLEDON(0);
        turnLEDON(1);
        delay(250);
        tone(BUZZEROUTPUT, 523, 200); 
        turnLEDOFF(0);
        turnLEDOFF(1);
        delay(250);

        
      }
      currentState = IDLE;
      noTone(BUZZEROUTPUT);
      return;

    case(WINNER):
      Serial.println("WINNER");
      delay(800);
      turnLEDON(0);
      delay(300);
      turnLEDON(1);
      delay(300);
      turnLEDON(2);
      delay(700);
      turnLEDOFF(2);
      delay(300);
      turnLEDOFF(1);
      delay(300);
      turnLEDOFF(0);
      delay(300);
      currentState = IDLE;
      noTone(BUZZEROUTPUT);
      return;

  }
}

void loop() {
  // put your main code here, to run repeatedly:
  buttonRead();
  updateLEDs();
  gameExec();
}

