#ifndef BLITE_H_
#define BLITE_H_

#if defined(ESP8266)

#define IO1 6
#define IO2 7
#define SW1 16

#define M12_A 0
#define M12_B 2
#define M34_A 14
#define M34_B 14

#define I2C_SCL 4
#define I2C_SDA 5

#define ADC1 A0
#include <Arduino.h>
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
        this->m1 = M12_A;
        this->m2 = M12_B;
    } else {
        this->m2 = M12_A;
        this->m1 = M12_B;
    }
};
void defineM34(bool polarity){
     if (polarity){
        this->m3 = M34_A;
        this->m4 = M34_B;
    } else {
        this->m4 = M34_A;
        this->m3 = M34_B;
    }
};
};
#endif
#endif