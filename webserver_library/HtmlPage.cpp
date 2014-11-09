#include "Arduino.h"
#include "HtmlPage.h"

// Entête HTML des pages
PROGMEM prog_char html_header[] = "HTTP/1.0 200 OK\nServer: arduino\nCache-Control: no-store, no-cache, must-revalidate\nPragma: no-cache\nConnection: close\nContent-Type: text/html\n";
PROGMEM prog_char css[] = ""
"<html>"
  "<body onload=\"onLoadFinished()\">"
    "<center>" 
      "<head>"
        "<style media='screen'type='text/css'>"
          "table{border-collapse: collapse;}"
          "table,th,td{border: 1px solid black;}"
          "td{padding: 8px;}" 
          "#container{margin:0 auto;width:800;background:#fff; border:1px outset black;}"
          "#header{background:#fff;padding:20px}"
          "#header h1{margin:0}"
          "#navigation{float:left;width:800;background:#333}"
          "#navigation ul{margin:0;padding:0}"
          "#navigation ul li{list-style-type:none;display:inline}"
          "#navigation li a{display:block;float:left;padding:5px 10px;color:#fff;text-decoration:none;border-right:1px solid#fff}"
          "#navigation li a:hover{background:#383}"
          "#content{clear:left;padding:20px}"
          "#content h2{color:#000;font-size:160%;margin:0 0.5em}"
          "#footer{background:#ccc;text-align:center;padding:20px;height:1%}"
        "</style>";
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
PROGMEM prog_char header[] = 
        "<div id='header'>"
          "<img alt='' src='data:image/jpeg;base64,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' />"
          "<h1 style='margin-bottom:0;'>ArtNet To DMX512</h1>"
        "</div>";
PROGMEM prog_char menu[] = 
        "<div id='navigation'>"
          "<ul>"
            "<li> <a href='0'>Home</a></li>"
            "<li> <a href='1'>Configure</a></li>"
            "<li> <a href='2'>Test</a></li>"
          "</ul>"
        "</div>";
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


typedef enum {HTML_HEADER, CSS, JAVASCRIPT, HEADER, MENU, CONTENT_TOP, CONTENT_BOTTOM, FOOTER,  IP_FIELD}html_index;


PROGMEM const char *html_content[] = {   
  html_header, css, javascript, header, 
  menu, content_top, content_bottom, footer
};


HtmlPage::HtmlPage(String pageName): _pageName(pageName)
{
  
  
}

void HtmlPage::sendHttpResponse(EthernetClient *client) {
  char b[200];
  strcpy_P(b, (char*)pgm_read_word(&(html_content[HTML_HEADER]))); 
  client->println(b);
  
}

void HtmlPage::beginPage(EthernetClient *client) {
  sendHttpResponse(client);
  sendStr(client,(char*)pgm_read_word(&(html_content[CSS])));
  sendStr(client,(char*)pgm_read_word(&(html_content[JAVASCRIPT])));
  sendStr(client,(char*)pgm_read_word(&(html_content[HEADER])));
  sendStr(client,(char*)pgm_read_word(&(html_content[MENU])));
  sendStr(client,(char*)pgm_read_word(&(html_content[CONTENT_TOP])));
}

void HtmlPage::endPage(EthernetClient *client) {
  sendStr(client,(char*)pgm_read_word(&(html_content[CONTENT_BOTTOM])));
  sendStr(client,(char*)pgm_read_word(&(html_content[FOOTER])));
}


// Envoyer une chaine de caractêre au client sans limite de longueur
void HtmlPage::sendStr(EthernetClient *client, PROGMEM const char *str) {
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



