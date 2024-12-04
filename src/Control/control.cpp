#include "control.h"

#define amp (A0)
#define fanc (A1)
#define servo (A5)
#define speaker (9)


void control::begin(){

    st.attach(servo); // attach to PWM pin 3
    pinMode(amp, OUTPUT); // relay amplifier control
    pinMode(fanc, OUTPUT); // relay ventilation control

    digitalWrite(amp, LOW);
    digitalWrite(fanc, LOW);

    delay(500);

    digitalWrite(amp, HIGH);
    digitalWrite(fanc, HIGH);

    servomap(0, 11); // servomap writes pure pwm to servo
                    // the Servo library uses a lot of timers to write values to servos
                    // something is interfering, it writes pure garbage to the servo over all pwm outputs
                    // i can't replicate that on a Mega so it is likely just an Uno thing

    //audio.speakerPin = 9;  // Set the output pin (9 or 10 on most Arduinos)
   // audio.setVolume(5);    // Volume level (0 to 7)

}
void control::servomap(int angle, int pin){
// Last ditch attempt at getting servo to work
    // Write PWM directly to servo over any pin capable at output.
    // Tested on other sketches, works. 
  int pulse = 0;
  pulse = map(angle, 0, 180, 1000, 2000);
  digitalWrite(pin, HIGH);
  delayMicroseconds(pulse);
  digitalWrite(pin, LOW);
  delayMicroseconds(20 - pulse);

}

void control::setServo(int state){
    // Given state, tell servo to do things. 

    st.attach(servo); // attach to PWM pin 3

    switch (state){
        case 1:
             for (int i = 180; i > -1; i--){
    servomap(i, servo);
             }


            break;
        case 2:
            for (int i = 0; i <180; i++){
    servomap(i, servo);
  }

             break;
        case 3:

              for (int i = 0; i <180; i++){
    servomap(i, servo);
  }

             break;
    }


}

void control::fan(int state){
// Given state, turn on and off fan
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
    // Given state, turn on and off fan
    // Also, play tone thru speaker
    

        switch (state){
        case 1:
            digitalWrite(amp, LOW);
                delay(300);
                tone(9, 5000); // Pin 9, frequency 100 Hz            digitalWrite(amp, HIGH);
                delay(1500);
                noTone(9);
            digitalWrite(amp, HIGH);

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

