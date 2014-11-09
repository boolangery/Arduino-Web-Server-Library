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
        enum types_t {INT, STRING};
        
        LinkedVar(int *var): _var(var), _type(INT) {}
        
        static LinkedVar** linkArray(int *array, int arrSize)
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
           
              
            }
        }
        
        
        void setValue(int newValue) { *((int*)(_var)) = newValue; }
        void setValue(String newValue) { *((String*)(_var)) = newValue; }
        
   
    private:
        void *_var;
        types_t _type;
};

#endif
