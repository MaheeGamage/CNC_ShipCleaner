#define EN        8  

//Direction pin
#define X_DIR     5 
#define Y_DIR     6
#define Z_DIR     7

//Step pin
#define X_STP     2
#define Y_STP     3 
#define Z_STP     4 


//DRV8825
int delayTime=1500; //Delay between each pause (uS)
int stps=500;// Steps to move


void step(boolean dir, byte dirPin, byte stepperPin, int steps)

{

  digitalWrite(dirPin, dir);

  delay(100);

  for (int i = 0; i < steps; i++) {

    digitalWrite(X_STP, HIGH);
    digitalWrite(Y_STP, HIGH);
    delayMicroseconds(delayTime); 

    digitalWrite(X_STP, LOW);
    digitalWrite(Y_STP, LOW);
    delayMicroseconds(delayTime); 

  }

}

void setup(){

  pinMode(X_DIR, OUTPUT); pinMode(X_STP, OUTPUT);

  pinMode(Y_DIR, OUTPUT); pinMode(Y_STP, OUTPUT);

  pinMode(Z_DIR, OUTPUT); pinMode(Z_STP, OUTPUT);

  pinMode(EN, OUTPUT);

  digitalWrite(EN, LOW);

}

void loop(){

  step(false, X_DIR, X_STP, stps); //X, Clockwise
  step(false, Y_DIR, Y_STP, stps); //Y, Clockwise
  step(false, Z_DIR, Z_STP, stps); //Z, Clockwise

  delay(1000);

  step(true, X_DIR, X_STP, stps); //X, Counterclockwise
  step(true, Y_DIR, Y_STP, stps); //Y, Counterclockwise
  step(true, Z_DIR, Z_STP, stps); //X, Counterclockwise

  delay(1000);

}
