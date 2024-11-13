
#define SEALEVELPRESSURE_HPA (1013.25)
#include <Adafruit_Sensor.h> // needed for all Adafruit libraries
#include "Adafruit_PM25AQI.h"
#include "ScioSense_ENS160.h"
#include <SoftwareSerial.h>
#include <Adafruit_AHTX0.h>
#include <LiquidCrystal_I2C.h>
#include <Servo.h>
#define amp (A0)
#define fanc (A1)
#define servo (3)
#define speaker (9)

SoftwareSerial pmSerial(2,3);
Adafruit_PM25AQI aqi = Adafruit_PM25AQI();
PM25_AQI_Data data;
ScioSense_ENS160 ens160(0x53);
Adafruit_AHTX0 aht;
LiquidCrystal_I2C lcd(0x27, 20, 4);
Servo st;


uint16_t temper = 0, humid = 0;

void setup(){
    Serial.begin(115200);
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

    pinMode(4, INPUT);
    pinMode(5, INPUT);
    pinMode(6, INPUT);
    pinMode(7, INPUT);
    pinMode(LED_BUILTIN, OUTPUT);

    st.attach(servo); // attach to PWM pin 3
    pinMode(amp, OUTPUT); // relay amplifier control
    pinMode(fanc, OUTPUT); // relay ventilation control

    digitalWrite(amp, LOW);
    digitalWrite(fanc, LOW);

  lcd.init();
  lcd.backlight();

    Serial.println("Prepping");
    delay(5000);  // wait for sensors to work

    

}

int checkPM25(){

    PM25_AQI_Data data;
  
  while (! aqi.read(&data)) {} // read
    uint16_t tvoc = data.particles_03um + data.particles_05um + data.particles_10um + data.particles_25um;
                Serial.println("pm25 check"); 
      if (tvoc <= 0 || tvoc > 50000){
        Serial.println("PM25 is reporting some strange values."); 
        Serial.println(tvoc);
        return -1; 
      }
      return 1;
}
int checkENS(){
    // returns ens160 tvoc
                  Serial.println("tvoc check"); 
    ens160.measure(true);
      uint16_t tvoc = ens160.getTVOC();
      if (tvoc <= 0 || tvoc > 50000){
        Serial.println("ENS TVOC is reporting a strange value."); 
        Serial.println(tvoc);
        return -1; 
      }
      return 1;
}

int checkco2(){
              Serial.println("co2 check"); 
       uint16_t tvoc = ens160.geteCO2();
      if (tvoc <= 0 || tvoc > 50000){
        Serial.println("ENS c02 is reporting a strange value."); 
        Serial.println(tvoc);
        return -1; 
      }
      return 1;
}

int checkaqi(){
  
      uint16_t tvoc = ens160.getAQI();
                    Serial.println("aqi check"); 
      if (tvoc < 0 || tvoc > 100){
        Serial.println("ENS AQI is reporting a strange value."); 
        Serial.println(tvoc);
        return -1; 
      }
      return 1;
}

void getEvent(){
    // gets sensor information from sensor
    // stores to temper and humid private variables
    
    sensors_event_t hum, temp;
    aht.getEvent(&hum, &temp);
    temper = temp.temperature;
    humid = hum.relative_humidity;
    
}
 
int checktemp(){

    
     getEvent();
      Serial.println("temp check"); 
      if (temper < -100 || temper > 100){
        Serial.println("AHT20 may be reporting a strange temp value."); 
        Serial.println(temper);
        return -1; 
      }
      return 1;
 
 }
 
uint16_t checkhum(){
                    Serial.println("hum check"); 
       if (humid <= 0 || humid > 100){ 
        Serial.println("AHT20 may be reporting a strange humidity value."); 
        Serial.println(humid);
        return -1; 
      }
      return 1;
    
    
}
 
void loop(){
  int fails = 0;

  int bt1 = 0, bt2 = 0, bt3 = 0, bt4 = 0;

  if (checkPM25() == -1) fails++;
  if (!checkENS() == -1) fails++;
  if(!checkco2() == -1) fails++;
  if (!checkaqi() == -1) fails++;
  if (!checktemp() == -1) fails++;

  Serial.println("Total sensor fails:");
  Serial.println(fails);

  // button check

  while (!digitalRead(4)) {}; 
  // wait for button press

  Serial.println("Button pressed."); 
  digitalWrite(LED_BUILTIN, HIGH);   
  delay(100);
  digitalWrite(LED_BUILTIN, LOW);   

  while (!digitalRead(5)) {}; 
  // wait for button press

  Serial.println("Button pressed."); 
  digitalWrite(LED_BUILTIN, HIGH);   
  delay(100);
  digitalWrite(LED_BUILTIN, LOW);   

  while (!digitalRead(6)) {}; 
  // wait for button press

  Serial.println("Button pressed."); 
  digitalWrite(LED_BUILTIN, HIGH);   
  delay(100);
  digitalWrite(LED_BUILTIN, LOW);   

  while (!digitalRead(7)) {}; 
  // wait for button press

  Serial.println("Button pressed."); 
  digitalWrite(LED_BUILTIN, HIGH);   
  delay(100);
  digitalWrite(LED_BUILTIN, LOW);   

  // relay check
  Serial.println("Relay check, amp followed by fan...");
  digitalWrite(amp, LOW);
  digitalWrite(fanc, LOW);
  delay(500);

  digitalWrite(amp, HIGH);
  digitalWrite(fanc, HIGH);

  // servo check

  Serial.println("Servo check");
  st.write(0);
  delay(1000);
  st.write(180);
  delay(1000);
  st.write(0);

  // screen check
  Serial.println("Screen check");
  
  for (int i = 0; i < 4; i++){
        for (int j = 0;  j < 20; j++){
            lcd.setCursor(j,i);
            lcd.print('#');
        }
    }

  lcd.clear();

  Serial.println("Finished");
  lcd.setCursor(1,1);
  lcd.print("Finished!");
    lcd.setCursor(1,2);
  lcd.print("# of fails, ");
  lcd.setCursor(1,3);
  lcd.print(fails);
  
}
