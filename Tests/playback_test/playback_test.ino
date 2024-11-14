#include <SD.h>
#include <TMRpcm.h>
#include <SPI.h>

TMRpcm audio; 

void setup() {
  Serial.begin(9600);
  
  if (!SD.begin(10)) {  // intitialze SD card
    Serial.println("SD card initialization failed");
    return;
  }

  audio.speakerPin = 9;  // set speaker output pin
}

void loop() {
  if (!audio.isPlaying()) { // play if the audio is not already playing
    audio.play("stOK.wav"); 
    delay(5000);            // wait for 5 seconds 
}
