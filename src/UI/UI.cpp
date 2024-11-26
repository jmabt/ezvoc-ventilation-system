#include "UI.h"


void UI::begin(){
  lcd.init();
  lcd.backlight();
  lcd.clear();
}

void UI::update() {
    
    int newState = 1;
    newState = changeState();
    
    if (newState != state){
        state = newState;
        Serial.println(F("---- STATE CHANGE ----"));
        Serial.println(F("State changed to: "));
        Serial.println(newState);
        c.setServo(state);
        c.fan(state);
        c.announce(state);
    }
}


int UI::changeState(){
    int count = 0;
    unsigned long previousTime = 0;
    
    /* this should only run every 15 seconds */
    unsigned long currentTime = millis(); // get the current time
    
    if (currentTime - previousTime < interval) {
      return 0; // 15 seconds have passed
    }
    previousTime = currentTime; // update the last execution time
  
    ppm = s.pm25();
    tvoc = s.tvoc();
    co2 = s.co2();
    aqi = s.eaqi();
    // see how many are over limit
    if (ppm >= userPPM){
        count++;
    }
    if (tvoc >= userTVOC){
        count++;
    }
    if (co2 >= userC02){
        count++;
    }
    if (aqi >= userAQI){
        count++;
    }
    // find new state based on hjow many over limit
    if (count < 1){
        return good;
    }
    if (count == 2 || count == 3){
        return ok;
    }
    if (count > 3){
        return poor;
    }

}

// looking at older commits will show a much more advanced version of this menu code
// what's better than something advanced is something that reliably works
// this has been simplified
void UI::menu() {
    Serial.println(F("---- STATE CHANGE ----"));
    Serial.println(F("State changed to: "));
    Serial.println(state);

    int selection = 1;

    // clear LCD, display required text
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print(F("Set Thresholds"));

    while (b.button() != 6) {

    lcd.setCursor(1, 1); // row 1 column 1
    lcd.print(F("1. PM25"));
    lcd.setCursor(11, 1);
    lcd.print(F("2. AQI"));

    lcd.setCursor(1, 2);
    lcd.print(F("3. CO2"));
    lcd.setCursor(11, 2);
    lcd.print(F("4. HUM"));

    if (b.button() == 3){
        selection++;
        selection = (selection == 5 ? 1 : selection); // wrap around - max option is 4 so if over 4 return to 1
    }
    else if (b.button() == 4){
        selection--;
        selection = (selection == 0 ? 4 : selection); // wrap around - min option is 1 so if less than 1 go to 4
    }
    if (b.button() == 5){
        callEnter(selection);
        return;
    }

    lcd.setCursor(0,3);
    lcd.print(F("Current Option: "));
    lcd.setCursor(17,3);
    lcd.print(selection);

    delay(100); // debouncing

    }
    lcd.clear();
}


void UI::callEnter(int option) {
    int newVal = 0;

    delay(1000);

    switch (option) {
                case 1: newVal = userPPM; break; // for ease of use, set newVal to the previous value so user can increment/decrement from that rather than zero
                case 2: newVal = userAQI; break;
                case 3: newVal = userC02; break;
                case 4: newVal = userTVOC; break;
            }

    lcd.clear();

    while (true) {
        lcd.clear(); // clear display and get new value
        lcd.setCursor(0, 1);
        lcd.print("New Value: ");
        lcd.setCursor(12, 1);
        lcd.print(newVal);

        if (b.button() == 3) {  // increment value
            newVal++;
        } else if (b.button() == 4) {  // decrement value
            newVal--;
        } else if (b.button() == 5) {  // save value
            // check if input is valud
            if (newVal < 0) {
                lcd.clear();
                lcd.print(F("Err: Negative"));
                delay(1000); // show error
                continue;    // restart loop
            }
            if (option == 4 && newVal > 100) { // if we're setting humidity which is percent then > 100 is not okay
                lcd.clear();
                lcd.print(F("Err: Out Of Range"));
                delay(1000); // show error
                continue;    // restart loop
            }

            // save value
            switch (option) {
                case 1: userPPM = newVal; break;
                case 2: userAQI = newVal; break;
                case 3: userC02 = newVal; break;
                case 4: userTVOC = newVal; break;
            }

            // clear screen, exit
            lcd.clear();
            return;
        } else if (b.button() == 6) {  // cancel
            lcd.clear();
            return;
        }

        delay(100); // debounce
    }
    lcd.clear();
}



void UI::mainScreen(){
    
    workingState = 0;

    lcd.setCursor(0,0);
    lcd.print(F("Status:"));
    lcd.setCursor(9,0);

    switch(state){
        case 1:
            lcd.print(F("Good"));
             break;
        case 2:
            lcd.print(F("-OK-"));
             break;
        case 3:
            lcd.print(F("Poor"));
             break;
        default:
            lcd.print(F("..."));
            break;
    }
    
    lcd.setCursor(0,1);
    lcd.print(F("PPM:"));
    lcd.setCursor(5,1);
    if (ppm != -1){
        lcd.print(ppm, 1); // one decimal point
    }

    lcd.setCursor(10,1);
    lcd.print(F("TVOC:"));
    lcd.setCursor(16,1);
    if (tvoc != -1){
        lcd.print(tvoc, 1); // one decimal point
    }

    lcd.setCursor(0,2);
    lcd.print(F("Temp:"));
    lcd.setCursor(6,2);
    lcd.print(s.temp());
    lcd.setCursor(11,2);
    lcd.print(F("Hum%:"));
    lcd.setCursor(15,2);
    lcd.print(s.hum(), 1);

    lcd.setCursor(0,3);
    lcd.print(F("C02:"));
    lcd.setCursor(5,3);
      if (co2 != -1){
        lcd.print(co2, 1); // one decimal point
    }

    lcd.setCursor(11,3);
    lcd.print(F("AQI:"));
    lcd.setCursor(15,3);
    if (aqi != -1){
        lcd.print(aqi, 1); // one decimal point
    }
    
}

int UI::returnState(){
    return state;
}
