/*
  Copyright (c) 2013 Arduino LLC. All right reserved.

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
  Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public
  License along with this library; if not, write to the Free Software
  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110-1301 USA
*/

#ifndef CCNET_H_
#define CCNET_H_

#include <avr/pgmspace.h>
#include "Arduino.h"
#include <SoftwareSerial.h>

class CashCode
{
    public:
    
        CashCode::CashCode(const int * baundrate);

    public:
    
        bool init(void);
        bool reset(void);
        bool start(void);
        unsigned int poll(void);
        
    private:
    
        unsigned int ready(String str); 
        void send(const byte * pData, int size);
};

#endif /* CCNET_H_ */
