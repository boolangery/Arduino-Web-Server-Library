#include "Webserver.h"

PROGMEM prog_char html_header[] = "HTTP/1.0 200 OK\nServer: arduino\nCache-Control: no-store, no-cache, must-revalidate\nPragma: no-cache\nConnection: close\nContent-Type: text/html\n";
PROGMEM prog_char pageBegin[] =
"<html>"
  "<body onload=\"onLoadFinished()\">"
    "<center>" 
      "<head>";
PROGMEM prog_char javascript[] = 
        "<script type=\"text/javascript\">"
          "function updateTextInput(id, val){"
            "var xmlhttp=new XMLHttpRequest();"
            "xmlhttp.onreadystatechange=function(){"
              "document.getElementById('rangevalue'+id).value=val;"
            "};"
            "xmlhttp.open('POST','?value'+id+'='+ val +'&t='+Math.random(),true);"
            "xmlhttp.send();"
            "}"
          "function updateDhcp(id,val){"
            "var xmlhttp=new XMLHttpRequest();"
            "xmlhttp.open('POST','?'+id+'='+val+'&t='+Math.random(),true);"
            "xmlhttp.send();"
            // desactiver les champs ips
            "document.getElementById('ip0').disabled = val;"
            "document.getElementById('ip1').disabled = val;"
            "document.getElementById('ip2').disabled = val;"
            "document.getElementById('ip3').disabled = val;"
            "document.getElementById('subnet0').disabled = val;"
            "document.getElementById('subnet1').disabled = val;"
            "document.getElementById('subnet2').disabled = val;"
            "document.getElementById('subnet3').disabled = val;"
            "document.getElementById('gateway0').disabled = val;"
            "document.getElementById('gateway1').disabled = val;"
            "document.getElementById('gateway2').disabled = val;"
            "document.getElementById('gateway3').disabled = val;"
          "}"
          "function updateIp() {"
            // envoie l'ip, le subnet, la gateway au serveur
	    // les id doivent etre : ip, subnet, gateway
            "var ip0 = document.getElementById('ip0').value;"
	    "var ip1 = document.getElementById('ip1').value;"
	    "var ip2 = document.getElementById('ip2').value;"
	    "var ip3 = document.getElementById('ip3').value;"
	    "var subnet0 = document.getElementById('subnet0').value;"
	    "var subnet1 = document.getElementById('subnet1').value;"
	    "var subnet2 = document.getElementById('subnet2').value;"
	    "var subnet3 = document.getElementById('subnet3').value;"
	    "var gateway0 = document.getElementById('gateway0').value;"
	    "var gateway1 = document.getElementById('gateway1').value;"
	    "var gateway2 = document.getElementById('gateway2').value;"
	    "var gateway3 = document.getElementById('gateway3').value;"
	    "var xmlhttp = new XMLHttpRequest();"
	    "xmlhttp.open('POST','?' + 'ip0='+ip0+'&'+'ip1='+ip1+'&'+'ip2='+ip2+'&'+'ip3='+ip3+'&'+"
				       "'subnet0='+subnet0+'&'+'subnet1='+subnet1+'&'+'subnet2='+subnet2+'&'+'subnet3='+subnet3+'&'+"
				       "'gateway0='+gateway0+'&'+'gateway1='+gateway1+'&'+'gateway2='+gateway2+'&'+'gateway3='+gateway3+'&'+"
				       "'&t=' + Math.random(),true);"
	    "xmlhttp.send();"
            // rediriger vers la nouvelle page
            "setTimeout(function() {"
              "window.alert('Le serveur va red\351marrer, vous allez \352tre redirig\351 automatiquement vers '+ ip0+'.'+ip1+'.'+ip2+'.'+ip3);"
              "window.location.replace('http://'+ip0+'.'+ip1+'.'+ip2+'.'+ip3);"
            "},600);"
	  "}"
        "function onLoadFinished() {"
          "var elem = document.getElementById('dhcp');"
          "if (elem == null) return;"
          "val = document.getElementById('dhcp').checked;"
          "document.getElementById('ip0').disabled = val;"
          "document.getElementById('ip1').disabled = val;"
          "document.getElementById('ip2').disabled = val;"
          "document.getElementById('ip3').disabled = val;"
          "document.getElementById('subnet0').disabled = val;"
          "document.getElementById('subnet1').disabled = val;"
          "document.getElementById('subnet2').disabled = val;"
          "document.getElementById('subnet3').disabled = val;"
          "document.getElementById('gateway0').disabled = val;"
          "document.getElementById('gateway1').disabled = val;"
          "document.getElementById('gateway2').disabled = val;"
          "document.getElementById('gateway3').disabled = val;"
        "}"
        "function updateNames() {"
          "var shortname = document.getElementById('shortname').value;"
          "var longname = document.getElementById('longname').value;"
          "var xmlhttp=new XMLHttpRequest();"
          "xmlhttp.open('POST','?shortname=' + shortname + '&longname=' + longname + '&t='+Math.random(),true);"
          "xmlhttp.send();"
        "}"
        "function updateField(id,val){"
            "var xmlhttp=new XMLHttpRequest();"
            "xmlhttp.open('POST','?'+id+'='+val+'&t='+Math.random(),true);"
            "xmlhttp.send();"
        "}"
        "</script>"
        "</head>"
        "<div id='container'>";
        
