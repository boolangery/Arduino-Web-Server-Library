
// "<input type='number' id='%s%d' min='0' max='255' value='%d' style='width:44px;'>&nbsp;"
 
#ifndef HTML_INPUT_NUMBER_HEADER
#define HTML_INPUT_NUMBER_HEADER

#include "Arduino.h"
#include "HtmlObject.h"

class HtmlInputNumber : public HtmlObject
{
    public:
        HtmlInputNumber(LinkedVar *var);
        void renderHtml(BufferedEthernetClient *client) const;
        virtual int acceptNChild() { return 1;}
  
    private:
        
};

#endif // HTML_INPUT_NUMBER_HEADER
