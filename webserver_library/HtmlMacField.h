#ifndef HTML_MAC_FIELD_HEADER
#define HTML_MAC_FIELD_HEADER

#include "Arduino.h"
#include "HtmlObject.h"
#include <avr/pgmspace.h>

#define BUFFER_SIZE 200

class HtmlMacField : public HtmlObject
{
    public:
        HtmlMacField();
        String getHtml() const;

  
    private:
        
};

#endif
