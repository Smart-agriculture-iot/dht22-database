#include <WiFi.h>;
#include <WiFiClient.h>;
#include <ThingSpeak.h>;
#include "DHT.h";
#define DHTPIN 13     
#define DHTTYPE DHT22 // DHT 22
const char* ssid = "EGATEEMIFI_CBFF"; //Your Network SSID
const char* password = "30359356"; //Your Network Password
WiFiClient client;
unsigned long myChannelNumber =1691654; //Your Channel Number (Without Brackets)
const char * myWriteAPIKey = "S8OFWFJV4RMPXY55"; //Your Write API Key
 DHT dht(DHTPIN, DHTTYPE);
 float sm;
 int val;
void setup()
{
  //delay(100);
  Serial.begin(9600);
  WiFi.begin(ssid, password);
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi..");
  }
  
  Serial.println("Connected to the WiFi network");
  dht.begin();
   ThingSpeak.begin(client);
}

void loop()
{
  
  int h = dht.readHumidity(); 
  int t = dht.readTemperature();
  val=analogRead(A0);
  sm=map(val,4095,1400,0,100);
 Serial.println(t);// printing the value of temp in the serial Monitor
 Serial.println(h);// printing the value of hum in the serial Monitor
 Serial.println(sm);//printing the value of soil moisture in the serial Monitor
 ThingSpeak.writeField(myChannelNumber, 1,t, myWriteAPIKey);
  ThingSpeak.writeField(myChannelNumber, 2,h, myWriteAPIKey);
  ThingSpeak.writeField(myChannelNumber, 3,sm, myWriteAPIKey);
}
