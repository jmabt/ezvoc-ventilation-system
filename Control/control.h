
#ifndef CONTROL_h
#define CONTROL_h
 // handles control of relays, ventilation fan, amp

#include <Servo.h>
#include <Arduino.h>
#include <SD.h>
#include <SPI.h>
#include "TMRpcm.h"



class control{

public:
    void begin();
    void setServo(int state); // receives current state and opens shutter
    void fan(int state);
    void announce(int state);

private:
    Servo st; // shutter servo
    const int cspin = 10; // sd card chip select
    TMRpcm audio;


};
#endif 
