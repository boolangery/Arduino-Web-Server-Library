#ifndef WEB_SERVER_HEADER
#define WEB_SERVER_HEADER

#include "Arduino.h"
#include <Ethernet.h>

class WebServer
{
    public:
        WebServer();
    
        void handle();
    
    private:
        EthernetServer _server;
       
};

#endif
