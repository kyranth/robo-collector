/* This code was written for an ITEST activity in which our objective was to automate a robot's response so that it can
   follow a black line in the shape of a square. We mounted sensors on the robot which detected the white and black lines.
*/

int leftmotorPin9CW = 9;
int leftmotorPin10CCW = 10;

int rightmotorPin5CW = 5;
int rightmotorPin6CCW = 6;

int leftsensor;
int centersensor;
int rightsensor;

int motorspeed = 75;
int timedelay = 200;
int rightangle = 200;

void rightturn()
{
  analogWrite(leftmotorPin9CW, motorspeed);
  analogWrite(leftmotorPin10CCW, LOW);
  Serial.println ("clockwise");
  delay(timedelay);
}

void leftturn()
{
  analogWrite(rightmotorPin5CW, motorspeed);
  analogWrite(rightmotorPin6CCW, LOW);
  Serial.println("counterClockWise");
  delay(timedelay);
}

void forward(int drivespeed)
{
  analogWrite(leftmotorPin10CCW, drivespeed);
  analogWrite(rightmotorPin5CW, LOW);
  analogWrite(leftmotorPin9CW, LOW);
  analogWrite(rightmotorPin6CCW, drivespeed);
  Serial.println("Forward");
}

void stopMotor()
{
  analogWrite(leftmotorPin10CCW, LOW);
  analogWrite(rightmotorPin5CW, LOW);
  analogWrite(leftmotorPin9CW, LOW);
  analogWrite(rightmotorPin6CCW, LOW);
  Serial.println("Stopped");
}

void rotate()
{
  analogWrite(leftmotorPin9CW, motorspeed);
  analogWrite(leftmotorPin10CCW, LOW);

  analogWrite(rightmotorPin5CW, LOW); 
  analogWrite(rightmotorPin6CCW, motorspeed);
}

void setup()
{

  Serial.begin(9600);
  pinMode(leftmotorPin9CW, OUTPUT);
  pinMode(leftmotorPin10CCW, OUTPUT);
  pinMode(rightmotorPin5CW, OUTPUT);
  pinMode(rightmotorPin6CCW, OUTPUT);

  pinMode(11, INPUT);
  pinMode(12, INPUT);
  pinMode(13, INPUT);


}

void loop() {

  leftsensor = digitalRead(13); // Left sensor takes input from Pin 13.
  centersensor = digitalRead(12);
  rightsensor = digitalRead(11);
  
  if (leftsensor == LOW && centersensor == HIGH && rightsensor == LOW)
  {
    forward (50);
  }
  else if (leftsensor == HIGH && centersensor == HIGH && rightsensor == LOW)
  {
    leftturn();
  }
  else if (leftsensor == LOW && centersensor == HIGH && rightsensor == HIGH)
  {
    rightturn();
  }
  else if (leftsensor == LOW && centersensor == LOW && rightsensor == HIGH)
  {
    rightturn();
  }
  else if (leftsensor == HIGH && centersensor == LOW && rightsensor == LOW)
  {
    leftturn();
  }
  else if (leftsensor == LOW && centersensor == LOW && rightsensor == LOW)
  {
    rotate();
  }
  else if (leftsensor == HIGH && centersensor == HIGH && rightsensor == HIGH)
  {
    rotate();
  }
  else if(leftsensor == HIGH && centersensor == LOW && rightsensor == HIGH)
  {
    rotate();
  }

}
     
// HIGH = black
// LOW = white
// left sensor = Pin 11
// center sensor = Pin 12
// right sensor = Pin 13
