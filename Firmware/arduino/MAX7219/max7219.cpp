/******************************************************************//**
* @file max7219.cpp
*
* @author Justin Jordan
*
* @version 0.0
*
* Started: 08JAN16
*
* Updated: 
* 
* 24JAN16 - ported to Arduino
*
* @brief Source file for Max7219 class
***********************************************************************
* Copyright (C) 2016 Maxim Integrated Products, Inc., All Rights Reserved.
*
* Permission is hereby granted, free of charge, to any person obtaining a
* copy of this software and associated documentation files (the "Software"),
* to deal in the Software without restriction, including without limitation
* the rights to use, copy, modify, merge, publish, distribute, sublicense,
* and/or sell copies of the Software, and to permit persons to whom the
* Software is furnished to do so, subject to the following conditions:
*
* The above copyright notice and this permission notice shall be included
* in all copies or substantial portions of the Software.
*
* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
* OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
* MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
* IN NO EVENT SHALL MAXIM INTEGRATED BE LIABLE FOR ANY CLAIM, DAMAGES
* OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
* ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
* OTHER DEALINGS IN THE SOFTWARE.
*
* Except as contained in this notice, the name of Maxim Integrated
* Products, Inc. shall not be used except as stated in the Maxim Integrated
* Products, Inc. Branding Policy.
*
* The mere transfer of this software does not imply any licenses
* of trade secrets, proprietary technology, copyrights, patents,
* trademarks, maskwork rights, or any other form of intellectual
* property whatsoever. Maxim Integrated Products, Inc. retains all
* ownership rights.
**********************************************************************/


#include "max7219.h"


//*********************************************************************
Max7219::Max7219()
{
}


//*********************************************************************
void Max7219::begin(uint8_t mosi, uint8_t sclk, uint8_t cs)
{
    _num_devices = 1;
    _mosi = mosi;
    _sclk = sclk;
    _cs = cs;

    pinMode(_mosi, OUTPUT);
    pinMode(_sclk, OUTPUT);
    pinMode(_cs, OUTPUT);
    
    digitalWrite(_cs, HIGH);
    digitalWrite(_mosi, LOW);
    digitalWrite(_sclk, LOW);
}


//*********************************************************************
void Max7219::end()
{
  //?
}


//*********************************************************************
uint8_t Max7219::set_num_devices(uint8_t num_devices)
{
    int32_t rtn_val = 0xFF;
    
    if(num_devices > 0)
    {
        _num_devices = num_devices;
        rtn_val = _num_devices;
    }
    
    return(rtn_val);
}


//*********************************************************************
void Max7219::set_display_test(void)
{
    uint8_t idx = 0;
    
    digitalWrite(_cs, LOW);
    for(idx = 0; idx < _num_devices; idx++)
    {
      //make sure clock starts low
      digitalWrite(_sclk, LOW);

      shiftOut(_mosi, _sclk, MSBFIRST, MAX7219_DISPLAY_TEST);
      shiftOut(_mosi, _sclk, MSBFIRST, 1);
    }
    digitalWrite(_cs, HIGH); 
}


//*********************************************************************
void Max7219::clear_display_test(void)
{
    uint8_t idx = 0;
    
    digitalWrite(_cs, LOW);
    for(idx = 0; idx < _num_devices; idx++)
    {
      //make sure clock starts low
      digitalWrite(_sclk, LOW);

      shiftOut(_mosi, _sclk, MSBFIRST, MAX7219_DISPLAY_TEST);
      shiftOut(_mosi, _sclk, MSBFIRST, 0);
    }
    digitalWrite(_cs, HIGH);  
}


