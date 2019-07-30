/************************************************************************************************************************************************************************                                              
 * - Author               : Shafiqur Khan, Lena Khoshrof, John (Yanni) Kitsios
 * - Main purpose         : iTEST Activity                                                                               
 * - Copyright (c) holder : All rights reserved
 * - License              : iTEST 
 * - Date                 : 07/26/2019
 * ***********************************************************************************************************************************************************************/
 
 /*********************************** NOTE **************************************/
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are met:

// * Redistributions of source code must retain the above copyright notice, this
//  list of conditions and the following disclaimer.

// * Redistributions in binary form must reproduce the above copyright notice,
//  this list of conditions and the following disclaimer in the documentation
//  and/or other materials provided with the distribution.

// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
// AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
// IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED


/*
    RAD(Clawbot)
    TEAM: {
      Dr. Walkot, Mr. Kiefer, Shafiqur Khan, Nischal Thapa
      Lena Khosrof, John (Yanni) Kitsios, Dushan Persaud
    }

    Configuration:
    Left Motor(10, 9)     leftColorSensor(11)       rightColorSensor(13)
    Right Motor(6, 6)     centerColorSensor(12)     IRSensor()
    ClawMotor(7, 8)       elbowMotor(2, 4)          RGB Led(11, 12, 13)

 */


#include "motor.h"
#include "sensor.h"
#include "robot.h"


robot rad;

void setup () {
  rad.begin();

}


void loop() {
  rad.sortCup();

}

