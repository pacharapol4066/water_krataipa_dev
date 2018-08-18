#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp8266.h>

char auth[] = "7973178c19e44ba3a99b19400be53f70";
const char* ssid     = "krataipa";
const char* password = "wildrabbit";

int pumpFlage1 = 0;
int pumpFlage2 = 0;
int pumpFlage3 = 0;
int pumpFlage4 = 0;
int pumpFlage5 = 0;

int relaySolinoidState[6] = {0,0,0,0,0,0};
const int relayInput[6] = {0,2,14,12,13,15};

BlynkTimer timer;
LiquidCrystal_I2C lcd(0x3F, 16, 2);

BLYNK_CONNECTED() {
    Blynk.syncAll();
}

BLYNK_WRITE(V1) //Relay 1
{
  int pinData = param.asInt(); 
  relayControl(pinData,relayInput[0],1);
}

BLYNK_WRITE(V2) //Relay 2
{
  int pinData = param.asInt(); 
  relayControl(pinData,relayInput[1],2);
}

BLYNK_WRITE(V3) //Relay 3
{
  int pinData = param.asInt(); 
  relayControl(pinData,relayInput[2],3);
}

BLYNK_WRITE(V4) //Relay 4
{
  int pinData = param.asInt(); 
  relayControl(pinData,relayInput[3],4);
}

BLYNK_WRITE(V5) //Relay 5
{
  int pinData = param.asInt(); 
  relayControl(pinData,relayInput[4],5);
}

BLYNK_WRITE(V6) //Relay 6
{
  int pinData = param.asInt(); 
  relayControl(pinData,relayInput[5],6);
}


void relayControl(int onoff,int relayNo,int statusFlage)
{
    if(onoff == 1) // Virtual button set to on
    {
        if(statusFlage == 6)
        { 
            if(relaySolinoidState[0] == 1 || relaySolinoidState[1] == 1 || relaySolinoidState[2] == 1 || relaySolinoidState[3] == 1 || relaySolinoidState[4] == 1)
            {
                digitalWrite(relayInput[5], HIGH);
            }
        }
        else
        {
            digitalWrite(relayNo, HIGH);
        }
        relaySolinoidState[statusFlage-1] = 1;
    }
    else if(onoff == 0)
    {
        relaySolinoidState[statusFlage-1] = 0;
        if(relaySolinoidState[0] == 0 && relaySolinoidState[1] == 0 && relaySolinoidState[2] == 0 && relaySolinoidState[3] == 0 && relaySolinoidState[4] == 0)
        {
            digitalWrite(relayInput[5], LOW);     //Cut off pump immediately
        }
        digitalWrite(relayNo, LOW);
    }
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

void setup() {
  // put your setup code here, to run once:
   Serial.begin(115200);
   Wire.begin(D2, D1);    //SCL,SDA
   
   pinMode(relayInput[0],OUTPUT);
   pinMode(relayInput[1],OUTPUT);
   pinMode(relayInput[2],OUTPUT);
   pinMode(relayInput[3],OUTPUT);
   pinMode(relayInput[4],OUTPUT);
   pinMode(relayInput[5],OUTPUT);
   digitalWrite(relayInput[0], LOW);
   digitalWrite(relayInput[1], LOW);
   digitalWrite(relayInput[2], LOW);
   digitalWrite(relayInput[3], LOW);
   digitalWrite(relayInput[4], LOW);
   digitalWrite(relayInput[5], LOW);
   
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
   Blynk.config(auth,"blynk-cloud.com", 8080);
   Blynk.connect();
}

void loop() {
  Blynk.run();
  //delay(500);
}
