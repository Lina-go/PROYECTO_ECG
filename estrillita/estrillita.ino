
#include <WiFi.h>
#include <ESPAsyncWebServer.h>
#include <SPIFFS.h>
#else
  #include <Arduino.h>
  #include <ESP8266wifi.h>
  #include <Hash.h>
  #include <ESPAsyncTCP.h>
  #include <ESPAsyncWebServer.h>
  #include <FS.h>
#endif
#include <Wire.h>


const chas*ssid = "ID_wifi"
const chas*password = "password"

AsyncWebServer server (80);
String  analog (){

  float analog_Read = analogRead (A0);
  if (isnan(analog_read)){
    Serial.println("Failed to read");
    return "";
  }
  else{
    
    Serial.println(analog_read);
    return String(analog_read);
  }
    
}



void setup() {

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
    request->send(SPIFFS, "/Nombre.html");});
  server.on("/FuncionHTML", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send_P(200, "text/plain", analog().c_str());});

  server.begin();
  


}

void loop() {
  // put your main code here, to run repeatedly:

}
