/******************************************************************//**
* @file maxrefdes99.h
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
* @brief Header file for maxrefdes99 demo
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


#ifndef MAXREFDES99_H
#define MAXREFDES99_H


#include "max7219.h"
    

/**********************************************************//**
* @brief gets character bitmap fom Flash memory
* 
* @details 
*
* On Entry:
*     @param[in] c - character to get bitmap for
*     @param[in] char_buff - pointer to buffer to store bitmap in
*                            must be at least 6 bytes
*
* On Exit:
*    @return none
**************************************************************/
void get_5x7_character(char c, uint8_t *char_buff);


/**********************************************************//**
* @brief prints character to MAXREFDES99 at given position
* 
* @details 
*
* On Entry:
*     @param[in] p_display - pointer to Max7219 object
*     @param[in] position99 - position to print char to
*                posiion 1 is top left column, position 32
*                is bottom right column
*     @param[in] c - char to print
*
* On Exit:
*    @return none
**************************************************************/
void print_char(Max7219 *p_display, uint8_t position99, char c);


/**********************************************************//**
* @brief prints given string to MAXREFDES99at given position
* 
* @details 
*
* On Entry:
*     @param[in] p_display - pointer to Max7219 object
*     @param[in] position99 - position to print char to
*                posiion 1 is top left column, position 32
*                is bottom right column
*     @param[in] s - pointer to string to print
*
* On Exit:
*    @return none
**************************************************************/
void print_string(Max7219 *p_display, uint8_t position99, const char *s);


/**********************************************************//**
* @brief shifts display right 'count' positions with given
*        delay between shifts 
* 
* @details 
*
* On Entry:
*     @param[in] p_display - pointer to Max7219 object
*     @param[in] count - number of positions to shift
*     @param[in] ms_delay - delay between shifts
*
* On Exit:
*    @return none
**************************************************************/
void shift_display_right(Max7219 *p_display, uint8_t count, uint8_t ms_delay);


/**********************************************************//**
* @brief shifts display left 'count' positions with given
*        delay between shifts
* 
* @details 
*
* On Entry:
*     @param[in] p_display - pointer to Max7219 object
*     @param[in] count - number of positions to shift
*     @param[in] ms_delay - delay between shifts
*
* On Exit:
*    @return none
**************************************************************/
void shift_display_left(Max7219 *p_display, uint8_t count, uint8_t ms_delay);


/**********************************************************//**
* @brief turns on all leds for given quadrant, with quad 1 being
*        top left and quad 4 being bottom right
* 
* @details 
*
* On Entry:
*     @param[in] p_display - pointer to Max7219 object
*     @param[in] quad - see brief
*
* On Exit:
*    @return none
**************************************************************/
void quad_all_on(Max7219 *p_display, uint8_t quad);


/**********************************************************//**
* @brief turns off all leds for given quadrant, with quad 1 being
*        top left and quad 4 being bottom right
* 
* @details 
*
* On Entry:
*     @param[in] p_display - pointer to Max7219 object
*     @param[in] quad - see brief
*
* On Exit:
*    @return none
**************************************************************/
void quad_all_off(Max7219 *p_display, uint8_t quad);


/**********************************************************//**
* @brief turns all leds for whole display on
* 
* @details 
*
* On Entry:
*     @param[in] p_display - pointer to Max7219 object
*
* On Exit:
*    @return none
**************************************************************/
void all_on(Max7219 *p_display);


/**********************************************************//**
* @brief turns all leds for whole display off
* 
* @details 
*
* On Entry:
*     @param[in] p_display - pointer to Max7219 object
*
* On Exit:
*    @return none
**************************************************************/
void all_off(Max7219 *p_display);


/**********************************************************//**
* @brief demo loop for MAXREFDES99
* 
* @details 
*
* On Entry:
*     @param[in] p_display - pointer to Max7219 object
*     @param[in] display_config - structure holding configuration data
*     @param[in] endless_loop - if true run demo in endless loop
*
* On Exit:
*    @return none
**************************************************************/
void demo(Max7219 *p_display, max7219_configuration_t display_config, bool endless_loop);


/**********************************************************//**
* @brief shift display in given direction forever
* 
* @details 
*
* On Entry:
*     @param[in] p_display - pointer to Max7219 object
*     @param[in] scroll_right - if true shift right, else shift left
*
* On Exit:
*    @return none
**************************************************************/
void endless_scroll_display(Max7219 *p_display, uint32_t scroll_right);


#endif /*MAXREFDES99_H*/


