#ifndef HTML_PAGE_HEADER
#define HTML_PAGE_HEADER

#include <Arduino.h>
#include <Ethernet.h>
#include <SPI.h>

#include "HtmlObject.h"
#include "Vector.h"

typedef void (*formCallback_t)(void);

class HtmlPage
{
    public:
        HtmlPage(String pageName, HtmlObject *content);

        void renderHtml(BufferedEthernetClient *client){ _content->renderHtml(client);}
        
        void setWebServerId(int id) {_webserverId=id;}
        int getWebServerId() {return _webserverId;}
        
        void propagateVars(char varName[], char varValue[]);
        
        void setFormCallback(formCallback_t cb) { _formCallback = cb;}
        void callback() {_formCallback();}
        
        
    
    private:
        void recursivePropagation(HtmlObject* object, char varName[], char varValue[]);
        String getUrlData(String& url, String fieldName, int maxSize);    

    private:
        String _pageName;
        HtmlObject *_content;
        int _webserverId;        // Identifiant attribué par le webserveur pour retrouver les pages en fonction du menu
        
        formCallback_t _formCallback;
};

#endif
