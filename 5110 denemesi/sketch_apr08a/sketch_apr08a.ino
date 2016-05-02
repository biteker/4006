#include <LCD5110_Basic.h>         // LCD kütüphanemizi ekliyoruz
LCD5110 myGLCD(8,9,10,11,12);     //  LCD pinlerimizi tanıtıyoruz
 
extern uint8_t BigNumbers[];      //Kullanacağımız fontlar için eklemeler yapıyoruz.
extern uint8_t SmallFont[];
 
extern uint8_t arduino_logo[];    //Programın başlangıcında Arduino Logosunu göstereceğiz bu yüzden bunu ekliyoruz
 
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
  
 // myGLCD.drawBitmap(0, 0, arduino_logo, 84, 48);    //Arduino logosunu ekrana çizdiriyoruz
  delay(4000);
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
  hazirlayan(377);
  hazirlayan(135);
  hazirlayan(397);
}

void hazirlayan(int okulno)
{
  myGLCD.setFont(SmallFont);        // küçük font kullanımı açılır
  myGLCD.print("Hazirlayan:",LEFT,10);  //ekrana "mesafe" yazdırılır
  myGLCD.setFont(BigNumbers);       //mesafeyi yazdırmak için büyük yazı tipini kullanıyoruz.
  myGLCD.printNumI(okulno,40,20);   //ekrana 100ms'de bir mesafeyi yazdırıyoruz
  delay(500);
  myGLCD.clrScr();    //ekranı temizliyoruz
}

