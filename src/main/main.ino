#include <UI.h>
#include <sensors.h>
#include <Button.h>
#include <control.h>


#define SLOTX 6
#define CYCLEX 4
#define SLOT_T 5000

int newState = 1;
int flag = 0;

// nov 27th
// - no servo because uno keeps writing gibberish, Mega 2560 works oddly
// - no microsd card based speech, not enough memory
// - stability increased significantly from pulling SD card libs out (free memory skyrocketed)


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
        for (int cycle=0; cycle<CYCLEX; cycle++){
          (*ttable[slot][cycle])();
        }
      }
  

}
