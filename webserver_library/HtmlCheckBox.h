#ifndef HTML_CHECK_BOX_HEADER
#define HTML_CHECK_BOX_HEADER

#include "Arduino.h"
#include "HtmlObject.h"

class HtmlCheckBox : public HtmlObject
{
    public:
        HtmlCheckBox();
        void renderHtml(BufferedEthernetClient *client) const;
        virtual int acceptNChild() {return 0;}

  
    private:
        
};

#endif // HTML_CHECK_BOX_HEADER
