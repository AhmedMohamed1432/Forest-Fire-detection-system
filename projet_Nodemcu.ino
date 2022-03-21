#include <DHT.h>  // Including library for dht
#include "ThingSpeak.h"
#include <ESP8266WiFi.h>
#include <Wire.h>

char ssid[] = "NU-Guest";        // your network SSID (name) 
char pass[] = "Welcome@NU";    // your network password
int keyIndex = 0;            // your network key Index number (needed only for WEP)
WiFiClient  client;
unsigned long myChannelNumber = 1614936;
const char * myWriteAPIKey = "WSEF82IHYUXGMP73";
String myStatus = "";

int GV;

int sensorThres=500;
 
#define DHTPIN 0          //pin where the dht11 is connected
#define DHTPIN1 2 
#define DHTPIN2 4  
DHT dht(DHTPIN, DHT11);
DHT dht1(DHTPIN1, DHT11);
DHT dht2(DHTPIN2, DHT11);

void setup() 
{
     pinMode(A0,INPUT);
     pinMode(13,OUTPUT);
     pinMode(15,OUTPUT);
    Serial.begin(9600);
    //Serial.begin(115200);  //Initialize serial
   Serial.begin(9600);
  //WiFi.mode(WIFI_STA);   
  ThingSpeak.begin(client);  // Initialize ThingSpeak
  Wire.begin();
  while (!Serial) continue;
  
       delay(10);
       dht.begin();
       dht1.begin();
       dht2.begin();
 
}
 
void loop() 
{
  GV=analogRead(A0);
Serial.println(GV);
delay(100);
      float h = dht.readHumidity();
      float t = dht.readTemperature();
      float h1 = dht1.readHumidity();
      float t1 = dht1.readTemperature();
      float h2 = dht2.readHumidity();
      float t2 = dht2.readTemperature();
      Serial.print("T1 ");
      Serial.println(t);
      Serial.print(" degrees Celcius, H1 ");
      Serial.println(h);

      Serial.print("T2 ");
      Serial.println(t1);
      Serial.print(" degrees Celcius, H2: ");
      Serial.println(h1);

      Serial.print("T3 ");
      Serial.println(t2);
      Serial.print(" degrees Celcius, H3: ");
      Serial.println(h2);
      delay(500);

  if(t>8){
    digitalWrite(13,HIGH);
    digitalWrite(15,LOW);
    Serial.println("7ariiii2aaaaaaa") ;
    }
  // Connect or reconnect to WiFi
  if(WiFi.status() != WL_CONNECTED){
    Serial.print("Attempting to connect to SSID: ");
    Serial.println(ssid);
    while(WiFi.status() != WL_CONNECTED){
      WiFi.begin(ssid, pass);  // Connect to WPA/WPA2 network. Change this line if using open or WEP network
      Serial.print(".");
      delay(5000);     
    } 
    Serial.println("\nConnected.");
  }
  
  // set the fields with the values
  ThingSpeak.setField(1, t);
  ThingSpeak.setField(2, h);
  ThingSpeak.setField(3, t1);
  ThingSpeak.setField(4, h1);
  ThingSpeak.setField(5, t2);
  ThingSpeak.setField(6, h2);
    ThingSpeak.setField(7, GV);
  // set the status
  ThingSpeak.setStatus(myStatus);
  
  // write to the ThingSpeak channel
  int x = ThingSpeak.writeFields(myChannelNumber, myWriteAPIKey);
  if(x == 200){
    Serial.println("Channel update successful.");
  }
  else{
    Serial.println("Problem updating channel. HTTP error code " + String(x));
  }

 
  delay(1000); 

}
