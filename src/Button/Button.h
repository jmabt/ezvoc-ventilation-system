
#ifndef BUTTON_H
#define BUTTON_H
#include <Arduino.h>

#define buttonUp (4) // define button and button pins
#define buttonDown (5)
#define buttonEnter (7)
#define buttonBack (8)

/***
Button class:

Handles buttons, and returning what button was called.
***/

class Button{
    
    public:
    int button(); // check if button is pressed, if it is, return what button was pressed
    void begin(); // configure pins

};
#endif
