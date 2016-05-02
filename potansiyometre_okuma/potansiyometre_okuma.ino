int led=13;
int pot=A0;
int potDeger;

void setup(){

}

void loop(){
  potDeger=analogRead(pot);
  potDeger=map(potDeger, 0, 1023, 0, 255);
  analogWrite(led, potDeger);
  delay(10);

}
