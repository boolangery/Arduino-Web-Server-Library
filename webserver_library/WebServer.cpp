#include "Webserver.h"

WebServer::WebServer(): 
_server(80)
{
    _server.begin();
}



void WebServer::handle()
{
    String HTTP_req;
    EthernetClient client = _server.available();
    if (client) {
        boolean currentLineIsBlank = true;
        while (client.connected()) {
            if (client.available()) {
                char c = client.read();
                HTTP_req += c;
                // if the line is blank we can send http response
                if (c == '\n' && currentLineIsBlank) {
                    if (HTTP_req.indexOf("favicon")>0) {
                        HTTP_req = "";  
                        return;
                    }
                    processUrlData(HTTP_req, node);
                    sendPage(&client, node, getPageId(HTTP_req)); 
                    HTTP_req = "";  
                    delay(1);
                    client.stop();
                    break;
                }
                if (c == '\n') {
                    // you're starting a new line
                    currentLineIsBlank = true;
                } 
                else if (c != '\r') {
                    // you've gotten a character on the current line
                    currentLineIsBlank = false;
                }
            }
        }
    }  

}

