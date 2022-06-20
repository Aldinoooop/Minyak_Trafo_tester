const int stepPin = 9; 
const int dirPin = 10; 
const int stepsPerRevolution = 200;

bool kanan = HIGH;
bool kiri = LOW;

int sprkSen = A0;
int homePin = 7;

int valSen = 0;
int valHome = 0;





void setup() {
  Serial.begin(9600);
  pinMode(stepPin,OUTPUT); 
  pinMode(dirPin,OUTPUT);
//  pinMode(sprkSen,INPUT_PULLUP);
  pinMode(homePin,INPUT_PULLUP);

  while(digitalRead(homePin) == 1){
    digitalWrite(dirPin,LOW);
    digitalWrite(stepPin,HIGH); 
    delayMicroseconds(15000); 
    digitalWrite(stepPin,LOW); 
    delayMicroseconds(15000); 
}
}

void loop() { 
  valSen = analogRead(sprkSen);
  valHome = digitalRead(homePin);
  Serial.println(valSen);
  Serial.println(valHome);

  if(valSen > 100){
    digitalWrite(dirPin,HIGH);
    digitalWrite(stepPin,HIGH); 
    delayMicroseconds(10000); 
    digitalWrite(stepPin,LOW); 
    delayMicroseconds(10000);
  }else{
    
  }

}
  
//  if(senVal == 
/*
void calibration(int speedMotor, bool arah){
    digitalWrite(dirPin,arah);
    digitalWrite(stepPin,HIGH); 
    delayMicroseconds(speedMotor); 
    digitalWrite(stepPin,LOW); 
    delayMicroseconds(speedMotor); 
  }
void motorRun(){
    digitalWrite(dirPin,LOW);
    digitalWrite(stepPin,HIGH); 
    delayMicroseconds(500); 
    digitalWrite(stepPin,LOW); 
    delayMicroseconds(500); 
  }
}
*/
