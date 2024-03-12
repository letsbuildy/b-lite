#include <blite.h>
#include "remote.h"

Blite myBot;
ESP8266WebServer wifiRemoteControl(80);

void setup(){
    myBot.setup();
    Serial.begin(115200);
    myBot.smartConnectWiFi();
    wifiRemoteControl.on("/", HTTP_GET, []() {
        Serial.println("Web Server: received a web page request");
        String html = REMOTE_HTML_CONTENT;
        wifiRemoteControl.send(200, "text/html", html);
    });
    wifiRemoteControl.begin();
}
void loop(){
    wifiRemoteControl.handleClient();
    if (myBot.buttonPressed()){
        myBot.blinkLed(2);
    }
}

