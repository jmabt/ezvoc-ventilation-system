#include "control.h"

#define amp (A0)
#define fanc (A1)
#define servo (3)
#define speaker (9)


void control::begin(){

    st.attach(servo); // attach to PWM pin 3
    pinMode(amp, OUTPUT); // relay amplifier control
    pinMode(fanc
    , OUTPUT); // relay ventilation control

    digitalWrite(amp, LOW);
    digitalWrite(fanc, LOW);

    delay(500);

    digitalWrite(amp, HIGH);
    digitalWrite(fanc, HIGH);

    if (!SD.begin(cspin)){

    }

    audio.speakerPin = speaker;

}

void control::setServo(int state){

    switch (state){
        case 1:
            st.write(0); // close shutter
            break;
        case 2:
            st.write(90); // open shutter midway
             break;
        case 3:
            st.write(180); // open shutter fully
             break;
    }

}

void control::fan(int state){

        switch (state){
        case 1:
            digitalWrite(fanc, HIGH);
             break;
        case 2:
            digitalWrite(fanc, LOW);
             break;
            // todo : speed control
        case 3:
            digitalWrite(fanc, LOW);
             break;
            // todo : speed control
    }

}

void control::announce(int state){

        switch (state){
        case 1:
            digitalWrite(amp, LOW);
            delay(300);
            audio.play(F("stG.wav"));
            digitalWrite(amp, HIGH);
             break;
        case 2:
            digitalWrite(amp, LOW);
            delay(300);
            audio.play(F("stG.wav"));
            digitalWrite(amp, HIGH);
             break;
        case 3:
            digitalWrite(amp, LOW);
            delay(300);
            audio.play(F("stG.wav"));
            digitalWrite(amp, HIGH);
             break;
    }

}

