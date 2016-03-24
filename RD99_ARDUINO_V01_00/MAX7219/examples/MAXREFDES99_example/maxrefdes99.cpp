/******************************************************************//**
* @file maxrefdes99.cpp
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
* @brief Source file for maxrefdes99 demo
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


#include "maxrefdes99.h"


//5x7 character bit map
static const PROGMEM uint8_t font_5x7[95][6] = {
    {0x00,0x00,0x00,0x00,0x00,0x00},    // SPACE
    {0x00,0x00,0x00,0x4F,0x00,0x00},    // !
    {0x00,0x00,0x07,0x00,0x07,0x00},    // "
    {0x00,0x14,0x7F,0x14,0x7F,0x14},    // #
    {0x00,0x24,0x2A,0x7F,0x2A,0x12},    // $
    {0x00,0x23,0x13,0x08,0x64,0x62},    // %
    {0x00,0x36,0x49,0x55,0x22,0x50},    // &
    {0x00,0x00,0x05,0x03,0x00,0x00},    // '
    {0x00,0x00,0x1C,0x22,0x41,0x00},    // (
    {0x00,0x00,0x41,0x22,0x1C,0x00},    // )
    {0x00,0x14,0x08,0x3E,0x08,0x14},    // *
    {0x00,0x08,0x08,0x3E,0x08,0x08},    // +
    {0x00,0x00,0x50,0x30,0x00,0x00},    // ,
    {0x00,0x08,0x08,0x08,0x08,0x08},    // -
    {0x00,0x00,0x60,0x60,0x00,0x00},    // .
    {0x00,0x20,0x10,0x08,0x04,0x02},    // /
    {0x00,0x3E,0x51,0x49,0x45,0x3E},    // 0
    {0x00,0x00,0x42,0x7F,0x40,0x00},    // 1
    {0x00,0x42,0x61,0x51,0x49,0x46},    // 2
    {0x00,0x21,0x41,0x45,0x4B,0x31},    // 3
    {0x00,0x18,0x14,0x12,0x7F,0x10},    // 4
    {0x00,0x27,0x45,0x45,0x45,0x39},    // 5
    {0x00,0x3C,0x4A,0x49,0x49,0x30},    // 6
    {0x00,0x01,0x71,0x09,0x05,0x03},    // 7
    {0x00,0x36,0x49,0x49,0x49,0x36},    // 8
    {0x00,0x06,0x49,0x49,0x29,0x1E},    // 9
    {0x00,0x36,0x36,0x00,0x00,0x00},    // :
    {0x00,0x56,0x36,0x00,0x00,0x00},    // ;
    {0x00,0x08,0x14,0x22,0x41,0x00},    // <
    {0x00,0x14,0x14,0x14,0x14,0x14},    // =
    {0x00,0x00,0x41,0x22,0x14,0x08},    // >
    {0x00,0x02,0x01,0x51,0x09,0x06},    // ?
    {0x00,0x30,0x49,0x79,0x41,0x3E},    // @
    {0x00,0x7E,0x11,0x11,0x11,0x7E},    // A
    {0x00,0x7F,0x49,0x49,0x49,0x36},    // B
    {0x00,0x3E,0x41,0x41,0x41,0x22},    // C
    {0x00,0x7F,0x41,0x41,0x22,0x1C},    // D
    {0x00,0x7F,0x49,0x49,0x49,0x41},    // E
    {0x00,0x7F,0x09,0x09,0x09,0x01},    // F
    {0x00,0x3E,0x41,0x49,0x49,0x7A},    // G
    {0x00,0x7F,0x08,0x08,0x08,0x7F},    // H
    {0x00,0x00,0x41,0x7F,0x41,0x00},    // I
    {0x00,0x20,0x40,0x41,0x3F,0x01},    // J
    {0x00,0x7F,0x08,0x14,0x22,0x41},    // K
    {0x00,0x7F,0x40,0x40,0x40,0x40},    // L
    {0x00,0x7F,0x02,0x0C,0x02,0x7F},    // M
    {0x00,0x7F,0x04,0x08,0x10,0x7F},    // N
    {0x00,0x3E,0x41,0x41,0x41,0x3E},    // O
    {0x00,0x7F,0x09,0x09,0x09,0x06},    // P
    {0x00,0x3E,0x41,0x51,0x21,0x5E},    // Q
    {0x00,0x7F,0x09,0x19,0x29,0x46},    // R
    {0x00,0x46,0x49,0x49,0x49,0x31},    // S
    {0x00,0x01,0x01,0x7F,0x01,0x01},    // T
    {0x00,0x3F,0x40,0x40,0x40,0x3F},    // U
    {0x00,0x1F,0x20,0x40,0x20,0x1F},    // V
    {0x00,0x3F,0x40,0x30,0x40,0x3F},    // W
    {0x00,0x63,0x14,0x08,0x14,0x63},    // X
    {0x00,0x07,0x08,0x70,0x08,0x07},    // Y
    {0x00,0x61,0x51,0x49,0x45,0x43},    // Z
    {0x00,0x00,0x7F,0x41,0x41,0x00},    // [
    {0x00,0x02,0x04,0x08,0x10,0x20},    // backslash
    {0x00,0x00,0x41,0x41,0x7F,0x00},    // ]
    {0x00,0x04,0x02,0x01,0x02,0x04},    // ^
    {0x00,0x40,0x40,0x40,0x40,0x40},    // _
    {0x00,0x00,0x01,0x02,0x04,0x00},    // `
    {0x00,0x20,0x54,0x54,0x54,0x78},    // a
    {0x00,0x7F,0x50,0x48,0x48,0x30},    // b
    {0x00,0x38,0x44,0x44,0x44,0x20},    // c
    {0x00,0x38,0x44,0x44,0x48,0x7F},    // d
    {0x00,0x38,0x54,0x54,0x54,0x18},    // e
    {0x00,0x08,0x7E,0x09,0x01,0x02},    // f
    {0x00,0x0C,0x52,0x52,0x52,0x3E},    // g
    {0x00,0x7F,0x08,0x04,0x04,0x78},    // h
    {0x00,0x00,0x44,0x7D,0x40,0x00},    // i
    {0x00,0x20,0x40,0x44,0x3D,0x00},    // j
    {0x00,0x7F,0x10,0x28,0x44,0x00},    // k
    {0x00,0x00,0x41,0x7F,0x40,0x00},    // l
    {0x00,0x78,0x04,0x58,0x44,0x78},    // m
    {0x00,0x7C,0x08,0x04,0x04,0x78},    // n
    {0x00,0x38,0x44,0x44,0x44,0x38},    // o
    {0x00,0x7C,0x14,0x14,0x14,0x08},    // p
    {0x00,0x08,0x14,0x14,0x18,0x7C},    // q
    {0x00,0x7C,0x08,0x04,0x04,0x08},    // r
    {0x00,0x48,0x54,0x54,0x54,0x20},    // s
    {0x00,0x04,0x3F,0x44,0x40,0x20},    // t
    {0x00,0x3C,0x40,0x40,0x20,0x7C},    // u
    {0x00,0x1C,0x20,0x40,0x20,0x1C},    // v
    {0x00,0x3C,0x40,0x30,0x40,0x3C},    // w
    {0x00,0x44,0x28,0x10,0x28,0x44},    // x
    {0x00,0x0C,0x50,0x50,0x50,0x3C},    // y
    {0x00,0x44,0x64,0x54,0x4C,0x44},    // z
    {0x00,0x00,0x08,0x36,0x41,0x00},    // {
    {0x00,0x00,0x00,0x7F,0x00,0x00},    // |
    {0x00,0x00,0x41,0x36,0x08,0x00},    // }
    {0x00,0x0C,0x02,0x0C,0x10,0x0C}     // ~
};


static uint8_t display_buff[256];
static uint8_t temp_buff[256];

static const uint8_t DISPLAY_BUFF_START = 0;
static const uint8_t DISPLAY_BUFF_END = 31;

static uint8_t buff_end = 0;


//*********************************************************************
void get_5x7_character(char c, uint8_t *char_buff)
{
    uint16_t temp_data;
    uint8_t idx, idy;

    for(idx = 0; idx < 6; idx++) 
    {
        //get byte of char from map and flip it, bit 0 becomes bit 7 and so on
        temp_data = (0x00FF & pgm_read_byte_near(&(font_5x7[c - 0x20][idx])));

        for(idy = 0; idy < 8; idy++) 
        {
            temp_data = (temp_data | (((temp_data & (1 << idy)) << (15 - (idy*2)))));
        }
        temp_data = ((temp_data >> 8) & 0x00FF);
        
        char_buff[idx] = ((uint8_t) temp_data);
    }
}


//*********************************************************************
void print_char(Max7219 *p_display, uint8_t position99, char c)
{
    uint8_t idx;
    uint8_t char_buff[6];
    uint8_t device;
    uint8_t wrap_device;
    uint8_t wrap_idx;
    uint8_t buff_start = position99;
    
    get_5x7_character(c, char_buff);

    if(position99 < 33)
    {
      //get device and device_position
      if(position99 > 8)
      {
          if(position99%8)
          {
              device = ((position99/8) + 1);
              position99 = position99%8;
          }
          else
          {
              device = position99/8;
              position99 = 8;
          }
      }
      else
      {
          device = 1;
      }

      //check for dispaly wrap around 
      //(moving to next 8x8 grid cause character doesn't fit on current one)
      if(position99 > 3)
      {
          wrap_idx = (9 - position99);
          if(device < 4)
          {
              wrap_device = (device + 1);
          }
          else
          {
              wrap_device = 1;
          }
      }
      else
      {
          wrap_idx = 6; //make bigger than idx, not used
          wrap_device = 0; //not used
      }

      //print character to position
      for(idx = 0; idx < 6; idx++)
      {
          //check for wrap
          if((idx >= wrap_idx)  && (device != 4))
          {
              p_display->write_digit(wrap_device, ((idx - wrap_idx) + 1), char_buff[idx]);
          }
          else
          {
              p_display->write_digit(device, (position99 + idx), char_buff[idx]);
          }

          buff_end = ((buff_start - 1) + idx);
          display_buff[buff_end] = char_buff[idx];
      }
    }
    else
    {
      for(idx = 0; idx < 6; idx++)
      {
        buff_end = ((buff_start - 1) + idx);
        display_buff[buff_end] = char_buff[idx];
      }
    }
}


//*********************************************************************
void print_string(Max7219 *p_display, uint8_t position99, const char *s)
{
    uint8_t idx = 0;
    
    while(s[idx] != '\0')
    {
      print_char(p_display, position99 + (idx*6), s[idx]);
      idx++;
    } 
}


//*********************************************************************
void shift_display_right(Max7219 *p_display, uint8_t count, uint8_t ms_delay)
{
    uint16_t idx, idy;
    uint8_t position99;
    
    for(idx = 0; idx < count; idx++)
    {
        for(idy = 0; idy < (buff_end + 1); idy++)
        {
            if(idy == buff_end)
            {
                temp_buff[0] = display_buff[idy];
            }
            else
            {
                temp_buff[idy + 1] = display_buff[idy];
            }
        }
        
        for(idy = 0; idy < (buff_end + 1); idy++)
        {
            //save shifted display in buffer
            display_buff[idy] = temp_buff[idy];
            
            if((idy >= DISPLAY_BUFF_START) && ( idy <= DISPLAY_BUFF_END))
            {
                position99 = ((idy - DISPLAY_BUFF_START) + 1);
                if(position99 > 24)
                {
                    if(position99 % 8)
                    {
                        position99 = position99  % 8;
                    }
                    else
                    {
                         position99 = 8;
                    }
                    p_display->write_digit(4, position99, display_buff[idy]);
                }
                else if(position99 > 16)
                {
                    if(position99 % 8)
                    {
                        position99 = position99  % 8;
                    }
                    else
                    {
                         position99 = 8;
                    }
                    p_display->write_digit(3, position99, display_buff[idy]);
                }
                else if(position99 > 8)
                {
                    if(position99 % 8)
                    {
                        position99 = position99  % 8;
                    }
                    else
                    {
                         position99 = 8;
                    }
                    p_display->write_digit(2, position99, display_buff[idy]);
                }
                else
                {
                    p_display->write_digit(1, position99, display_buff[idy]);
                }
            }
        }

        delay(ms_delay);
    }
}


void shift_display_left(Max7219 *p_display, uint8_t count, uint8_t ms_delay)
{
    uint16_t idx, idy;
    uint8_t position99;
    
    for(idx = 0; idx < count; idx++)
    {
        for(idy = 0; idy < (buff_end + 1); idy++)
        {
            if(idy == 0)
            {
                temp_buff[buff_end] = display_buff[idy];
            }
            else
            {
                temp_buff[idy - 1] = display_buff[idy];
            }
        }
        
        for(idy = 0; idy < (buff_end + 1); idy++)
        {
            //save shifted display in buffer
            display_buff[idy] = temp_buff[idy];
            
            if((idy >= DISPLAY_BUFF_START) && ( idy <= DISPLAY_BUFF_END))
            {
                position99 = ((idy - DISPLAY_BUFF_START) + 1);
                if(position99 > 24)
                {
                    if(position99 % 8)
                    {
                        position99 = position99  % 8;
                    }
                    else
                    {
                         position99 = 8;
                    }
                    p_display->write_digit(4, position99, display_buff[idy]);
                }
                else if(position99 > 16)
                {
                    if(position99 % 8)
                    {
                        position99 = position99  % 8;
                    }
                    else
                    {
                         position99 = 8;
                    }
                    p_display->write_digit(3, position99, display_buff[idy]);
                }
                else if(position99 > 8)
                {
                    if(position99 % 8)
                    {
                        position99 = position99  % 8;
                    }
                    else
                    {
                         position99 = 8;
                    }
                    p_display->write_digit(2, position99, display_buff[idy]);
                }
                else
                {
                    p_display->write_digit(1, position99, display_buff[idy]);
                }
            }
        }

        delay(ms_delay);
    }
}


//*********************************************************************
void quad_all_on(Max7219 *p_display, uint8_t quad)
{
    if(quad > 1)
    {
        for(uint8_t idx = 0; idx < 8; idx++)
        {
            display_buff[((quad - 1)*8) + DISPLAY_BUFF_START + idx] = 0xFF;
        }
    }
    else
    {
        for(uint8_t idx = 0; idx < 8; idx++)
        {
            display_buff[idx + DISPLAY_BUFF_START] = 0xFF;
        }
    }

    if(buff_end < (quad * 8))
    {
      buff_end = (quad * 8);
    }
    
    p_display->device_all_on(quad);
}


//*********************************************************************
void quad_all_off(Max7219 *p_display, uint8_t quad)
{
    if(quad > 1)
    {
        for(uint8_t idx = 0; idx < 8; idx++)
        {
            display_buff[((quad - 1)*8) + DISPLAY_BUFF_START + idx] = 0;
        }
    }
    else
    {
        for(uint8_t idx = 0; idx < 8; idx++)
        {
            display_buff[idx + DISPLAY_BUFF_START] = 0;
        }
    }

    //is buff_end in the quad?
    if((((quad - 1) * 8) < buff_end) && ((quad * 8) > buff_end))
    {
      buff_end = ((quad - 1) * 8);
    }
    //leave it alone otherwise
    
    p_display->device_all_off(quad);
}


//*********************************************************************
void all_on(Max7219 *p_display)
{
    for(uint16_t idx = 0; idx < 32; idx++)
    {
        display_buff[idx] = 0xFF;
    }

    if(buff_end < 32)
    {
      buff_end = 32;
    }
    
    p_display->display_all_on();
}


//*********************************************************************
void all_off(Max7219 *p_display)
{
    for(uint16_t idx = 0; idx < 32; idx++)
    {
        display_buff[idx] = 0;
    }

    if(buff_end < 32)
    {
      buff_end = 0;
    }
    
    p_display->display_all_off();
}


//*********************************************************************
void demo(Max7219 *p_display, max7219_configuration_t display_config, bool endless_loop)
{
    uint8_t position99 = 1;
    uint8_t idx = 0;
    
    do
    {
        all_off(p_display);
        
        if(position99 > 25)
        {
            position99 = 1;
        }
        
        for(idx = 0x20; idx < 0x7F; idx++)
        {
            print_char(p_display, position99, (char) idx);
            delay(250);
        }
        position99 = (position99 + 8);
        
        all_on(p_display);
        
        for(idx = 0; idx < 16; idx++)
        {
            display_config.intensity = 15 - idx;
            p_display->init_display(display_config);
            delay(100);
        } 
        
        for(idx = 0; idx < 16; idx++)
        {
            display_config.intensity = idx;
            p_display->init_display(display_config);
            delay(100);
        } 
        
        delay(100);
        all_off(p_display);
        delay(100);
        
        quad_all_on(p_display, 1);
        delay(500);
        shift_display_right(p_display, 32, 100);
        shift_display_left(p_display, 32, 100);
        all_off(p_display);
        delay(100);
        
        print_string(p_display, 1, "Maxim");
        delay(100);
        shift_display_right(p_display, 32, 100);
        shift_display_left(p_display, 32, 100);
        delay(100);
    }
    while(endless_loop);
}


//*********************************************************************
void endless_scroll_display(Max7219 *p_display, uint32_t scroll_right)
{
    if(scroll_right)
    {
        while(1)
        {
            shift_display_right(p_display, 1, 100);
        }
    }
    else
    {
        while(1)
        {
            shift_display_left(p_display, 1, 100);
        }
    }
}


