
#include <Servo.h>
#include <SoftwareSerial.h>

  /***Serial init****/

  SoftwareSerial mySerial(2,3) ; 
  
  /*** servo init ***/
  
  Servo passage_controller ;

  /*** Buzzer init ***/

  int buzzer = 9 ;
  int start = 0 ; 


 /***    led    ****/

  int led = 11 ;
  

void setup() {

pinMode(led , OUTPUT) ;

mySerial.begin(9600) ;
Serial.begin(9600) ;

passage_controller.attach(7) ;
passage_controller.write(90);
//Serial.println("attached +  90° ===> setup method") ;
pinMode(buzzer, OUTPUT) ;


}

void loop() {

/////////////////////////////////////////////////////////
////////////////////Reading Data From ESP ///////////////
///////////////////////////////////////////////////////// 
 
 String IncomingStringFromEsp = "" ; 

      if(mySerial.available()){
        
          IncomingStringFromEsp = mySerial.readString() ;
            Serial.println("available string with value of : " + IncomingStringFromEsp) ;
        }

/////////////////////////////////////////////////////
///////////////Testing if incomming data qual Down///
/////////////////////////////////////////////////////
 
      if(IncomingStringFromEsp == "down"){ // maybe i will add start == 0

        start = start + 1 ;

             for (int position = 90; position >= 0; position--) {
                passage_controller.write(position);
                delay(20);
              
                } 
    Serial.println("data_2 : " + IncomingStringFromEsp) ;
        
        }else{

//////////////////////////////////////////////////////
/////////////////Testing if there is an obstacle /////
//////////////////////////////////////////////////////
          
              if(IncomingStringFromEsp == "obstacle"  && start > 0 ){

                      Serial.println("data_3 : " + IncomingStringFromEsp) ;

                        
                   for (int position = 0; position <= 90; position++) {           
                        passage_controller.write(position);
                        digitalWrite(buzzer , HIGH) ;
                        delay(20);         
                     } 
                    passage_controller.detach();
                    digitalWrite(buzzer , LOW) ;
                    digitalWrite(led , HIGH) ;
                      
  
                
                }
///////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////Another condition based on srart value from esp///////
///////////////////////////////////////////////////////////////////////////////////////////////
                else if(IncomingStringFromEsp == "start" && start > 0 && passage_controller.read() == 90){

                     passage_controller.attach(7);
                       
                      for (int position = 90; position >= 0; position--) {
                    
                        passage_controller.write(position);
                        delay(20);
                      
                      }

                      digitalWrite(led , LOW) ;
                  
                  }


               
          }




}
