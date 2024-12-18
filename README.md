Disclaimer: 
This code is released into the public domain. You are free to use, modify, and distribute it without any restrictions. This code is provided "as is," withouta  warranty of any kind, express or implied, including but not limited to the warranties of merchantability, fitness for a particular purpose, or non-infringement. In no event shall the author(s) be liable for any claim, damages, or other liability arising from its use.

This readme pertains to the EzVOC ventilation system. 

Setup:

In order to compile the project, place the files in the "src" directory into your Arduino "libraries" directory. On Mac OS this is found in the "Arduino" directory in your documents folder. On Debian based Linux distributions, this is found inside the "Arduino" directory inside your home folder. 

Outside of the files found in the src folder, you will need the following libraries: 

- Adafruit PM25 Sensor Library
- ScioSense ENS160 Sensor Library (Adafruit Fork)
- Adafruit AHTX0 Library
- Adafruit BusIO Library
- Adafruit Unified Sensor Library
- LiquidCrystal I2C Library
- Servo library

These libraries can be installed using the Library manager in the Arduino IDE. 

These libraries may require other libraries not listed to be installed. The Arduino IDE will prompt you if this is the case.

To compile and upload to your arduino, open the main.ino file included in the src folder. For connections, use the following list:
- Up Button, pin 4
- Down Button, pin 5
- Enter Button, pin 7
- Back Button, pin 8
- Servo Motor, pin 6
- I2C LCD Display (20x4), SDA and SDC
- ENS160, SDA and SDC
- AHT20, SDA and SDC
- Relay 1, pin A0
- Relay 2, pin A1

Usage: 

After assembling, compiling and uploading the project to the Arduino, the Arduino will start and show the main screen. The main screen shows the overall status at the top, and six sensor readings, two per row, afterwards. It will show the following readings in this order: PPM and TVOC in the first column, Temperature and Humidity percentage in the second, C02 and AQI in the third row. 

To enter the menu, you can press any of the four buttons while in the main screen. This will take you to the menu, where you can view the four modifiable thresholds. The bottom of the screen will show the currently selected value. You can choose the threshold you want to modify by using the up and down buttons to increase or decrease the value. Once you reach the value equal to the desired threshold you want to change, strike the "enter" key. The system will then display the currently set threshold value. 

From here, you can use the up and down arrows to increase or decerease the value. After setting it to your desired value, strike the enter key to save the value. If you enter a negative value, the system will display an error, before returning to the value entry field. If you decide at any point that you want to quit without saving, simply press the back button. This will return you to the main screen. 

Interaction: 

Based on the thresholds you set, the system will interact with its environment accordingly. If 1 value crosses a threshold, the system does nothing, and remains in the "Good" state. If 2 or 3 values cross their respective thresholds, the system switches to the "OK" state. If more than 3 values cross their respective thresholds, the system moves to the "Poor" state. In all cases, the system reports the sensor values, the state, plays tones through the speaker, and turns the vent fan on and off accordingly. 

Future Plans:
- Replace Uno with more powerful microcontroller 
- Design and print a case
- Rebuild the menu function
- Variable AC fan control
  