PROGMEM prog_char header_begin[] = 
"<div id='header'>  ";
PROGMEM prog_char header_end[] = 
"</div> ";
PROGMEM prog_char content_top[] = "<div id='content' align='left'>";
PROGMEM prog_char content_bottom[] = "</div>";
PROGMEM prog_char footer_begin[] = 
        "<div id='footer'>"  ;  
PROGMEM prog_char footer_end[] = 
        "</div>"
      "</div>"
    "</center>"
  "</body>"
"</html>";

typedef enum {HTML_HEADER, PAGE_BEGIN, JAVASCRIPT, HEADER_BEGIN, HEADER_END, CONTENT_TOP, CONTENT_BOTTOM, FOOTER_BEGIN, FOOTER_END}html_index;


PROGMEM const char *html_content[] = {   
  html_header, pageBegin, javascript, header_begin, header_end,
  content_top, content_bottom, footer_begin, footer_end
};

//*************************************************************************************************
// Constructeur
//*************************************************************************************************
WebServer::WebServer(): EthernetServer(80), _client(NULL), _serial(NULL), _header(NULL), _css(NULL), _footer(NULL), _counter(0)
{

}

//*************************************************************************************************
// Ajouter une page au serveur.
//*************************************************************************************************
void WebServer::add(HtmlPage *page)
{
    page->setWebServerId(_htmlPages.size()); // On enregistre dans la page l'indice de sa position dans le web serveur.
    _htmlPages.push_back(page);
}

//*************************************************************************************************
// Envoyer la page au client.
//*************************************************************************************************
void WebServer::render(BufferedEthernetClient& client, int page)
{
    beginPage(&client);
    if (_htmlPages.size() == 0)
        client.println("Aucunne pages à afficher");
    else
        _htmlPages[page]->renderHtml(&client);
        //client->println(_htmlPages[page]->getHtml());
    endPage(&client);
    client.flush();
}


