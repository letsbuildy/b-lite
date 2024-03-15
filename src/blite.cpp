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
    analogWrite(this->m1,this->speed);
    digitalWrite(this->m2,LOW);
    analogWrite(this->m4,this->speed);
    digitalWrite(this->m3,LOW);
}
void Blite::moveBackward(){
    analogWrite(this->m2,this->speed);
    digitalWrite(this->m1,LOW);
    analogWrite(this->m3,this->speed);
    digitalWrite(this->m4,LOW);
}
void Blite::turnRight(){
    digitalWrite(this->m1,LOW);
    digitalWrite(this->m2,LOW);
    analogWrite(this->m4,this->speed);
    digitalWrite(this->m3,LOW);
}
void Blite::turnLeft(){
    analogWrite(this->m1,this->speed);
    digitalWrite(this->m2,LOW);
    digitalWrite(this->m3,LOW);
    digitalWrite(this->m4,LOW);
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
bool Blite::smartConnectWiFi(){
    WiFi.disconnect();
    WiFi.mode(WIFI_STA);
    WiFiManager wm;
    bool res;
    res = wm.autoConnect("Buildybee-smart-config","buildybee"); // password protected ap
    return res;
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
  pinMode(M1,OUTPUT);
  pinMode(M2,OUTPUT);
  pinMode(M3,OUTPUT);
  pinMode(M4,OUTPUT);
  this->stopMotor();
  this->defineM12(true);
  this->defineM34(true);
  this->speed = 100;
  String newHostname = "buildybee";
  WiFi.hostname(newHostname.c_str());
  WiFi.disconnect();
  WiFi.mode(WIFI_OFF);
  this->otaSetup();

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

void Blite::setupServer(String HTML_CONTENT) {
    this->webServer.on("/", HTTP_GET, [=]() {
        this->webServer.send(200, "text/html", HTML_CONTENT);
    });
    this->webServer.begin();
    this->serverSetupDone = true;
}

void Blite::renderServer() {
    this->webServer.handleClient();
    this->otaLoop();
}

void Blite::smartRenderServer(String HTML_CONTENT){
    if (!this->serverSetupDone) {
        this->setupServer(HTML_CONTENT);
    }
    this->renderServer();
}

void Blite::otaSetup(){

  ArduinoOTA.onStart([]() {
    String type;
    if (ArduinoOTA.getCommand() == U_FLASH) {
      type = "sketch";
    } else {  // U_FS
      type = "filesystem";
    }

    // NOTE: if updating FS this would be the place to unmount FS using FS.end()
    Serial.println("Start updating " + type);
  });
  ArduinoOTA.onEnd([]() {
    Serial.println("\nEnd");
  });
  ArduinoOTA.onProgress([](unsigned int progress, unsigned int total) {
    Serial.printf("Progress: %u%%\r", (progress / (total / 100)));
  });
  ArduinoOTA.onError([](ota_error_t error) {
    Serial.printf("Error[%u]: ", error);
    if (error == OTA_AUTH_ERROR) {
      Serial.println("Auth Failed");
    } else if (error == OTA_BEGIN_ERROR) {
      Serial.println("Begin Failed");
    } else if (error == OTA_CONNECT_ERROR) {
      Serial.println("Connect Failed");
    } else if (error == OTA_RECEIVE_ERROR) {
      Serial.println("Receive Failed");
    } else if (error == OTA_END_ERROR) {
      Serial.println("End Failed");
    }
  });
  ArduinoOTA.begin();
}

void Blite::otaLoop(){
    ArduinoOTA.handle();
}

void Blite::stopMotor(){
  digitalWrite(M1,LOW);
  digitalWrite(M2,LOW);
  digitalWrite(M3,LOW);
  digitalWrite(M4,LOW);

}
