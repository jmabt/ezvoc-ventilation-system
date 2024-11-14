
#ifndef UI_h
#define UI_h

#include <LiquidCrystal_I2C.h>
#include <Arduino.h>
#include <Button.h>
#include <sensors.h>
#include <control.h>

enum state {
    mainScreen = 0,
    good = 1,
    ok = 2,
    poor = 3,
    menu = 4
};


class UI{
    friend class software_test; // code testing class

    private:
    Button b; //button object
    sensors s; // sensor object
    control c; // control objecg
	LiquidCrystal_I2C lcd; // lcd display
    
    
    int state = 1 ;
    uint16_t userPPM = 375, userTVOC = 40, userC02 = 400, userAQI = 2; // user set values for air quality
    uint16_t ppm = 0;
    uint16_t tvoc = 0;
    uint16_t co2 = 0;
    uint16_t aqi = 0;
    
    void callEnter(int option);
    int changeState();


	public:
	void begin(); // tell display to get ready
	void update(); // updates display when called
    void menu(const __FlashStringHelper* menuTitle, const __FlashStringHelper* option[], int options); // writes menu
	UI() : lcd(0x27, 20, 4) {} // class constructor
    void mainScreen(); // writes the main display screen
    int returnState();


};
#endif 
