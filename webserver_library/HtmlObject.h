#ifndef HTML_OBJECT_HEADER
#define HTML_OBJECT_HEADER

#include "Arduino.h"
#include "LinkedVar.h"

#define BUFFER_SIZE 200

/**
*
* Cette classe représente un objet générique Html.
*
*/
class HtmlObject
{
    public:
        enum dataFormat_t {NORMAL, HEXA};
    
        HtmlObject(int linkedVar);
        HtmlObject(int linkedVar, dataFormat_t f);
        ~HtmlObject();
        virtual String getHtml() const = 0;

        void linkVar(LinkedVar *var);
        void linkVars(LinkedVar **var, int n);
        void setFormat(dataFormat_t f) { _format=f;}
        
    protected:
        String getFormatedString(PROGMEM const char *str) const;
        LinkedVar **_linkedVars;
        int _counter;
        int _nLinked;
        dataFormat_t _format;
  
    private:
        
        
       
};

#endif
