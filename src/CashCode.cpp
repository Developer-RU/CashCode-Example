#include <avr/pgmspace.h>
#include "Arduino.h"
#include <SoftwareSerial.h>
#include "CashCode.h"


const byte RESET[] = {0x02, 0x03, 0x06, 0x30, 0x41, 0xB3},
           POLL[]  = {0x02, 0x03, 0x06, 0x33, 0xDA, 0x81},
           NAK[]   = {0x02, 0x03, 0x06, 0x00, 0xC2, 0x82},
           START[] = {0x02, 0x03, 0x0C, 0x34, 0x00, 0x00, 0xFC, 0x00, 0x00, 0x00, 0x08, 0xEC};


extern const uint8_t * CashCode_RX;
extern const uint8_t * CashCode_TX;

int CashCode_BaundRate;

SoftwareSerial SerialCashCode((uint8_t *) CashCode_RX, (uint8_t *) CashCode_TX);

CashCode::CashCode(const int * baundrate) { CashCode_BaundRate = (int *) baundrate; }

bool CashCode::init() 
{   
    SerialCashCode.begin((int *) CashCode_BaundRate);

    if(!reset()) return false;   
    if(start()) return true;  
    return false;
}

bool CashCode::reset() 
{       
    for(uint8_t i = 0; i < 3; ++i, send ( RESET, sizeof(RESET))) {
        delay(10);
        if (SerialCashCode.available()) {    
            String response = "";
            while(SerialCashCode.available()) { response += SerialCashCode.read(), HEX; response += " "; }
            response.trim();
            if(response == "2 3 6 0 194 130") return true;
        }
    }
    return false;
}

bool CashCode::start()
{        
    send ( START, sizeof(START));
    return true;
}

unsigned int CashCode::poll()
{
    send ( POLL, sizeof(POLL));
    delay(10);
    if (SerialCashCode.available()) {
        String response = "";
        while(SerialCashCode.available()) { response += SerialCashCode.read(), HEX; response += " "; }
        response.trim();
        return ready(response);
    }
    return 0;    
}

unsigned int CashCode::ready(String str)
{
    if(str == "2 3 7 129 3 207 24")  { send ( NAK, sizeof(NAK)); return 50; }
    else if(str == "2 3 7 129 4 112 108") { send ( NAK, sizeof(NAK)); return 100; }
    else if(str == "2 3 7 129 5 249 125") { send ( NAK, sizeof(NAK)); return 500; }
    else if(str == "2 3 7 129 6 98 79")   { send ( NAK, sizeof(NAK)); return 1000; }
    else if(str == "2 3 7 129 7 235 94")  { send ( NAK, sizeof(NAK)); return 5000; }
    else return 0;
}

void CashCode::send(const byte * pData, int size)
{
    byte * pData2 = (const byte *) pData;    
    for (; size > 0; size--) SerialCashCode.write( ( byte ) * pData2++ );
}
