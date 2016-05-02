#define ag_ismi "Pikatel Airmax-104"
#define ag_sifresi "A1B2C3D4E5"
#define IP "184.106.153.149"    //thingspeak.com IP adresi
#define DHT11PIN 4 // DHT11PIN olarak Dijital 2"yi belirliyoruz.
#include <SoftwareSerial.h> 
#include <dht11.h> // dht11 kütüphanesini ekliyoruz.
SoftwareSerial esp8266(2,3); // make RX Arduino line is pin 12, make TX Arduino line is pin 11.
dht11 DHT11; 
float sicaklik;
 
void setup()
{
  esp8266.begin(9600); //Seriport'u açıyoruz. Güncellediğimiz 
                        //ESP modülünün baudRate değeri 115200 olduğu için bizde Seriport'u 115200 şeklinde seçiyoruz
  Serial.begin(9600);
  
  esp8266.println("AT"); //ESP modülümüz ile bağlantı kurulup kurulmadığını kontrol ediyoruz.
  
  delay(3000); //EPSP ile iletişim için 3 saniye bekliyoruz.
 
  if(esp8266.find("OK")){         //esp modülü ile bağlantıyı kurabilmişsek modül "AT" komutuna "OK" komutu ile geri dönüş yapıyor.
    Serial.println("Baglanti Kuruldu...");
     esp8266.println("AT+CWMODE=1"); //esp modülümüzün WiFi modunu STA şekline getiriyoruz. Bu mod ile modülümüz başka ağlara bağlanabilecek.
     delay(2000);
     String baglantiKomutu=String("AT+CWJAP=\"")+ag_ismi+"\",\""+ag_sifresi+"\"";
    esp8266.println(baglantiKomutu);
    esp8266.println("AT+CIFSR");
    Serial.println((char)esp8266.read());
     delay(5000);
  }
   else
   {
    Serial.println("Baglanti hatası...");
   }
}
 
void loop(){
  int chk = DHT11.read(DHT11PIN);
  sicaklik = DHT11.temperature;
  Serial.println(sicaklik);
 sicaklik_yolla(sicaklik);
 // dakikada 1 güncellenmesi için 1 dakika bekle
 delay(60000);
}
 
 
void sicaklik_yolla(float sicaklik){
 esp8266.println(String("AT+CIPSTART=\"TCP\",\"") + IP + "\",80");  //thingspeak sunucusuna bağlanmak için bu kodu kullanıyoruz. 
                                                                   //AT+CIPSTART komutu ile sunucuya bağlanmak için sunucudan izin istiyoruz. 
                                                                   //TCP burada yapacağımız bağlantı çeşidini gösteriyor. 80 ise bağlanacağımız portu gösteriyor
 delay(1000);
  if(esp8266.find("Error")){     //sunucuya bağlanamazsak ESP modülü bize "Error" komutu ile dönüyor.
   Serial.println("AT+CIPSTART Error");
    return;
  }
  
 String yollanacakkomut = "GET /update?api_key=HVAV4UVW53IWIMUV&field1=";   // Burada J9CHDM47T3LVG5BV yazan kısım bizim API Key den aldığımız Key. Siz buraya kendi keyinizi yazacaksınız.
 yollanacakkomut += (float(sicaklik));                                      // Burada ise sıcaklığımızı float değişkenine atayarak yollanacakkomut değişkenine ekliyoruz.
 yollanacakkomut += "\r\n\r\n";                                             // ESP modülümüz ile seri iletişim kurarken yazdığımız komutların modüle iletilebilmesi için Enter komutu yani
                                                                                  // /r/n komutu kullanmamız gerekiyor.
 
 esp8266.print("AT+CIPSEND=");                    //veri yollayacağımız zaman bu komutu kullanıyoruz. Bu komut ile önce kaç tane karakter yollayacağımızı söylememiz gerekiyor.
 esp8266.println(yollanacakkomut.length());       //yollanacakkomut değişkeninin kaç karakterden oluştuğunu .length() ile bulup yazırıyoruz.
 
 delay(1000);
 
 if(esp8266.find(">")){                           //eğer sunucu ile iletişim sağlayıp komut uzunluğunu gönderebilmişsek ESP modülü bize ">" işareti ile geri dönüyor.
  Serial.println("Sunucu ile iletisim kuruldu");
                                                 // arduino da ">" işaretini gördüğü anda sıcaklık verisini esp modülü ile thingspeak sunucusuna yolluyor.
 esp8266.print(yollanacakkomut);
 esp8266.print("\r\n\r\n");
 }
 else{
 esp8266.println("AT+CIPCLOSE");
 Serial.println("Sunucu hatası");
 }
}
