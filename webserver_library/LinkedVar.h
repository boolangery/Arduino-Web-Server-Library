#ifndef HTML_LINKED_VAR_HEADER
#define HTML_LINKED_VAR_HEADER

#include "Arduino.h"
#include "LinkedVar.h"

/**
* Représente une variable qui va étre linkée à un objet Html.
*
**/

class LinkedVar
{
    public:
        enum types_t {INT,BYTE, STRING, BOOL};
        
        LinkedVar(int *var): _var(var), _type(INT) {}
        LinkedVar(byte *var): _var(var), _type(BYTE) {}
        LinkedVar(bool *var): _var(var), _type(BOOL) {}
        
        static LinkedVar** linkArray(int *array, int arrSize)
        {
            LinkedVar **vars = new LinkedVar*[arrSize];
            for (int i=0; i<arrSize;i++)
                vars[i] = new LinkedVar(&array[i]);
            return vars;
        }
        static LinkedVar** linkArray(byte *array, int arrSize)
        {
            LinkedVar **vars = new LinkedVar*[arrSize];
            for (int i=0; i<arrSize;i++)
                vars[i] = new LinkedVar(&array[i]);
            return vars;
        }
        
        
        String getValue()
        {
            switch(_type) {
                case INT:
                return String(*((int*)(_var)));
                case BYTE:
                return String(*((byte*)(_var)));
                case BOOL:
                return String(*((bool*)(_var)));
                case STRING:
                return *((String*)(_var));
            }
        }
        
        String getHexValue()
        {
            char buffer[40];
            switch(_type) {
                case INT:
                sprintf(buffer, "%x", *((int*)(_var)));
                return String(buffer);
                case BYTE:
                sprintf(buffer, "%x", *((byte*)(_var)));
                return String(buffer);
              
            }
        }
        
        void setValue(int newValue) { *((int*)(_var)) = newValue; }
        void setValue(String newValue) 
        { 
            //Serial.println("setValue : " + newValue);
            switch(_type) {
                case BOOL:
                *((bool*)(_var)) = newValue.equals("true")?true:false ;
            }
        }
        
   
    private:
        void *_var;
        types_t _type;
};



#endif
