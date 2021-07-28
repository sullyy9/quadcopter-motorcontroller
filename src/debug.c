/**
 * -------------------------------------------------------------------------------------------------
 * @author  Ryan Sullivan (ryansullivan@googlemail.com)
 * 
 * @file    debug.c
 * @brief   Debugging functions.
 * 
 * @date    2021-07-18
 * -------------------------------------------------------------------------------------------------
 */

#include "types.h"
#include <stdarg.h>

#include "debug.h"
#include "usart.h"

/*------------------------------------------------------------------------------------------------*/
/*-constant-definitions---------------------------------------------------------------------------*/
/*------------------------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------------------------*/
/*-exported-variables-----------------------------------------------------------------------------*/
/*------------------------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------------------------*/
/*-static-variables-------------------------------------------------------------------------------*/
/*------------------------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------------------------*/
/*-forward-declarations---------------------------------------------------------------------------*/
/*------------------------------------------------------------------------------------------------*/

void print_character(char character);
void print_number(uint32_t number);

/*------------------------------------------------------------------------------------------------*/
/*-exported-functions-----------------------------------------------------------------------------*/
/*------------------------------------------------------------------------------------------------*/

/**
 * @brief               Printf-like function for debugging.
 * @param string_ptr    String to print.
 * @param ...           Variables.
 */
void debug_printf(char const *string_ptr, ...)
{
    va_list argument_list;

    va_start(argument_list, string_ptr);
    while(*string_ptr != 0)
    {
        /*
         * Print a character or if its an embedded variable, process it.
         */
        if(*string_ptr != '%')
        {
            print_character(*string_ptr);
        }
        else
        {
            /*
             * Depending on the type of variable, process it differently.
             */
            string_ptr++;
            switch(*string_ptr)
            {
                /*
                 * Character.
                 */
                case 'c':
                {
                    char c = (char)va_arg(argument_list, int);
                    print_character(c);
                    break;
                }

                /*
                 * String.
                 */
                case 's':
                {
                    char *ptr = va_arg(argument_list, char *);
                    while(*ptr != 0)
                    {
                        print_character(*ptr);
                        ptr++;
                    }
                    break;
                }

                /*
                 * Signed integer.
                 */
                case 'd':
                {
                    int32_t number = va_arg(argument_list, int32_t);
                    if(number < 0)
                    {
                        print_character('-');
                        number = 0 - number;
                    }
                    print_number((uint32_t)number);
                    break;
                }

                /*
                 * Unsigned integer.
                 */
                case 'u':
                {
                    print_number(va_arg(argument_list, uint32_t));
                    break;
                }

                default:
                {
                    break;
                }
            }
        }

        string_ptr++;
    }
}

/*------------------------------------------------------------------------------------------------*/
/*-static-functions-------------------------------------------------------------------------------*/
/*------------------------------------------------------------------------------------------------*/

/**
 * @brief           Print a character via UART.
 * @param character Character to print.
 */
void print_character(char character)
{
    while(usart0_tx_free() == 0) {}
    usart0_tx_byte((uint8_t)character);
}

/*------------------------------------------------------------------------------------------------*/

/**
 * @brief        Print a number via UART.
 * @param number Number to print.
 */
void print_number(uint32_t number)
{
    char    buffer[10];
    uint8_t buffer_ptr = 0;

    do
    {
        buffer[buffer_ptr] = ('0' + (number % 10));
        number             = number / 10;
        buffer_ptr++;
    } while(number != 0);

    while(buffer_ptr > 0)
    {
        buffer_ptr--;
        print_character(buffer[buffer_ptr]);
    }
}

/*------------------------------------------------------------------------------------------------*/
/*-end-of-module----------------------------------------------------------------------------------*/
/*------------------------------------------------------------------------------------------------*/
