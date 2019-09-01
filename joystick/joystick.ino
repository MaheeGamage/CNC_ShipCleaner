#define EN        8  

//Limit Switches
#define X_C_LIMIT   9
#define Y_C_LIMIT   10
#define X_CC_LIMIT   11
#define Y_CC_LIMIT   12

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
int stps=1;// Steps to move


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

void multiStep(boolean xDir, boolean xMove, boolean yDir, boolean yMove)

{

  digitalWrite(X_DIR, xDir);
  digitalWrite(Y_DIR, yDir);

  if(xMove)
    digitalWrite(X_STP, HIGH);
  if(yMove)
    digitalWrite(Y_STP, HIGH);
    
    delayMicroseconds(delayTime); 

  if(xMove)
    digitalWrite(X_STP, LOW);
  if(yMove)
    digitalWrite(Y_STP, LOW);

    delayMicroseconds(delayTime); 
}

int xValue = 0;
int yValue = 0;

int xCLimit = 0;
int yCLimit = 0;
int xCCLimit = 0;
int yCCLimit = 0;

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


void setup(){

  pinMode(X_C_LIMIT, INPUT_PULLUP); pinMode(Y_C_LIMIT, INPUT_PULLUP);
  pinMode(X_CC_LIMIT, INPUT_PULLUP); pinMode(Y_CC_LIMIT, INPUT_PULLUP);

  pinMode(X_DIR, OUTPUT); pinMode(X_STP, OUTPUT);
  pinMode(Y_DIR, OUTPUT); pinMode(Y_STP, OUTPUT);

  pinMode(EN, OUTPUT);

  digitalWrite(EN, LOW);

  Serial.begin(9600);

}

void loop(){
  // put your main code here, to run repeatedly:
  xValue = analogRead(joyX);
  yValue = analogRead(joyY);

  xCLimit = digitalRead(X_C_LIMIT);
  yCLimit = digitalRead(Y_C_LIMIT);
  xCCLimit = digitalRead(X_CC_LIMIT);
  yCCLimit = digitalRead(Y_CC_LIMIT);

  prexAxis = xAxis;
  preyAxis = yAxis;
  
  if(xValue < 100)
    xAxis = c;
  else if(xValue > 924)
    xAxis = cc;
  else
    xAxis = n;

  if(yValue < 100)
    yAxis = c;
  else if(yValue > 924)
    yAxis = cc;
  else
    yAxis = n;

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

//  if(xAxis == c && yAxis == n && xCLimit){
//    step(false, X_DIR, X_STP, stps);
//  }
//  if(xAxis == cc && yAxis == n && xCCLimit){
//    step(true, X_DIR, X_STP, stps);
//  }
//  if(xAxis == n && yAxis == c && yCLimit){
//    step(false, Y_DIR, Y_STP, stps);
//  }
//  if(xAxis == n && yAxis == cc && yCCLimit){
//    step(true, Y_DIR, Y_STP, stps);
//  }

  if(xAxis == c && yAxis == n && xCLimit){
    multiStep(false, true, false, false);//Xdir, XMove, YDir, YMove
//    step(false, X_DIR, X_STP, stps);
  }
  if(xAxis == cc && yAxis == n && xCCLimit){
    multiStep(true, true, false, false);//Xdir, XMove, YDir, YMove
//    step(true, X_DIR, X_STP, stps);
  }
  if(xAxis == n && yAxis == c && yCLimit){
    multiStep(false, false, false, true);//Xdir, XMove, YDir, YMove
//    step(false, Y_DIR, Y_STP, stps);
  }
  if(xAxis == n && yAxis == cc && yCCLimit){
    multiStep(false, false, true, true);//Xdir, XMove, YDir, YMove
//    step(true, Y_DIR, Y_STP, stps);
  }
  if(xAxis == c && yAxis == c && xCLimit){
    multiStep(false, true, false, true);//Xdir, XMove, YDir, YMove
  }
  if(xAxis == c && yAxis == cc && xCLimit){
    multiStep(false, true, true, true);//Xdir, XMove, YDir, YMove
  }
  if(xAxis == cc && yAxis == cc && xCLimit){
    multiStep(true, true, true, true);//Xdir, XMove, YDir, YMove
  }
  if(xAxis == cc && yAxis == c && xCLimit){
    multiStep(true, true, false, true);//Xdir, XMove, YDir, YMove
  }
  
  
//  Serial.print(xCStop);
//  Serial.print("  ");
//  Serial.print(xCCStop);
//  Serial.print("  ");
//  Serial.print(yCStop);
//  Serial.print("  ");
//  Serial.print(yCCStop);
//  Serial.println("  ");


}
