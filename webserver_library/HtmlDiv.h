#ifndef HTML_DIV_HEADER
#define HTML_DIV_HEADER

#include "Arduino.h"
#include "HtmlObject.h"

class HtmlDiv : public HtmlObject
{
    public:
        HtmlDiv(HtmlObject *child);
        void renderHtml(BufferedEthernetClient *client) const;
        virtual int acceptNChild() { return 1;}
  
    private:
        
};

#endif
