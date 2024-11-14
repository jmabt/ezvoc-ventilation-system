
#ifndef CONTROL_h
#define CONTROL_h
 // handles control of relays, ventilation fan, amp

#include <Servo.h>
#include <Arduino.h>
#include <SD.h>
//#include <SPI.h>
//#include <SD.h>
//#include <TMRpcm.h>




class control{

public:
    void begin();
    void setServo(int state); // receives current state and opens shutter
    void fan(int state);
    void announce(int state);
    //TMRpcm audio;


private:
    Servo st; // shutter servo
};
#endif 
