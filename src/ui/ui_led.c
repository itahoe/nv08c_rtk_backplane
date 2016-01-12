/**
  * @file    ui_led.h
  * @brief   User Interface - LED service
  * @author  Igor T. <research.tahoe@gmail.com>
  */

#include	"ui_led.h"

static
void	ui_led_set_flsh_long(           ui_led_t *              p           )
{
	if( p->tick == 0 )
	{
		p->toggle();
	}

	p->tick		=	UI_LED_FLSH_LONG_TCKS;
}

static
void	ui_led_set_flsh_shrt(           ui_led_t *              p           )
{
	if( p->tick == 0 )
	{
		p->toggle();
	}

	p->tick		=	UI_LED_FLSH_SHRT_TCKS;
}

/**
 * @brief UI LED set
 */
void	ui_led_set(                     ui_led_t *              p,
	                        const   ui_led_mode_t           mode        )
{
	switch( mode )
	{
		case UI_LED_MODE_OFF:	        p->set( false );                break;
		case UI_LED_MODE_ON:            p->set( true );                 break;
		case UI_LED_MODE_TOGGLE:        p->toggle();                    break;
		case UI_LED_MODE_FLSH_LONG:     ui_led_set_flsh_long( p );      break;
		case UI_LED_MODE_FLSH_SHRT:     ui_led_set_flsh_shrt( p );      break;
		default:
			break;
	}
}

/**
 * @brief UI LED hook
 */
bool	ui_led_hook(                    ui_led_t *              p           )
{
	bool			resp	=	false;

	if( p->tick > 0 )
	{
		p->tick--;

		if( p->tick == 0 )
		{
			p->toggle();
			resp	=	true;
		}
	}

	return( resp );
}
