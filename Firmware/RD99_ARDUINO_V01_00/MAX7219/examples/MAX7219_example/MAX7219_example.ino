/***********************************************************************
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


#include <max7219.h>

//Blinky demo run on MAXREFDES99#; 
//4 8x8 monocolor displays arranged in a square

Max7219 led_display;
max7219_configuration_t display_config;

uint8_t rtn_val;
uint8_t idx, idy;
uint16_t idz;
 
void setup() 
{
  Serial.begin(115200);
  led_display.begin(11, 13, 10);

  display_config.decode_mode = 0;
  display_config.intensity = 0x0F;
  display_config.scan_limit = 0x07;

  Serial.println("Start of demo");
  
  led_display.set_num_devices(4);
  led_display.set_display_test();
  
  delay(2000);
  
  led_display.clear_display_test();
  
  led_display.display_all_off();
  led_display.init_display(display_config);

  led_display.enable_display();
    
  for(idx = 0; idx < 4; idx++)
  {
      for(idy = 0; idy < 8; idy++)
      {
        led_display.write_digit(idx+1, idy+1, 0xFF);
        delay(100);
        led_display.clear_digit(idx+1, idy+1);
        delay(100);
      }
  }
}

void loop() 
{
  for(idx = 0; idx < 4; idx++)
  {
      for(idy = 0; idy < 8; idy++)
      {
          for(idz = 0; idz < 256; idz++)
          {
              led_display.write_digit(idx+1, idy+1, idz);
              delay(50);
          }
      }
  }
  
  led_display.display_all_off();
  
  delay(500);
  
  for(idx = 0; idx < 4; idx++)
  {
      led_display.device_all_on(idx + 1);
      delay(250);
      led_display.device_all_off(idx + 1);
      delay(250);
  }
}

