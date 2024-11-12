#include "Button.h"


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
