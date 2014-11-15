#ifndef HTML_PAGE_HEADER
#define HTML_PAGE_HEADER

#include <Arduino.h>
#include <Ethernet.h>
#include <SPI.h>

#include "HtmlObject.h"
#include "Vector.h"

class HtmlPage
{
    public:
        HtmlPage(String pageName, HtmlObject *content);

        String getHtml()
        {
            return _content->getHtml();
        }
        
        void setWebServerId(int id) {_webserverId=id;}
        int getWebServerId() {return _webserverId;}
        
        void propagateJavascriptValues(String& httpReq);
        
        void recursivePropagation(HtmlObject* object, String& httpReq);
    
    private:
        String getUrlData(String& url, String fieldName, int maxSize);    

    private:
        String _pageName;
        HtmlObject *_content;
        int _webserverId;        // Identifiant attribué par le webserveur pour retrouver les pages en fonction du menu
};

#endif
