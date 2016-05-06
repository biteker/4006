#include <SoftwareSerial.h>
#define ag_ismi "TUBITAK4006"
#define ag_sifresi "34havuz34"
SoftwareSerial esp8266(2,3); // make RX Arduino line is pin 12, make TX Arduino line is pin 11.

void setup()
{
  Serial.begin(9600);
  Serial.println("Akilli Ev sistemi");
  esp8266.begin(9600); //Seriport'u açıyoruz. Güncellediğimiz 
                        //ESP modülünün baudRate değeri 115200 olduğu için bizde Seriport'u 115200 şeklinde seçiyoruz
  esp8266.println("AT"); //ESP modülümüz ile bağlantı kurulup kurulmadığını kontrol ediyoruz.
  pinMode(13,OUTPUT);
  delay(3000); //ESP ile iletişim için 3 saniye bekliyoruz.
 
  if(esp8266.find("OK")){         //esp modülü ile bağlantıyı kurabilmişsek modül "AT" komutuna "OK" komutu ile geri dönüş yapıyor.
     esp8266.println("AT+CWMODE=1"); //esp modülümüzün WiFi modunu STA şekline getiriyoruz. Bu mod ile modülümüz başka ağlara bağlanabilecek.
     delay(2000);
     String baglantiKomutu=String("AT+CWJAP=\"")+ag_ismi+"\",\""+ag_sifresi+"\"";
    esp8266.println(baglantiKomutu);
     delay(5000);
 }
 
   esp8266.print("AT+CIPMUX=1\r\n");
   delay(200);
   esp8266.print("AT+CIPSERVER=1,80\r\n"); 
}
void loop(){
  /*delay(1000);
   esp8266.print("AT+CIFSR\r\n");*/
  if(esp8266.available()>0){
       /* while(esp8266.available())
   {
      // The esp has data so display its output to the serial window 
      char c = esp8266.read(); // read the next character.
      Serial.write(c);
    }  */
    
    if(esp8266.find("+IPD,")){
      String metin = "<head> Hello World </head>";
      metin += "<br><a href=\" ?pin=on\"><button type='button'>ON</button></a>"; 
      metin += "<br><a href=\" ?pin=off\"><button type='button'>OFF</button></a>";      
      String cipsend = "AT+CIPSEND=";
      cipsend +="0";
      cipsend +=",";
      cipsend += metin.length();
      cipsend += "\r\n";
      esp8266.print(cipsend);
      delay(500);
      esp8266.println(metin);
      led_yakma();
      esp8266.println("AT+CIPCLOSE=0");
      
    }
  }
}
 
void led_yakma(){
 String gelen ="";
 char serialdenokunan;
 while(esp8266.available()>0){
 serialdenokunan = (char)esp8266.read();
 gelen +=serialdenokunan;
 
 }
 Serial.println(gelen);
 if((gelen.indexOf("pin=on")>1)){  //on butonuna basıldığında server adresinde /?pin=on var ise
  digitalWrite(13,HIGH);                  //ledi yakar
  Serial.println("ON");
 }
  if((gelen.indexOf("pin=off")>1)){ // off butonuna basıldığında server adresinde /?pin=off var ise
  digitalWrite(13,LOW);                    //ledi söndürür
  Serial.println("Off");
 }
 }
