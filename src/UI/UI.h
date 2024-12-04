
#ifndef UI_h
#define UI_h

#include <LiquidCrystal_I2C.h>
#include <Arduino.h>
#include <Button.h>
#include <sensors.h>
#include <control.h>
#include <EEPROM.h>

enum state {
    good = 1,
    ok = 2,
    poor = 3
};

enum workingState{
    mainScreen = 0,
    MEnu = 1
};

/***
This class handles the UI. UI is main screen, menu, value storing, etc.
	The class also contains the threshold values set by the user, and 
	the function responsible for getting sensor values and comparing them
to said thresholds. After comparison, it returns a new state value to the calling
function.
	***/ 


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
    
    uint16_t userPPM = 1500, userTVOC = 200, userC02 = 400, userAQI = 2; // user set values for air quality
    uint16_t ppm = 0;
    uint16_t tvoc = 0;
    uint16_t co2 = 0;
    uint16_t aqi = 0;
    
    void callEnter(int option);


	public:
	void begin(); // tell display to get ready
    void menu(); // writes menu
	UI() : lcd(0x27, 20, 4) {} // class constructor
    void mainScreen(); // writes the main display screen
    int returnState();
    int state = 1 ;
    int changeState();




};
#endif 
