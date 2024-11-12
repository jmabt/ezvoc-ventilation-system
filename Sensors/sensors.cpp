#include "sensors.h"

SoftwareSerial pmSerial(2,3);
Adafruit_PM25AQI aqi = Adafruit_PM25AQI();
PM25_AQI_Data data;
ScioSense_ENS160 ens160(0x53);
//Adafruit_SGP40 sgp;

void sensors::begin(){
    /* PMS25 */
    pmSerial.begin(9600);
    if (! aqi.begin_UART(&pmSerial)) { // connect to the sensor over software serial
        //Serial.println("PM2.5 Not found.");
        while (1) delay(10);
    }
    
    /* ENS160 */
    ens160.begin();
    if (!ens160.available()){
        //Serial.println("ENS160 not found.");
    }
    
    if (!ens160.setMode(ENS160_OPMODE_STD)){
        //Serial.println("Standard mode failed.");
    }
    /*

    if (!sgp.begin())
        */
}

uint16_t sensors::pm25(){
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

uint16_t sensors::tvoc(){
    // function returns the average TVOC gathered by the ENS160 and SGP40
    // one sensor hands to be higher, one tends to be lower, and while
    // there is overlap they don't measure all the same gases
    
    // this method yields a slightly more realistic result
    Serial.println(ens160.getTVOC());
    //Serial.println(sgp.measureRaw());

    ens160.measure(true);
    
    return ens160.getTVOC();
}

uint16_t sensors::co2(){
    return ens160.geteCO2();
}

uint16_t sensors::eaqi(){
    return ens160.getAQI();
}
