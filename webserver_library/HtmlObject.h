#ifndef HTML_OBJECT_HEADER
#define HTML_OBJECT_HEADER

#include "Arduino.h"
#include "LinkedVar.h"
#include "Vector.h"
#include "BufferedEthernetClient.h"

class JavascriptOnChange;


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
    
        HtmlObject(int linkedVarsMax);
        HtmlObject(int linkedVarsMax, dataFormat_t f);
        
        ~HtmlObject();
        virtual void renderHtml(BufferedEthernetClient *client) const = 0;
        
        virtual int acceptNChild()=0;

        void linkVar(LinkedVar *var);
        void linkVars(LinkedVar **var, int n);
        void setFormat(dataFormat_t f) { _format=f;}
        
        void add(HtmlObject *o);
        void addJavascript(JavascriptOnChange *o) { _javascript = o;}
        JavascriptOnChange* getJavascript() {return _javascript;}
        Vector<HtmlObject*>& getChilds() {return _childs;}
        
        // test
        LinkedVar** getLinkedVars() {return _linkedVars;}
        
        // Identifiant des objets Html
        String getId() const;
        const static char ID_DELIMITER; 
        
        
        
        int setId(char id[])
        {
            if (strlen(id) >5) return -1;
            strcmp(_idStr, id);
        }
        
        
    protected:
        void getFormatedString(BufferedEthernetClient *client, String str) const;
        void getFormatedString(BufferedEthernetClient *client, PROGMEM prog_char str[]) const;
        void getFormatedDoWork(BufferedEthernetClient *client, const char * str) const;
        
        LinkedVar **_linkedVars;
        int _counter;
        int _nLinked;
        dataFormat_t _format;
        Vector<HtmlObject*> _childs;
        JavascriptOnChange *_javascript;
        
        static int _instanceCounter;
        int _id;
        
        char _idStr[5];
        
  
    private:
        
        
       
};

#endif
