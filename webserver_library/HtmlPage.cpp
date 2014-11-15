#include "Arduino.h"
#include "HtmlPage.h"
#include "LinkedVar.h"


HtmlPage::HtmlPage(String pageName, HtmlObject *content): _pageName(pageName), _content(content), _webserverId(0)
{
  
  
}


void HtmlPage::propagateJavascriptValues(String& httpReq)
{
    recursivePropagation(_content, httpReq);
}

void HtmlPage::recursivePropagation(HtmlObject* object, String& httpReq)
{
    if (object == NULL)
        return;
    if (object->getJavascript() != NULL)
    {
        String data = getUrlData(httpReq, object->getId(), 10);
        object->getLinkedVars()[0]->setValue(data);
        Serial.println(data);
    }
    Vector<HtmlObject*>& childs = object->getChilds();
    for (int i=0 ; i<childs.size() ; i++) 
    {
        recursivePropagation(childs[i] , httpReq);
    }
}



String HtmlPage::getUrlData(String& url, String fieldName, int maxSize) {
  String data;
  int pos = url.indexOf(fieldName);
  int maxPos = url.indexOf("Host");
  if (pos <= -1 || pos > maxPos ) return NULL;
  pos += fieldName.length() + 1;
  for(int i =0; i<maxSize; i++) {
    if (url[pos + i] == '&' || url[pos + i] == ' ') {
      break;
    }
    else if (url[pos + i] == '+')
      data += ' ';
    else 
      data += url[pos + i];
  }
  return data;
}
