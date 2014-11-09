#include "HtmlPage.h"
#include "HtmlMacField.h"
#include "LinkedVar.h"
#include "WebServer.h"
#include "HtmlDiv.h"

#include <Ethernet.h>
#include <SPI.h>

#include "MemoryFree.h"

WebServer server;


byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };
IPAddress ip(192,168,2,42);

void setup() 
{
    Serial.begin(9600);
    
    
    HtmlMacField *macField = new HtmlMacField();
    macField->linkVars(LinkedVar::linkArray(mac, 6), 6);
    HtmlDiv *div = new HtmlDiv(macField);
    
    
    HtmlPage *page = new HtmlPage("Page 1", div);
    server.add(page);
    
    Serial.println(page->getHtml());
    
    Serial.print("RAM libre   : "); Serial.println(freeMemory());
    
    Ethernet.begin(mac, ip);
    server.begin();
    
}



void loop()
{
    server.handle();
  
}
