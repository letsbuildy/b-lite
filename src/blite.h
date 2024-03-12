#ifndef BLITE_H_
#define BLITE_H_

#if defined(ESP8266)

#define IO1 12
#define IO2 13
#define SW1 16

#define M1 0
#define M2 2
#define M3 14
#define M4 15

#define I2C_SCL 5
#define I2C_SDA 4

#define ADC1 A0

#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <WiFiManager.h>

class Blite {
public:
void setup();
bool APServer();
bool connectWiFi(const char * username, const char * password);
bool smartConnectWiFi();
void moveForward();
void moveBackward();
void turnRight();
void turnLeft();
void setSpeed(int speed);

void reversePolarityM12();
void reversePolarityM34();

int getIO(const char * io);
bool buttonPressed();
void glowLed(bool s);
void blinkLed(int c);
int readADC();

private:
int m1,m2,m3,m4,speed;
void defineM12(bool polarity){
    if (polarity){
        this->m1 = M1;
        this->m2 = M2;
    } else {
        this->m2 = M1;
        this->m1 = M2;
    }
};
void defineM34(bool polarity){
     if (polarity){
        this->m3 = M3;
        this->m4 = M4;
    } else {
        this->m4 = M3;
        this->m3 = M4;
    }
};
};
#endif
#endif