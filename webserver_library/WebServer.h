#ifndef WEB_SERVER_HEADER
#define WEB_SERVER_HEADER

#include "Arduino.h"
#include <Ethernet.h>

#include "HtmlPage.h"
#include "Vector.h"

class WebServer: public EthernetServer
{
    public:
        WebServer();
    
        void add(HtmlPage *page);
        void handle();
        
    private:
        void render(EthernetClient *client);
        void sendHttpResponse(EthernetClient *client);
        void beginPage(EthernetClient *client);
        void endPage(EthernetClient *client);
        void sendStr(EthernetClient *client, PROGMEM const char *str);


    
    private:
        Vector<HtmlPage*> _htmlPages;
};

#endif