//*********************************************************************
uint8_t Max7219::init_device(max7219_configuration_t config)
{
    int32_t rtn_val = 0xFF;
    uint8_t idx = 0;
    
    if(config.device_number > _num_devices)
    {
        rtn_val = 1;
    }
    else if(config.device_number == 0)
    {
        //device numbering starts with index 1
        rtn_val = 2;
    }
    else
    {
        //write DECODE_MODE register of device
        digitalWrite(_cs, LOW);
        for(idx = _num_devices; idx > 0; idx--)
        {
            if(config.device_number == idx)
            {
              //make sure clock starts low
              digitalWrite(_sclk, LOW);
        
              shiftOut(_mosi, _sclk, MSBFIRST, MAX7219_DECODE_MODE);
              shiftOut(_mosi, _sclk, MSBFIRST, config.decode_mode);
            }
            else
            {
              //make sure clock starts low
              digitalWrite(_sclk, LOW);
        
              shiftOut(_mosi, _sclk, MSBFIRST, MAX7219_NO_OP);
              shiftOut(_mosi, _sclk, MSBFIRST, 0);
            }
        }
        digitalWrite(_cs, HIGH);
        
        delayMicroseconds(1);
        
        //write INTENSITY register of device
        digitalWrite(_cs, LOW);
        for(idx = _num_devices; idx > 0; idx--)
        {
            if(config.device_number == idx)
            {
              //make sure clock starts low
              digitalWrite(_sclk, LOW);
        
              shiftOut(_mosi, _sclk, MSBFIRST, MAX7219_INTENSITY);
              shiftOut(_mosi, _sclk, MSBFIRST, config.intensity);
            }
            else
            {
              //make sure clock starts low
              digitalWrite(_sclk, LOW);
        
              shiftOut(_mosi, _sclk, MSBFIRST, MAX7219_NO_OP);
              shiftOut(_mosi, _sclk, MSBFIRST, 0);
            }
        }
        digitalWrite(_cs, HIGH); 
        
        delayMicroseconds(1);
        
        //write SCAN_LIMT register of device
        digitalWrite(_cs, LOW); 
        for(idx = _num_devices; idx > 0; idx--)
        {
            if(config.device_number == idx)
            {
              //make sure clock starts low
              digitalWrite(_sclk, LOW);
        
              shiftOut(_mosi, _sclk, MSBFIRST, MAX7219_SCAN_LIMIT);
              shiftOut(_mosi, _sclk, MSBFIRST, config.scan_limit);
            }
            else
            {
              //make sure clock starts low
              digitalWrite(_sclk, LOW);
        
              shiftOut(_mosi, _sclk, MSBFIRST, MAX7219_NO_OP);
              shiftOut(_mosi, _sclk, MSBFIRST, 0);
            }
        }
        digitalWrite(_cs, HIGH);  
        
        delayMicroseconds(1);
        
        rtn_val = 0;
    }
    
    return(rtn_val);
}


//*********************************************************************
void Max7219::init_display(max7219_configuration_t config)
{
    uint8_t idx = 0;
    
    //write DECODE_MODE register of all devices
    digitalWrite(_cs, LOW);  
    for(idx = 0; idx < _num_devices; idx++)
    {
      //make sure clock starts low
      digitalWrite(_sclk, LOW);

      shiftOut(_mosi, _sclk, MSBFIRST, MAX7219_DECODE_MODE);
      shiftOut(_mosi, _sclk, MSBFIRST, config.decode_mode);
    }
    digitalWrite(_cs, HIGH);   
    
    delayMicroseconds(1);
    
    //write INTENSITY register of all devices
    digitalWrite(_cs, LOW);  
    for(idx = 0; idx < _num_devices; idx++)
    {
      //make sure clock starts low
      digitalWrite(_sclk, LOW);

      shiftOut(_mosi, _sclk, MSBFIRST, MAX7219_INTENSITY);
      shiftOut(_mosi, _sclk, MSBFIRST, config.intensity);
    }
    digitalWrite(_cs, HIGH);
    
    delayMicroseconds(1);
    
    //write SCAN_LIMT register of all devices
    digitalWrite(_cs, LOW);   
    for(idx = 0; idx < _num_devices; idx++)
    {
      //make sure clock starts low
      digitalWrite(_sclk, LOW);

      shiftOut(_mosi, _sclk, MSBFIRST, MAX7219_SCAN_LIMIT);
      shiftOut(_mosi, _sclk, MSBFIRST, config.scan_limit);
    }
    digitalWrite(_cs, HIGH);
    
    delayMicroseconds(1);
}


