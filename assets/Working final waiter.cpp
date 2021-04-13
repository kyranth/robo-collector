
#include <IRremote.h>
IRrecv irrecv(2);
decode_results key;

int rightMotor = 6, rightMotor2 = 9, leftMotor = 3, leftMotor2 = 5;
int sensorL = 8, sensorR = 4, IR = 10, ClawF = 12, ClawB = 13, sensorM = 7, sensorFL = 14, sensorFR = 11;
int Cup = 1, pickup = 1;
String turn;
int cross, table = 0, iCounter = 1;
int count = 0, returnCount;


void TurnLeft() {
  analogWrite (leftMotor, 0);        //turn left on spot  255 regular, 1600 for 90
  analogWrite (leftMotor2, 255);
  analogWrite (rightMotor, 255);
  analogWrite (rightMotor2, 0);
}

void TurnRight() {
  analogWrite (leftMotor, 255);          //turn right on spot
  analogWrite (leftMotor2, 0);
  analogWrite (rightMotor, 0);
  analogWrite (rightMotor2, 255);
}

void CloseClaw() {
  digitalWrite(ClawF, LOW);     //claw close
  digitalWrite(ClawB, HIGH);
}

void OpenClaw() {
  digitalWrite(ClawF, HIGH);     //claw open
  digitalWrite(ClawB, LOW);
}


void Forward() {
  analogWrite (leftMotor, 255);      //forward
  analogWrite (leftMotor2, 0);
  analogWrite (rightMotor, 255);
  analogWrite (rightMotor2, 0);
}

void Backward() {
  analogWrite (leftMotor, 0);      //forward
  analogWrite (leftMotor2, 255);
  analogWrite (rightMotor, 0);
  analogWrite (rightMotor2, 255);
}

void PivotRight() {
  analogWrite (leftMotor, 255);      //right
  analogWrite (leftMotor2, 0);
  analogWrite (rightMotor, 0);
  analogWrite (rightMotor2, 0);
}

void PivotLeft() {
  analogWrite (leftMotor, 0);      //left
  analogWrite (leftMotor2, 0);
  analogWrite (rightMotor, 255);
  analogWrite (rightMotor2, 0);
}

void Stop()
{
  analogWrite (leftMotor, 0);    //stop
  analogWrite (leftMotor2, 0);
  analogWrite (rightMotor, 0);
  analogWrite (rightMotor2, 0);
}

void PleaseGoHome1()
{
  if (1 == digitalRead(sensorL))
  {
    while (digitalRead(sensorM) == 0)     //Waits till middle sensor hits black line before stopping the turn
    {
      TurnLeft ();
    }
  }

  if (1 == digitalRead(sensorR))
  {
    while (digitalRead(sensorM) == 0)   //Waits till middle sensor hits black line before stopping the turn
    {
      TurnRight();
    }
  }
}

void Junction()
{
  if (digitalRead(sensorFL) == 1 && digitalRead(sensorFR) == 1 )     //if both sensors hit black, it will add 1 to count
  {
    count = count + 1;
    Stop();
    delay(500);
    if (count == cross)       //after stopping, it will check if they are equal, then will turn if so
    {
      TURN();
    }
    Forward();
    delay(200);
  }
}

void ReturnJunction()
{
  if (digitalRead(sensorFL) == 1 && digitalRead(sensorFR) == 1 )     //if both sensors hit black, it will add 1 to count
  {
    returnCount = returnCount - 1;
    Stop();
    delay(500);
    Forward();
    delay(200);
  }
}

