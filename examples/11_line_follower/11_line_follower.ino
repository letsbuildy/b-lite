#include <blite.h>

Blite myBot;
int irLeft = myBot.getIO("io1");
int irRight = myBot.getIO("io2");
bool lineFollwerMode = false;

void setup()
{
  // Debug console
  Serial.begin(115200);
  myBot.setup();
  myBot.smartConnectWiFi();

}

void loop()
{
  myBot.otaLoop();

  if(myBot.buttonPressed()) {
    lineFollwerMode = !lineFollwerMode;
  }
  if (lineFollwerMode){
    Serial.print("Line Follower Mode");
    if(digitalRead(irLeft)==LOW  && digitalRead(irRight)==LOW)
    {
      myBot.moveForward();
    }
    if(digitalRead(irLeft)==HIGH  && digitalRead(irRight)==LOW)
    {
      myBot.turnRight();
    }
    if(digitalRead(irLeft)==LOW  && digitalRead(irRight)==HIGH)
    {
      myBot.turnLeft();
    }
    if(digitalRead(irLeft)==HIGH  && digitalRead(irRight)==HIGH)
    {
      myBot.stopMotor();
      lineFollwerMode = false;

    }
  }

}