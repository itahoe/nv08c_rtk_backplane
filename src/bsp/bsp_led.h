/**
  * @file    bsp_led.h
  * @brief   Board Support Package - LED services
  * @author  Igor T. <research.tahoe@gmail.com>
  */

#ifndef  BSP_LED_H
#define  BSP_LED_H

#include	<stdbool.h>

void	bsp_led0_init( void );
void	bsp_led1_init( void );
void	bsp_led2_init( void );

void	bsp_led0_set( bool val );
void	bsp_led1_set( bool val );
void	bsp_led2_set( bool val );

void	bsp_led0_toggle( void );
void	bsp_led1_toggle( void );
void	bsp_led2_toggle( void );

#endif	//BSP_LED_H
