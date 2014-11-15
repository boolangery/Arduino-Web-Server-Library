#include "HtmlObject.h"
#include "JavascriptOnChange.h"

int HtmlObject::_instanceCounter = 0;
const char HtmlObject::ID_DELIMITER = 'd';

HtmlObject::HtmlObject(int linkedVarsMax): _counter(0), _nLinked(linkedVarsMax), _format(NORMAL), _javascript(NULL)
{
    _linkedVars = new LinkedVar*[_nLinked];
    _id = _instanceCounter;
    _instanceCounter++;
}

HtmlObject::HtmlObject(int linkedVarsMax, dataFormat_t f):_counter(0), _nLinked(linkedVarsMax), _format(f), _javascript(NULL)
{
    _linkedVars = new LinkedVar*[_nLinked];
    _id = _instanceCounter;
    _instanceCounter++;
}

HtmlObject::~HtmlObject()
{
    delete _linkedVars;
}

void HtmlObject::add(HtmlObject *o) 
{
    if (_childs.size() < acceptNChild())
        _childs.push_back(o); 
}

void HtmlObject::linkVar(LinkedVar *var)
{
    if (_counter >= _nLinked)
        return;     
    _linkedVars[_counter++] = var;   
}

void HtmlObject::linkVars(LinkedVar **var, int n)
{
    for(int i=0;i<n;i++)
    {
         if (_counter >= _nLinked)
            return;     
        _linkedVars[_counter++] = var[i];     
    }
}

String HtmlObject::getId()
{
    String s(ID_DELIMITER);
    s += _id;
    s += ID_DELIMITER;
    return s;
}
    
String HtmlObject::getFormatedString(PROGMEM const char *str) const {
    char b1[BUFFER_SIZE];
    strcpy_P(b1, str);
    return getFormatedDoWork(b1);
}

String HtmlObject::getFormatedString(String str) const
{
    return getFormatedDoWork(str.c_str());
}

String HtmlObject::getFormatedDoWork(const char * str) const
{
    String ret;
    int k=0;
    int counter=0;
    int len = strlen(str);
    
    if (_counter > _nLinked)
    {
        String error = "HtmlObject::Error::Linked vars " ;
        error += _nLinked;
        error += " vars";
        return error;
    }
        
   /* for(int i=0; i<len; i++)
        if (str[i] == '#')
            counter++;
    
    if (counter != _counter)
        return "HtmlObject::Error::Number of # != size";*/
        
    counter=0;
    for(int i=0; i<len; i++)
        if (str[i] == '$')
            counter++;
    
    if (counter != _childs.size())
        return "HtmlObject::Error::Number of $ != _child.size()";
  
    for(int i=0; i<len; i++)
    {
        if (str[i] == '#')        // linked vars
        {
            if (_format == HEXA)
                ret += _linkedVars[k++]->getHexValue();
            else
                ret += _linkedVars[k++]->getValue();
        }
        else if (str[i] == '$')    // enfants
        {
            ret += _childs[k++]->getHtml();
        }
        else if (str[i] == '&')    // javascript
        {
            if (_javascript != NULL)
                ret += _javascript->getInnerHtml();
        }
        else
        {
            ret += str[i];
        }
    }    
  return ret;
}