void FollowLine()
{
  if(Cup == 1)
  {
  if (1 == digitalRead(sensorL))
  {
    Junction();
    if (count == 3 && digitalRead(sensorFR) == 0 && digitalRead(sensorM) == 1 && digitalRead(sensorFL) == 1 && iCounter <= 4)  //If the far sensors detect, they can help with the 90degree turns in the intersection
    {
      iCounter = iCounter + 1;
      Forward();
      delay(140);
      TurnLeft();
      delay(630);
    }
    TurnLeft ();
    delay(5);
  }

  if (1 == digitalRead(sensorR))
  {
    Junction();
    if (count == 3 && digitalRead(sensorFL) == 0 && digitalRead(sensorM) == 1 && digitalRead(sensorFR) == 1 && iCounter <= 4)    //If the far sensors detect, they can help with the 90degree turns in the intersection
    {
      iCounter = iCounter + 1;
      Forward();
      delay(140);    //if it hits 3 junctions, and the far right sensor hits 1 while the far left sensor is 0
      TurnRight();
      delay(630);
    }
    TurnRight();
    delay(5);
  }
  }
   else if(Cup == 2)
  {
  if (1 == digitalRead(sensorL))
  {
    ReturnJunction();
    if (returnCount == 3 && digitalRead(sensorFR) == 0 && digitalRead(sensorM) == 1 && digitalRead(sensorFL) == 1 && iCounter <= 4)  //If the far sensors detect, they can help with the 90degree turns in the intersection
    {
      iCounter = iCounter + 1;
      Forward();
      delay(140);
      TurnLeft();
      delay(630);
    }
    TurnLeft ();
    delay(5);
  }

  if (1 == digitalRead(sensorR))
  {
    ReturnJunction();
    if (returnCount == 3 && digitalRead(sensorFL) == 0 && digitalRead(sensorM) == 1 && digitalRead(sensorFR) == 1 && iCounter <= 4)    //If the far sensors detect, they can help with the 90degree turns in the intersection
    {
      iCounter = iCounter + 1;
      Forward();
      delay(140);    //if it hits 3 junctions, and the far right sensor hits 1 while the far left sensor is 0
      TurnRight();
      delay(630);
    }
    TurnRight();
    delay(5);
  }
  }
}

void LEFT()
{
  Forward();      //Small going forward so that the center of rotation is more on the intersection
  delay(130);
  TurnLeft();
  delay (500);
  while (digitalRead(sensorM) == 0)
  {
    TurnLeft();
  }
  TurnLeft();
  delay(15);
  Stop();
  delay(100);
  while (Cup == 1)    //to continue the follow line till all three hit white
  {
    if (digitalRead(sensorL) == 0 && digitalRead(sensorR) == 0 && digitalRead(sensorM) == 0)    //condition to check all white
    {
      Stop();
      delay(100);
      OpenClaw();
      delay (1000);
      returnL();
    }
    else
    {
      Forward();
      FollowLine();
    }
  }
}

void RIGHT()
{
  Forward();
  delay(130);
  TurnRight();
  delay (500);
  while (digitalRead(sensorM) == 0)
  {
    TurnRight();
  }
  TurnRight();
  delay(15);
  Stop();
  delay(100);
  while (Cup == 1)    //to continue the follow line till all three hit white
  {
    if (digitalRead(sensorL) == 0 && digitalRead(sensorR) == 0 && digitalRead(sensorM) == 0)    //condition to check all white
    {
      Stop();
      delay(100);
      OpenClaw();
      delay (1000);
      returnR();
    }
    else
    {
      Forward();
      FollowLine();
    }
  }
}



void returnL() {
  pickup = 1;
  Cup = 2;    //To signify the returning of the robot
  Backward();
  delay(100);
  TurnRight();
  delay(1100);
  while (digitalRead(sensorM) == 0)
  {
    TurnRight();
  }
  Stop();
  returnCount = count - 1;
  count = 1;    //To satisfy the next condition so that the while loop will repeat till it hits the intersection
  delay(300);
  while (count == 1) {
    if (digitalRead(sensorL) == 1 && digitalRead(sensorR) == 1) {
      Forward();
      delay(200);
      TurnRight();
      delay(877);
      Forward();
      delay(100);
      count = 3;
    }
    else {
      Forward();
      PleaseGoHome1();
    }
  }
  while (digitalRead(sensorM) == 1 || digitalRead(sensorL) == 1 || digitalRead(sensorR) == 1)    //If all hit white then it stops and waits for remote
  {
    Forward();
    FollowLine();
  }
  Stop();
  Cup = 1;
  pickup = 1;
  count = 0;
  table = 0;
  delay(100);
  RemoteControl();
}


