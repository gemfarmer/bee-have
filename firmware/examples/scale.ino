// This #include statement was automatically added by the Particle IDE.
#include "HX711ADC/HX711ADC.h"

// HX711.DOUT (DAT)	  - pin #A1
// HX711.PD_SCK	(CLK) - pin #A0

HX711ADC scale(A1, A0);		// parameter "gain" is ommited; the default value 128 is used by the library


int addr = 10;
struct Status {
  float current_weight;
  bool reset; 
};

float OFFSET = 0;

Status Memory;

Status Default = { 0, false, 1 };

void setup() {
  
  Serial.begin(9600);
  scale.set_scale(-5624.f);                      // this value is obtained by calibrating the scale with known weights; see the README for details
  EEPROM.get(addr, Memory);
  
  // Questions/Next steps:
  // Should this be an edit of the actual HIX... library
  // Need a button to trigger the "factory reset"
  // Future: Need to ensure that the EEPROM value is valid before storing it!!!!
  

  scale.tare();
  
  if (!Memory.reset) {
    OFFSET = Memory.current_weight;
  }   
}

void loop() {
  
  float weight = scale.get_units(10) + OFFSET;
  Memory.current_weight = weight;
  String current_weight = String(weight, 1);
  
  Memory.reset = false;
//   Memory.current_weight = 0;
  EEPROM.put(addr, Memory);
 
  
  Particle.publish("current_weight", current_weight, PRIVATE);
  
  scale.power_down();			        // put the ADC in sleep mode
//   delay(600000); // every 15 mins
  delay(500); // every 15 mins
  scale.power_up();
}