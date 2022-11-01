#ifdef ESP32
  #include <WiFi.h>
  #include <ESPAsyncWebServer.h>
  #include <SPIFFS.h>
#else
  #include <Arduino.h>
  #include <ESP8266WiFi.h>
  #include <Hash.h>
  #include <ESPAsyncTCP.h>
  #include <ESPAsyncWebServer.h>
  #include <FS.h>
#endif
#include <Wire.h>

// Replace with your network credentials
const char* ssid = "iPhone de Veronica";
const char* password = "987654321";

// Create AsyncWebServer object on port 80
AsyncWebServer server (80);
String  readNodeMCU (){

  float t = analogRead (A0);
  if (isnan(t)){
    Serial.println("Failed to read from sensor!");
    return "";
  }
  else{
    
    Serial.println(t);
    return String(t);
  }
    
}



void setup() {
  // Serial port for debugging purposes
  Serial.begin(115200);

  //inicializando SPIFFS
  if(!SPIFFS.begin()){

    Serial.println("An error has ocurred while, punting SPIFFS");
    return;
  }

  //Conexión wifi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED){

    delay(1000);
    Serial.println("Connecting to Wifi...");
  }

  //Print ESP8266 IP
  Serial.println(WiFi.localIP());

  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(SPIFFS, "/index jose 1.html");});
  server.on("/EEG", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send_P(200, "text/plain", readNodeMCU().c_str());});

  server.begin();
  


}

void loop() {
  // put your main code here, to run repeatedly:

}
