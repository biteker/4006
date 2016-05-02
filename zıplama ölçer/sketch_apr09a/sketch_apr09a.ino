#include <LCD5110_Basic.h>         // LCD kütüphanemizi ekliyoruz
LCD5110 myGLCD(8,9,10,11,12);     //  LCD pinlerimizi tanıtıyoruz

extern uint8_t BigNumbers[];      //Kullanacağımız fontlar için eklemeler yapıyoruz.
extern uint8_t SmallFont[];

//extern uint8_t arduino_logo[];    //Programın başlangıcında Arduino Logosunu göstereceğiz bu yüzden bunu ekliyoruz

int trigPin = 3;    //Ultrasonic sensörün trig ve echo pinleri
int echoPin = 2;
int sure=0; 
float mesafe=0;
int lcd_ledi = 6;
int buton_pini = 7;
int buton_durumu = 0;
void setup()
{
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(lcd_ledi,OUTPUT);
  digitalWrite(lcd_ledi,HIGH);    //ekran ışığını açıyoruz
  myGLCD.InitLCD();   //LCD ekranı başlatıyoruz
  
  //myGLCD.drawBitmap(0, 0, arduino_logo, 84, 48);    //Arduino logosunu ekrana çizdiriyoruz
  //delay(4000);
  for (int i=0; i<2; i++)  //invert komutu ekranın tersinin alınması için. Yani ekranda siyah olan yerler beyaz, beyaz yerler ise siyah oluyor.
  {
    myGLCD.invert(true);
    delay(500);
    myGLCD.invert(false);
    delay(500);
  }

  
  myGLCD.clrScr(); //Ekran temizlenir
  
}

void loop()
{
  //TrigPin'e 10 mikrosaniye 5v gönderilir.
  
  digitalWrite(trigPin, LOW);
  delayMicroseconds(5);  
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  
  sure = pulseIn(echoPin, HIGH);    //EchoPin'den gelen 5v süresi pulseIn fonksiyonuyla alınır.
  mesafe = (sure/2) / 29.1;         //Süre ses hızına bağlı olarak cm cinsinden mesafye çevrilir.
  
  if (mesafe <= 0){                 //Mesafe 50 cm'den büyükse mesafe 50'ye eşitlenir.
    mesafe=0;                       //Aynı şekilde hatalı bir şekilde negatif bir değer gelirse mesafe 0'a eşitlenir
  }
  else if(mesafe >= 250){
    mesafe = 250;
  }
  myGLCD.setFont(SmallFont);        // küçük font kullanımı açılır
  myGLCD.print("Mesafe:",LEFT,10);  //ekrana "mesafe" yazdırılır
  myGLCD.setFont(BigNumbers);       //mesafeyi yazdırmak için büyük yazı tipini kullanıyoruz.
  myGLCD.printNumI(mesafe,40,20);   //ekrana 100ms'de bir mesafeyi yazdırıyoruz
  delay(1000);
  myGLCD.clrScr();    //ekranı temizliyoruz
  
      //LCD ekran uyku modu kullanımı
  if(digitalRead(buton_pini) == HIGH && buton_durumu == 0){ //butona her basıldığında LCD ekran uykuda değilse uykuya sokar, uykuda ise uyandırır
    digitalWrite(lcd_ledi,LOW);
    myGLCD.enableSleep();
    buton_durumu = 1;
    delay(300);
  }
  if(digitalRead(buton_pini) == HIGH && buton_durumu == 1){
    digitalWrite(lcd_ledi,HIGH);
    myGLCD.disableSleep();
    buton_durumu = 0;
    delay(300);
  }
}
