#include "CashCode.h"

const uint8_t * CashCode_RX = 4;
const uint8_t * CashCode_TX = 5;

CashCode CashCode(9600);

void setup () 
{    
    Serial.begin(9600);
    if (!CashCode.init()) Serial.println("ERROR INIT CASHCODE");
}

void loop() 
{
    if(int res = CashCode.poll()) Serial.println(res), delay(500);
}
