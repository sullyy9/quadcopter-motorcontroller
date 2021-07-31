/**
 * -------------------------------------------------------------------------------------------------
 * @author  Ryan Sullivan (ryansullivan@googlemail.com)
 * 
 * @file    utils.c
 * @brief   Utility functions.
 * 
 * @date    2021-07-31
 * -------------------------------------------------------------------------------------------------
 */

#include "types.h"

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

static volatile uint32_t timer = 0;

/*------------------------------------------------------------------------------------------------*/
/*-forward-declarations---------------------------------------------------------------------------*/
/*------------------------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------------------------*/
/*-exported-functions-----------------------------------------------------------------------------*/
/*------------------------------------------------------------------------------------------------*/

/**
 * @brief              Wait the specified number of milliseconds.
 * @param milliseconds Milliseconds to wait.
 */
void utils_wait_ms(uint32_t milliseconds)
{
    timer = 0;
    while(timer < milliseconds) {}
}

/*------------------------------------------------------------------------------------------------*/

/**
 * @brief Poll for the utils module. Called by the TCA interupt in main.
 */
void utils_1ms_poll(void)
{
    timer++;
}

/*------------------------------------------------------------------------------------------------*/
/*-static-functions-------------------------------------------------------------------------------*/
/*------------------------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------------------------*/
/*-end-of-module----------------------------------------------------------------------------------*/
/*------------------------------------------------------------------------------------------------*/
