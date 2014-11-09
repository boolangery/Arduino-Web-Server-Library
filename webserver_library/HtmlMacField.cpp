#include "HtmlMacField.h"


PROGMEM prog_char test[] = "Mac Field : # # # # # # ";

PROGMEM const char *html_test[] = {   
  test
};

HtmlMacField::HtmlMacField(): HtmlObject(6, HtmlObject::HEXA)
{
    
}


String HtmlMacField::getHtml() const
{
    return getFormatedString((char*)pgm_read_word(&(html_test[0])));
}
