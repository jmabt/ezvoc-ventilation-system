#include "sensors.h"

/*
In a perfect world, these are in the .h file's private section.
For some reason, putting them here reduces dynamic memory usage????
Not only that but one of them generated linker errors when in the .h,
so they're here.
*/

SoftwareSerial pmSerial(2,3);
Adafruit_PM25AQI aqi = Adafruit_PM25AQI();
PM25_AQI_Data data;
ScioSense_ENS160 ens160(0x53);
Adafruit_AHTX0 aht;



void sensors::begin(){
    /* PMS25 */
    pmSerial.begin(9600);
    if (! aqi.begin_UART(&pmSerial)) { // connect to the sensor over software serial
        Serial.println(F("PM2.5 Not found."));
        while (1) delay(10);
    }
    
    /* ENS160 */
    ens160.begin();
    if (!ens160.available()){
        Serial.println(F("ENS160 not found."));
    }
    
    if (!ens160.setMode(ENS160_OPMODE_STD)){
        Serial.println(F("Standard mode failed.")); 
    }
    
    /*AHT20*/
    if (!aht.begin()){
        Serial.println(F("AHT20 not found."));
    }

}

uint16_t sensors::pm25(){
    // call pm25 sensor and sum up all particulate data under 25uM
    // return that value
    static int count = 0;
    static int fails = 0;
    static bool flag = false;
    float tvoc = 0;
    
    if (flag){
        tvoc = 0;
        flag = false;
    }
    
    if (!aqi.read(&data)) {
      delay(500);
      return -1;
    }

    tvoc += data.particles_03um + data.particles_05um + data.particles_10um + data.particles_25um;
    
    return tvoc;
}

int sensors::tvoc(){
    // returns ens160 tvoc

    ens160.measure(true); // tell sensor to measure
    
    return ens160.getTVOC(); // return the tvoc value
}

int sensors::co2(){
    return ens160.geteCO2(); // return co2 value
}

int sensors::eaqi(){
    return ens160.getAQI(); // return the AQI (air quality index) value
}

void sensors::getEvent(){
    // gets sensor information from sensor
    // stores to temper and humid private variables
    
    sensors_event_t hum, temp;
    aht.getEvent(&hum, &temp);
    temper = temp.temperature;
    humid = hum.relative_humidity;
    
}
 
int sensors::temp(){
     
    // calls getEvent to get updated temp and sensor values
    // returns new temperature
    getEvent();
    return temper;
 
 }
 
uint16_t sensors::hum(){
    
    // this does not need to call getEvent()
    // at the moment this follows temperature reading only
    // temp function calls getEvent already
    
    return humid; // why did i make this a function?
    // better yet, why did i make humid a private variable?
    
}
 
