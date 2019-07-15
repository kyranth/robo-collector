#include "robot.h"
#include "motor.h"
#include "sensor.h"
#include "Arduino.h"
#include <IRremote.h>

robot::robot(){}

void robot::begin(){
	Serial.begin(9600);
	Serial.println("Robot Ready");
	//irrecv.enableIRIn();
  	//irrecv.blink13(true);
}
/* 
void robot::manualControl(){
	if (irrecv.decode(&results)) {
 
        if (results.value == 0XFFFFFFFF)
          results.value = key_value;

        switch(results.value){
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
          break ;  
          case 0xFFC23D:
          Serial.println("Right");
          break ;   

          case 0xFFE01F:
		  leftMotor.backward(200);
		  rightMotor.backward(200);
          Serial.println("Down");
          break ;
		  case 0xFF906F:
		  leftMotor.forward(200);
		  rightMotor.forward(200);
          Serial.println("Up");
          break ;

          case 0xFFA857:
          Serial.println("+");
          break ;
          case 0xFF6897:
          Serial.println("0");
          break ;  
          case 0xFF9867:
          Serial.println("100+");
          break ;
          case 0xFFB04F:
          Serial.println("200+");
          break ;


          case 0xFF30CF:
          Serial.println("1");
          break ;
          case 0xFF18E7:
          Serial.println("2");
          break ;
          case 0xFF7A85:
          Serial.println("3");
          break ;
          case 0xFF10EF:
          Serial.println("4");
          break ;
          case 0xFF38C7:
          Serial.println("5");
          break ;
          case 0xFF5AA5:
          Serial.println("6");
          break ;
          case 0xFF42BD:
          Serial.println("7");
          break ;
          case 0xFF4AB5:
          Serial.println("8");
          break ;
          case 0xFF52AD:
          Serial.println("9");
          break ;
          default:
          digitalWrite(11, LOW); 
          break;     
        }
        key_value = results.value;
        irrecv.resume();
	}
}

*/