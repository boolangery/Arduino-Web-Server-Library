#include "HtmlP.h"


HtmlP::HtmlP(String content): HtmlObject(0), _content(content)
{
}


String HtmlP::getHtml() const
{
    String ret = "<p>";
    ret += _content;
    ret += "</p>";
    return ret;
}
