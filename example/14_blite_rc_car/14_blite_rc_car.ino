#include "blite.h"
#include "remote.h"

Blite myBot;
ESP8266WebServer server(80);

void setup(){
    myBot.setup();
    Serial.begin(115200);
    myBot.APServer();
    server.on("/", HTTP_GET, []() {
    Serial.println("Web Server: received a web page request");
    String html = HTML_CONTENT;  // Use the HTML content from the servo_html.h file
    server.send(200, "text/html", html);
  });
  server.begin();
}
void loop(){
    server.handleClient();
    if (myBot.buttonPressed()){
        myBot.blinkLed(2);
    }
}

