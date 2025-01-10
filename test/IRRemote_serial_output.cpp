/**
 * @file IRRemote_serial_output.cpp
 * @brief This file contains the implementation for reading IR remote signals and outputting corresponding commands to the serial monitor.
 *
 * This program uses the IRremote library to decode signals from an IR remote control. The decoded signals are then mapped to specific commands
 * which are printed to the serial monitor.
 *
 * @author kyranth
 * @date 2019-09-26
 */

#include <Arduino.h>
#include <IRremote.h>

const int RECV_PIN = 7; // Pin connected to the IR receiver

IRrecv irrecv(RECV_PIN); // IR receiver object
decode_results results; // Structure to store the results of the IR decoding
unsigned long key_value = 0; // Variable to store the last valid key press

/**
 * @brief Initializes the serial communication and the IR receiver.
 *
 * This function sets up the serial communication at 9600 baud rate and enables the IR receiver.
 */
void setup()
{
  Serial.begin(9600);
  irrecv.enableIRIn();
  irrecv.blink13(true);
}

/**
 * @brief Main loop function.
 *
 * This function continuously calls the IRremote function to check for IR signals.
 */
void loop()
{
  IRremote();
}

/**
 * @brief Decodes and processes the IR signals.
 *
 * This function checks if an IR signal is received, decodes it, and prints the corresponding command to the serial monitor.
 * It handles repeated key presses by storing the last valid key press.
 */
void IRremote()
{
  if (irrecv.decode(&results))
  {

    if (results.value == 0XFFFFFFFF)
      results.value = key_value;

    switch (results.value)
    {
    case 0xFFA25D:
      Serial.println("ON/Off");
      break;
    case 0xFF629D:
      Serial.println("Vol+");
      break;
    case 0xFFE21D:
      Serial.println("Func");
      break;
    case 0xFF22DD:
      Serial.println("left");
      break;
    case 0xFF02FD:
      Serial.println(">>|");
      break;
    case 0xFFC23D:
      Serial.println("Right");
      break;
    case 0xFFE01F:
      Serial.println("Down");
      break;
    case 0xFFA857:
      Serial.println("+");
      break;
    case 0xFF906F:
      Serial.println("Up");
      break;
    case 0xFF6897:
      Serial.println("0");
      break;
    case 0xFF9867:
      Serial.println("100+");
      break;
    case 0xFFB04F:
      Serial.println("200+");
      break;
    case 0xFF30CF:
      Serial.println("1");
      break;
    case 0xFF18E7:
      Serial.println("2");
      break;
    case 0xFF7A85:
      Serial.println("3");
      break;
    case 0xFF10EF:
      Serial.println("4");
      break;
    case 0xFF38C7:
      Serial.println("5");
      break;
    case 0xFF5AA5:
      Serial.println("6");
      break;
    case 0xFF42BD:
      Serial.println("7");
      break;
    case 0xFF4AB5:
      Serial.println("8");
      break;
    case 0xFF52AD:
      Serial.println("9");
      break;
    default:
      break;
    }
    key_value = results.value;
    irrecv.resume();
  }
}