//*********************************************************************
uint8_t Max7219::enable_device(uint8_t device_number)
{
    int32_t rtn_val = 0xFF;
    uint8_t idx = 0;
    
    if(device_number > _num_devices)
    {
        rtn_val = 1;
    }
    else if(device_number == 0)
    {
        //device numbering starts with index 1
        rtn_val = 2;
    }
    else
    {
        digitalWrite(_cs, LOW); 
        for(idx = _num_devices; idx > 0; idx--)
        {
            if(device_number == idx)
            {
              //make sure clock starts low
              digitalWrite(_sclk, LOW);
        
              shiftOut(_mosi, _sclk, MSBFIRST, MAX7219_SHUTDOWN);
              shiftOut(_mosi, _sclk, MSBFIRST, 1);
            }
            else
            {
              //make sure clock starts low
              digitalWrite(_sclk, LOW);
        
              shiftOut(_mosi, _sclk, MSBFIRST, MAX7219_NO_OP);
              shiftOut(_mosi, _sclk, MSBFIRST, 0);
            }
        }
        digitalWrite(_cs, HIGH); 
        
        rtn_val = 0;
    }
    
    return(rtn_val);
}


//*********************************************************************
void Max7219::enable_display(void)
{
    uint8_t idx = 0;
    
    digitalWrite(_cs, LOW); 
    for(idx = 0; idx < _num_devices; idx++)
    {
      //make sure clock starts low
      digitalWrite(_sclk, LOW);

      shiftOut(_mosi, _sclk, MSBFIRST, MAX7219_SHUTDOWN);
      shiftOut(_mosi, _sclk, MSBFIRST, 1);
    }
    digitalWrite(_cs, HIGH); 
}
    

//*********************************************************************    
uint8_t Max7219::disable_device(uint8_t device_number)
{
    int32_t rtn_val = 0xFF;
    uint8_t idx = 0;
    
    if(device_number > _num_devices)
    {
        rtn_val = 1;
    }
    else if(device_number == 0)
    {
        //device numbering starts with index 1
        rtn_val = 2;
    }
    else
    {
        digitalWrite(_cs, LOW); 
        for(idx = _num_devices; idx > 0; idx--)
        {
            if(device_number == idx)
            {
              //make sure clock starts low
              digitalWrite(_sclk, LOW);
        
              shiftOut(_mosi, _sclk, MSBFIRST, MAX7219_SHUTDOWN);
              shiftOut(_mosi, _sclk, MSBFIRST, 0);
            }
            else
            {
              //make sure clock starts low
              digitalWrite(_sclk, LOW);
        
              shiftOut(_mosi, _sclk, MSBFIRST, MAX7219_NO_OP);
              shiftOut(_mosi, _sclk, MSBFIRST, 0);
            }
        }
        digitalWrite(_cs, HIGH);
        
        rtn_val = 0;
    }
    
    return(rtn_val);
}


//*********************************************************************    
void Max7219::disable_display(void)
{
    uint8_t idx = 0;
    
    digitalWrite(_cs, LOW); 
    for(idx = 0; idx < _num_devices; idx++)
    {
      //make sure clock starts low
      digitalWrite(_sclk, LOW);

      shiftOut(_mosi, _sclk, MSBFIRST, MAX7219_SHUTDOWN);
      shiftOut(_mosi, _sclk, MSBFIRST, 0);
    }
    digitalWrite(_cs, HIGH);  
}



//********************************************************************* 
uint8_t Max7219::write_digit(uint8_t device_number, uint8_t digit, uint8_t data)
{
    int32_t rtn_val = 0xFF;
    uint8_t idx = 0;
    
    if(digit > MAX7219_DIGIT_7)
    {
        rtn_val = 3;
    }
    else if(digit < MAX7219_DIGIT_0)
    {
        rtn_val = 4;
    }
    else
    {
        if(device_number > _num_devices)
        {
            rtn_val = 1;
        }
        else if(device_number == 0)
        {
            rtn_val = 2;
        }
        else
        {
            digitalWrite(_cs, LOW);
            for(idx = _num_devices; idx > 0; idx--)
            {
                if(idx == device_number)
                {
                  //make sure clock starts low
                  digitalWrite(_sclk, LOW);
            
                  shiftOut(_mosi, _sclk, MSBFIRST, digit);
                  shiftOut(_mosi, _sclk, MSBFIRST, data);
                }
                else
                {
                  //make sure clock starts low
                  digitalWrite(_sclk, LOW);
            
                  shiftOut(_mosi, _sclk, MSBFIRST, MAX7219_NO_OP);
                  shiftOut(_mosi, _sclk, MSBFIRST, 0);
                }
            }
            digitalWrite(_cs, HIGH);
            
            rtn_val = 0;
        }
    }
    
    return(rtn_val);
}
    