void returnR() {
  pickup = 1;
  Cup = 2;    //To signify the returning of the robot
  Backward();
  delay(100);
  TurnRight();
  delay(1100);
  while (digitalRead(sensorM) == 0)
  {
    TurnRight();
  }
  Stop();
  returnCount = count - 1;
  count = 1;    //To satisfy the next condition so that the while loop will repeat till it hits the intersection
  delay(300);
  while (count == 1) {
    if (digitalRead(sensorL) == 1 && digitalRead(sensorR) == 1) {
      Forward();
      delay(200);
      TurnLeft();
      delay(877);
      Forward();
      delay(100);
      count = 3;
    }
    else {
      Forward();
      PleaseGoHome1();
    }
  }
  while (digitalRead(sensorM) == 1 || digitalRead(sensorL) == 1 || digitalRead(sensorR) == 1) //If all hit white then it stops and waits for remote
  {
    Forward();
    FollowLine();
  }
  Stop();
  Cup = 1;
  pickup = 1;
  count = 0;
  table = 0;
  delay(100);
  RemoteControl();
}

void RemoteControl()
{
  while (table == 0) {    //Wait till a button is pressed
    if (irrecv.decode(&key))
    {
      switch (key.value) {
        case 0xFF30CF:
          table = 1;
          break;
        case 0xFF18E7:
          table = 2;
          break;
        case 0xFF7A85:
          table = 3;
          break;
        case 0xFF10EF:
          table = 4;
          break;
        case 0xFF38C7:
          table = 5;
          break;
        case 0xFF5AA5:
          table = 6;
          break;
        case 0xFF42BD:
          table = 7;
          break;
        case 0xFF4AB5:
          table = 8;
          break;
        case 0xFF52AD:
          table = 9;
          break;
        case 0xFF6897:
          table = 10;
          break;
        case 0xFF9867:
          table = 11;
          break;
        case 0xFFB04F:
          table = 12;
          break;
        default:
          break;
      }
      irrecv.resume();
    }
  }
  Cup = 1;
  TableSet();   //function determines even or odd and sets the cross variable
  OpenClaw();
  delay (1000);
  while (!0 == digitalRead(IR))
  {
    Forward();
  }
  Stop();
  delay(700);
  PICKUP();
  Waiter();
}

void PICKUP()   //To determine whether to pick up or not
{
  if (digitalRead(IR) == 0)
  {
    switch (pickup)
    {
      case 1:
        Stop();
        delay(500);
        CloseClaw();
        delay (500);
        digitalWrite(ClawF, LOW);
        digitalWrite(ClawB, LOW);
        while (digitalRead(sensorM) == 0)
        {
          TurnLeft();
        }
        Stop();
        delay(700);
        pickup = 2;
        break;
      default:
        break;
    }
  }
}

void TableSet()
{
  if (table % 2 == 0) {       //checks if table is even
    turn = "even";
    cross = table / 2;
  }

  if (table % 2 == 1) {       //checks if table is odd
    turn = "odd";
    cross = table + 1;
    cross = cross / 2;
  }
  Serial.println (table);
}

void TURN()   //If even turn right, if odd turn left
{
  if (turn == "even")
  {
    RIGHT();
  }
  else if (turn == "odd")
  {
    LEFT();
  }
}

void Waiter()
{
  while (count < cross)     //Continues to move and follow line
  {
    Forward();
    FollowLine();
  }
}

void setup()
{
  Serial.begin (9600);
  irrecv.enableIRIn();
  pinMode (rightMotor, OUTPUT);
  pinMode (rightMotor2, OUTPUT);
  pinMode (leftMotor, OUTPUT);
  pinMode (leftMotor2, OUTPUT);
  pinMode (sensorL, INPUT);
  pinMode (sensorR, INPUT);
  pinMode(sensorM, INPUT);
  pinMode (IR, INPUT);
  pinMode(2, INPUT);
  pinMode(sensorFR, INPUT);
  pinMode(sensorFL, INPUT);
}

void loop()
{
  RemoteControl();          //Starting the Code
}







