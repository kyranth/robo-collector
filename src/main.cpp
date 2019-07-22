/*
    JEFF BOB THE 3RD(Clawbot)
    License: iTEST NYU Robotis Course
    TEAM: {
      Dr. Walkot, Mr. Kiefer, Shafiqur Khan, Nishal Thapa
      Lena Khosrof, Yanni, Dushan Persaud
    }

    Configuration:
    Left Motor(10, 9)     leftColorSensor(11)       rightColorSensor(13)
    Right Motor(6, 6)     centerColorSensor(12)     IRSensor()
    ClawMotor(7, 8)       elbowMotor(2, 4)          RGB Led(11, 12, 13)

 */


#include "motor.h"
#include "sensor.h"
#include "robot.h"
#include <IRremote.h>
#include <HCSR04.h>

int defualtSpeed = 80;

motor elbow(2, 4);
motor claw(7, 8);
robot jeffbobthe3rd;
UltraSonicDistanceSensor distanceSensor(A4, A3);

const byte RECV_PIN = 3;
IRrecv irrecv(RECV_PIN);
decode_results results;
unsigned long key_value = 0;

void manualControl(){
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
          jeffbobthe3rd.turnLeft();
          break;
          case 0xFF02FD:
          Serial.println("Play/Pause");
          break ;  
          case 0xFFC23D:
          Serial.println("Right");
          jeffbobthe3rd.turnRight();
          break ;   
          case 0xFFE01F:
          Serial.println("Down");
          jeffbobthe3rd.backward(defualtSpeed);
          break ;
		      case 0xFF906F:
          Serial.println("Up");
          jeffbobthe3rd.forward(defualtSpeed);
          break ;
          case 0xFFA857:
          Serial.println("Vol+");
          break ;
          case 0xFF6897:
          Serial.println("0");
          break ;  
          case 0xFF9867:
          Serial.println("EQ");
          break ;
          case 0xFFB04F:
          Serial.println("ST/REPT");
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
          
          break;     
        }
        key_value = results.value;
        irrecv.resume();
	}
}


void setup () {
  jeffbobthe3rd.begin();
  irrecv.enableIRIn();
  irrecv.blink13(true);

}

void loop() {
  /*
if(irrecv.decode(&results)) {
  if (results.value == 0XFFFFFFFF)
    results.value = key_value;
    switch(results.value) {
      case 0xFF6897:
      Serial.println("0: Autonomous Mode");
      jeffbobthe3rd.followLine();
      break ;

      case 0xFF30CF:
      Serial.println("1: Manual Mode");
      manualControl();
      break ;
    }
    key_value = results.value;
    irrecv.resume();
  }
*/
  int centimeters = distanceSensor.measureDistanceCm();
  Serial.println(centimeters);
  delay(100);
  if(0 < centimeters < 5) {
    jeffbobthe3rd.setColor(200, 0, 0);
    claw.open();

  } else if (centimeters > 5) {
    jeffbobthe3rd.setColor(0, 200, 0);
    claw.close();
    delay(2000);
    claw.open();
  }
  
}