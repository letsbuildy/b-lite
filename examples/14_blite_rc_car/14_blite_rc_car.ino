#include <blite.h>
#include "remote.h"

Blite myBot;

void setup(){
    myBot.setup();
    Serial.begin(115200);
    myBot.smartConnectWiFi();

}
void loop(){
    String html = REMOTE_HTML_CONTENT;
    myBot.smartRenderServer(html);
}
