#ifndef HTML_ARRAY_HEADER
#define HTML_ARRAY_HEADER

#include "Arduino.h"
#include "HtmlObject.h"

class HtmlArray : public HtmlObject
{
    public:
        HtmlArray(int row, int column);
        String getHtml() const;
        virtual int acceptNChild() { return _nRow*_nColumn;}
  
    private:
        int _nRow, _nColumn;
        
};

#endif // HTML_ARRAY_HEADER
