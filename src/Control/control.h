
#ifndef CONTROL_h
#define CONTROL_h
 // handles control of relays, ventilation fan, amp

#include <Servo.h>
#include <Arduino.h>




class control{

public:
    void begin();
    void setServo(int state); // receives current state and opens shutter
    void fan(int state);
    void announce(int state);
    void servomap(int angle, int pin);


};
#endif 
