#include "HtmlDiv.h"

PROGMEM prog_char HtmlDiv[] = "<div> $ </div>";

PROGMEM const char *HtmlDiv_tab[] = {   
  HtmlDiv
};

HtmlDiv::HtmlDiv(HtmlObject *child): HtmlObject(0)
{
    HtmlObject::add(child);
}


void HtmlDiv::renderHtml(BufferedEthernetClient *client) const
{
    String ret = "<div> $ </div>", tmp;
    for (int i=0; i<_childs.size(); i++)
        tmp += "$";
        
    ret.replace("$", tmp);
    getFormatedString(client, ret);
    //return getFormatedString((char*)pgm_read_word(&(HtmlDiv_tab[0])));
}
