
#ifndef UI_h
#define UI_h

#include <LiquidCrystal_I2C.h>
#include <Arduino.h>
#include <Button.h>
#include <sensors.h>
#include <control.h>

enum state {
    good = 1,
    ok = 2,
    poor = 3
};

enum workingState{
    mainScreen = 0,
    MEnu = 1
};


class UI{
    friend class software_test; // code testing class

    private:
    Button b; //button object
    sensors s; // sensor object
    control c; // control objecg
	LiquidCrystal_I2C lcd; // lcd display
    unsigned long prevTime = 0; // last time we were called
    const unsigned long interval = 15000; // 15 seconds
    int workingState = 0;
    
    //int state = 1 ;
    uint16_t userPPM = 3000, userTVOC = 40, userC02 = 450, userAQI = 2; // user set values for air quality
    uint16_t ppm = 0;
    uint16_t tvoc = 0;
    uint16_t co2 = 0;
    uint16_t aqi = 0;
    
    void callEnter(int option);
    //int changeState();


	public:
	void begin(); // tell display to get ready
	void update(); // updates display when called
    void menu(); // writes menu
	UI() : lcd(0x27, 20, 4) {} // class constructor
    void mainScreen(); // writes the main display screen
    int returnState();
    int state = 1 ;
    int changeState();




};
#endif 
