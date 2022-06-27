#include <SoftwareSerial.h>
#define  a_ref_voltage  3.3;
String value;
// Motor A connections
int enA = 9;
int in1 = 8;
int in2 = 7;
int TxD = 11;
int RxD = 10;
int temppin = 0;
float Temp_Intercept;
SoftwareSerial bluetooth(TxD, RxD);
void setup() {
  Serial.begin(9600);// start serial communication at 9600bps
  bluetooth.begin(9600);
  analogReference(EXTERNAL);
  // Set all the motor control pins to outputs
  pinMode(enA, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  // Turn off motors - Initial state
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
  Temp_Intercept = 0.0;
}

void loop() {
 digitalWrite(in1, HIGH);
 digitalWrite(in2, LOW);
 if (bluetooth.available())
   {
    value = bluetooth.readString();
    Serial.print("Command given : ");Serial.print(value);
    Serial.println(" - ");
    if (value == "change 1" || value == "Change 1" || value == "change one" || value == "Change one" || value == "Change One"  ){
        Temp_Intercept= Temp_Intercept + 12.8;
      }

    if (value == "change 2" || value == "Change 2" || value == "change two" || value == "Change two" || value == "Change Two" || value == "change to"  ){
         Temp_Intercept= Temp_Intercept + 25.5;   
      }

    if (value == "change 3" || value == "Change 3" || value == "change three" || value == "Change three" || value == "Change Three" ){
          Temp_Intercept= Temp_Intercept + 38.3;
      }
     if (value == "change 4" || value == "Change 4" || value == "change four" || value == "Change four" || value == "Change Four" ){
        Temp_Intercept= Temp_Intercept - 12.8;
      }

    if (value == "change 5" || value == "Change 5" || value == "change five" || value == "Change five" || value == "Change Five" ){
         Temp_Intercept= Temp_Intercept - 25.5;   
      }

    if (value == "change 6" || value == "Change 6" || value == "change six" || value == "Change six" || value == "Change Six"  ){
          Temp_Intercept= Temp_Intercept - 38.3;
      }
   }
else
  { Temp_Intercept=Temp_Intercept;}
  float TempReading = analogRead(temppin);
  float pwm_voltage= TempReading*255.0;
  float temp_voltage = TempReading*a_ref_voltage;
  pwm_voltage =  pwm_voltage/1024.0;
  temp_voltage = temp_voltage/1024.0;
  float speed_perct= ((pwm_voltage+ Temp_Intercept)/255)*100;
  float temp_C = (temp_voltage - 0.5)*100;
  if(pwm_voltage < 250.00 && pwm_voltage > 10.00)
  { pwm_voltage+= Temp_Intercept;
    analogWrite(enA,pwm_voltage);}
  else
  {if(pwm_voltage > 250.00 || pwm_voltage == 250.00)
   {pwm_voltage = pwm_voltage;
    analogWrite(enA,250);}
   if(|| pwm_voltage < 10.00 || pwm_voltage == 10.00)
   {pwm_voltage = pwm_voltage;
   analogWrite(enA,10);} }
  Serial.print("Pwm vlotage : ");Serial.print(pwm_voltage);
  Serial.println(" - ");
  Serial.print("Temperature Intercept : ");Serial.print(Temp_Intercept);
  Serial.println(" - ");
  Serial.print("Temperature Read  : ");Serial.print(TempReading);
  Serial.print(" - ");
  Serial.print("Temperature Measured : ");Serial.print(temp_C);Serial.print(" C");
  Serial.print(" - ");
  Serial.print("Speed Percentage : ");Serial.print(speed_perct);Serial.println(" %");
  delay(2000);
 }
