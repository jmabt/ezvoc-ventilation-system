
#ifndef CONTROL_h
#define CONTROL_h
 // handles control of relays, ventilation fan, amp

#include <Servo.h>
#include <Arduino.h>

/***
 Control class:

 Handles physical hardware controls. Functions are called with states, 
this class turns those states into physical actions. Sets servo angle,
turns fan on and off, turns speaker amp on and off, plays tones thru speaker.
 ***/


class control{

public:
    void begin();
    void setServo(int state); // receives current state and opens shutter
    void fan(int state);
    void announce(int state);
    void servomap(int angle, int pin);
private:
    Servo st;

};
#endif 
