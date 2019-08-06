#include "ThingSpeak.h"
#include <ESP8266WiFi.h>

char ssid[] = "SSID";   // your network SSID (name) 
char pass[] = "PASSWORD";   // your network password

WiFiClient  client;

unsigned long TSChannelID = 123456;//SECRET_CH_ID;
const char * TSReadAPIKey = "ABCDEFGHIJ12345";//SECRET_READ_APIKEY;
unsigned int TSFieldNumber = 1; // Field number

void setup() {
  Serial.begin(115200);  // Initialize serial

  WiFi.mode(WIFI_STA); 
  ThingSpeak.begin(client);  // Initialize ThingSpeak
}

void loop() {

  int statusCode = 0;
  
  // Connect or reconnect to WiFi
  if(WiFi.status() != WL_CONNECTED){
    Serial.print("Attempting to connect to SSID: ");
    Serial.println(ssid);
    while(WiFi.status() != WL_CONNECTED){
      WiFi.begin(ssid, pass); // Connect to WPA/WPA2 network. Change this line if using open or WEP network
      Serial.print(".");
      delay(5000);     
    } 
    Serial.println("\nConnected");
  }

  float readData = ThingSpeak.readFloatField(TSChannelID,TSFieldNumber,TSReadAPIKey);

  statusCode = ThingSpeak.getLastReadStatus();
  if(statusCode == 200){
    Serial.println("Data ----> " + String(readData));
  }
  else{
    Serial.println("Problem reading channel. HTTP error code " + String(statusCode)); 
  }
  delay(15000);
}
