#ifndef HTML_DIV_HEADER
#define HTML_DIV_HEADER

#include "Arduino.h"
#include "HtmlObject.h"

class HtmlDiv : public HtmlObject
{
    public:
        HtmlDiv(HtmlObject *child);
        String getHtml() const;

  
    private:
        
};

#endif
