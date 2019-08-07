/*
  



    97 a -> juncNum++
    98 b -> arr[x][0] = 1/2/3
    99 c -> arr[x][1] = 1/2/3
    100 d -> arr[x][0] = 1/2/3
    101 e -> next line printLn arr
    102 f -> run Junction Protocol
    102 g -> increment lap 0 - 3
*/

#include <Arduino.h>

int incomingByte = 0; // for incoming serial data
byte juncNum = 0;
byte junctionNumber = 0;
byte lap = 0;
const int juncMax = 6, subJunc = 2;
int junctionArr[juncMax][subJunc];
int counter = 0;
int count = 0;

void myDelay(unsigned long del)
{
  unsigned long myPrevMillis = millis();
  while (millis() - myPrevMillis <= del)
    ;
}

void printArr()
{
  for (int i = 0; i < juncMax; i++)
  {

    for (int j = 0; j < subJunc; j++)
    {
      Serial.print(junctionArr[i][j]);
      Serial.print(' ');
    }
    Serial.println();
  }
}

void junctionProtocol()
{
  juncNum++;
  Serial.print("Junction: ");
  Serial.println(juncNum);
  switch (lap)
  {
  case 2:
    if (junctionArr[juncNum - 1][0] == 2 && junctionArr[juncNum - 1][1] == 2)
    {
      Serial.println("Call Junction");
    }
    else if (junctionArr[juncNum - 1][1] == 2)
    {
      Serial.println("Hard Left and grab cup");
    }
    else if (junctionArr[juncNum - 1][0] == 2)
    {
      Serial.println("Hard Right and grab cup");
    }
    else
    {
      Serial.println("Pass though");
    }
    break;

  case 3:
    if (junctionArr[juncNum - 1][0] == 3 && junctionArr[juncNum - 1][1] == 3)
    {
      Serial.println("Call Junction");
    }
    else if (junctionArr[juncNum - 1][1] == 3)
    {
      Serial.println("Hard Left and grab cup");
    }
    else if (junctionArr[juncNum - 1][0] == 3)
    {
      Serial.println("Hard Right and grab cup");
    }
    else
    {
      Serial.println("Pass though");
    }
    break;
  }
}

void setup()
{
  Serial.begin(9600); // opens serial port, sets data rate to 9600 bps
  Serial.flush();
  printArr();
}

void loop()
{
  // reply only when you receive data:
  if (Serial.available() > 0)
  {
    // read the incoming byte:
    incomingByte = Serial.read();

    switch (incomingByte) // a
    {
    case 97:
      juncNum++;
      Serial.println();
      Serial.println(juncNum);
      break;
    case 98: // b
      counter++;
      Serial.print("left: ");
      Serial.println(counter);
      if (counter == 1)
      {
        junctionArr[juncNum - 1][0] = 1;
      }
      else if (counter == 2)
      {
        junctionArr[juncNum - 1][0] = 2;
      }
      else if (counter == 3)
      {
        junctionArr[juncNum - 1][0] = 3;
      }
      else if (counter == 4)
      {
        junctionArr[juncNum - 1][0] = 0;
        counter = 0;
      }
      break;
    case 99: // c
      count++;
      Serial.print("Right: ");
      Serial.println(count);
      if (count == 1)
      {
        junctionArr[juncNum - 1][1] = 1;
      }
      else if (count == 2)
      {
        junctionArr[juncNum - 1][1] = 2;
      }
      else if (count == 3)
      {
        junctionArr[juncNum - 1][1] = 3;
      }
      else if (count == 4)
      {
        junctionArr[juncNum - 1][1] = 0;
        count = 0;
      }
      break;
    case 101: // e
      Serial.println();
      printArr();
      break;

    case 102: // f
      junctionProtocol();
      break;

    case 103: // g
      lap++;
      if (lap == 1)
      {
        Serial.print("Lap: ");
        Serial.println(lap);
      }
      else if (lap == 2)
      {
        Serial.print("Lap: ");
        Serial.println(lap);
      }
      else if (lap == 3)
      {
        Serial.print("Lap: ");
        Serial.println(lap);
      }
      else if (lap == 4)
      {
        lap = 0;
        Serial.print("Lap: ");
        Serial.println(lap);
      }
      break;
    }

    // // say what you got:
    // Serial.print("I received: ");
    // Serial.println(incomingByte, DEC);
  }

  if (juncNum > juncMax)
  {
    juncNum = 0;
  }
}
