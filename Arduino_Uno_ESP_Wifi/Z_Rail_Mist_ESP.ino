
#include <ESP8266WiFi.h>
#include <PubSubClient.h>

#define MQTT_SERVER "192.168.43.242"
const char* ssid = "Root_host";
const char* password = "mouda007" ;

boolean checker_1 = false ;
boolean checker_2 = false ;
int starter = 1 ;

char* rail_topic = "rail_topic";
char* car_topic = "car_topic";

int state = 3 ;

void callback(char* topic, byte* payload, unsigned int length); 

WiFiClient WifiClient ;
PubSubClient client (MQTT_SERVER, 1883, callback, WifiClient) ;

void setup() {
 
   pinMode(2 , INPUT) ;
  Serial.begin(115200);
  Serial.begin(9600);
  WiFi.begin(ssid, password);  
  // attempt to connect to the WIFI network and then connect to the MQTT server
   reconnect();
   
   delay(2000);
}

void loop() {

  
//reconnect if connection is lost
  if (!client.connected() && WiFi.status() == 3) {reconnect();}

  if(checker_1 == true && checker_2 == false && state == 2 ){
    Serial.write("start");
    client.publish("rail_topic","4");
    starter = starter + 1 ;
    //it was or in condition
    state = 3 ;
  
  }
  
    int n_sensing = 0 ;

    while(true){

       int value = digitalRead(2) ;

       if(value == LOW){   

            n_sensing = n_sensing + 1 ; 
  
        }else{
          /*****new code ++ ****/
              checker_1 = true ; 
              checker_2 = false ;   
          /*********************/      
           break ;  
            
        }
        
        if(n_sensing > 8 /*&& state == 3*/){  // mybe i will make it 5
         /*****new code ++ ****/           
          checker_1 = false ;  
          checker_2 = true ; 
         /*********************/
          Serial.write("obstacle") ;
          client.publish("rail_topic","3");
          state = 2 ;

            break ;
         /*****new code ++ ****/  
        }
 //         else if(n_sensing < 8 && n_sensing >= 1 && state == 3){
 //         Serial.write("wait") ;
//        client.publish("rail_topic","7"); // didnt decide it was 7
//        }
         /*********************/     
              delay(625) ;
      }


  //maintain MQTT connection
  client.loop();

  //MUST delay to allow ESP8266 WIFI functions to run
 //delay(10); 

}


///////////////////////////////////////////////////////////
///////////////////////////Callback Method////////////////
//////////////////////////////////////////////////////////

void callback(char* topic, byte* payload, unsigned int length) {

//convert topic to string to make it easier to work with

  String rail_topic = topic; 

//  Print out some debugging info
//  Serial.println("Callback update.");
//  Serial.print("Topic: ");
//  Serial.println(rail_topic);

  //turn the light on if the payload is '1' and publish to the MQTT server a confirmation message
  if(payload[0] == '2'){
      
    client.publish("test_topic", "i recieved joujou down");
     Serial.write("down");
  }


}

///////////////////////////////////////////////////////////////
////////////////////////////Reconnect Method //////////////////
///////////////////////////////////////////////////////////////

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
       
        client.subscribe(rail_topic);
      }

      //otherwise print failed for debugging
      else{//Serial.println("\tFailed."); 
      abort();}
    }
  }
}


//////////////////////////////////////////////////////////////////
/////////////////////////// MAC TO STR ///////////////////////////
//////////////////////////////////////////////////////////////////


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
