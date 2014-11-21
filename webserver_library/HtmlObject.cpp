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

String HtmlObject::getId() const
{
    String s(ID_DELIMITER);
    s += _id;
    s += ID_DELIMITER;
    return s;
}
    
/*void HtmlObject::getFormatedString(BufferedEthernetClient *client,PROGMEM const char *str) const {
    char b1[BUFFER_SIZE];
    strcpy_P(b1, str);
    getFormatedDoWork(client, b1);
}*/

void HtmlObject::getFormatedString(BufferedEthernetClient *client,String str) const
{
    getFormatedDoWork(client, str.c_str());
}

// TODO enlever les buffers
void HtmlObject::getFormatedString(BufferedEthernetClient *client, PROGMEM prog_char str[]) const
{
    char b1[BUFFER_SIZE];
    strcpy_P(b1, str);
    getFormatedDoWork(client, b1);
}

void HtmlObject::getFormatedDoWork(BufferedEthernetClient *client, const char * str) const
{
    //String ret;
    bool addAllChild = false;
    char strBuffer[64];
    int k=0, m=0;
    int counter=0;
    int len = strlen(str);
    
    if (_counter > _nLinked)
    {
        client->print("HtmlObject::Error::Linked vars");
        return;
    }
    counter=0;
    for(int i=0; i<len; i++)
        if (str[i] == '$')
            counter++;
    
    if (counter != _childs.size())
    {
        addAllChild = true;
    }
  
    for(int i=0; i<len; i++)
    {
        if (str[i] == '#')        // linked vars
        {
            if (_format == HEXA)
            {
                _linkedVars[k++]->getValueStr(strBuffer, 16);
                client->print(strBuffer);
            }
            else
            {
                _linkedVars[k++]->getValueStr(strBuffer, 10);
                client->print((char*)strBuffer);
            }
        }
        else if (str[i] == '$')    // enfants
        {
            if (addAllChild)
                for(int i=0; i<_childs.size();i++)
                    _childs[i]->renderHtml(client);
            else
                _childs[m++]->renderHtml(client);

        }
        else if (str[i] == '&')    // javascript
        {
            if (_javascript != NULL)
                client->print(_javascript->getInnerHtml());
        }
        else if (str[i] == '%')
        {
            client->print(this->getId());   
        }
        else
        {
            client->print(str[i]);
        }
    }    
}

