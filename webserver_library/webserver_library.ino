#include <Ethernet.h>
#include <SPI.h>
#include "MemoryFree.h"
#include "WebServer.h"


extern PROGMEM prog_char header[];
extern PROGMEM prog_char css[];
PROGMEM const char *code[] = {   
    css, header
};

WebServer server;
byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };
IPAddress ip(192,168,2,42);

bool globalBool = false;
bool lastState = globalBool;

void setup() 
{
    Serial.begin(9600);

    // Page 1 :
    HtmlCheckBox *checkBox = new HtmlCheckBox();                        // Création d'une checkbox.
    checkBox->linkVar(new LinkedVar(&globalBool));                      // Relier un boolean à la checkbox.
    JavascriptOnChange *javascript = new JavascriptOnChange(checkBox);  // Faire changer la valeur du boolean sur l'evenement 'OnChange'.
    HtmlDiv *div = new HtmlDiv(checkBox);                               // Ajouter le tout dans une div.
    HtmlPage *page1 = new HtmlPage("Page 1", div);                       // Ajouter la div dans la page.
    
    // Page 2 :
    div = new HtmlDiv(new HtmlP("Ceci est un paragraphe de la page 2"));   // Ajouter le tout dans une div.
    HtmlPage *page2 = new HtmlPage("Page 1", div);                       // Ajouter la div dans la page.
    
    // Configuration du serveur :
    server.setCss(code[0]);
    server.setHeader(code[1]);
    server.add(page1);                                                   // Ajouter la page au serveur.
    server.add(page2); 
    server.addMenuItem(new MenuItem("Page 1 ", page1));
    server.addMenuItem(new MenuItem("Page 2", page2));


    
    Serial.print("RAM libre   : "); Serial.println(freeMemory());
    Ethernet.begin(mac, ip);
    server.begin();
}

void loop()
{
    server.handle();

    if (lastState!=globalBool)
    {
        Serial.println(globalBool?"true":"false");
        lastState=globalBool;
    }
}
