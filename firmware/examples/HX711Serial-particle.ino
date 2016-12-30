// This #include statement was automatically added by the Particle IDE.
#include "HX711ADC/HX711ADC.h"

// HX711.DOUT (DAT)	  - pin #A1
// HX711.PD_SCK	(CLK) - pin #A0

HX711ADC scale(A1, A0);		// parameter "gain" is ommited; the default value 128 is used by the library

void setup() {
  Cellular.on();
    
  Serial.begin(9600);
  Serial.println("HX711 Demo");

  Serial.println("Before setting up the scale:");
  Serial.print("read: \t\t");
  Serial.println(scale.read());			// print a raw reading from the ADC

  Serial.print("read average: \t\t");
  Serial.println(scale.read_average(20));  	// print the average of 20 readings from the ADC

  Serial.print("get value: \t\t");
  Serial.println(scale.get_value(5));		// print the average of 5 readings from the ADC minus the tare weight (not set yet)

  Serial.print("get units: \t\t");
  Serial.println(scale.get_units(5), 1);	// print the average of 5 readings from the ADC minus tare weight (not set) divided 
				// 		by the SCALE parameter (not set yet)  

  // calibration factor for 20lbs
  scale.set_scale(-5624.f);                      // this value is obtained by calibrating the scale with known weights; see the README for details
  
  // -5797.13 : 20 lbs
  scale.tare();				        // reset the scale to 0

  Serial.println("After setting up the scale:");

  Serial.print("read: \t\t");
  Serial.println(scale.read());                 // print a raw reading from the ADC

  Serial.print("read average: \t\t");
  Serial.println(scale.read_average(20));       // print the average of 20 readings from the ADC

  Serial.print("get value: \t\t");
  Serial.println(scale.get_value(5));		// print the average of 5 readings from the ADC minus the tare weight, set with tare()

  Serial.print("get units: \t\t");
  Serial.println(scale.get_units(5), 1);        // print the average of 5 readings from the ADC minus tare weight, divided 
						// by the SCALE parameter set with set_scale

  Serial.println("Add weight...");
  
  delay(5000);

  Serial.println("Readings:");
}

void loop() {
  Serial.print("one reading:\t");
  Serial.print(scale.get_units(), 1);
  Serial.print("\t| 10x average:\t");
  Serial.println(scale.get_units(10), 1);

  scale.power_down();			        // put the ADC in sleep mode
  delay(1000);
  scale.power_up();
}