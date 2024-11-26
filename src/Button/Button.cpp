#include "Button.h"

void Button::begin(){
    // set pin types
    pinMode(buttonUp, INPUT);
    pinMode(buttonDown, INPUT);
    pinMode(buttonEnter, INPUT);
    pinMode(buttonBack, INPUT);
    

}


int Button::button(){
    // return value based on button read
    // 3-6 were the original button pins, not anymore, but i coded around that idea
    
    if (digitalRead(buttonUp)){
        return 3;
    }
    if (digitalRead(buttonDown)){
        return 4;
    }
    if (digitalRead(buttonEnter)){
        return 5;
    }
    if (digitalRead(buttonBack)){
        return 6;
    }
    
    return 0;
}
