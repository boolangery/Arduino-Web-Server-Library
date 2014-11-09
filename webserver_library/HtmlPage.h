#ifndef HTML_PAGE_HEADER
#define HTML_PAGE_HEADER

#include <Arduino.h>
#include <Ethernet.h>
#include <SPI.h>

#include "HtmlObject.h"

class HtmlPage
{
    public:
        HtmlPage(String pageName, HtmlObject *content);

        String getHtml()
        {
            return _content->getHtml();
        }

    private:
        String _pageName;
        HtmlObject *_content;
};

#endif
