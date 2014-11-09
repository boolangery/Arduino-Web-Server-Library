#include "HtmlPage.h"
#include "HtmlMacField.h"
#include "LinkedVar.h"


#include <Ethernet.h>
#include <SPI.h>


void setup() 
{
    Serial.begin(9600);
    

  //  LinkedVar array[2] = {LinkedVar(&value, LinkedVar::INT), LinkedVar(&fvalue, LinkedVar::INT)};
   // Serial.println(getFormatedString("Bonjour # avez vous recu # euros ?", array, 2));
   
    int mac_values[6] = {255,1,2,3,4,5};
    
    HtmlPage page("Page 1");
   
    HtmlMacField mac;
    
    mac.linkVars(LinkedVar::linkArray(mac_values, 6), 6);
    
    
    Serial.println(mac.getHtml());
    
  
}


void loop()
{
  
  
}
