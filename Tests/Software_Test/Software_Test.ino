#ifndef _SOFTWARE_TEST_H
#define _SOFTWARE_TEST_H
#include <UI.h>


// This code tests the changeState function, which is a vital function. 
class software_test{
  public:
  void test();
  private:
  UI u;
};

software_test t;


void setup() {
// Serial for test info
  Serial.begin(115200);

}

void loop() {

  t.test(); // call test function 
  exit(1);
}
#endif 

void software_test::test(){
  int state  = 0, flag = 0; // state is state returned by changeState, flag is whether we fail or not 
// this is dependent on what the user values are set to. 
  u.ppm = 400; // set some sensor values
  u.tvoc = 50;
  u.co2  = 500;
  u.aqi = 3;

  state = u.changeState(); // call changeState
  Serial.println(state);
  if (state != 3){ // see if it returned the right value 
    Serial.println("changeState failed");
    flag = 1;
  }

   u.ppm = 400; // do it again, but for each of the other two states
  u.tvoc = 10;
  u.co2  = 500;
  u.aqi = 1;

  state = u.changeState();
    Serial.println(state);

  if (state != 2){
    Serial.println("changeState failed");
        flag = 1;
  }

  u.ppm = 200;
  u.tvoc = 10;
  u.co2  = 100;
  u.aqi = 1;

  state = u.changeState();
    Serial.println(state);

  if (state != 1){
    Serial.println("changeState failed");
        flag = 1;
  }

  if (!flag){
    Serial.println("Tests passed");
  }

  return;
  
}
