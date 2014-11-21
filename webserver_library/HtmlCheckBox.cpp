#include "HtmlCheckBox.h"

PROGMEM prog_char HtmlCheckBox[] = "<input type=checkbox &>";

PROGMEM const char *HtmlCheckBox_tab[] = {   
  HtmlCheckBox
};

HtmlCheckBox::HtmlCheckBox(): HtmlObject(1)
{
}


void HtmlCheckBox::renderHtml(BufferedEthernetClient *client) const
{
    getFormatedString(client, (char*)pgm_read_word(&(HtmlCheckBox_tab[0])));
}
