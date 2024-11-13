#ifndef _SOFTWARE_TEST_H
#define _SOFTWARE_TEST_H
#include <UI.h>



class software_test{
  public:
  void test();
  private:
  UI u;
};

software_test t;


void setup() {
  // put your setup code here, to run once:

}

void loop() {
  // put your main code here, to run repeatedly:
  t.test();
  exit(1);
}
#endif 

void software_test::test(){
  int state  = 0, flag = 0;

  u.ppm = 400;
  u.tvoc = 50;
  u.co2  = 500;
  u.aqi = 3;

  state = u.changeState();
  if (state != 3 || state != u.state){
    Serial.println("changeState failed");
    flag = 1;
  }

   u.ppm = 400;
  u.tvoc = 10;
  u.co2  = 500;
  u.aqi = 1;

  state = u.changeState();
  if (state != 2 || state != u.state){
    Serial.println("changeState failed");
        flag = 1;
  }

  u.ppm = 200;
  u.tvoc = 10;
  u.co2  = 100;
  u.aqi = 1;

  state = u.changeState();
  if (state != 1 || state != u.state){
    Serial.println("changeState failed");
        flag = 1;
  }

  if (!flag){
    Serial.println("Tests passed");
  }

  return;

  // todo: more error checking
  
}
