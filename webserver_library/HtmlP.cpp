#include "HtmlP.h"


HtmlP::HtmlP(String content): HtmlObject(0), _content(content)
{
}


void HtmlP::renderHtml(BufferedEthernetClient *client) const
{
    String ret = "<p>";
    ret += _content;
    ret += "</p>";
    //return ret;
    client->print(ret);
}
