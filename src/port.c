/**
 * -------------------------------------------------------------------------------------------------
 * @author  Ryan Sullivan (ryansullivan@googlemail.com)
 *
 * @file    port.c
 * @brief   IO port HAL.
 *
 * @date    2021-07-18
 * -------------------------------------------------------------------------------------------------
 */

#include "types.h"

#include "port.h"

/*------------------------------------------------------------------------------------------------*/
/*-constant-definitions---------------------------------------------------------------------------*/
/*------------------------------------------------------------------------------------------------*/

#define PORT_MASK(pin) (*(PORT_t *)(0x400 + ((pin / 8) * 0x20)))
#define PIN_MASK(pin)  (uint8_t)(1 << (pin % 8))

/*------------------------------------------------------------------------------------------------*/
/*-exported-variables-----------------------------------------------------------------------------*/
/*------------------------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------------------------*/
/*-static-variables-------------------------------------------------------------------------------*/
/*------------------------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------------------------*/
/*-forward-declarations---------------------------------------------------------------------------*/
/*------------------------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------------------------*/
/*-exported-functions-----------------------------------------------------------------------------*/
/*------------------------------------------------------------------------------------------------*/

/**
 * @brief       Initialise a pin to the specified mode.
 * @param pin   Pin to be initialised.
 * @param mode  Mode the pin will be initialised to.
 */
void port_initialise(pin_t pin, pin_mode_t mode)
{
    /*
     *  Initialise as input or output.
     */
    if(mode <= PORT_MODE_OUTPUT_PULLUP)
    {
        PORT_MASK(pin).DIRSET = PIN_MASK(pin);
    }
    else
    {
        PORT_MASK(pin).DIRCLR = PIN_MASK(pin);
    }

    /*
     * Initialise the pullup if requested.
     */
    if(mode == PORT_MODE_OUTPUT_PULLUP || mode == PORT_MODE_INPUT_PULLUP)
    {
        switch(pin % 8)
        {
            case 0:
            {
                PORT_MASK(pin).PIN0CTRL = PORT_PULLUPEN_bm;
                break;
            }
            case 1:
            {
                PORT_MASK(pin).PIN1CTRL = PORT_PULLUPEN_bm;
                break;
            }
            case 2:
            {
                PORT_MASK(pin).PIN2CTRL = PORT_PULLUPEN_bm;
                break;
            }
            case 3:
            {
                PORT_MASK(pin).PIN3CTRL = PORT_PULLUPEN_bm;
                break;
            }
            case 4:
            {
                PORT_MASK(pin).PIN4CTRL = PORT_PULLUPEN_bm;
                break;
            }
            case 5:
            {
                PORT_MASK(pin).PIN5CTRL = PORT_PULLUPEN_bm;
                break;
            }
            case 6:
            {
                PORT_MASK(pin).PIN6CTRL = PORT_PULLUPEN_bm;
                break;
            }
            case 7:
            {
                PORT_MASK(pin).PIN7CTRL = PORT_PULLUPEN_bm;
                break;
            }
            default:
            {
                break;
            }
        }
    }
}

/*------------------------------------------------------------------------------------------------*/

/**
 * @brief       Set a pin to a high logic level.
 * @param pin   Pin to set.
 */
void port_set(pin_t pin)
{
    PORT_MASK(pin).OUTSET |= PIN_MASK(pin);
}

/*------------------------------------------------------------------------------------------------*/

/**
 * @brief       Set a pin to a low logic level.
 * @param pin   Pin to set.
 */
void port_clear(pin_t pin)
{
    PORT_MASK(pin).OUTCLR |= PIN_MASK(pin);
}

/*------------------------------------------------------------------------------------------------*/
/*-static-functions-------------------------------------------------------------------------------*/
/*------------------------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------------------------*/
/*-end-of-module----------------------------------------------------------------------------------*/
/*------------------------------------------------------------------------------------------------*/
