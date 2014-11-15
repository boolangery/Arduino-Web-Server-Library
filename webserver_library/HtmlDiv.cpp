#include "HtmlDiv.h"

PROGMEM prog_char HtmlDiv[] = "<div> $ </div>";

PROGMEM const char *HtmlDiv_tab[] = {   
  HtmlDiv
};

HtmlDiv::HtmlDiv(HtmlObject *child): HtmlObject(0)
{
    HtmlObject::add(child);
}


String HtmlDiv::getHtml() const
{
    return getFormatedString((char*)pgm_read_word(&(HtmlDiv_tab[0])));
}
