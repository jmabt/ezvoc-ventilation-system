#include "control.h"

#define amp (A0)
#define fanc (A1)
#define servo (6)
#define speaker (9)
const int chipSelect = 10;  // CS pin for SD card module

void control::begin(){

    st.attach(servo); // attach to PWM pin 3
    pinMode(amp, OUTPUT); // relay amplifier control
    pinMode(fanc, OUTPUT); // relay ventilation control

    digitalWrite(amp, LOW);
    digitalWrite(fanc, LOW);

    delay(500);

    digitalWrite(amp, HIGH);
    digitalWrite(fanc, HIGH);
    
    if (!SD.begin(chipSelect)) {
      Serial.println(F("SD card failed or not present."));
      return;
    }
    
    //audio.speakerPin = 9;  // Set the output pin (9 or 10 on most Arduinos)
   // audio.setVolume(5);    // Volume level (0 to 7)

}

void control::setServo(int state){

    switch (state){
        case 1:
            Serial.println(F("setting servo to 0"));
            Serial.println(state);
            st.write(0); // close shutter
            break;
        case 2:
            Serial.println(F("setting servo to 90"));
            Serial.println(state);
            st.write(90); // open shutter midway
             break;
        case 3:
            Serial.println(F("setting servo to 180"));
            Serial.println(state);
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
                tone(9, 5000); // Pin 9, frequency 100 Hz            digitalWrite(amp, HIGH);
                delay(1500);
                noTone(9);
             break;
        case 2:
            digitalWrite(amp, LOW);
            delay(300);
                tone(9, 2500); // Pin 9, frequency 100 Hz            digitalWrite(amp, HIGH);
                delay(1500);
                noTone(9);
            digitalWrite(amp, HIGH);
             break;
        case 3:
            digitalWrite(amp, LOW);
            delay(300);
                tone(9, 1250); // Pin 9, frequency 100 Hz            digitalWrite(amp, HIGH);
                delay(1500);
                noTone(9);
            digitalWrite(amp, HIGH);
             break;
    }

}

