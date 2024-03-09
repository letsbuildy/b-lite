#ifndef BLITE_H_
#define BLITE_H_

#define IO1 6
#define IO2 7

#define M12_A 0
#define M12_B 2
#define M34_A 14
#define M34_B 14

#define I2C_SCL 4
#define I2C_SDA 5

#define ADC A0
#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
class Blite {
public:
bool startServer();
bool connectWifi(char username, char password);

void moveForward();
void moveBackward();
void turnRight();
void turnLeft();
void setSpeed(int speed);

void reversePolarityM12();
void reversePolarityM34();

int getIO(const char * io);

private:
int m1,m2,m3,m4,speed;
void defineM12(bool polarity);
void defineM34(bool polarity);
};
#endif