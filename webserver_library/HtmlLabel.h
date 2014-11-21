#ifndef HTML_LABEL_HEADER
#define HTML_LABEL_HEADER

#include "Arduino.h"
#include "HtmlObject.h"

class HtmlLabel : public HtmlObject
{
    public:
        HtmlLabel(PROGMEM prog_char name[]): HtmlObject(0), _name(name){}
        
        void renderHtml(BufferedEthernetClient *client) const
        {
            client->printP(_name);
        }
        
        virtual int acceptNChild() { return 0;}
        
  
    private:
        PROGMEM prog_char *_name;
};

#endif
