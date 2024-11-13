
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


class UI{

	private:
    Button b;
    sensors s;
    control c;
    char display[4][20];
	void writeScreen(); // writes to screen when called
    void clearArray(); // clears display array
	LiquidCrystal_I2C lcd;
    void callEnter(int option);
    uint16_t ppm = 0;
    uint16_t tvoc = 0;
    uint16_t co2 = 0;
    uint16_t aqi = 0;
    int changeState();
    int state = 1 ;
    uint16_t userPPM = 375, userTVOC = 40, userC02 = 400, userAQI = 2; // user set values for air quality


	public:
	void begin(); // tell display to get ready
	void update(); // updates display when called
    void menu(const __FlashStringHelper* menuTitle, const __FlashStringHelper* option[3]); // writes menu
	UI() : lcd(0x27, 20, 4) {} // class constructor
    void mainScreen(); // writes the main display screen
    int returnState();


};
#endif 
