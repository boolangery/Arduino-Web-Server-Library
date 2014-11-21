#include "HtmlFormPost.h"
#include "WebServer.h"

P(htmlFormPost) = "<form method=GET name=formid> $ <br><input type=submit value=Submit></form>";

HtmlFormPost::HtmlFormPost(): HtmlObject(0)
{
    //HtmlObject::add(child);
}


void HtmlFormPost::renderHtml(BufferedEthernetClient *client) const
{
    getFormatedString(client, htmlFormPost);
}
