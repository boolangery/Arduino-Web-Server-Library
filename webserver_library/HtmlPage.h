#ifndef HTML_PAGE_HEADER
#define HTML_PAGE_HEADER

#include <Arduino.h>
#include <Ethernet.h>
#include <SPI.h>


class HtmlPage
{
    public:
        HtmlPage(String pageName);
        
    
        void sendHttpResponse(EthernetClient *client);
        void beginPage(EthernetClient *client);
        void endPage(EthernetClient *client);

        void sendStr(EthernetClient *client, PROGMEM const char *str);


    private:
        String _pageName;
};

#endif
