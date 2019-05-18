#include <ESP8266WiFi.h>
#include <PubSubClient.h>


const char* ssid = "Honor 6X";
const char* password =  "25022019";
const char* mqttServer = "m16.cloudmqtt.com";
const int mqttPort =  15826;
const char* mqttUser = "tgepnmwm";
const char* mqttPassword = "ga7uomnLGGrq";
 
WiFiClient espClient;
PubSubClient client(espClient);
 
void setup() {
  
  Serial.begin(115200);
  pinMode(16, OUTPUT);
  digitalWrite(16, HIGH);
  
  WiFi.begin(ssid, password);
 
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.println("Connecting to WiFi..");
  }
  Serial.println("Connected to the WiFi network");
 
  client.setServer(mqttServer, mqttPort);
  client.setCallback(callback);
 
  while (!client.connected()) {
    Serial.println("Connecting to MQTT...");
 
    if (client.connect("ESP8266Client", mqttUser, mqttPassword )) {
 
      Serial.println("connected");  
 
    } else {
 
      Serial.print("failed with state ");
      Serial.print(client.state());
      delay(2000);
 
    }
  }
 
  
  client.subscribe("topic");
 
}
 
void callback(char* topic, byte* payload, unsigned int length) {
 
  Serial.print("Message arrived in topic: ");
  Serial.println(topic);
  
  if(length==3)
    digitalWrite(16,HIGH);  
  else 
     digitalWrite(16,LOW); 
 
  Serial.print("Message:");
  for (int i = 0; i < length; i++) {
    Serial.print((char)payload[i]);
  }
 
  Serial.println();
  Serial.println("-----------------------");
 
}
 
void loop() {
  client.loop();
}