//*************************************************************************************************
// Gestion du serveur.
//*************************************************************************************************
#include "MemoryFree.h"
void WebServer::handle()
{    
    _client = available();
    //String HTTP_req;
    if (_client)
    {
        BufferedEthernetClient bufferedClient(_client);
        int pageNumber = -1;
        MethodType method = readMethod();
        
    #if WEB_SERVER_DEBUGGING < WEB_SERVER_DEBUGGING_INFO
        Serial.print("method = ");
        if (method==GET)          Serial.println("GET");  
        else if (method==POST)    Serial.println("POST"); 
        else if (method==INVALID) Serial.println("INVALID"); 
    #endif
        
        if (method==GET)
        {
            pageNumber = readUrlPageNumber();
            
                
        #if WEB_SERVER_DEBUGGING < WEB_SERVER_DEBUGGING_INFO
            Serial.println(freeMemory());
            Serial.print("pageNumber = ");
            Serial.println(pageNumber);  
        #endif
        
            int ret=0;
            int k=0;
            char varName[PARSE_VAR_MAX_NAME_LENGTH], varValue[PARSE_VAR_MAX_VALUE_LENGTH];
            while (ret != -1)
            {
                ret = readNextVar(varName, PARSE_VAR_MAX_NAME_LENGTH, varValue, PARSE_VAR_MAX_VALUE_LENGTH);
                if (ret == -1)
                    break;
                k++;
                // Propagation des valeurs aux variables liées:
                _htmlPages[pageNumber]->propagateVars(varName, varValue);    

            #if WEB_SERVER_DEBUGGING < WEB_SERVER_DEBUGGING_INFO
                Serial.print("varName = ");
                Serial.println(varName); 
                Serial.print("varValue = ");
                Serial.println(varValue);  
            #endif
            }
            
            if (pageNumber != -1)
                render(bufferedClient, pageNumber); 
            
            if (k>0)
                _htmlPages[pageNumber]->callback();
        
        }
        else if (method==POST)
        {
            // Lecture des variables POST:
            int ret=0;
            char varName[PARSE_VAR_MAX_NAME_LENGTH], varValue[PARSE_VAR_MAX_VALUE_LENGTH];
            pageNumber = readUrlPageNumber();
            if (pageNumber != -1)
                render(bufferedClient, pageNumber); 
            
         #if WEB_SERVER_DEBUGGING < WEB_SERVER_DEBUGGING_INFO
            Serial.print("pageNumber = ");
            Serial.println(pageNumber);  
        #endif
            
            while (ret != -1)
            {
                ret = readNextVar(varName, PARSE_VAR_MAX_NAME_LENGTH, varValue, PARSE_VAR_MAX_VALUE_LENGTH);
                if (ret == -1)
                    break;
                
                // Propagation des valeurs aux variables liées:
                _htmlPages[pageNumber]->propagateVars(varName, varValue);    
                
            #if WEB_SERVER_DEBUGGING < WEB_SERVER_DEBUGGING_INFO
                Serial.print("varName = ");
                Serial.println(varName); 
                Serial.print("varValue = ");
                Serial.println(varValue);  
            #endif
            }
        }
        else if (method==INVALID)
        {
           
        }
        
        
        /*
        bool currentLineIsBlank = false;
        while (_client.connected())
        {
            char c = read();
            HTTP_req += c;
            if (c == '\n' && currentLineIsBlank) {
                Serial.println(HTTP_req);
                break;
            }
            if (c == '\n')
                currentLineIsBlank = true;
            else if (c != '\r')
                currentLineIsBlank = false;
        }*/
        
        delay(1);
        _client.flush();
        _client.stop();
    }
}


//*************************************************************************************************
// Ajouter un menu.
//*************************************************************************************************
void WebServer::addMenuItem(MenuItem* menu)
{
    _menus.push_back(menu);
}

//*************************************************************************************************
//
//*************************************************************************************************
void WebServer::sendHttpResponse(BufferedEthernetClient *client) {
  char b[200];
  strcpy_P(b, (char*)pgm_read_word(&(html_content[HTML_HEADER]))); 
  client->println(b);
}

//*************************************************************************************************
//
//*************************************************************************************************
void WebServer::beginPage(BufferedEthernetClient *client) {
  sendHttpResponse(client);
  sendStr(client,(char*)pgm_read_word(&(html_content[PAGE_BEGIN])));
  sendStr(client, _css);
  sendStr(client,(char*)pgm_read_word(&(html_content[JAVASCRIPT])));
  sendStr(client,(char*)pgm_read_word(&(html_content[HEADER_BEGIN])));
  sendStr(client, _header);
  sendStr(client,(char*)pgm_read_word(&(html_content[HEADER_END])));
  sendMenu(client);
  sendStr(client,(char*)pgm_read_word(&(html_content[CONTENT_TOP])));
}

