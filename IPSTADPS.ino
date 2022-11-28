#include <ipst.h>
#include <Wire.h>
#include <SparkFun_APDS9960.h>
 
// Global Variables
SparkFun_APDS9960 apds = SparkFun_APDS9960();
uint16_t ambient_light = 0;
uint16_t red_light = 0;
uint16_t green_light = 0;
uint16_t blue_light = 0;
void setup() {
  Serial.begin(9600);
  // put your setup code here, to run once:
 if ( apds.init() ) {
    Serial.println(F("APDS-9960 initialization complete"));
  } else {
    Serial.println(F("Something went wrong during APDS-9960 init!"));
  }
  
  // Start running the APDS-9960 light sensor (no interrupts)
  if ( apds.enableLightSensor(false) ) {
    Serial.println(F("Light sensor is now running"));
  } else {
    Serial.println(F("Something went wrong during light sensor init!"));
  }
  
  // Wait for initialization and calibration to finish
  OK();
}

void loop() {
  // put your main code here, to run repeatedly:
if (  !apds.readAmbientLight(ambient_light) ||
        !apds.readRedLight(red_light) ||
        !apds.readGreenLight(green_light) ||
        !apds.readBlueLight(blue_light) ) {
    Serial.println("Error reading light values");
  } else {
    if(red_light > green_light && red_light > blue_light){
      //Serial.println("RED!");
      glcdFillScreen(GLCD_RED);
      }
    else if(green_light > red_light && green_light > blue_light){
      //Serial.println("GREEN!");
      glcdFillScreen(GLCD_GREEN);
      }
    else if(blue_light > red_light && blue_light > green_light){
      //Serial.println("BLUE!");
      glcdFillScreen(GLCD_BLUE);
      }
  }
  
  // Wait 1 second before next reading
  delay(1000);
}
