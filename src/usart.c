/**
 * -------------------------------------------------------------------------------------------------
 * @author  Ryan Sullivan (ryansullivan@googlemail.com)
 *
 * @file    usart.c
 * @brief   USART HAL.
 *
 * @date    2021-07-18
 * -------------------------------------------------------------------------------------------------
 */

#include "types.h"

#include "usart.h"

/*------------------------------------------------------------------------------------------------*/
/*-constant-definitions---------------------------------------------------------------------------*/
/*------------------------------------------------------------------------------------------------*/

#define USART0_TX_BUFFER_SIZE 255

/*------------------------------------------------------------------------------------------------*/
/*-exported-variables-----------------------------------------------------------------------------*/
/*------------------------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------------------------*/
/*-static-variables-------------------------------------------------------------------------------*/
/*------------------------------------------------------------------------------------------------*/

static volatile uint8_t usart0_tx_buffer[USART0_TX_BUFFER_SIZE];
static volatile uint8_t usart0_tx_in_ptr         = 0;
static volatile uint8_t usart0_tx_out_ptr        = 0;
static volatile uint8_t usart0_tx_buffered_bytes = 0;
static volatile bool    usart0_tx_in_progress    = false;

/*------------------------------------------------------------------------------------------------*/
/*-forward-declarations---------------------------------------------------------------------------*/
/*------------------------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------------------------*/
/*-exported-functions-----------------------------------------------------------------------------*/
/*------------------------------------------------------------------------------------------------*/

/**
 * @brief           Initialise the USART peripheral.
 * @param baud_rate Baud rate.
 */
void usart_initialise(uint16_t baud_rate)
{
    USART0.BAUD = (uint16_t)(F_CPU * 64 / (16 * (float)baud_rate) + 0.5f);

    USART0.CTRLA = USART_TXCIE_bm;
    USART0.CTRLB = USART_TXEN_bm;
    USART0.CTRLC = (USART_CHSIZE_8BIT_gc | USART_SBMODE_1BIT_gc | USART_PMODE_DISABLED_gc |
                    USART_CMODE_ASYNCHRONOUS_gc);

    while(!(USART0.STATUS & USART_DREIF_bm)) {}
}

/*------------------------------------------------------------------------------------------------*/

/**
 * @brief      Write a byte into the USART0 TX buffer.
 * @param byte Byte.
 */
void usart0_tx_byte(uint8_t byte)
{
    usart0_tx_buffer[usart0_tx_in_ptr] = byte;
    usart0_tx_in_ptr++;
    usart0_tx_buffered_bytes++;

    /*
     * If there's no ongoing transmition, start one by putting the first byte into the tx register.
     */
    if(usart0_tx_in_progress == false)
    {
        USART0.TXDATAL = usart0_tx_buffer[usart0_tx_out_ptr];
        usart0_tx_out_ptr++;
        usart0_tx_buffered_bytes--;
        usart0_tx_in_progress = true;
    }

    if(usart0_tx_in_ptr >= USART0_TX_BUFFER_SIZE)
    {
        usart0_tx_in_ptr = 0;
    }
    if(usart0_tx_out_ptr >= USART0_TX_BUFFER_SIZE)
    {
        usart0_tx_out_ptr = 0;
    }
}

/*------------------------------------------------------------------------------------------------*/

/**
 * @brief           Return the free space in the tx buffer in bytes.
 * @return uint8_t  bytes of free space.
 */
uint8_t usart0_tx_free(void)
{
    return (USART0_TX_BUFFER_SIZE - usart0_tx_buffered_bytes);
}

/*------------------------------------------------------------------------------------------------*/

/**
 * @brief   USART0 transmit interrupt function. Send the next byte to the output register.
 */
ISR(USART0_TXC_vect)
{
    USART0.STATUS |= USART_TXCIF_bm;

    if(usart0_tx_buffered_bytes > 0)
    {
        USART0.TXDATAL = usart0_tx_buffer[usart0_tx_out_ptr];
        usart0_tx_out_ptr++;
        usart0_tx_buffered_bytes--;
    }
    else
    {
        usart0_tx_in_progress = false;
    }

    if(usart0_tx_out_ptr >= USART0_TX_BUFFER_SIZE)
    {
        usart0_tx_out_ptr = 0;
    }
}

/*------------------------------------------------------------------------------------------------*/
/*-static-functions-------------------------------------------------------------------------------*/
/*------------------------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------------------------*/
/*-end-of-module----------------------------------------------------------------------------------*/
/*------------------------------------------------------------------------------------------------*/
