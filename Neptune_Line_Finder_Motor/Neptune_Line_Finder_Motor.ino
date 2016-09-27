

#include <stdlib.h>
#include <Wire.h>
#include "Seeed_MiniI2CMotorDriver.h"


#define LINE_FINDER_PIN    A5

#define MOTOR_RUN_TIME    5000 // Time in ms
#define MOTOR_SPEED    64 // Max is 256

#define RANDOM_MAX    3


MiniI2CMotorDriver miniI2CMotorDriver(5, 6);


void setup()
{
    Serial.begin(115200);
    Serial.print("Line finder motor.\r\n");
        
    pinMode(13, OUTPUT);
    for(int i=0;i<2; i++)
    {
        digitalWrite(13, HIGH);
        delay(500);
        digitalWrite(13, LOW);
        delay(500);
    }
    digitalWrite(13, HIGH);
    
    pinMode(LINE_FINDER_PIN, INPUT);
    miniI2CMotorDriver.Driver(0, 0);
    miniI2CMotorDriver.Driver(1, 0);
}

void loop()
{
    unsigned char data = 0;
    
    if(digitalRead(LINE_FINDER_PIN) == LOW)
    {
        data = random(RANDOM_MAX);
        if(data == 1)
        {
            miniI2CMotorDriver.Driver(0, 63);
            miniI2CMotorDriver.Driver(1, -63);
            delay(random(MOTOR_RUN_TIME) + 1000);
            miniI2CMotorDriver.Driver(0, 0);
            miniI2CMotorDriver.Driver(1, 0);
        }
        while(digitalRead(LINE_FINDER_PIN) == LOW);
    }
    
    delay(50);
}
