//#include <dht.h>

    #include <SoftwareSerial.h>
     
    #define DEBUG true
     
    SoftwareSerial esp8266(12,11); // make RX Arduino line is pin 2, make TX Arduino line is pin 3.
                                 // This means that you need to connect the TX line from the esp to the Arduino's pin 2
                                 // and the RX line from the esp to the Arduino's pin 3
    int status=0;
    
    //#define dht_dpin 4 //no ; here. Set equal to channel sensor is on
 

 
   // dht DHT;
    
    
    void setup()
    {
      Serial.begin(9600);
      esp8266.begin(115200); // your esp's baud rate might be different
      
     
      
      sendData("AT+RST\r\n",2000,DEBUG); // reset module
      sendData("AT+CWMODE=1\r\n",1000,DEBUG); // configure 

      sendData("AT+CWJAP=\"Pikatel Airmax-104\",\"A1B2C3D4E5\"\r\n",5000,DEBUG);
      delay(3000);      
      sendData("AT+CIFSR\r\n",3000,DEBUG); // get ip address
      sendData("AT+CIPMUX=1\r\n",1000,DEBUG); // configure for multiple connections
      sendData("AT+CIPSERVER=1,80\r\n",1000,DEBUG); // turn on server on port 80
      
      
    }
     
    void loop()
    {
      //DHT.read11(dht_dpin);
      if(esp8266.available()) // check if the esp is sending a message 
      {
        Serial.println("ip adresi");
        sendData("AT+CIFSR\r\n",3000,DEBUG); // get ip address
        /*
        while(esp8266.available())
        {
          // The esp has data so display its output to the serial window 
          char c = esp8266.read(); // read the next character.
          Serial.write(c);
        } */
        
        if(esp8266.find("+IPD,"))
        {
         delay(1000);
     
         int connectionId = esp8266.read()-48; // subtract 48 because the read() function returns 
                                               // the ASCII decimal value and 0 (the first decimal number) starts at 48
         
         String webpage = "<h1>Arduino! - BARIS SANLI</h1><br><h1>Nem: ";
         //webpage.concat(DHT.humidity);
         webpage="<h1>Sicaklik  ";
         //webpage.concat("DHT.temperature");
         webpage+=" C </h1>";  
         webpage+="<br><a href=\"?pin=on\"><button><h1>LED2</h1></button></a>";
         
         String cipSend = "AT+CIPSEND=";
         cipSend += connectionId;
         cipSend += ",";
         cipSend +=webpage.length();
         cipSend +="\r\n";
         
         sendData(cipSend,1000,DEBUG);
         sendData(webpage,1000,DEBUG);
     
         String closeCommand = "AT+CIPCLOSE="; 
         closeCommand+=connectionId; // append connection id
         closeCommand+="\r\n";
         
         sendData(closeCommand,3000,DEBUG);
         delay(1000);
        }
      }
    }
     
     
    String sendData(String command, const int timeout, boolean debug)
    {
        String response = "";
        
        esp8266.print(command); // send the read character to the esp8266
        
        long int time = millis();
        
        while( (time+timeout) > millis())
        {
          while(esp8266.available())
          {
            
            // The esp has data so display its output to the serial window 
            char c = esp8266.read(); // read the next character.
            response+=c;
          }  
        }
        
        if(debug)
        {
 //         Serial.print("---");
          Serial.print(response);
 //         Serial.println("---");
          int a=response.indexOf(":GET /?pin=on");
          Serial.print("-0-0-0-0-0-----a=");
          Serial.println(a);
          if(a>3){
            pinMode(13, OUTPUT);
            if(status==0){
              digitalWrite(13,HIGH);
              status=1;
            }else{
              digitalWrite(13,LOW);
              status=0;
              }
          }
        }
        
        return response;
    }
     
