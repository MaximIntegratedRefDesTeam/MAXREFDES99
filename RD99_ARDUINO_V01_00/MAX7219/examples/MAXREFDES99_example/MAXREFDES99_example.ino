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


#include "maxrefdes99.h"

void print_menu(void);
uint8_t get_user_int(const char *msg, uint8_t max_val);
char get_user_char(const char *msg);
void get_user_string(const char *msg, char *char_buff);

Max7219 display99;

void setup() 
{
  Serial.begin(9600);
  Serial.setTimeout(5000);
  
  display99.begin(11, 13, 10);
  
  //struct for holding MAX7219 configuration data
  max7219_configuration_t display_config;
  
  //configuration data
  display_config.decode_mode = 0; //no BCD decode
  display_config.intensity = 0x0F; //max intensity
  display_config.scan_limit = 0x07; //scan all digits
  
  //set number of MAX7219 devices being used
  display99.set_num_devices(4);
  
  //config display 
  display99.init_display(display_config);
  
  //ensure all data registers are 0
  display99.display_all_off();
  
  display99.enable_display();

  uint8_t user_input = 0;
  uint8_t shift_right;
  char user_char;
  char user_str[24];

  uint8_t char_buff[6];
  
  while(user_input != 9)
  {
      print_menu();

      user_input = get_user_int(NULL, 9);

      switch(user_input) 
      {
          case 1:
          
              user_input = get_user_int("Please enter a value from 0 to 15: ", 15);  
              
              Serial.println(F("Updating display configuration..."));
              
              display_config.intensity = user_input;
              
              display99.init_display(display_config);
              
              //make sure is good for next loop
              user_input = 0;
              
          break;

          case 2:
          
              user_input = get_user_int("Please enter which position, 1 to 32: ", 32);
              
              user_char = get_user_char("Please enter an ASCII character from 'space' (0x20), to '~' (0x7E): ");
              
              print_char(&display99, user_input, user_char);
              
              //make sure is good for next loop
              user_input = 0;
              
          break;
          
          case 3: 
          
              user_input = get_user_int("Please enter which position, 1 to 32: ", 32);
              
              get_user_string("\nPlease enter a string less than 24 characters: ", user_str);
              
              print_string(&display99, user_input, user_str);

              //make sure is good for next loop
              user_input = 0;
              
          break;
          
          case 4:
          
              user_input = get_user_int("Please enter number of shifts, 1 to 32: ", 32);
              shift_right = get_user_int("Which direction? 0 for left, 1 for right.: ", 1);
              
              if(shift_right)
              {
                  Serial.print(F("Shifting Display Right "));
                  Serial.print(user_input, DEC);
                  Serial.println(F(" positions"));
                  shift_display_right(&display99, user_input, 100);
              }
              else
              {
                  Serial.print(F("Shifting Display Left "));
                  Serial.print(user_input, DEC);
                  Serial.println(F(" positions"));
                  shift_display_left(&display99, user_input, 100);
              }
              
          break;

          case 5:
          
              all_off(&display99);
              
          break;

          case 6:
          
              Serial.println(F("Running Demo"));
              demo(&display99, display_config, false);
              
          break;

          case 7:
          
              Serial.println(F("Entering Endless Loop"));
              demo(&display99, display_config, true);
              
          break;
          
          case 8:
              
              //blocking case, endless loop
              shift_right = get_user_int("Which direction? 0 for left, 1 for right.: ", 1);
              endless_scroll_display(&display99, shift_right);
              
          break;
          
          case 9:
          
              Serial.println(F("Ending Program"));
              
          break;

          default:
              Serial.println(F("Invalid entry, please try again"));
          break;
      }
  }
}

void loop() 
{
  //no infinite loop
}


//*********************************************************************
void print_menu(void)
{
  Serial.println();
  Serial.println(F("Please select an option below: "));
  Serial.println(F("1. Set Brightness"));
  Serial.println(F("2. Print a characther to given position"));
  Serial.println(F("3. Print a string to position"));
  Serial.println(F("4. Shift display given number of position and direction"));
  Serial.println(F("5. Clear display"));
  Serial.println(F("6. Run the Demo Rotuine"));
  Serial.println(F("7. Run the Demo Rotuine In Endless Loop"));
  Serial.println(F("8. Scroll Display In Endless Loop, left or right"));
  Serial.println(F("9. Quit"));
  Serial.println();
}


//*********************************************************************
uint8_t get_user_int(const char *msg, uint8_t max_val)
{
  uint8_t user_int;
  uint8_t bytes_available;
  uint8_t input_buffer[64];

  do
  {
    Serial.println(msg);
    do
    {
      bytes_available = Serial.readBytesUntil(0x0A, input_buffer, 64);
    }
    while(!bytes_available);

    if(bytes_available > 3)
    {
      Serial.println(F("Invalid Entry"));
      user_int = 0xFF;
    }
    else if(bytes_available > 2)
    {
      user_int = (10*(input_buffer[0] - '0'));
      user_int += (input_buffer[1] - '0');
      
    }
    else
    {
      user_int = (input_buffer[0] - '0');
    }

    Serial.print(F("You entered "));
    Serial.println(user_int, DEC);
    if(user_int > max_val)
    {
      Serial.println(F("Value out of range"));
    }
    
  }
  while(user_int > max_val);

  return(user_int);
}


//*********************************************************************
char get_user_char(const char *msg)
{
  char user_char;
  uint8_t bytes_available;
  uint8_t input_buffer[64];

  Serial.println(msg);
  do
  {
    bytes_available = Serial.readBytesUntil(0x0A, input_buffer, 2);
  }
  while(!bytes_available);

  user_char = input_buffer[0];

  Serial.print(F("You entered "));
  Serial.println(user_char);

  return(user_char);
}


//*********************************************************************
void get_user_string(const char *msg, char *char_buff)
{
  uint8_t bytes_available;

  Serial.println(msg);
  do
  {
    bytes_available = Serial.readBytesUntil(0x0A, char_buff, 24);
  }
  while(!bytes_available);

  for(uint8_t idx = (bytes_available - 1); idx < 24; idx++)
  {
    char_buff[idx] = 0;
  }

  Serial.println(F("You entered "));
  Serial.println(char_buff);
}

