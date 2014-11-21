#include "Arduino.h"
#include "HtmlPage.h"
#include "LinkedVar.h"
#include "WebServer.h"

HtmlPage::HtmlPage(String pageName, HtmlObject *content): _pageName(pageName), _content(content), _webserverId(0), _formCallback(NULL)
{
  
  
}


void HtmlPage::propagateVars(char varName[], char varValue[])
{
    recursivePropagation(_content, varName, varValue);
}

#include "MemoryFree.h"

void HtmlPage::recursivePropagation(HtmlObject* object, char varName[], char varValue[])
{
    if (object == NULL)
        return;
    //if (object->getJavascript() != NULL)
   // {
        char objectVarName[PARSE_VAR_MAX_NAME_LENGTH];
        object->getId().toCharArray(objectVarName, PARSE_VAR_MAX_NAME_LENGTH);

        if (strcmp(objectVarName, varName) == 0)
        {
            object->getLinkedVars()[0]->setValue(varValue);
        #if WEB_SERVER_DEBUGGING < WEB_SERVER_DEBUGGING_INFO
            Serial.println("HtmlPage::recursivePropagation: variable trouvée");
            Serial.print("varName = ");
            Serial.println(varName); 
            Serial.print("varValue = ");
            Serial.println(varValue);  
        #endif
        }
    //}
    Vector<HtmlObject*>& childs = object->getChilds();
    for (int i=0 ; i<childs.size() ; i++) 
    {
        recursivePropagation(childs[i] , varName, varValue);
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
