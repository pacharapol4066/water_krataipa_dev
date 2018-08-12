#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp8266.h>

char auth[] = "YourAuthToken";
const char* ssid     = "krataipa";
const char* password = "wildrabbit";

const int relayInput1 = 4;  /* GPI00 (D2)*/
const int relayInput2 = 0;  /* GPI00 (D3)*/
const int relayInput3 = 2;  /* GPI02 (D4)*/
const int relayInput4 = 14;  /* GPI014 (D5)*/
const int relayInput5 = 12;  /* GPI012 (D6)*/
const int relayInput6 = 13;  /* GPI013 (D7)*/
const int relayInput7 = 15;  /* GPI015 (D8)*/

LiquidCrystal_I2C lcd(0x3F, 16, 2);

void setup() {
  // put your setup code here, to run once:
   Serial.begin(115200);
   Wire.begin(D0, D1);
   
   pinMode(relayInput1,OUTPUT);
   pinMode(relayInput2,OUTPUT);
   pinMode(relayInput3,OUTPUT);
   pinMode(relayInput4,OUTPUT);
   pinMode(relayInput5,OUTPUT);
   pinMode(relayInput6,OUTPUT);
   
   lcd.begin();
   lcd.backlight();
   lcd.print("Starting");

   WiFi.begin(ssid, password);
   while (WiFi.status() != WL_CONNECTED) 
   {
      delay(1000);
      lcd.print(".");
   }
   recheckWifi();
   Blynk.begin(auth, ssid, password);
}

void loop() {
  Blynk.run();
}

void recheckWifi(){
  
  if(WiFi.status() == WL_CONNECTED)
   {
       lcd.setCursor(0, 0);
       lcd.print("WiFi connected");  
       lcd.setCursor(0, 1);
       lcd.print(WiFi.localIP());
   }
   else
   {
       lcd.setCursor(0, 1);
       lcd.print("Wifi Not Connect");
   }
}
