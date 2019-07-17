/* This code was written for an ITEST activity in which our objective was to automate a robot's response so that it can
   follow a black line in the shape of a square. We mounted sensors on the robot which detected the white and black lines.

   JEFF BOB THE 3RD(Clawbot)
    License: iTEST NYU Robotis Course
    TEAM: {
      Dr. Walcott, Mr. Kiefer, Shafiqur Khan, Nishal Thapa
      Lena Khosrof, Yanni, Dushan Persaud
    }
*/

int leftmotorPin9B = 9;
int leftmotorPin10F = 10;

int rightmotorPin5F = 5;
int rightmotorPin6B = 6;

int leftsensor;
int centersensor;
int rightsensor;

int motorspeed = 125;
int timedelay = 200;
int rightangle = 200;

void checksensor()
{
  leftsensor = digitalRead(A2); // Left sensor takes input from Pin 13.
  centersensor = digitalRead(A1);
  rightsensor = digitalRead(A0);
}

void rightturn()
{
  analogWrite(leftmotorPin9B, LOW);
  analogWrite(leftmotorPin10F, motorspeed);
  analogWrite(rightmotorPin5F, motorspeed);
  analogWrite(rightmotorPin6B, LOW);
  Serial.println("clockwise");
  checksensor();
}

void leftturn()
{
  analogWrite(rightmotorPin5F, LOW);
  analogWrite(rightmotorPin6B, motorspeed);
  analogWrite(leftmotorPin9B, motorspeed);
  analogWrite(leftmotorPin10F, LOW);
  Serial.println("counterClockWise");
  //delay(timedelay);
  checksensor();
}

void forward(int drivespeed)
{
  analogWrite(leftmotorPin10F, drivespeed);
  analogWrite(rightmotorPin5F, LOW);
  analogWrite(leftmotorPin9B, LOW);
  analogWrite(rightmotorPin6B, drivespeed);
  checksensor();
  Serial.println("Forward");
}

void stopMotor()
{
  analogWrite(leftmotorPin10F, LOW);
  analogWrite(rightmotorPin5F, LOW);
  analogWrite(leftmotorPin9B, LOW);
  analogWrite(rightmotorPin6B, LOW);
  //Serial.println("Stopped");
}

void rotate()
{
  analogWrite(leftmotorPin9B, motorspeed);
  analogWrite(leftmotorPin10F, LOW);

  analogWrite(rightmotorPin5F, LOW);
  analogWrite(rightmotorPin6B, motorspeed);
}

void setup()
{

  Serial.begin(9600);
  pinMode(leftmotorPin9B, OUTPUT);
  pinMode(leftmotorPin10F, OUTPUT);
  pinMode(rightmotorPin5F, OUTPUT);
  pinMode(rightmotorPin6B, OUTPUT);

  pinMode(A0, INPUT);
  pinMode(A1, INPUT);
  pinMode(A2, INPUT);
}

void loop() {
  int centimeters = distanceSensor.measureDistanceCm();
  int inches = centimeters / 2.54;
  
  leftsensor = digitalRead(A2); // Left sensor takes input from Pin 13.
  centersensor = digitalRead(A1);
  rightsensor = digitalRead(A0);
  Serial.print(leftsensor);
  Serial.print(centersensor);
  Serial.print(rightsensor);

  if (leftsensor == LOW && centersensor == HIGH && rightsensor == LOW)
  {
    forward(125);
  }
  else if (leftsensor == HIGH && centersensor == HIGH && rightsensor == LOW)
  {
    // Serial.println("leftturn!!");
    rightturn();
  }
  else if (leftsensor == LOW && centersensor == HIGH && rightsensor == HIGH)
  {
    leftturn();
  }
  else if (leftsensor == LOW && centersensor == LOW && rightsensor == HIGH)
  {
    leftturn();
  }
  else if (leftsensor == HIGH && centersensor == LOW && rightsensor == LOW)
  {
    rightturn();
  }
  else if (leftsensor == LOW && centersensor == LOW && rightsensor == LOW)
  {
    forward(125);
  }
  else if (leftsensor == HIGH && centersensor == HIGH && rightsensor == HIGH)
  {
    forward(125);
    delay(timedelay);
  }

  else if (leftsensor == HIGH && centersensor == LOW && rightsensor == HIGH)
  {
    forward(125);
  }

}
 
//else
//{
//clockwise_rotate(rightangle);
//Serial.println(leftsensor);
//Serial.println(centersensor);
//Serial.println(rightsensor);
//}

//  clockwise_rotate();
//  delay(2000);
//  anticlockwise_rotate();
//  delay(2000);

/* forward(240, 2000);
  clockwise_rotate();
  delay(650);
  forward(240, 2000);
  clockwise_rotate();
  delay(650);
  forward(240, 2000);
  clockwise_rotate();
  delay(650);
  forward(240, 2000);
  clockwise_rotate();
  delay(650); */




// HIGH = black
// LOW = white
// left sensor = Pin 11
// center sensor = Pin 12
// right sensor = Pin 13


// Every 500 miliseconds, do a measurement using the sensor and print the distance in centimeters.
    Serial.println(distanceSensor.measureDistanceCm());
    int centimeters = distanceSensor.measureDistanceCm();
    int inches = centimeters / 2.54;
    Serial.println(inches);
    delay(500);

    if(inches <= 3)
    {
      // Close claw motor
    }