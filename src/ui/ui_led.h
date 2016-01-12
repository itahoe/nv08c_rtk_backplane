/**
  * @file    ui_led.h
  * @brief   User Interface - LED service
  * @author  Igor T. <research.tahoe@gmail.com>
  */

#ifndef  UI_LED_H
#define  UI_LED_H

#include	<stdbool.h>
#include	<string.h>
#include	"config.h"
#include	"bsp.h"

#define	UI_SYSTICK_HZ                           BSP_SYSTICK_HZ

#define	UI_LED_FLSH_SHRT_TCKS           ( ((uint32_t) CFG_UI_LED_FLSH_SHRT_mSEC * UI_SYSTICK_HZ) / 1000 )
#define	UI_LED_FLSH_LONG_TCKS           ( ((uint32_t) CFG_UI_LED_FLSH_LONG_mSEC * UI_SYSTICK_HZ) / 1000 )

typedef	enum	ui_led_mode_e
{
	UI_LED_MODE_OFF,
	UI_LED_MODE_ON,
	UI_LED_MODE_TOGGLE,
	UI_LED_MODE_FLSH_SHRT,
	UI_LED_MODE_FLSH_LONG,
}	ui_led_mode_t;

typedef    void    ( * ui_led_init_t )( void );
typedef    void    ( * ui_led_set_t )( bool );
typedef    void    ( * ui_led_toggle_t )( void );

typedef	struct	ui_led_s
{
	ui_led_init_t           init;
	ui_led_set_t            set;
	ui_led_toggle_t         toggle;
	size_t                  tick;
} ui_led_t;

void	ui_led_set(			ui_led_t *              p,
	                        const   ui_led_mode_t           mode        );

bool	ui_led_hook(                    ui_led_t *              p           );

#endif	//UI_LED_H
