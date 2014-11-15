#include "JavascriptOnChange.h"


PROGMEM prog_char JavascriptOnChange_page[] = 
            "function updateField(id,val){"
                "var xmlhttp=new XMLHttpRequest();"
                "xmlhttp.open('POST','?'+id+'='+val+'&t='+Math.random(),true);"
                "xmlhttp.send();"
            "}";
            
PROGMEM prog_char JavascriptOnChange_inner[] = 
            "onchange=\"updateField('#', this.checked)\"";

PROGMEM const char *JavascriptOnChange_tab[] = {   
  JavascriptOnChange_page, JavascriptOnChange_inner
};

JavascriptOnChange::JavascriptOnChange(HtmlObject *child): HtmlObject(0), _child(child)
{
    child->addJavascript(this);
} 

String JavascriptOnChange::getInnerHtml() const
{
    char buffer[60];
    strcpy_P(buffer, (char*)pgm_read_word(&(JavascriptOnChange_tab[1]))); 
    String tmp(buffer);
    tmp.replace("#", _child->getId());
    return tmp;
}


String JavascriptOnChange::getHtml() const
{
    return getFormatedString((char*)pgm_read_word(&(JavascriptOnChange_tab[0])));
}
