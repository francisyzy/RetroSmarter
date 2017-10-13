#include <FS.h>                                               // This needs to be first, or it all crashes and burns
  
  #include <IRremoteESP8266.h>
  #include <IRsend.h>
  #include <IRrecv.h>
  #include <IRutils.h>
  #include <ESP8266WiFi.h>
  #include <WiFiManager.h>                                      // https://github.com/tzapu/WiFiManager WiFi Configuration Magic
  #include <ESP8266mDNS.h>                                      // Useful to access to ESP by hostname.local
  
  #include <ArduinoJson.h>
  #include <ESP8266WebServer.h>
  #include <ESP8266HTTPClient.h>
  
  #include <Ticker.h>                                           // For LED status
  #include <NTPClient.h>


  
IRrecv irrecv(12);
decode_results results;
IRsend irsend(2);
 WiFiServer server(80);

String readString; 

void setup() {
  Serial.begin(115200);
  irsend.begin();
  pinMode(LED_BUILTIN, OUTPUT);     // Initialize the LED_BUILTIN pin as an output
  pinMode(13, OUTPUT);
  irrecv.enableIRIn();
  WiFi.begin("MacbookAir11", "password");

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");
 
  // Start the server
  server.begin();
  Serial.println("Server started");

  Serial.print("Use this URL to connect: ");
  Serial.print("http://");
  Serial.print(WiFi.localIP());
  Serial.println("/");
  Serial.println("connected...yeey :)");
}

void loop(){
  // Create a client connection
  WiFiClient client = server.available();
  if (client) {
    while (client.connected()) {
      if (client.available()) {
        char c = client.read();

        //read char by char HTTP request
        if (readString.length() < 100) {

          //store characters to string 
          readString += c; 
          //Serial.print(c);
        } 

        //if HTTP request has ended
        if (c == '\n') {

          ///////////////
          Serial.println(readString); //print to serial monitor for debuging 

          client.println("HTTP/1.1 200 OK"); //send new page
          client.println("Content-Type: text/html");
          client.println();

          client.println("<HTML>");
          client.println("<HEAD>");
          client.println("<TITLE>Arduino GET test page</TITLE>");
          client.println("</HEAD>");
          client.println("<BODY>");

          client.println("<H1>Simple Arduino button</H1>");
          
          client.println("<a href=\"/?on\">ON</a>"); 
          client.println("<a href=\"/?off\">OFF</a>"); 

          client.println("</BODY>");
          client.println("</HTML>");

          delay(1);
          //stopping client
          client.stop();

          ///////////////////// control arduino pin
          if(readString.indexOf("chplus") != -1)//checks for on
          {
            ///Serial.println(readString.indexOf("chplus") + "chplus number");
            Serial.println(readString.indexOf("plus"));
            irsend.sendNEC(0x56874159, 32);
            digitalWrite(13, HIGH);    // set pin 5 high //LED
            Serial.println("Led On");

          }
          if(readString.indexOf("chminus") != -1)//checks for off
          {
            ///Serial.println(readString.indexOf("chminus") + "chminus number");
            Serial.println(readString.indexOf("minus"));
            irsend.sendNEC(0x15467823, 32);
            digitalWrite(13, LOW);    // set pin 5 low //LED
            Serial.println("Led Off");
          }
          //clearing string for next read
          if(readString.indexOf("power") != -1)//checks for off
          {
            ///Serial.println(readString.indexOf("chminus") + "chminus number");
            Serial.println(readString.indexOf("power"));
            irsend.sendSAMSUNG(0xE0E040BF, 32);
            
            Serial.println("TV On/Off");
          }
          readString="";

        }
      

        
      }

      
    }
  }

  if (irrecv.decode(&results)) {
        if (results.decode_type == NEC) {
      Serial.print("NEC: ");
    } else if (results.decode_type == SONY) {
      Serial.print("SONY: ");
    } else if (results.decode_type == RC5) {
      Serial.print("RC5: ");
    } else if (results.decode_type == RC6) {
      Serial.print("RC6: ");
    } else if (results.decode_type == UNKNOWN) {
      Serial.print("UNKNOWN: ");
    }
    serialPrintUint64(results.value, HEX);
        Serial.println("");
    irrecv.resume(); // Receive the next value
        }


  
} 

/*  void loop() {
    WiFiClient client = server.available();
  if (!client) {
    return;
  }

  Serial.println("new client");
  while(!client.available()){
    delay(1);
  }
 
  // Read the first line of the request
  String request = client.readStringUntil('\r');
  Serial.println(request);
  client.flush();

  
  digitalWrite(LED_BUILTIN, LOW);   // Turn the LED on (Note that LOW is the voltage level
                                    // but actually the LED is on; this is because 
                                    // it is acive low on the ESP-01)
  delay(1000);                      // Wait for a second
  
  irsend.sendNEC(0x34895725, 32);
  Serial.println("yoooo...yeey :)");
  
  digitalWrite(LED_BUILTIN, HIGH);  // Turn the LED off by making the voltage HIGH
  delay(2000);                      // Wait for two seconds (to demonstrate the active low LED)
}*/
