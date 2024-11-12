
#ifndef sensors_h
#define sensors_h
#define SEALEVELPRESSURE_HPA (1013.25)
#include <Adafruit_Sensor.h> // needed for all Adafruit libraries
#include "Adafruit_PM25AQI.h"
#include "ScioSense_ENS160.h"
#include "Adafruit_SGP40.h"
#include <SoftwareSerial.h>

class sensors{

	private:

	public:
	void begin(); // tell display to get ready
    uint16_t pm25();
    uint16_t tvoc();
    uint16_t co2();
    uint16_t eaqi();

};
#endif 
