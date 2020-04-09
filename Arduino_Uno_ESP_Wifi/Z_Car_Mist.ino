

/*  Car Variables  */

 /********Motor A ***************/
  int enA = 5; 
  int in1 = 6 ; 
  int in2 = 7 ;
 
 /********Motor B ***************/
  int enB = 10 ; 
  int in3 = 8 ;
  int in4 = 9 ;


 /*** line sensors init ***/
  int sensor_left   = A0 ;//4  ;
  int center_sensor = A2 ;
  int sensor_right  = A1 ;//3 ;

 /*** ultrasonic sensor ***/ 
  
  int echo_pin = 3  ;
  int trig_pin = 2 ;

  long duration ;
  long distance ;


 /*** buzzer sensor ***/

 int buzzer = 13 ;

 void setup() {

  /*** Sensing Line ***/ 
  pinMode(sensor_left , INPUT);
  pinMode(center_sensor , INPUT);
  pinMode(sensor_right , INPUT);
 
   /*** init Motor A***/  
 
    pinMode(enA, OUTPUT);
    pinMode(in1, OUTPUT);
    pinMode(in2, OUTPUT);
  
  /*** init Motor B***/

    pinMode(enB, OUTPUT);
    pinMode(in3, OUTPUT);
    pinMode(in4, OUTPUT);

    /*** init ULTRASONIC ***/
   pinMode(trig_pin ,OUTPUT) ;
   pinMode(echo_pin , INPUT) ;

    /*** init buzzer ***/

    pinMode(buzzer , OUTPUT);
  
  Serial.begin(9600);

}


 void StopingCar(){
      
     digitalWrite(in1, LOW);
     digitalWrite(in2, LOW);
     analogWrite(enA,0);

     digitalWrite(in3, LOW);
     digitalWrite(in4, LOW);
     analogWrite(enB,0);
      
   }

    void turnLeft(int speed){
      
      digitalWrite(in1, LOW);
      digitalWrite(in2, HIGH);
      
      digitalWrite(in3, LOW);
      digitalWrite(in4, LOW); // a mettre HIGH pour que les roux ne s'arretront pas
      analogWrite(enA,speed + 10);  // to rotate
      analogWrite(enB,speed); 
       
    }

    void turnRight(int speed){
      
      digitalWrite(in1, LOW);
      digitalWrite(in2, LOW); // a mettre HIGH pour que les roux ne s'arretront pas
      digitalWrite(in3, LOW);
      digitalWrite(in4, HIGH); 
      analogWrite(enA,speed);  
      analogWrite(enB,speed+10); //to rotate
     }

    void MoveForward(int speed){
     
      digitalWrite(in1, LOW);
      digitalWrite(in2, HIGH);
      analogWrite(enA,speed);  
      
      digitalWrite(in3, LOW);
      digitalWrite(in4, HIGH);
      analogWrite(enB,speed); 
     
      } 


void loop() {

    digitalWrite(trig_pin , LOW);
    delayMicroseconds(2); 
    digitalWrite(trig_pin , HIGH);
    delayMicroseconds(10);
    digitalWrite(trig_pin , LOW);

    duration = pulseIn(echo_pin,HIGH);
    distance = (duration / 2) * 0.0343 ;

  
  
  if(distance <= 10){

    digitalWrite(buzzer ,LOW) ;
    StopingCar() ;
   // Serial.println("stoping car and distance is : " + distance) ;
    }
    
  if (distance > 10 &&  distance  <= 20){

       digitalWrite(buzzer ,HIGH) ;
      
       if (( digitalRead(sensor_left) == 0)&&( digitalRead(center_sensor) == 1)&&( digitalRead(sensor_right) == 0)){  MoveForward(60);}

      if (( digitalRead(sensor_left) == 1)&&( digitalRead(center_sensor) == 1)&&( digitalRead(sensor_right) == 0)){  turnLeft(70);   }
      
      if (( digitalRead(sensor_left) == 1)&&( digitalRead(center_sensor) == 0)&&( digitalRead(sensor_right) == 0)){  turnLeft(70);   }
      
      if (( digitalRead(sensor_left) == 0)&&( digitalRead(center_sensor) == 1)&&( digitalRead(sensor_right) == 1)){  turnRight(70);  }
      
      if (( digitalRead(sensor_left) == 0)&&( digitalRead(center_sensor) == 0)&&( digitalRead(sensor_right) == 1)){  turnRight(70);  }
      //cas de low low low
    
     //   Serial.println("moving car with buzzer on and distance is : " + distance) ;

    }
    
  if ( distance > 20){

    //same code for controlling the car + stoping buzzer

     digitalWrite(buzzer ,LOW) ;

      if (( digitalRead(sensor_left) == 0)&&( digitalRead(center_sensor) == 1)&&( digitalRead(sensor_right) == 0)){  MoveForward(60);}

      if (( digitalRead(sensor_left) == 1)&&( digitalRead(center_sensor) == 1)&&( digitalRead(sensor_right) == 0)){  turnLeft(70);   }
      
      if (( digitalRead(sensor_left) == 1)&&( digitalRead(center_sensor) == 0)&&( digitalRead(sensor_right) == 0)){  turnLeft(70);   }
      
      if (( digitalRead(sensor_left) == 0)&&( digitalRead(center_sensor) == 1)&&( digitalRead(sensor_right) == 1)){  turnRight(70);  }
      
      if (( digitalRead(sensor_left) == 0)&&( digitalRead(center_sensor) == 0)&&( digitalRead(sensor_right) == 1)){  turnRight(70);  }

       //       Serial.println("moving car with buzzer off and distance is : " + distance) ;

      
    }

  

}
