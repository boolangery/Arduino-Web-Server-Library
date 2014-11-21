#ifndef WEB_SERVER_HEADER
#define WEB_SERVER_HEADER

#include "Arduino.h"
#include <Ethernet.h>
#include "Vector.h"

#include "MenuItem.h"
#include "HtmlP.h"
#include "HtmlDiv.h"
#include "HtmlArray.h"
#include "JavascriptOnChange.h"
#include "HtmlCheckBox.h"
#include "HtmlPage.h"
#include "HtmlMacField.h"
#include "LinkedVar.h"
#include "BufferedEthernetClient.h"
#include "HtmlInputNumber.h"
#include "HtmlFormPost.h"
#include "HtmlLabel.h"

// Macro pour stocker une chaine de caractère en memoire SRAM
#define P(str)   PROGMEM prog_char str[] 
//#define P(str) PROGMEM const char str[]

// Macro pour compter le nombre d'element d'un tableau.
#define SIZE(array) (sizeof(array) / sizeof(*array))

//#define ToCharArr(pstr) (char*)pgm_read_word(&(html_content[PAGE_BEGIN]))

// Enumeration pour le type de méthode.
typedef enum MethodType {GET, POST, INVALID} MethodType; 

#define PARSE_VAR_MAX_VALUE_LENGTH 32
#define PARSE_VAR_MAX_NAME_LENGTH 32

// Niveau pour les messages d'erreur et de debugging:
#define WEB_SERVER_DEBUGGING_INFO        1
#define WEB_SERVER_DEBUGGING_MSG_ERROR   2
#define WEB_SERVER_DEBUGGING             0

class WebServer: public EthernetServer
{
    public:
        WebServer();
        
        // Définir le code Html du header des pages web.
        void setHeader(PROGMEM const char *p) {_header=p;}
        
        // Définir le code Html du footer des pages web.
        void setFooter(PROGMEM const char *p) {_footer=p;}
        
        // Définir le code de mise en forme des pages web.
        void setCss(PROGMEM const char *p) {_css=p;}
        
        // Ajouter une page Html au serveur web.
        void add(HtmlPage *page);
        
        // Gérer le web serveur. Fonction à appeller dans la boucle principale.
        void handle();
        
        // Ajouter un item de menu.
        void addMenuItem(MenuItem* menu);
        
    private:
        // Envoyer les pages Html au client.
        // page: L'index de la page à envoyer, il est automatiquement 
        // calculé lorsque l'utilisateur ajoute des menus.
        void render(BufferedEthernetClient& client, int page);
        
        // Envoyer la reponse Http au client.
        void sendHttpResponse(BufferedEthernetClient *client);
        
        // Envoyer le debut de la page au client.
        // S'arrete au debut du contenu de la page.
        void beginPage(BufferedEthernetClient *client);
        
        // Envoyer la fin de la page au client.
        void endPage(BufferedEthernetClient *client);
        
        // Envoyer une chaine de caractère stockée en SRAM au client.
        void sendStr(BufferedEthernetClient *client, PROGMEM const char *str);
        
        // Envoyer le code HTML des menus au client.
        void sendMenu(BufferedEthernetClient *client);
 
        
        // Lire un caractère de la requete du client connecté.
        // Return : -1 si le client n'est pas connecté ou si il 
        // n'y à plus de caractère à lire.
        int read();
        
        // Lire des caractères de la requette jusqu'a atteindre le caractère 'c'.
        // until: Les caractères d'arret.
        // n: le nombre de caractère
        // buffer: Où les caracteres sont stockées.
        // length: Nombre de caractère maximum à lire.
        // return: -1 si le caractère 'c' n'a pas pu être atteint.
        int readUntil(char until[], int n, char buffer[], int length);
        int readUntil(char until, char buffer[], int length);
        int skipUntil(char until);
        
        // Lire le type de méthode de la requette.
        // return: Le type de méthode.
        MethodType readMethod();
        
        // Lire le numero de la page à afficher d'une requette GET
        // return: Le numero de la page à afficher.
        // -1 si c'est une demande de favicon
        int readUrlPageNumber();
        
        // Lire la prochaine variable d'une requette POST.
        // Le flux doit être placé sur le premier caractère du nom de la variable.
        // return: -1 si pas de variable, ou si les longueurs indiquée sont depassées.
        int readNextVar(char name[], int nameLength, char value[], int valueLength);
        
    private:
        EthernetClient _client;
        Vector<HtmlPage*> _htmlPages;
        HardwareSerial *_serial;
        //PROGMEM const char *_header, *_css, *_footer;
        PROGMEM const char *_header, *_css, *_footer;
        Vector<MenuItem*> _menus;
        
        int _counter;
        unsigned char _readingBufferIndex;
        
};

#endif
