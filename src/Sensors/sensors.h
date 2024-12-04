
#ifndef sensors_h
#define sensors_h
#define SEALEVELPRESSURE_HPA (1013.25)
#include <Adafruit_Sensor.h> // needed for all Adafruit libraries
#include "Adafruit_PM25AQI.h"
#include "ScioSense_ENS160.h"
#include <SoftwareSerial.h>
#include <Adafruit_AHTX0.h>
/*** 
	This class handles sensors.
	When its member functions are called,
	it returns the values of sensors. 
	***/

class sensors{

	private:
    void getEvent();
    int temper = 0, humid = 0;

	public:
	void begin(); // tell display to get ready
    uint16_t pm25();
    int tvoc();
    int co2();
    int eaqi();
    int temp();
    uint16_t hum();

};
#endif 
