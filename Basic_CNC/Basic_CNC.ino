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

  // Saving Previous Moving direction
  prexAxis = xAxis;
  preyAxis = yAxis;

    // for Joy
//  xValue = analogRead(joyX);
//  yValue = analogRead(joyY);

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

  if(!resetPos && (mode == AUTO)){
    if((xPos == xActualPos) && (yPos == yActualPos)){
      if(xPos == 0 && yPos == 0){
        xPos = 9999999999;
      }
      if(
    }
    else{
      if(xPos != xActualPos){
        if(xPos > xActualPos){
          if(xLimit == HIGH){
            autoStep(true, X_DIR, X_STP); // Rotate CounterClockwise
            xActualPos += 1;
          }
          else{
            xPos = xActualPos;
          }
        }
        else{
          if(xLimit == HIGH){
            autoStep(false, X_DIR, X_STP); // Rotate CounterClockwise
            xActualPos += 1;
          }
          else{
            xPos = xActualPos;
          }
        }
      }
      else if(yPos != yActualPos){
        if(yPos > yActualPos){
          if(yLimit == HIGH){
            autoStep(true, Y_DIR, Y_STP); // Rotate CounterClockwise
            yActualPos += 1;
          }
          else{
            yPos = yActualPos;
          }
        }
        else{
          if(yLimit == HIGH){
            autoStep(false, Y_DIR, Y_STP); // Rotate CounterClockwise
            yActualPos += 1;
          }
          else{
            yPos = yActualPos;
          }
        }
      }
    }
  }
  
//  if(xValue < 100)
//    xAxis = c;
//  else if(xValue > 924)
//    xAxis = cc;
//  else
//    xAxis = n;
//
//  if(yValue < 100)
//    yAxis = c;
//  else if(yValue > 924)
//    yAxis = cc;
//  else
//    yAxis = n;

//  if(reverseStepCount <= 0){
//    if(xLimit == LOW){
//      reverseStepCount = reverseLimitSteps;
//      if(prexAxis == c)
//        xCStop = true;
//      if(prexAxis == cc)
//        xCCStop = true;
//    }
//    else{
//      xCStop = false;
//      xCCStop = false;
//    }
//    
//    if(yLimit == LOW){
//      reverseStepCount = reverseLimitSteps;
//      if(preyAxis == c)
//        yCStop = true;
//      if(preyAxis == cc)
//        yCCStop = true;
//    }
//    else{
//      yCStop = false;
//      yCCStop = false;
//    }
//  }

//  if(xAxis == c && yAxis == n && !xCStop){
//    step(false, X_DIR, X_STP, stps);
//  }
//  if(xAxis == cc && yAxis == n && !xCCStop){
//    step(true, X_DIR, X_STP, stps);
//  }
//  if(xAxis == n && yAxis == c && !yCStop){
//    step(false, Y_DIR, Y_STP, stps);
//  }
//  if(xAxis == n && yAxis == cc && !yCCStop){
//    step(true, Y_DIR, Y_STP, stps);
//  }

//  if(reverseStepCount > 0 )
//    reverseStepCount--;
  
  
//  Serial.print(xCStop);
//  Serial.print("  ");
//  Serial.print(xCCStop);
//  Serial.print("  ");
//  Serial.print(yCStop);
//  Serial.print("  ");
//  Serial.print(yCCStop);
//  Serial.println("  ");

//  Serial.print(xPos);
//  Serial.print("  ");
//  Serial.print(xActualPos);
//  Serial.print("\t");
//  Serial.print(yPos);
//  Serial.print("  ");
//  Serial.print(yActualPos);
//  Serial.print("  RstPos: ");
//  Serial.print(resetPos);
//  Serial.print("  M ");
//  Serial.print(mode);
//  Serial.println("  ");
//


}
