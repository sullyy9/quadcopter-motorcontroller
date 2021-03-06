/**
 * -------------------------------------------------------------------------------------------------
 * @author  Ryan Sullivan (ryansullivan@googlemail.com)
 *
 * @file    main.c
 * @brief   Main.
 *
 * @date    2021-07-07
 * -------------------------------------------------------------------------------------------------
 */

#include "types.h"

#include "main.h"
#include "io.h"
#include "debug.h"
#include "system.h"
#include "utils.h"

/*------------------------------------------------------------------------------------------------*/
/*-constant-definitions---------------------------------------------------------------------------*/
/*------------------------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------------------------*/
/*-exported-variables-----------------------------------------------------------------------------*/
/*------------------------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------------------------*/
/*-static-variables-------------------------------------------------------------------------------*/
/*------------------------------------------------------------------------------------------------*/

static bool run_main = true;

/*------------------------------------------------------------------------------------------------*/
/*-forward-declarations---------------------------------------------------------------------------*/
/*------------------------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------------------------*/
/*-exported-functions-----------------------------------------------------------------------------*/
/*------------------------------------------------------------------------------------------------*/

/**
 * @brief      Main function.
 * @return int Unused.
 */
int main(void)
{
    system_initialise();
    system_timer_initialise();
    io_initialise();

    /*
     * Enable interupts.
     */
    sei();

    // PORTA.OUTCLR |= PIN3_bm;

    while(run_main)
    {
        debug_printf("hello\r\n");
        utils_wait_ms(1000);
    }

    return (0);
}

/*------------------------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------------------------*/
/*-static-functions-------------------------------------------------------------------------------*/
/*------------------------------------------------------------------------------------------------*/

/**
 * @brief   1ms system timer interrupt.
 */
ISR(TCA0_OVF_vect)
{
    TCA0.SINGLE.INTFLAGS = TCA_SINGLE_OVF_bm;

    io_1ms_poll();
    utils_1ms_poll();
}

/*------------------------------------------------------------------------------------------------*/
/*-end-of-module----------------------------------------------------------------------------------*/
/*------------------------------------------------------------------------------------------------*/
