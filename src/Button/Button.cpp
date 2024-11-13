#include "Button.h"

void Button::begin(){
    pinMode(4, INPUT);
    pinMode(5, INPUT);
    pinMode(6, INPUT);
    pinMode(7, INPUT);
}


int Button::button(){
    
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