//*************************************************************************************************
//
//*************************************************************************************************
void WebServer::endPage(BufferedEthernetClient *client) {
  sendStr(client,(char*)pgm_read_word(&(html_content[CONTENT_BOTTOM])));
  sendStr(client,(char*)pgm_read_word(&(html_content[FOOTER_BEGIN])));
  sendStr(client, _footer);
  sendStr(client,(char*)pgm_read_word(&(html_content[FOOTER_END])));
}

//*************************************************************************************************
//
//*************************************************************************************************
void WebServer::sendMenu(BufferedEthernetClient *client)
{
    client->print("<div id='navigation'><ul>");
    for (int i=0 ; i<_menus.size() ; i++) {
        client->print("<li> <a href='");
        client->print(String(_menus[i]->getPage()->getWebServerId()));
        client->print("'>");
        client->print(_menus[i]->getName());
        client->print("</a></li>");   
    }
    client->print("</ul></div>");
}

//*************************************************************************************************
//
//*************************************************************************************************
// Envoyer une chaine de caractêre au client sans limite de longueur
void WebServer::sendStr(BufferedEthernetClient *client, PROGMEM const char *str) {
    if (str==NULL) return;
    char b[64];
    int remaining = strlen_P(str);
    const char * offsetPtr = str;
    int nSize = sizeof(b);

    while (remaining > 0) {
        if (nSize > remaining)
            nSize = remaining; 
        memcpy_P(b, offsetPtr, nSize);
        client->write((const char *)b, nSize);
        //bufferedClientOutputBytes(client, (const char *)b, nSize);
        remaining -= nSize;
        offsetPtr += nSize;
    }
}

int WebServer::read()
{
    if (!_client)
        return -1;
    if (_client.connected())
        return _client.read(); 
}

int WebServer::readUntil(char until[], int n, char buffer[], int length)
{
    for (int i=0; i<length; i++)
    {
        char c = read();
        if (c == -1)
            return -1;
        for (int j=0;j<n;j++)
            if (c == until[j])
                return i;
        if (c == '\n')
            return -1;
        buffer[i] = c;
    }
    // Si on arrive ici c'est qu'on n'a pas atteint le caractère de fin.
    return -1;
}


int WebServer::readUntil(char until, char buffer[], int length)
{
    readUntil(&until, 1, buffer, length);
}

int WebServer::skipUntil(char until)
{
    while(true)
    {
        char c = read();
        if (c == -1)
            return -1;
        if (c == until)
            return 0;
        if (c == '\n')
            return -1;
    }
    // Si on arrive ici c'est qu'on n'a pas atteint le caractère de fin.
    return -1;
}

MethodType WebServer::readMethod()
{
    // Taille max du nom de la méthode = CONNECT
    char method[8] = {0};    
    char until[1] = {' '};
    if (readUntil(until, 1, method, 8) == -1)
        return INVALID;
    if (strcmp(method, "GET") == 0)
        return GET;
    if (strcmp(method, "POST") ==0)
        return POST;
    return INVALID;
}

int WebServer::readUrlPageNumber()
{
    // Normalement l'url est simplement /n
    // avec n le numéro de la page.
    // Si l'url est plus longue c'est qu'on demande la favicon.
    char url[2] = {0}; 
    char until[2] = {' ', '?'};
    // On laisse passer le '/' de l'url:
    if (read() != '/')
        return -1;
    if (readUntil(until, 2, url, 2) == -1)
        return -1;
    return atoi(url);
}

int WebServer::readNextVar(char name[], int nameLength, char value[], int valueLength)
{   
    memset(name, 0, nameLength);
    memset(value, 0, valueLength);
    char until[3] = {'&', '=', ' '};
    // Lecture du nom de la variable:
    if (readUntil(until, 3, name, nameLength) == -1)
        return -1;
    // Lecture de la valeur:
    if (readUntil(until, 3, value, valueLength) == -1)
        return -1;
    return 0;
}

