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

void setup() {
  Serial.begin(115200);
  pinMode(LED_BUILTIN, OUTPUT);     // Initialize the LED_BUILTIN pin as an output
  WiFiManager wifiManager;

  wifiManager.autoConnect("MacbookAir11", "password");

  Serial.println("connected...yeey :)");
}

  void loop() {
  digitalWrite(LED_BUILTIN, LOW);   // Turn the LED on (Note that LOW is the voltage level
                                    // but actually the LED is on; this is because 
                                    // it is acive low on the ESP-01)
  delay(1000);                      // Wait for a second
  
  Serial.println("yoooo...yeey :)");
  digitalWrite(LED_BUILTIN, HIGH);  // Turn the LED off by making the voltage HIGH
  delay(2000);                      // Wait for two seconds (to demonstrate the active low LED)
}

