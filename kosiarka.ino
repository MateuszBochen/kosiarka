/*
  Blink
  Turns on an LED on for one second, then off for one second, repeatedly.

  Most Arduinos have an on-board LED you can control. On the Uno and
  Leonardo, it is attached to digital pin 13. If you're unsure what
  pin the on-board LED is connected to on your Arduino model, check
  the documentation at http://www.arduino.cc

  This example code is in the public domain.

  modified 8 May 2014
  by Scott Fitzgerald
 */
//int changeDirectionPin = 3;
int opticSensorPin1 = 12;
int opticSensorPin2 = 13; 
int pinsLeft[4] = {4, 5, 6, 7};
int pinsRight[4] = {8, 9, 10, 11};
bool canGoForward = true;
//int countModulo = 1;

int command = 1;

void leftForward()
{
  digitalWrite(pinsLeft[0], LOW);
  digitalWrite(pinsLeft[1], LOW);
}

void leftRearward()
{
  digitalWrite(pinsLeft[2], LOW);
  digitalWrite(pinsLeft[3], LOW);
}

void leftStop()
{
  digitalWrite(pinsLeft[0], HIGH);
  digitalWrite(pinsLeft[1], HIGH);
  digitalWrite(pinsLeft[2], HIGH);
  digitalWrite(pinsLeft[3], HIGH);
  
}

void rightForward()
{
  digitalWrite(pinsRight[0], LOW);
  digitalWrite(pinsRight[1], LOW);
  
}

void rightStop()
{
  digitalWrite(pinsRight[0], HIGH);
  digitalWrite(pinsRight[1], HIGH);
  digitalWrite(pinsRight[2], HIGH);
  digitalWrite(pinsRight[3], HIGH);
}

void rightRearward()
{
  digitalWrite(pinsRight[2], LOW);
  digitalWrite(pinsRight[3], LOW);
}

void goForward()
{
  rightStop();
  leftStop();
  rightForward();
  //if (countModulo % 11 != 0) {
    leftForward();
  //}
  //else {
    //countModulo = 1;
  //}
  //countModulo++;
}

void goRearward()
{
  rightStop();
  leftStop();
  rightRearward();
  leftRearward();
}



// the setup function runs once when you press reset or power the board
void setup() {
  // initialize digital pin 13 as an output.

  
  //pinMode(4, OUTPUT);
  Serial.begin(9600);

 // pinMode(changeDirectionPin, INPUT);
  pinMode(opticSensorPin1, INPUT);
  pinMode(opticSensorPin2, INPUT);
  
  // init
  for (int i = 0; i < 4; i++) {
    pinMode(pinsLeft[i], OUTPUT);
    pinMode(pinsRight[i], OUTPUT); 
  }

  rightStop();
  leftStop();
}



// the loop function runs over and over again forever
void loop() {

  //int analogVal = analogRead(changeDirectionPin);    // read the input pin

  
  //Serial.println(analogVal);
  //Serial.print("\n s:");
  //Serial.print(sensorVal); 
  //Serial.print("--\n");

  //digitalWrite(13, LOW);

  if (digitalRead(opticSensorPin1) == LOW || digitalRead(opticSensorPin2) == LOW) {
      command = 2;
      Serial.print("Odpalanie cofania\n");
  }
  
  switch (command) {
    case 1:
      Serial.print("jedzie do przodu--\n");
      goForward();
      command = 0;
      break;
    case 2:
      Serial.print("jedzie do tylu--\n");
      goRearward();
      delay(3000);
      rightStop();
      leftStop();
      delay(40);
      Serial.print("prawe do tylu lewe do przodu--\n");
      rightRearward();
      leftForward();
      delay(2000);
      Serial.print("Oba stop--\n");
      rightStop();
      leftStop();
      delay(40);
      command = 1;
      break;
    default:
      command = 0;
  }

  
}

