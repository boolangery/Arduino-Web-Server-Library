#ifndef WEB_SERVER_HEADER
#define WEB_SERVER_HEADER

#include "Arduino.h"
#include <Ethernet.h>
#include "Vector.h"

#include "MenuItem.h"
#include "HtmlP.h"
#include "HtmlDiv.h"
#include "HtmlArray.h"
#include "JavascriptOnChange.h"
#include "HtmlCheckBox.h"
#include "HtmlPage.h"
#include "HtmlMacField.h"
#include "LinkedVar.h"

class WebServer: public EthernetServer
{
    public:
        WebServer();
        void setHeader(PROGMEM const char *p) {_header=p;}
        void setCss(PROGMEM const char *p) {_css=p;}
        void add(HtmlPage *page);
        void handle();
        void addMenuItem(MenuItem* menu);
        
        // Debug
        void debug_printPage(int i, HardwareSerial *serial);
        
    private:
        void render(EthernetClient *client, int page);
        void sendHttpResponse(EthernetClient *client);
        void beginPage(EthernetClient *client);
        void endPage(EthernetClient *client);
        void sendStr(EthernetClient *client, PROGMEM const char *str);
        void sendMenu(EthernetClient *client);
        int getPageId(String HTTP_req);

    private:
        Vector<HtmlPage*> _htmlPages;
        HardwareSerial *_serial;
        PROGMEM const char *_header, *_css;
        Vector<MenuItem*> _menus;
};

#endif
