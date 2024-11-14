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
    if (count == 2 || count == 3){
        return ok;
    }
    if (count > 3){
        return poor;
    }

}

void UI::menu(const __FlashStringHelper* menuTitle, const __FlashStringHelper* option[], int options) {
    
    state = 5;
    Serial.println(F("---- STATE CHANGE ----"));
    Serial.println(F("State changed to: "));
    Serial.println(state);

    int currentOption = 0; // track selected option within the current page
    int pageIndex = 0;     // track the current page
    int totalPages = (options + 2) / 3; // calc the number of pages needed
    int cursorx = 0, cursory = 1; // initial cursor position

    lcd.clear();

    for (int r = 0; r < 8000; r++) { // run for 8 seconds to give the user a chance to read options
        lcd.setCursor(0, 0);
        lcd.print(menuTitle);

        // display options for the current page
        for (int row = 1; row <= 3; ++row) {
            int optionIndex = pageIndex * 3 + (row - 1);
            lcd.setCursor(1, row);
            if (optionIndex < options) {
                lcd.print(option[optionIndex]);
            } else {
                lcd.print(" ");
            }
        }

        lcd.setCursor(cursorx, cursory);
        lcd.print('>'); // place cursor at the initial position

        for (;;) {
            int button = b.button(); // updated button input within loop
            
            // move cursor based on button input
            switch (button) {
                case 3: { // up button
                    lcd.setCursor(cursorx, cursory);
                    lcd.print(' ');

                    if (currentOption > 0) {
                        currentOption--; // move up in current page
                    } else if (pageIndex > 0) {
                        pageIndex--; // go to previous page
                        currentOption = 2; // move to bottom option on new page
                    } else {
                        currentOption = 2; // wrap around within the page
                    }

                    cursory = (currentOption % 3) + 1; // adjuct cursor y-position within current page
                    lcd.setCursor(cursorx, cursory);
                    lcd.print('>'); // new cursor position
                    break;
                }

                case 4: { // down button
                    lcd.setCursor(cursorx, cursory);
                    lcd.print(' ');

                    if (currentOption < 2 && (pageIndex * 3 + currentOption + 1) < options) {
                        currentOption++; // move down in current page
                    } else if (pageIndex < totalPages - 1) {
                        pageIndex++; // go to next page
                        currentOption = 0; // move to top option on new page
                    } else {
                        currentOption = 0; // wrap around within the page
                    }

                    cursory = (currentOption % 3) + 1; // adjust cursor y-position within current page
                    lcd.setCursor(cursorx, cursory);
                    lcd.print('>'); // new cursor position
                    break;
                }

                case 5: // select button
                    callEnter(pageIndex * 3 + currentOption); // perform action for the selected option
                    break;

                case 6: // Exit button
                    lcd.clear();
                    return;
            }
            delay(50);
        }
    }
}


void UI::callEnter(int option){
    
    Serial.println(F("option is: "));
    Serial.println(option);
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
