#include <UI.h>
#include <sensors.h>
#include <Button.h>
#include <control.h>


#define SLOTX 6
#define CYCLEX 4

int newState = 1;
int flag = 0;

//last major code change nov 27th
// - no servo because uno keeps writing gibberish, Mega 2560 works oddly
// - no microsd card based speech, not enough memory
// - stability increased significantly from pulling SD card libs out (free memory skyrocketed)

/***
This main.ino file is the main loop for the EzVOC ventilation system project.
The main file here handles state changes, and calls various functions using a 
table based realtime scheduler. The size of the table is SLOTX * CYCLEX. The
member functions in this file call functions in other classes, namely Sensors, UI,
Button, Control. The member functions themselves are called by a member function, 
ttable. Ttable is called by nested for loops in the loop() function. The member 
functions generally only call functions in other classes. Very few of them actually
do any sort of major calculation or checking - generally they just call functions and
occasionally pass values. 

The ttable function is used in place of a basic loop based function. It increases 
responsiveness by checking button presses significantly more often, and helps reduce
state deboucing by calling the state change functions in UI.h only once per loop. 
The table method was inspired by an assignment completed in UB's CSE-321 course 
in the Fall 2024 semester, and modified to work for the arduino uno. 
***/ 

UI d;
sensors s;
Button button;
control c;

 
 #define servo (A5)

void setup() {

  Serial.begin(115200); // debug
  d.begin();
  s.begin();
  c.begin();
  button.begin();

}


void getState(){
  newState = d.changeState();
}

void callMain(){
    d.mainScreen();
}

void menuCheck(){
    if (button.button() > 0) {
    d.menu();
  }
}

void checkStateChange(){
    if (newState != d.state){
     flag = 1;
  }
}

void flagCheck(){
    if (flag){
      d.state = newState;
      Serial.println(F("---- STATE CHANGE ----"));
      Serial.println(F("State changed to: "));
      Serial.println(newState);
      c.setServo(d.state);
      c.fan(d.state);
      c.announce(d.state);
  }
  flag = 0;
}

void (*ttable[SLOTX][CYCLEX])() = {
    {callMain, menuCheck, callMain, menuCheck},
    {callMain, menuCheck, callMain, menuCheck},
    {callMain, getState, callMain, menuCheck},
    {callMain, menuCheck, callMain, menuCheck},
    {callMain, checkStateChange, callMain, menuCheck},
    {callMain, flagCheck, callMain, menuCheck}};



void loop() {
      /* mildly more advanced scheduling than just calling functions in the loop */
      /* this was taken and modified from a previous class assignment, where we did table based scheduling */
      /* this greatly increased menu resposniveness though. the original plan was to have buttons be interrupts, 
      but since only 2 pins that were in use have hardware interrupts, this is the best alternative.*/

      for (int slot=0; slot < SLOTX; slot++){
        for (int cycle=0; cycle < CYCLEX; cycle++){
          (*ttable[slot][cycle])();
        }
      }
  

}
