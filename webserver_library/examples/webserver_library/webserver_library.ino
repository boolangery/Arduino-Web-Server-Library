#include <Ethernet.h>
#include <SPI.h>
#include "MemoryFree.h"
#include "WebServer.h"

extern P(css);
extern P(header);
extern P(footer);

//extern prog_uchar* css;

/*
PROGMEM const char *code[] = {   
    css, header, footer
};*/

WebServer server;
byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };
IPAddress ip(192,168,2,42);
int ipAdress[] = {192,168,2,42};
int gateway[] = {255,255,255,0};

bool globalBool = false;
bool lastState = globalBool;
int globalInt = 42;


void page3Callback()
{
    Serial.println("FORM SUBMITTED");
}


P(label_ip) = "Ip Address : ";
P(label_gateway) = "Gateway : ";
P(label_br) = "<br>";

void setup() 
{
    Serial.begin(9600);

    // Page 1 :
    HtmlCheckBox *checkBox = new HtmlCheckBox();                        // Création d'une checkbox.
    checkBox->linkVar(new LinkedVar(&globalBool));                      // Relier un boolean à la checkbox.
    new JavascriptOnChange(checkBox);                                   // Faire changer la valeur du boolean sur l'evenement 'OnChange'.
    HtmlDiv *div = new HtmlDiv(checkBox);                               // Ajouter le tout dans une div.
    HtmlPage *page1 = new HtmlPage("Page 1", div);                      // Ajouter la div dans la page.
    
    // Page 2 :
    div = new HtmlDiv(new HtmlP("Ceci est un paragraphe de la page 2")); // Ajouter le tout dans une div.
    HtmlPage *page2 = new HtmlPage("Page 1", div);                       // Ajouter la div dans la page.
    
    // Page 3 :
    HtmlFormPost *form = new HtmlFormPost();
    form->add(new HtmlLabel(label_ip));
    form->add(new HtmlInputNumber(new LinkedVar(&ipAdress[0])));    
    form->add(new HtmlInputNumber(new LinkedVar(&ipAdress[1])));
    form->add(new HtmlInputNumber(new LinkedVar(&ipAdress[2])));
    form->add(new HtmlInputNumber(new LinkedVar(&ipAdress[3])));
    form->add(new HtmlLabel(label_br));
    
    form->add(new HtmlLabel(label_gateway));
    form->add(new HtmlInputNumber(new LinkedVar(&gateway[0])));    
    form->add(new HtmlInputNumber(new LinkedVar(&gateway[1])));
    form->add(new HtmlInputNumber(new LinkedVar(&gateway[2])));
    form->add(new HtmlInputNumber(new LinkedVar(&gateway[3])));
    form->add(new HtmlLabel(label_br));
    
    HtmlPage *page3 = new HtmlPage("Page 3", form);
    page3->setFormCallback(&page3Callback);
    
    // Configuration du serveur :
    server.setCss(css);
    server.setHeader(header);
    server.setFooter(footer);
    server.add(page1);                                                   // Ajouter la page au serveur.
    server.add(page2); 
    server.add(page3);
    server.addMenuItem(new MenuItem("Page 1 ", page1));
    server.addMenuItem(new MenuItem("Page 2 ", page2));
    server.addMenuItem(new MenuItem("Page 3 ", page3));
 
    Serial.print("RAM libre   : "); Serial.println(freeMemory());
    
    Ethernet.begin(mac, ip);
    server.begin();
}

void loop()
{
    server.handle();
    //Serial.println(globalInt);

    if (lastState!=globalBool)
    {
        Serial.println(globalBool?"true":"false");
        lastState=globalBool;
    }
}
