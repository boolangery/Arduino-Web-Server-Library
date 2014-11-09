#include "HtmlMacField.h"


PROGMEM prog_char HtmlMacField[] = "Mac Field : 0x#:0x#:0x#:0x#:0x#:0x# ";

PROGMEM const char *HtmlMacField_tab[] = {   
  HtmlMacField
};

HtmlMacField::HtmlMacField(): HtmlObject(6, HtmlObject::HEXA)
{
    
}


String HtmlMacField::getHtml() const
{
    return getFormatedString((char*)pgm_read_word(&(HtmlMacField_tab[0])));
}
