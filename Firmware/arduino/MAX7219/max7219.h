/******************************************************************//**
* @file max7219.h
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
* @brief Header file for Max7219 class
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


#ifndef MAX7219_H
#define MAX7219_H

#include <Arduino.h>


/**
* max7219_configuration_t - Structure for holding configuration data
* 
* Usefull in daisy chain applications 
* 
* Members:
*
* - uint8_t device_number - Represents device position in daisy chain applications, min val of 1
*
* - uint8_t decode_mode - Represents decode mode device uses, BCD or straight data
*
* - uint8_t intensity - Device intensity
*
* - uint8_t scan_limit - Device Scan limit
*/
typedef struct
{
    uint8_t device_number;
    uint8_t decode_mode;
    uint8_t intensity;
    uint8_t scan_limit;
}max7219_configuration_t;


class Max7219
{
    public:
    
    typedef enum
    {
        MAX7219_NO_OP = 0,
        MAX7219_DIGIT_0,
        MAX7219_DIGIT_1,
        MAX7219_DIGIT_2,
        MAX7219_DIGIT_3,
        MAX7219_DIGIT_4,
        MAX7219_DIGIT_5,
        MAX7219_DIGIT_6,
        MAX7219_DIGIT_7,
        MAX7219_DECODE_MODE,
        MAX7219_INTENSITY,
        MAX7219_SCAN_LIMIT,
        MAX7219_SHUTDOWN,
        MAX7219_DISPLAY_TEST = 15
    }max7219_register_e;
    
    
    typedef enum
    {
        MAX7219_INTENSITY_0 = 0,
        MAX7219_INTENSITY_1,
        MAX7219_INTENSITY_2,
        MAX7219_INTENSITY_3,
        MAX7219_INTENSITY_4,
        MAX7219_INTENSITY_5,
        MAX7219_INTENSITY_6,
        MAX7219_INTENSITY_7,
        MAX7219_INTENSITY_8,
        MAX7219_INTENSITY_9,
        MAX7219_INTENSITY_A,
        MAX7219_INTENSITY_B,
        MAX7219_INTENSITY_C,
        MAX7219_INTENSITY_D,
        MAX7219_INTENSITY_E,
        MAX7219_INTENSITY_F
    }max7219_intensity_e;
    
    
    typedef enum
    {
        MAX7219_SCAN_1 = 0,
        MAX7219_SCAN_2,
        MAX7219_SCAN_3,
        MAX7219_SCAN_4,
        MAX7219_SCAN_5,
        MAX7219_SCAN_6,
        MAX7219_SCAN_7,
        MAX7219_SCAN_8
    }max7219_scan_limit_e;
        
    
    /**********************************************************//**
    * @brief Constructor for Max7219 Class.  
    * 
    * @details 
    *
    * On Entry:
    *
    * On Exit:
    *    @return none
    **************************************************************/
    Max7219();
    
    
    /**********************************************************//**
    * @brief use in void setup()  
    * 
    * @details initializes given pins for use with 'shiftout'
    *
    * On Entry:
    *     @param[in] mosi - pin to use for mosi
    *     @param[in] sclk - pin to use for sclk
    *     @param[in] cs - pin to use for cs
    *
    * On Exit:
    *    @return none
    **************************************************************/
    void begin(uint8_t mosi, uint8_t sclk, uint8_t cs);
    
    
    /**********************************************************//**
    * @brief used inplace of destructor
    *
    * @details 
    *
    * On Entry:
    *
    * On Exit:
    *    @return none
    **************************************************************/
    void end();
    
    
    /**********************************************************//**
    * @brief Sets the number of MAX7219 devices being used.
    *        Defaults to one
    *
    * @details 
    *
    * On Entry:
    *     @param[in] num_devices - number of MAX7219 devices being
    *                              used, must be >= 1.
    *
    * On Exit:
    *    @return returns number of devices, or 0xFF if error
    **************************************************************/
    uint8_t set_num_devices(uint8_t num_devices);
    
    
    /**********************************************************//**
    * @brief Tests all devices being used 
    *
    * @details Sets bit0 of DISPLAY_TEST regiser in all devices
    *
    * On Entry:
    *
    * On Exit:
    *    @return none
    **************************************************************/
    void set_display_test(void);
    
    
    /**********************************************************//**
    * @brief Stops test
    *
    * @details Clear bit0 of DISPLAY_TEST regiser in all devices
    *
    * On Entry:
    *
    * On Exit:
    *    @return none
    **************************************************************/
    void clear_display_test(void);
    
    
    /**********************************************************//**
    * @brief initializes specific device in display with given 
    *        config data
    *
    * @details specific device is determined by config.device_number
    *
    * On Entry:
    *     @param[in] config - Structure containing configuration 
    *                         data of device
    *
    * On Exit:
    *    @return returns 0 on success, 
    *            returns 1 if device number is > _num_devices
    *            returns 2 if device number is 0
    *            returns 0xFF if function just returns
    **************************************************************/
    uint8_t init_device(max7219_configuration_t config);
    
    
    /**********************************************************//**
    * @brief initializes all devices with given config data
    *
    * @details all devices are configured with given data
    *
    * On Entry:
    *     @param[in] config - Structure containing configuration 
    *                         data
    * On Exit:
    *    @return none
    **************************************************************/
    void init_display(max7219_configuration_t config);
    
    
    /**********************************************************//**
    * @brief enables specific device in display
    *
    * @details 
    *
    * On Entry:
    *     @param[in] device_number - device to enable
    *
    * On Exit:
    *    @return returns 0 on success, 
    *            returns 1 if device number is > _num_devices
    *            returns 2 if device number is 0
    *            returns 0xFF if function just returns
    **************************************************************/
    uint8_t enable_device(uint8_t device_number);
    
    
    /**********************************************************//**
    * @brief enables all device in display 
    *
    * @details 
    *
    * On Entry:
    *
    * On Exit:
    *    @return none
    **************************************************************/
    void enable_display(void);
    
    
    /**********************************************************//**
    * @brief disables specific device in display
    *
    * @details 
    *
    * On Entry:
    *     @param[in] device_number - device to disable
    *
    * On Exit:
    *    @return returns 0 on success, 
    *            returns 1 if device number is > _num_devices
    *            returns 2 if device number is 0
    *            returns 0xFF if function just returns
    **************************************************************/
    uint8_t disable_device(uint8_t device_number);
    
    
    /**********************************************************//**
    * @brief disables all devices in display
    *
    * @details 
    *
    * On Entry:
    *
    * On Exit:
    *    @return none
    **************************************************************/
    void disable_display(void);
    
    
    /**********************************************************//**
    * @brief writes digit of given device with given data, user
    *        must enter correct data for decode_mode chosen
    *
    * @details 
    *
    * On Entry:
    *     @param[in] device_number - device to write too
    *     @param[in] digit - digit to write
    *     @param[in] data - data to write
    *
    * On Exit:
    *    @return returns 0 on success, 
    *            returns 1 if device number is > _num_devices
    *            returns 2 if device number is 0
    *            returns 3 if digit > 8
    *            returns 4 if digit < 1
    *            returns 0xFF if function just returns
    **************************************************************/
    uint8_t write_digit(uint8_t device_number, uint8_t digit, uint8_t data);
    
    
    /**********************************************************//**
    * @brief clears digit of given device
    *
    * @details 
    *
    * On Entry:
    *     @param[in] device_number - device to write too
    *     @param[in] digit - digit to clear
    *
    * On Exit:
    *    @return returns 0 on success, 
    *            returns 1 if device number is > _num_devices
    *            returns 2 if device number is 0
    *            returns 3 if digit > 8
    *            returns 4 if digit < 1
    *            returns 0xFF if function just returns
    **************************************************************/
    uint8_t clear_digit(uint8_t device_number, uint8_t digit);
    
    
    /**********************************************************//**
    * @brief turns on all segments/digits of given device
    *
    * @details 
    *
    * On Entry:
    *     @param[in] device_number - device to write too
    *
    * On Exit:
    *    @return returns 0 on success, 
    *            returns 1 if device number is > _num_devices
    *            returns 2 if device number is 0
    *            returns 0xFF if function just returns
    **************************************************************/
    uint8_t device_all_on(uint8_t device_number);
    
    
    /**********************************************************//**
    * @brief turns off all segments/digits of given device
    *
    * @details 
    *
    * On Entry:
    *     @param[in] device_number - device to write too
    *
    * On Exit:
    *    @return returns 0 on success, 
    *            returns 1 if device number is > _num_devices
    *            returns 2 if device number is 0
    *            returns 0xFF if function just returns
    **************************************************************/
    uint8_t device_all_off(uint8_t device_number);
    
    
    /**********************************************************//**
    * @brief turns on all segments/digits of display
    *
    * @details 
    *
    * On Entry:
    *
    * On Exit:
    *    @return none
    **************************************************************/
    void display_all_on(void);
    
    
    /**********************************************************//**
    * @brief turns off all segments/digits of display
    *
    * @details 
    *
    * On Entry:
    *
    * On Exit:
    *    @return none
    **************************************************************/
    void display_all_off(void);
    
      
    private:

    uint8_t _mosi;
    uint8_t _sclk;
    uint8_t _cs;
    uint8_t _num_devices; 
   
};
#endif /* MAX7219_H*/
