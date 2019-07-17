/* This code was written for an ITEST activity in which our objective was to automate a robot's response so that it can
   follow a black line in the shape of a square. We mounted sensors on the robot which detected the white and black lines.
   Yanni

*/

int leftmotorPin9CW = 9;
int leftmotorPin10CCW = 10;
int rightmotorPin5CCW = 5;
int rightmotorPin6CW = 6;


int leftsensor;
int centersensor;
int rightsensor;

int motorspeed = 75;
int timedelay = 200;
int rightangle = 200;

void rightturn()
{
  analogWrite(leftmotorPin9CW, LOW);
  analogWrite(leftmotorPin10CCW, motorspeed);
  analogWrite(rightmotorPin5CCW, LOW);   
  analogWrite(rightmotorPin6CW, LOW);
  Serial.println ("clockwise");
  delay(timedelay);
}

void leftturn()
{
  analogWrite(rightmotorPin5CCW, LOW);
  analogWrite(rightmotorPin6CW, motorspeed);
  analogWrite(leftmotorPin9CW, LOW);
  analogWrite(leftmotorPin10CCW, LOW);
  Serial.println("counterClockWise");
  delay(timedelay);
  
}


void forward(int drivespeed)
{
  analogWrite(leftmotorPin10CCW, drivespeed);
  analogWrite(rightmotorPin5CCW, LOW);
  analogWrite(leftmotorPin9CW, LOW);
  analogWrite(rightmotorPin6CW, drivespeed);
  Serial.println("Forward");
  delay(timedelay);
  
}


void stopMotor()
{
  analogWrite(leftmotorPin10CCW, LOW);
  analogWrite(rightmotorPin5CCW, LOW);
  analogWrite(leftmotorPin9CW, LOW);
  analogWrite(rightmotorPin6CW, LOW);
  Serial.println("Stopped");
  delay(timedelay);
  
}

void rotate()
{
  analogWrite(leftmotorPin9CW, motorspeed);
  analogWrite(leftmotorPin10CCW, LOW);
  analogWrite(rightmotorPin5CCW, LOW);
  analogWrite(rightmotorPin6CW, motorspeed);
  Serial.println("rotate");
  delay(timedelay);
   
   //i recommend using while because the time delay will differ depending on battery life and is called hard coding.
   // the way you have it now, it is too dependent on the arduino going back to that if statement over and over again rather than it 
   // finishing it's job then moving on.
  
}


void setup()
{

  Serial.begin(9600);
  pinMode(leftmotorPin9CW, OUTPUT);
  pinMode(leftmotorPin10CCW, OUTPUT);
  pinMode(rightmotorPin5CCW, OUTPUT);
  pinMode(rightmotorPin6CW, OUTPUT);

  pinMode(11, INPUT);
  pinMode(12, INPUT);
  pinMode(13, INPUT);


}

void loop() {

  leftsensor = digitalRead(13); // Left sensor takes input from Pin 13.
  centersensor = digitalRead(12);
  rightsensor = digitalRead(11);

  // left to right
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
  else if (leftsensor == HIGH && centersensor == LOW && rightsensor == HIGH)
  {
    rotate();
  }

}

// HIGH = black
// LOW = white
// left sensor = Pin 11
// center sensor = Pin 12
// right sensor = Pin 13
