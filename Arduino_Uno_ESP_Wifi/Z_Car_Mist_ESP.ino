#include <ESP8266WiFi.h>
#include <PubSubClient.h>

#define MQTT_SERVER "192.168.43.242"
const char* ssid = "Root_host";
const char* password = "mouda007" ;

char* rail_topic = "rail_topic";
char* car_topic = "car_topic";

void callback(char* topic, byte* payload, unsigned int length); 
 
WiFiClient WifiClient ;
PubSubClient client (MQTT_SERVER, 1883, callback, WifiClient) ;

void setup() {
   
 pinMode(2 , OUTPUT) ;
 digitalWrite(2 , LOW) ;
 Serial.begin(9600);
  WiFi.begin(ssid, password);  
  // attempt to connect to the WIFI network and then connect to the MQTT server
   reconnect();
// publish ON car topic value 1
   
   client.publish("car_topic", "1");
   delay(2000);

}

void loop() {

if (!client.connected() && WiFi.status() == 3) {reconnect();}
  
  client.loop();
  
   delay(20);
}


void callback(char* topic, byte* payload, unsigned int length) {

//convert topic to string to make it easier to work with

  String rail_topic = topic; 

 //turn the light on if the payload is '1' and publish to the MQTT server a confirmation message
  
  if(payload[0] == '5'){
    
   // Serial.write("LED HIGH");commented when buying new esp
  //  client.publish("test_topic", "stop");
    digitalWrite(2,HIGH) ;
 
  }else if (payload[0] == '6'){
    
   // client.publish("test_topic", "start");
   // Serial.write("LED LOW"); commented when buying new esp
    digitalWrite(2,LOW) ;
  
  }

}


void reconnect() {

  //attempt to connect to the wifi if connection is lost
  if(WiFi.status() != WL_CONNECTED){
  
    //loop while we wait for connection
    while (WiFi.status() != WL_CONNECTED) {
      delay(500);
    }

  }

  //make sure we are connected to WIFI before attemping to reconnect to MQTT
  if(WiFi.status() == WL_CONNECTED){
  // Loop until we're reconnected to the MQTT server
    while (!client.connected()) {

      // Generate client name based on MAC address and last 8 bits of microsecond counter
      String clientName;
      clientName += "esp8266-";
      uint8_t mac[6];
      WiFi.macAddress(mac);
      clientName += macToStr(mac);

      //if connected, subscribe to the topic(s) we want to be notified about
      if (client.connect((char*) clientName.c_str())) {
       
        client.subscribe("car_topic");
      }

      //otherwise print failed for debugging
      else{//Serial.println("\tFailed."); 
      abort();}
    }
  }
}

//generate unique name from MAC addr
String macToStr(const uint8_t* mac){

  String result;

  for (int i = 0; i < 6; ++i) {
    result += String(mac[i], 16);

    if (i < 5){
      result += ':';
    }
  }

  return result;
}
