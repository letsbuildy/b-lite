#include <ESP8266WiFi.h>
#include <WiFiClient.h> 
#include <ESP8266WebServer.h>
// Motor pins(2 X 2-pin connector) connected to DRR8833
#define m1_pin1 0
#define m1_pin2 2
#define m2_pin1 14
#define m2_pin2 15

// programmable I/O (2 X 3-pin connector) 5v bi-directional level shifted driving at BAT level
#define io1 12
#define io2 13

// Analog input pin (1 X 3-pin connector) driving at 3.3V
#define analog_sensor A0

// I2C/HC-SR04 pin (1X 4-pin connector) driving at BAT level
#define i2c_tx 4
#define i2c_rx 5


String command;             //String to store app command state.
int speedCar = 800;         // 400 - 1023.
int speed_Coeff = 3;
int wither = 0; 
const int IN_1 = m1_pin2;
const int IN_2 = m1_pin1;
const int IN_3 = m2_pin2;
const int IN_4 = m2_pin1;

const char* ssid = "buidybee_rc_car";
ESP8266WebServer server(80);

void setup() {
 pinMode(IN_1, OUTPUT);
 pinMode(IN_2, OUTPUT);
 pinMode(IN_3, OUTPUT);
 pinMode(IN_4, OUTPUT); 
  
  Serial.begin(115200);
    // We set a Static IP address
  IPAddress local_IP(192, 168, 4, 1);
  // We set a Gateway IP address
  IPAddress gateway(192, 168, 4, 1);
  IPAddress subnet(255, 255, 255, 0);
// Connecting WiFi
  WiFi.softAPConfig(local_IP,gateway,subnet);
  WiFi.mode(WIFI_AP);
  WiFi.softAP(ssid);

  IPAddress myIP = WiFi.softAPIP();
  // should print the same ip set above
  Serial.print("AP IP address: ");
  Serial.println(myIP);
 
 // Starting WEB-server 
     server.on ( "move", HTTP_handleRoot );
     server.onNotFound ( HTTP_handleRoot );
     server.begin();    
}

void goAhead(){ 

      digitalWrite(IN_1, LOW);
      analogWrite(IN_2, speedCar);

      digitalWrite(IN_3, LOW);
      analogWrite(IN_4, speedCar);

  }

void goBack(){ 

      analogWrite(IN_1, speedCar);
      digitalWrite(IN_2, LOW);

      analogWrite(IN_3, speedCar);
      digitalWrite(IN_4, LOW);
  }

void goRight(){ 

      analogWrite(IN_1, speedCar);
      digitalWrite(IN_2, LOW);

      digitalWrite(IN_3, LOW);
      analogWrite(IN_4, speedCar);
  }

void goLeft(){

      digitalWrite(IN_1, LOW);
      analogWrite(IN_2, speedCar);

      analogWrite(IN_3, speedCar);
      digitalWrite(IN_4, LOW);
  }

void goAheadRight(){
      
      digitalWrite(IN_1, LOW);
      analogWrite(IN_2, speedCar/speed_Coeff);
 
      digitalWrite(IN_3, LOW);
      analogWrite(IN_4, speedCar);
   }

void goAheadLeft(){
      
      digitalWrite(IN_1, LOW);
      analogWrite(IN_2, speedCar);

      digitalWrite(IN_3, LOW);
      analogWrite(IN_4, speedCar/speed_Coeff);
  }

void goBackRight(){ 

      analogWrite(IN_1, speedCar/speed_Coeff);
      digitalWrite(IN_2, LOW);

      analogWrite(IN_3, speedCar);
      digitalWrite(IN_4, LOW);
  }

void goBackLeft(){ 

      analogWrite(IN_1, speedCar);
      digitalWrite(IN_2, LOW);

      analogWrite(IN_3, speedCar/speed_Coeff);
      digitalWrite(IN_4, LOW);
  }

void stopRobot(){  

      digitalWrite(IN_1, LOW);
      digitalWrite(IN_2, LOW);

      digitalWrite(IN_3, LOW);
      digitalWrite(IN_4, LOW);
 }

void loop() {
    server.handleClient();
    
      command = server.arg("dir");
      if (command == "F") goAhead();
      else if (command == "B") goBack();
      else if (command == "L") goLeft();
      else if (command == "R") goRight();
      else if (command == "I") goAheadRight();
      else if (command == "G") goAheadLeft();
      else if (command == "J") goBackRight();
      else if (command == "H") goBackLeft();
      else if (command == "0") speedCar = 400;
      else if (command == "1") speedCar = 470;
      else if (command == "2") speedCar = 540;
      else if (command == "3") speedCar = 610;
      else if (command == "4") speedCar = 680;
      else if (command == "5") speedCar = 750;
      else if (command == "6") speedCar = 820;
      else if (command == "7") speedCar = 890;
      else if (command == "8") speedCar = 960;
      else if (command == "9") speedCar = 1023;
      else if (command == "S") stopRobot();
    
}

void HTTP_handleRoot(void) {

if( server.hasArg("dir") ){
       Serial.println(server.arg("dir"));
       server.send ( 200, "text/html", "" );
       wither = 0;
  }
  delay(1);
}
