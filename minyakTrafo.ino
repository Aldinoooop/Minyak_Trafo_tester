#include "A4988.h"
#include <PZEM004Tv30.h>
#include <SoftwareSerial.h>


// using a 200-step motor (most common)
#define MOTOR_STEPS 200
#define MICROSTEPS 16

// configure the pins connected
#define DIR 13
#define STEP 12

#if !defined(PZEM_RX_PIN) && !defined(PZEM_TX_PIN)
#define PZEM_RX_PIN 6
#define PZEM_TX_PIN 7
#endif


int sprkSen = 3;
bool valSen;
int lastvalSen = 1;
int i = 0;
int ind = 0;

int target = -1;

int homePin = 4;

//    float voltage ;
//    float current ;
//    float power ;
//    float energy ;
//    float frequency ;
//    float pf ;

#define RPM 10
#define MOTOR_STEPS 200
A4988 stepper(MOTOR_STEPS, DIR, STEP);

SoftwareSerial pzemSWSerial(PZEM_RX_PIN, PZEM_TX_PIN);
PZEM004Tv30 pzem(pzemSWSerial);

volatile int output = LOW;

void setup() {
    Serial.begin(9600);
    pinMode(sprkSen, INPUT);
    pinMode(homePin,INPUT_PULLUP);



    stepper.begin(RPM);
    stepper.enable();
    
     attachInterrupt(digitalPinToInterrupt(3), scan, FALLING);
    
    while(digitalRead(homePin)){
      stepper.setMicrostep(16);
      stepper.move(target*MICROSTEPS);
      target--;
  
    }

       target=1;
      while(!digitalRead(homePin)){
      stepper.setMicrostep(16);
      stepper.move(target*MICROSTEPS);
      target++;

    }
    
    delay(1000);

    
}

void loop() {
  

      if(ind == 1){
      Serial.println("test");

    float voltage = pzem.voltage();
    float current = pzem.current();
    float power = pzem.power();
    float energy = pzem.energy();
    float frequency = pzem.frequency();
    float pf = pzem.pf();  
    
       if(isnan(voltage)){
        Serial.println("Error reading voltage");
    } else if (isnan(current)) {
        Serial.println("Error reading current");
    } else if (isnan(power)) {
        Serial.println("Error reading power");
    } else if (isnan(energy)) {
        Serial.println("Error reading energy");
    } else if (isnan(frequency)) {
        Serial.println("Error reading frequency");
    } else if (isnan(pf)) {
        Serial.println("Error reading power factor");
    } else {

        // Print the values to the Serial console
        Serial.print("Voltage: ");      Serial.print(voltage);      Serial.println("V");
        Serial.print("Current: ");      Serial.print(current);      Serial.println("A");
        Serial.print("Power: ");        Serial.print(power);        Serial.println("W");
        Serial.print("Energy: ");       Serial.print(energy,3);     Serial.println("kWh");
        Serial.print("Frequency: ");    Serial.print(frequency, 1); Serial.println("Hz");
        Serial.print("PF: ");           Serial.println(pf);
    }

    Serial.println();
    i = 1;
    ind = 0;
   }
   else if(i == 0){
      stepper.setMicrostep(16);
      stepper.move(target*MICROSTEPS);
      target++;
   }
}

void scan(){
   ind = 1;

   }

   

   
  