//*********************************************************************     
uint8_t Max7219::clear_digit(uint8_t device_number, uint8_t digit)
{
    int32_t rtn_val = 0xFF;
    uint8_t idx = 0;
    
    if(digit > MAX7219_DIGIT_7)
    {
        rtn_val = 3;
    }
    else if(digit < MAX7219_DIGIT_0)
    {
        rtn_val = 4;
    }
    else
    {
        if(device_number > _num_devices)
        {
            rtn_val = 1;
        }
        else if(device_number == 0)
        {
            rtn_val = 2;
        }
        else
        {
            digitalWrite(_cs, LOW);
            for(idx = _num_devices; idx > 0; idx--)
            {
                if(idx == device_number)
                {
                  //make sure clock starts low
                  digitalWrite(_sclk, LOW);
            
                  shiftOut(_mosi, _sclk, MSBFIRST, digit);
                  shiftOut(_mosi, _sclk, MSBFIRST, 0);
                }
                else
                {
                  //make sure clock starts low
                  digitalWrite(_sclk, LOW);
            
                  shiftOut(_mosi, _sclk, MSBFIRST, MAX7219_NO_OP);
                  shiftOut(_mosi, _sclk, MSBFIRST, 0);
                }
            }
            digitalWrite(_cs, HIGH); 
            
            rtn_val = 0;
        }
    }
    
    return(rtn_val);
}


//********************************************************************* 
uint8_t Max7219::device_all_on(uint8_t device_number)
{
    int32_t rtn_val = 0xFF;
    uint8_t idx = 0;
    
    if(device_number > _num_devices)
    {
        rtn_val = 1;
    }
    else if(device_number == 0)
    {
        rtn_val = 2;
    }
    else
    {
        rtn_val = 0;
        
        //writes every digit of given device to 0xFF
        for(idx = 0; idx < 8; idx++)
        {
            if(rtn_val == 0)
            {
                rtn_val = write_digit(device_number, (idx + 1), 0xFF);
            }
        }
    }
    
    return(rtn_val);
}


//********************************************************************* 
uint8_t Max7219::device_all_off(uint8_t device_number)
{
    int32_t rtn_val = 0xFF;
    uint8_t idx = 0;
    
    if(device_number > _num_devices)
    {
        rtn_val = 1;
    }
    else if(device_number == 0)
    {
        rtn_val = 2;
    }
    else
    {
        rtn_val = 0;
        
        //writes every digit of given device to 0
        for(idx = 0; idx < 8; idx++)
        {
            if(rtn_val == 0)
            {
                rtn_val = write_digit(device_number, (idx + 1), 0);
            }
        }
    }
    
    return(rtn_val);
}


//*********************************************************************
void Max7219::display_all_on(void)
{
    uint8_t idx, idy;
    
    //writes every digit of every device to 0xFF
    for(idx = 0; idx < _num_devices; idx++)
    {
        for(idy = 0; idy < MAX7219_DIGIT_7; idy++)
        {
            write_digit((idx + 1), (idy + 1), 0xFF);
        }
    }
}

    
//*********************************************************************    
void Max7219::display_all_off(void)
{
    uint8_t idx, idy;
    
    //writes every digit of every device to 0
    for(idx = 0; idx < _num_devices; idx++)
    {
        for(idy = 0; idy < MAX7219_DIGIT_7; idy++)
        {
            write_digit((idx + 1), (idy + 1), 0);
        }
    }
}

