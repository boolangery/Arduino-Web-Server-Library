#include "HtmlInputNumber.h"
#include "WebServer.h"

P(html) = "<input type='number' name='%' min='0' max='255' value='#' style='width:44px;' &>";

HtmlInputNumber::HtmlInputNumber(LinkedVar *var): HtmlObject(1)
{
   // HtmlObject::linkVar(var);
   this->linkVar(var);
}


void HtmlInputNumber::renderHtml(BufferedEthernetClient *client) const
{
 
    
    //P(html) = "<input type='number' min='0' max='255' value='#' style='width:44px;'>";
    getFormatedString(client, html);
   
    /*String ret = "<div> $ </div>", tmp;
    for (int i=0; i<_childs.size(); i++)
        tmp += "$";
        
    ret.replace("$", tmp);
    getFormatedString(client, ret);*/
    //return getFormatedString((char*)pgm_read_word(&(HtmlDiv_tab[0])));
}
