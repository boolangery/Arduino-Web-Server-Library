#include "HtmlObject.h"


HtmlObject::HtmlObject(int linkedVar): _counter(0), _nLinked(linkedVar), _format(NORMAL)
{
    _linkedVars = new LinkedVar*[_nLinked];
}

HtmlObject::HtmlObject(int linkedVar, dataFormat_t f):_counter(0), _nLinked(linkedVar), _format(f)
{
    _linkedVars = new LinkedVar*[_nLinked];
}

HtmlObject::~HtmlObject()
{
    delete _linkedVars;
}


void HtmlObject::linkVar(LinkedVar *var)
{
    
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


String HtmlObject::getFormatedString(PROGMEM const char *str) const {
    char b1[BUFFER_SIZE], b2[BUFFER_SIZE];
    String ret;
    int k=0;
    int counter=0;
    
    if (_counter != _nLinked)
    {
        String error = "HtmlObject::Error::You must link " ;
        error += _nLinked;
        error += " vars";
        return error;
    }
        
    strcpy_P(b1, str);
    int len = strlen(b1);
    
    for(int i=0; i<len; i++)
        if (b1[i] == '#')
            counter++;
    
    if (counter != _counter)
        return "HtmlObject::Error::Number of # != size";
  
    for(int i=0; i<len; i++)
    {
        if (b1[i] == '#')
        {
            if (_format == HEXA)
                ret += _linkedVars[k++]->getHexValue();
            else
                ret += _linkedVars[k++]->getValue();
        }
        else
        {
            ret += b1[i];
        }
    }    
  return ret;
}
