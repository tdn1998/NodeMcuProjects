#include "ThingSpeak.h"
#include <ESP8266WiFi.h>

#define SECRET_SSID "AndroidAP"    // replace MySSID with your WiFi network name
#define SECRET_PASS "turbodrive1"  // replace MyPassword with your WiFi password

#define SECRET_CH_ID 725122     // replace 0000000 with your channel number
#define SECRET_WRITE_APIKEY "I189AFD7EIAUHRGD"   // replace XYZ with your channel write API Key

#include "DHT.h"

#define DHTPIN D3     // what digital pin we're connected to
#define DHTTYPE DHT11

char ssid[] = SECRET_SSID;   // your network SSID (name) 
char pass[] = SECRET_PASS;   // your network password
int keyIndex = 0;            // your network key Index number (needed only for WEP)

WiFiClient  client;

DHT dht(DHTPIN, DHTTYPE);

unsigned long myChannelNumber = SECRET_CH_ID;
const char * myWriteAPIKey = SECRET_WRITE_APIKEY;

void setup() {
  Serial.begin(115200);  // Initialize serial

  WiFi.mode(WIFI_STA); 
  ThingSpeak.begin(client);  // Initialize ThingSpeak

  Serial.println("DHTxx test!");

  dht.begin();
  }

void loop() {
  if(WiFi.status() != WL_CONNECTED){
    Serial.print("Attempting to connect to SSID: ");
    Serial.println(SECRET_SSID);
    while(WiFi.status() != WL_CONNECTED){
      WiFi.begin(ssid, pass);  // Connect to WPA/WPA2 network. Change this line if using open or WEP network
      Serial.print(".");
      delay(5000);     
    } 
    Serial.println("\nConnected.");
    
  }

  float h = dht.readHumidity();
  float t = dht.readTemperature();

  // Compute heat index in Celcius (the default)
  float hic = dht.computeHeatIndex(t, h);

  // Check if any reads failed and exit early (to try again).
  if (isnan(h) || isnan(t)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }

  // set the fields with the values
  ThingSpeak.setField(1, h);
  ThingSpeak.setField(2, t);
  ThingSpeak.setField(3, hic);

  int x = ThingSpeak.writeFields(myChannelNumber, myWriteAPIKey);
  if(x == 200){
    Serial.println("Channel update successful.");
  }
  else{
    Serial.println("Problem updating channel. HTTP error code " + String(x));
  }

  delay(20000);
  }
 
