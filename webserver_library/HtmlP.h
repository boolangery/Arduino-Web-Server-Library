#ifndef HTML_P_HEADER
#define HTML_P_HEADER

#include "Arduino.h"
#include "HtmlObject.h"

class HtmlP : public HtmlObject
{
    public:
        HtmlP(String content);
        String getHtml() const;
        virtual int acceptNChild() { return 0;}
  
    private:
        String _content;
};

#endif // HTML_P_HEADER
