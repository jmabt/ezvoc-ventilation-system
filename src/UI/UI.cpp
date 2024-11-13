#include "UI.h"


void UI::begin(){
  lcd.init();
  lcd.backlight();
    for (int i = 0; i < 4; i++){
        for (int j = 0;  j < 20; j++){
            display[i][j] = ' ';
        }
    }
  writeScreen();
}

void UI::update() {

  int newState = 1;
  newState = changeState();

  if (newState != state){
    state = newState;
      Serial.println(F("---- STATE CHANGE ----"));
      Serial.println(F("State changed to: "));
      Serial.println(newState);
  }
    mainScreen();
}


int UI::changeState(){

    int count = 0;

    ppm = s.pm25();
    tvoc = s.tvoc();
    co2 = s.co2();
    aqi = s.eaqi();

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

    if (count < 1){
        return good;
    }
    if (count > 1 && count < 3){
        return ok;
    }
    if (count > 3){
        return poor;
    }

}
// write what is in our display array
// onto the display, going by row and column
void UI::writeScreen() {
    for (int i = 0; i < 4; i++){
        for (int j = 0; j < 20; j++){
            lcd.setCursor(i,j);
            lcd.print(display[i][j]);
        }
    }
}

void UI::clearArray() {
    for (int i = 0; i < 4; i++){
        for (int j = 0; j < 20; j++){
            display[i][j] = ' ';
        }
    }
}

void UI::menu(const __FlashStringHelper* menuTitle, const __FlashStringHelper* option[3]) {
    
    int currentOption = 0;
    int cursorx = 0, cursory = 1; // initial cursor pos
    
    clearArray();
    lcd.clear();
    
    for (int r = 0; r < 8000; r++) { // run for 8 seconds to give the user a chance to read options
        lcd.setCursor(0, 0);
        lcd.print(menuTitle);
        
        // display options
        for (int row = 1; row <= 3; ++row) {
            lcd.setCursor(1, row);
            lcd.print(option[row - 1]);
        }

        for (;;) {
            int button = b.button(); // updated button input within loop
            
            // move cursor based on button input
            switch (button) {
                case 3: // up button
                    lcd.setCursor(cursorx, cursory);
                    lcd.print(' ');
                    
                    currentOption = (currentOption == 0) ? 2 : currentOption - 1; // wrap around
                    cursorx = 0;
                    cursory = currentOption + 1;
                    
                    lcd.setCursor(cursorx, cursory);
                    lcd.print('>'); // new cursor
                    break;
                    
                case 4: // down button
                    lcd.setCursor(cursorx, cursory);
                    lcd.print(' ');
                    
                    currentOption = (currentOption == 2) ? 0 : currentOption + 1; // wrap around
                    cursorx = 0;
                    cursory = currentOption + 1;
                    
                    lcd.setCursor(cursorx, cursory);
                    lcd.print('>'); // new cursor
                    break;
                    
                case 5: // select button
                    callEnter(currentOption); // perform action for the selected option
                    writeScreen();
                    break;
                    
                case 6:
                    lcd.clear();
                    return;
            }
            delay(50);
        }
    }
}

void UI::callEnter(int option){
    /*
    switch (option) {
        case 3:
            // list TVOC thresholds
        case 4:
            // turn on relay, play test audio
        case 5:
            // set servo thresholds
    }
     */
}


void UI::mainScreen(){

    lcd.setCursor(0,0);
    lcd.print(F("Status:"));
    lcd.setCursor(9,0);
    switch(state){
        case 1:
            lcd.print(F("Good"));
             break;
        case 2:
            lcd.print(F("OK"));
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
