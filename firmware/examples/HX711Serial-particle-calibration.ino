// This #include statement was automatically added by the Particle IDE.
#include "HX711ADC/HX711ADC.h"

// HX711.DOUT (DAT)   - pin #A1
// HX711.PD_SCK (CLK) - pin #A0

HX711ADC scale(A1, A0);   // parameter "gain" is ommited; the default value 128 is used by the library
float calibration_factor;
float calibration_weight;

void calibrate(bool restart) {
  if (restart == true) {
    Serial.println("Restarting calibration...");
  } else {
    Serial.println("HX711 Bee scale calibration");
    Serial.println("Readings:");
  }
  
  scale.set_scale();
  scale.tare();
  Serial.println("------------------");
  Serial.println("Input your weight value and then press 'q' when ready");
  bool done = false;
  String basket = "";
  
  do {
      if(Serial.available()) 
      {
        char temp = Serial.read();
        basket += temp;
        Serial.print("Value received: ");
        Serial.println(temp);
        if (temp == 'q') { done = !done; }
      }
  } while (done == false);
  
  calibration_weight = basket.toFloat();
  Serial.print("Calibration weight: ");
  Serial.println(calibration_weight);
  Serial.println("------------------");
  Serial.println("Add weight...");
  Serial.println("Press 'q' when ready...");

  bool wait = false;
  do {
      if(Serial.available()) 
      {
        char temp = Serial.read();
        if (temp == 'q') { wait = !wait; }
      }
  } while (wait == false);
  
  Serial.println("------------------");
  
  calibration_factor = scale.get_units(10) / calibration_weight;
  Serial.print("Initial calibration factor: ");
  Serial.println(calibration_factor);
}


void setup() {
  Cellular.on();
    
  Serial.begin(9600);
  calibrate(false);
}

void loop() {
//   Serial.print("one reading:\t");
//   Serial.print(scale.get_units(), 1);
//   Serial.print("\t| 10x average:\t");
//   Serial.println(scale.get_units(10), 1);

  scale.set_scale(calibration_factor);
  
  Serial.print("Reading: average of ");
  Serial.print(scale.get_units(10), 3);
  Serial.print(" lbs | "); //Change this to kg and re-adjust the calibration factor if you follow SI units like a sane person
  Serial.print(" calibration_factor: ");
  Serial.print(calibration_factor);
  Serial.println();

  if(Serial.available())
  {
    char temp = Serial.read();
    if(temp == 'a')
      calibration_factor += 10;
    else if(temp == '+')
      calibration_factor += 100;
    else if(temp == 'z')
      calibration_factor -= 10;
    else if(temp == '-')
      calibration_factor -= 100;
    else if(temp == 'c')
      calibrate(true);
  }

  scale.power_down();             // put the ADC in sleep mode
  delay(100);
  scale.power_up();
}