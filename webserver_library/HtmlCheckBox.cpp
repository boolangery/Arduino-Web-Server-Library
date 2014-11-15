#include "HtmlCheckBox.h"

PROGMEM prog_char HtmlCheckBox[] = "<input type='checkbox' &>";

PROGMEM const char *HtmlCheckBox_tab[] = {   
  HtmlCheckBox
};

HtmlCheckBox::HtmlCheckBox(): HtmlObject(1)
{
}


String HtmlCheckBox::getHtml() const
{
    return getFormatedString((char*)pgm_read_word(&(HtmlCheckBox_tab[0])));
}
