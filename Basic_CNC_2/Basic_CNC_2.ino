#define EN        8  

//Limit Switches
#define X_LIMIT   9
#define Y_LIMIT   10

//Direction pin
#define X_DIR     5 
#define Y_DIR     6
#define Z_DIR     7

//Step pin
#define X_STP     2
#define Y_STP     3 
#define Z_STP     4 

#define joyX A0
#define joyY A1


//DRV8825

int delayTime=1500; //Delay between each pause (uS)
int stps=10;// Steps to move


void step(boolean dir, byte dirPin, byte stepperPin, int steps)

{

  digitalWrite(dirPin, dir);

//  delay(100);

  for (int i = 0; i < steps; i++) {

    digitalWrite(stepperPin, HIGH);

    delayMicroseconds(delayTime); 

    digitalWrite(stepperPin, LOW);

    delayMicroseconds(delayTime); 

  }

}

int autoDelayTime=2500; //Delay between each pause (uS)

void autoStep(boolean dir, byte dirPin, byte stepperPin)

{

  digitalWrite(dirPin, dir);
  
  digitalWrite(stepperPin, HIGH);
  delayMicroseconds(autoDelayTime); 
  digitalWrite(stepperPin, LOW);
  delayMicroseconds(autoDelayTime); 

}

int xValue = 0;
int yValue = 0;

int xLimit = 0;
int yLimit = 0;

static int reverseLimitSteps = 10;

int reverseStepCount = 0;

//Limit Stop
boolean xCStop = false;
boolean xCCStop = false;
boolean yCStop = false;
boolean yCCStop = false;

#define c  -1
#define n  0
#define cc  1

int xAxis = n;
int yAxis = n;

int prexAxis = n;
int preyAxis = n;

int xPos;
int yPos;
int xActualPos;
int yActualPos;
boolean xPosCLimit;
boolean xPosCCLimit;
boolean yPosCLimit;
boolean yPosCCLimit;

boolean resetPos;
boolean mode;

//Mode defining
#define AUTO false
#define JOY true


void setup(){

  pinMode(X_LIMIT, INPUT_PULLUP); pinMode(Y_LIMIT, INPUT_PULLUP);

  pinMode(X_DIR, OUTPUT); pinMode(X_STP, OUTPUT);

  pinMode(Y_DIR, OUTPUT); pinMode(Y_STP, OUTPUT);

  pinMode(Z_DIR, OUTPUT); pinMode(Z_STP, OUTPUT);

  pinMode(EN, OUTPUT);

  digitalWrite(EN, LOW);

  xPos = -1;
  yPos = -1;
  xActualPos = -1;
  yActualPos = -1;
  resetPos = true;

//  xPosCLimit = false;
//  yPosCLimit = false;
//  xPosCCLimit = false;
//  yPosCCLimit = false;

  mode = AUTO;

  Serial.begin(9600);

}

void loop(){

  xLimit = digitalRead(X_LIMIT);
  yLimit = digitalRead(Y_LIMIT);

  if(resetPos){
    if(xLimit == HIGH ){
       autoStep(false, X_DIR, X_STP);
    }
    else{
      if(yLimit == HIGH) 
       autoStep(false, Y_DIR, Y_STP);
      else{
        resetPos = false;
        xPos = 0;
        yPos = 0;
        xActualPos = 0;
        yActualPos = 0;
      }
    }
  }

  while(

}
