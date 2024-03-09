#include "blite.h"

void Blite::defineM12(bool polarity) {
    if (polarity){
        m1 = M12_A;
        m2 = M12_B;
    } else {
        m2 = M12_A;
        m1 = M12_B;
    }
}

void Blite::defineM34(bool polarity) {
    if (polarity){
        m3 = M34_A;
        m4 = M34_B;
    } else {
        m4 = M34_A;
        m3 = M34_B;
    }
}

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
    defineM12(false);
}

void Blite::reversePolarityM34(){
    defineM34(false);
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
    speed = s ;
}
bool Blite::connectWifi(char username, char password){
    int retry = 0;
    while (retry <= 10) {
    if (!WiFi.isConnected()) {
        WiFi.begin(username,password);
        delay(500);
    } else {
        return 1;
    }
    retry += 1;
    }
    return 0;
}

bool Blite::startServer() {
    if (WiFi.isConnected()){
        WiFi.disconnect();
    }
    return 0;
}