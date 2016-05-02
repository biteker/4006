/*
Adafruit Arduino - Lesson 16. Stepper
*/
 
#include <Stepper.h>
 
int in1Pin = 12;
int in2Pin = 11;
int in3Pin = 10;
int in4Pin = 9;
 
Stepper motor(512, in1Pin, in2Pin, in3Pin, in4Pin);

int LDR_Pin = A0; //analog pin 0

void setup()
{
pinMode(in1Pin, OUTPUT);
  pinMode(in2Pin, OUTPUT);
  pinMode(in3Pin, OUTPUT);
  pinMode(in4Pin, OUTPUT);
 
  // this line is for Leonardo's, it delays the serial interface
  // until the terminal window is opened
  while (!Serial);
  
  Serial.begin(9600);
  motor.setSpeed(20);
}

void loop()
{
int LDRReading = analogRead(LDR_Pin);
Serial.println(LDRReading);
delay(250); //Değerleri serial monitörden daha kolay okuyabilmeniz için konuldu kaldırılabilir...

  if (Serial.available())
  {
    int steps = Serial.parseInt();
    motor.step(steps);
  }
}
