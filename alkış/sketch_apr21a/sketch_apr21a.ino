const int SensorOutPin = 0; //Sensörün out bacağının bağlı olduğu pin tanımlanır.
const int ledPin = 13;      //13. pine bağlı Led tanımlanır.
 
int deger;                  //Mikrofondan okunan değerin tutulacağı değişken tanımlanır.
 
const int esik = 800;       //Ledin yanmasını istediğimiz eşik değeri tanımlanır.
// Eşik değerinin hassasiyeti kart üzerindeki potansiyometre ile
// değiştirilebilir.
void setup()
{
pinMode (ledPin, OUTPUT);//dijital 13. pin çıkış olarak ayarlanır.
Serial.begin(9600); // Serial monitor baud rate değeri belirlenir.
}
 
void loop() {
deger = analogRead(SensorOutPin); //Arduino döngü içinde sürekli sensör değerini okur.
Serial.println(deger);
if (deger > esik)
{
digitalWrite (ledPin, HIGH); //Eğer okunan değer belirlenen eşik değerinden büyükse led yanar.
delay (500);                 //Ledin yarım saniye yanması sağlanır.
digitalWrite (ledPin, LOW);  //Led söndürülür.
}
else // eşik değeri farklı diğer tüm değerler için led söndürülür.
{
digitalWrite(ledPin, LOW);
}
}
