#include <LiquidCrystal.h> /* LCD kullanimi icin kutuphane dahil edilmelidir */
/*
 Devre şeması;
 - LCD'nin RS pini -> Arduino'nun 12. pini
 - LCD'nin Enable (E) pini -> Arduino'nun 11. pini
 - LCD'nin D4 pini -> Arduino'nun 5. pini
 - LCD'nin D5 pini -> Arduino'nun 4. pini
 - LCD'nin D6 pini -> Arduino'nun 3. pini
 - LCD'nin D7 pini -> Arduino'nun 2. pini
 
 - LCD'nin R/W pini -> toprağa
 - LCD'nin R0 pini -> potansiyometre çıkışına
 - LCD VDD -> Arduino 5 Voltuna
 - LCD VSS -> toprağa
*/
LiquidCrystal lcd(12, 11, 5, 4, 3, 2); /* LCDnin baglandigi Arduino pinleri */

void setup() {
  lcd.begin(16, 2); /* Kullandigimiz LCDnin sutun ve satir sayisini belirtmeliyiz */
  lcd.print("HAVUZBASI ABO"); /* Ekrana yazi yazalim */
}
void loop() {
  lcd.setCursor(0, 1); /* Imlecin yeri 1. satir 0. sutun olarak ayarlandi */
  /* Artik LCDye yazilanlar alt satirda gorunecektir */
  lcd.print(millis()/1000); /* LCDye Arduinonun calisma suresi saniye cinsinden yaziliyor*/
  /*
  millis() fonksiyonu Arduino calismaya basladiginda calisan bir Kronometredir. 
  Fonksiyon cagirildiginda gecen sureyi milisaniye olarak dondurur
  Ekrana gecen sureyi saniye cinsinden yazdirmak icin fonksiyonun degeri 1000e bolunmustur
  */  
}
