#include "blite.h"
#include "index.h"

Blite myBot;

void setup(){
    myBot.setup();
    Serial.begin(115200);
    delay(1000);
    Serial.println(myBot.getIO("io1"));
    
    //check local server
    if (myBot.APServer()){
      myBot.glowLed(true);
    }
    
    //check wifi
    // if (myBot.connectWiFi("","")){
    //     myBot.glowLed(true);
    // } else {
    //     Serial.println("Cannot connect");
    // }
}
void loop(){
    if (myBot.buttonPressed()){
        myBot.blinkLed(2);
    }
}

