#ifndef HTML_FORM_POST_HEADER
#define HTML_FORM_POST_HEADER

#include "Arduino.h"
#include "HtmlObject.h"

class HtmlFormPost : public HtmlObject
{
    public:
        HtmlFormPost();
        void renderHtml(BufferedEthernetClient *client) const;
        virtual int acceptNChild() { return 10;}
  
    private:
        
};

#endif
