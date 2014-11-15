#include "Webserver.h"

// Entête HTML des pages
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
/*
PROGMEM prog_char menu[] = 
        "<div id='navigation'>"
          "<ul>"
            "<li> <a href='0'>Home</a></li>"
            "<li> <a href='1'>Configure</a></li>"
            "<li> <a href='2'>Test</a></li>"
          "</ul>"
        "</div>";*/
PROGMEM prog_char content_top[] = "<div id='content' align='left'>";
PROGMEM prog_char content_bottom[] = "</div>";
PROGMEM prog_char footer[] = 
        "<div id='footer'>"
          "Adrem Solutions"
        "</div>"
      "</div>"
    "</center>"
  "</body>"
"</html>";


typedef enum {HTML_HEADER, PAGE_BEGIN, JAVASCRIPT, HEADER_BEGIN, HEADER_END, CONTENT_TOP, CONTENT_BOTTOM, FOOTER,  IP_FIELD}html_index;


PROGMEM const char *html_content[] = {   
  html_header, pageBegin, javascript, header_begin, header_end,
  content_top, content_bottom, footer
};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
WebServer::WebServer(): EthernetServer(80), _serial(NULL), _header(NULL), _css(NULL)
{
}

void WebServer::add(HtmlPage *page)
{
    page->setWebServerId(_htmlPages.size());    // Indice de la page dans le vector.
    _htmlPages.push_back(page);
}


void WebServer::render(EthernetClient *client, int page)
{
    beginPage(client);
    if (_htmlPages.size() == 0)
        client->println("Aucunne page à afficher");
    else
    {
        client->println(_htmlPages[page]->getHtml());
        
    }
    endPage(client);
}

int WebServer::getPageId(String HTTP_req) {
      String ret = "";
      int maxPos = HTTP_req.indexOf("Host");
      int beginPos = HTTP_req.indexOf("/") + 1;
      while( HTTP_req[beginPos] != ' ') {
        ret += HTTP_req[beginPos];
        beginPos ++;
      }
      if (ret.length() == 0) return 0;
      return ret.toInt();
}


void WebServer::debug_printPage(int i, HardwareSerial *serial)
{
    serial->println(_htmlPages[i]->getHtml());
}

void WebServer::handle()
{
    String HTTP_req;
    EthernetClient client = available();
    if (client) {
        boolean currentLineIsBlank = true;
        while (client.connected()) {
            if (client.available()) {
                char c = client.read();
                HTTP_req += c;
                // if the line is blank we can send http response
                if (c == '\n' && currentLineIsBlank) {
                    if (HTTP_req.indexOf("favicon")>0) {
                        HTTP_req = "";  
                        return;
                    }
                    //processUrlData(HTTP_req, node);
                   // sendPage(&client, node, getPageId(HTTP_req));
                    //Serial.println(HTTP_req);
                    
                    _htmlPages[0]->propagateJavascriptValues(HTTP_req);
                   
                    render(&client, getPageId(HTTP_req)); 
                    HTTP_req = "";  
                    delay(1);
                    client.stop();
                    break;
                }
                if (c == '\n') {
                    // you're starting a new line
                    currentLineIsBlank = true;
                } 
                else if (c != '\r') {
                    // you've gotten a character on the current line
                    currentLineIsBlank = false;
                }
            }
        }
    }  

}

void WebServer::addMenuItem(MenuItem* menu)
{
    _menus.push_back(menu);
}

void WebServer::sendHttpResponse(EthernetClient *client) {
  char b[200];
  strcpy_P(b, (char*)pgm_read_word(&(html_content[HTML_HEADER]))); 
  client->println(b);
  
}

void WebServer::beginPage(EthernetClient *client) {
  sendHttpResponse(client);
  sendStr(client,(char*)pgm_read_word(&(html_content[PAGE_BEGIN])));
  sendStr(client, _css);
  sendStr(client,(char*)pgm_read_word(&(html_content[JAVASCRIPT])));
  sendStr(client,(char*)pgm_read_word(&(html_content[HEADER_BEGIN])));
  sendStr(client, _header);
  sendStr(client,(char*)pgm_read_word(&(html_content[HEADER_END])));
  //sendStr(client,(char*)pgm_read_word(&(html_content[MENU])));
  sendMenu(client);
  sendStr(client,(char*)pgm_read_word(&(html_content[CONTENT_TOP])));
}

void WebServer::endPage(EthernetClient *client) {
  sendStr(client,(char*)pgm_read_word(&(html_content[CONTENT_BOTTOM])));
  sendStr(client,(char*)pgm_read_word(&(html_content[FOOTER])));
}

void WebServer::sendMenu(EthernetClient *client)
{
    client->print("<div id='navigation'><ul>");
    for (int i=0 ; i<_menus.size() ; i++) {
        client->print("<li> <a href='");
        client->print(_menus[i]->getPage()->getWebServerId());
        client->print("'>");
        client->print(_menus[i]->getName());
        client->print("</a></li>");   
    }
    client->print("</ul></div>");
}


// Envoyer une chaine de caractêre au client sans limite de longueur
void WebServer::sendStr(EthernetClient *client, PROGMEM const char *str) {
  if (str==NULL) return;
  char b[200];
  int remaining = strlen_P(str);
  const char * offsetPtr = str;
  int nSize = sizeof(b);

  while (remaining > 0) {
    if (nSize > remaining)
      nSize = remaining;      // Partial buffer left to send
    memcpy_P(b, offsetPtr, nSize);
    client->write((const uint8_t *)b, nSize);

    remaining -= nSize;
    offsetPtr += nSize;
  }
}



