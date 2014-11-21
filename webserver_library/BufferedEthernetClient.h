#ifndef BUFFERED_ETHERNET_CLIENT_HEADER
#define BUFFERED_ETHERNET_CLIENT_HEADER

#include "Arduino.h"
#include <Ethernet.h>

#define BUFFER_SIZE 64

// Version bufferisée d'EthernetClient.
class BufferedEthernetClient
{
    public:
        BufferedEthernetClient(EthernetClient& client): 
            _client(client), 
            _counter(0)
        {
        }
        
        void print(char c)
        {
            _buffer[_counter++] = c;
            if (_counter >= (BUFFER_SIZE-1))
                flush();
        }
        
        void print(char str[])
        {
            char* p = str;
            while(true)
            {
                if (*p == '\0')
                    break;
                print(*p);
                p++;
            }
        }
        
        void print(String str)
        {
            for (int i=0; i<str.length(); i++)
            {
                print(str[i]);
            }
        }
        
        void printP(PROGMEM prog_char str[])
        {
            char c;
            while((c = pgm_read_byte(str++)))
                print(c);
        }
        
        void write(const char a[], int l)
        {
            for (int i=0; i<l; i++)
            {
                print(a[i]);
            }
        }
        
        void println(String str)
        {
            for (int i=0; i<str.length(); i++)
            {
               print(str[i]);
            }
            _buffer[_counter++] = '\n';    
        }
        
        void flush() 
        {
            _client.write((const uint8_t*)_buffer, _counter);
            _counter = 0;     
        }
   
  
    private:
        EthernetClient& _client;
        char _buffer[BUFFER_SIZE];
        int _counter;    
};

#endif // BUFFERED_ETHERNET_CLIENT_HEADER
