
#ifndef BUTTON_H
#define BUTTON_H
#include <Arduino.h>

#define buttonUp (8) // define button and button pins
#define buttonDown (7)
#define buttonEnter (5)
#define buttonBack (4)

class Button{
    
    public:
    int button(); // check if button is pressed, if it is, return what button was pressed
    void begin(); // configure pins

};
#endif
