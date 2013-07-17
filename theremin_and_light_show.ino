#include <Esplora.h>

// calibration constants between the light sensor and L brightness
int lightMin = 0;
int lightMax = 1023;

void setup() {
 Serial.begin(9600); 
}

void loop() {
  int startButton = Esplora.readButton(SWITCH_2);
  int stopButton = Esplora.readButton(SWITCH_4);
  int lightIntensity = Esplora.readLightSensor();
  
  // map the reading from the light sensor to a brightness setting in the LED
  int calibratedLightReading = map(lightIntensity,lightMin,lightMax,0, 255);
 
  // limit the brightness for the LED to its range
  calibratedLightReading = constrain(calibratedLightReading, 0, 255);

  /* start the light show and theremin */
  if(startButton == LOW) {
    if(calibratedLightReading >= 171) {
      Esplora.writeRGB(255,0,0);
    } else if(calibratedLightReading <= 170 && calibratedLightReading >= 85) {
      Esplora.writeRGB(0,calibratedLightReading,0);
    } else if(calibratedLightReading <= 84) {
      Esplora.writeRGB(0,0,calibratedLightReading);
    }
    
    // play a tone matching the raw light sensor reading (uncalibrated)
   Esplora.tone(lightIntensity);
  }
  
  /* kill the theremin and light show */
  if(stopButton == LOW) {
    Esplora.noTone();
    Esplora.writeRGB(0,0,0); 
  }
  
  delay(1);
}
