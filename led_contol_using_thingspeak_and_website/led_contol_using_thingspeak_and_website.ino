#include"ThingSpeak.h"
#include<ESP8266WiFi.h>

const char*ssid="AndroidAP";
const char*pass="turbodrive1";
unsigned long channel = 606161;
const char * APIKey = "68QSX2OY8OSSJAW5";

WiFiClient  client;

void setup()
{

Serial.begin(115200);
Serial.println("Connecting to ");
Serial.println(ssid);
WiFi.begin(ssid,pass);
while(WiFi.status()!= WL_CONNECTED) 
{
delay(1000);
Serial.print(".");
}
Serial.println("");
Serial.println("WiFi connected");
  
ThingSpeak.begin(client);

pinMode(D5,OUTPUT);
digitalWrite(D5,LOW);
}

void loop()
{
int readValue=ThingSpeak.readIntField(channel,1,APIKey);
Serial.print("readValue = ");
Serial.println(readValue);

if(readValue==1)
{
digitalWrite(D5,HIGH);
}
else
{
digitalWrite(D5,LOW);
}
}
