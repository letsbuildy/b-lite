#include "blite.h"

int Blite::getIO(const char * io){
    if (io == "io1") {
        return IO1;
    } else if (io =="io2") {
        return IO2;
    } else if (io == "scl") {
        return I2C_SCL;
    } else if (io == "sda"){
        return I2C_SDA;
    }
    return -1;
    
}
void Blite::reversePolarityM12(){
    this->defineM12(false);
}
void Blite::reversePolarityM34(){
    this->defineM34(false);
}
void Blite::moveForward(){
    analogWrite(m1,speed);
    digitalWrite(m2,LOW);
    analogWrite(m4,speed);
    digitalWrite(m3,LOW);
}
void Blite::moveBackward(){
    analogWrite(m2,speed);
    digitalWrite(m1,LOW);
    analogWrite(m3,speed);
    digitalWrite(m4,LOW);
}
void Blite::turnRight(){
    digitalWrite(m1,LOW);
    digitalWrite(m2,LOW);
    analogWrite(m4,speed);
    digitalWrite(m3,LOW);
}
void Blite::turnLeft(){
    analogWrite(m1,speed);
    digitalWrite(m2,LOW);
    digitalWrite(m3,LOW);
    digitalWrite(m4,LOW);
}
void Blite::setSpeed(int s){
    this->speed = s ;
}
bool Blite::connectWiFi(const char *username, const char *password){
    WiFi.disconnect();
    WiFi.mode(WIFI_STA);
    int retry = 0;
    while (retry <= 20) {
    if (WiFi.status() != WL_CONNECTED) {
        Serial.println("Trying to connect to wifi");
        WiFi.begin(username,password);
        WiFi.waitForConnectResult();
        delay(1000);
    } else {
        Serial.println("connected to wifi");
        Serial.println(WiFi.localIP());
        return 1;
    }
    retry++;
    }
    return 0;
}
void Blite::connectWiFi(){
    int cnt = 0;
    while(WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
    if(cnt++ >= 15){
       WiFi.beginSmartConfig();
       while(1){
           delay(500);
           if(WiFi.smartConfigDone()){
            //  Serial.println("SmartConfig Success");
            //  blinkSmartConfig();
             break;
           }
       }
    }
  }
}
bool Blite::APServer() {
    if (WiFi.isConnected()){
        if (WiFi.disconnect()){
            return 0;
        }
    }
    const char* ssid = "buidybee_rc_car";
    IPAddress local_IP(192, 168, 4, 1);
    // We set a Gateway IP address
    IPAddress gateway(192, 168, 4, 1);
    IPAddress subnet(255, 255, 255, 0);
    // Connecting WiFi
    WiFi.softAPConfig(local_IP,gateway,subnet);
    WiFi.mode(WIFI_AP);
    return WiFi.softAP(ssid);
}
bool Blite::buttonPressed() {
    return !digitalRead(SW1);
}

void Blite::setup(){
  pinMode(SW1,INPUT_PULLUP);
  pinMode(M12_A,OUTPUT);
  pinMode(M12_B,OUTPUT);
  pinMode(M34_A,OUTPUT);
  pinMode(M34_B,OUTPUT);
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, HIGH);
  this->defineM12(true);
  this->defineM34(true);
  WiFi.disconnect();
  WiFi.mode(WIFI_OFF);

}

void Blite::glowLed(bool s){
  if (s){
    digitalWrite(LED_BUILTIN, LOW);
  } else{
    digitalWrite(LED_BUILTIN, HIGH);
  }

}

void Blite::blinkLed(int c){
  for (int i=0;i<c;i++){
     digitalWrite(LED_BUILTIN, !digitalRead(LED_BUILTIN));
     delay(500);
    digitalWrite(LED_BUILTIN, !digitalRead(LED_BUILTIN));
    delay(500);
  }
}

int Blite::readADC(){
    return analogRead(ADC1);
}