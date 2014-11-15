#ifndef JAVASCRIPT_ON_CHANGE
#define JAVASCRIPT_ON_CHANGE

#include "Arduino.h"


#include "HtmlObject.h"

class JavascriptOnChange : public HtmlObject
{
    public:
        JavascriptOnChange(HtmlObject *child);
        virtual int acceptNChild() {return 0;}
        String getHtml() const;
        String getInnerHtml() const;
  
    private:
        HtmlObject *_child;
   
};

#endif
