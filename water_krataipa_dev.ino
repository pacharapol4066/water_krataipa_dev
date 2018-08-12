#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <SimpleTimer.h>
#include <BlynkSimpleEsp8266.h>
#include <DHT.h>

#define DHTPIN 5
#define DHTTYPE DHT11

char auth[] = "7973178c19e44ba3a99b19400be53f70";
const char* ssid     = "krataipa";
const char* password = "wildrabbit";
int pumpFlage1 = 0;
int pumpFlage2 = 0;
int pumpFlage3 = 0;
int pumpFlage4 = 0;
int pumpFlage5 = 0;
int pumpFlage6 = 0;

const int relayInput1 = 4;   /* GP4(D2)*/
const int relayInput2 = 0;   /* GP0(D3)*/
const int relayInput3 = 2;   /* GP2(D4)*/
const int relayInput4 = 14;  /* GP14(D5)*/
const int relayInput5 = 12;  /* GP12(D6)*/
const int relayInput6 = 13;  /* GP13(D7)*/
const int relayInput7 = 15;  /* GP15(D8)*/

DHT dht(DHTPIN, DHTTYPE);
SimpleTimer timer;
LiquidCrystal_I2C lcd(0x3F, 16, 2);

BLYNK_CONNECTED() {
    Blynk.syncAll();
}

BLYNK_WRITE(GP4) //Button Widget is writing to pin GP4
{
  int pinData = param.asInt(); 
  if (pinData == 1) 
    pumpFlage1 = 1;
  else if (pinData == 0)
    pumpFlage1 = 0;
}

BLYNK_WRITE(GP0) //Button Widget is writing to pin GP0
{
  int pinData = param.asInt(); 
  if (pinData == 1) 
    pumpFlage2 = 1;
  else if (pinData == 0)
    pumpFlage2 = 0;
}

BLYNK_WRITE(GP2) //Button Widget is writing to pin GP2
{
  int pinData = param.asInt(); 
  if (pinData == 1) 
    pumpFlage3 = 1;
  else if (pinData == 0)
    pumpFlage3 = 0;
}

BLYNK_WRITE(GP14) //Button Widget is writing to pin GP2
{
  int pinData = param.asInt(); 
  if (pinData == 1) 
    pumpFlage4 = 1;
  else if (pinData == 0)
    pumpFlage4 = 0;
}

BLYNK_WRITE(GP12) //Button Widget is writing to pin GP2
{
  int pinData = param.asInt(); 
  if (pinData == 1) 
    pumpFlage5 = 1;
  else if (pinData == 0)
    pumpFlage5 = 0;
}

BLYNK_WRITE(GP13) //Button Widget is writing to pin GP2
{
  int pinData = param.asInt(); 
  if (pinData == 1) 
    pumpFlage6 = 1;
  else if (pinData == 0)
    pumpFlage6 = 0;
}

BLYNK_WRITE(GP15) //Button Widget is writing to pin GP2
{
  int pinData = param.asInt(); 
  if (pinData == 1) 
  {
    if(pumpFlage1 == 1 || pumpFlage2 == 1 || pumpFlage3 == 1 || pumpFlage4 == 1 || pumpFlage5 == 1 || pumpFlage6 == 1){
        digitalWrite(relayInput7, LOW);
    }
  }
}

void sendSensor()
{
  float t = dht.readTemperature();
  if (isnan(t)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }
  Blynk.virtualWrite(V1, t);
}

void setup() {
  // put your setup code here, to run once:
   Serial.begin(115200);
   Wire.begin(D0, D1);    //SCL,SDA
   
   pinMode(relayInput1,OUTPUT);
   pinMode(relayInput2,OUTPUT);
   pinMode(relayInput3,OUTPUT);
   pinMode(relayInput4,OUTPUT);
   pinMode(relayInput5,OUTPUT);
   pinMode(relayInput6,OUTPUT);
   pinMode(relayInput7,OUTPUT);
   
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
   timer.setInterval(1000L, sendSensor);
}

void loop() {
  Blynk.run();
  timer.run();
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
