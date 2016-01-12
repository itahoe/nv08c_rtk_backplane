/**
  * @file    ui.h
  * @brief   User Interface
  * @author  Igor T. <research.tahoe@gmail.com>
  */

#include	"bsp_key.h"
#include	"bsp_led.h"
#include	"ui.h"

        ui_t	ui	=   {	.led[0].init    =   bsp_led0_init,
	                        .led[0].set     =   bsp_led0_set,
	                        .led[0].toggle  =   bsp_led0_toggle,

	                        .led[1].init    =   bsp_led1_init,
	                        .led[1].set     =   bsp_led1_set,
	                        .led[1].toggle  =   bsp_led1_toggle,

	                        .led[2].init    =   bsp_led2_init,
	                        .led[2].set     =   bsp_led2_set,
	                        .led[2].toggle  =   bsp_led2_toggle,

	                        .key[0].init    =   bsp_key0_init,
	                        .key[0].get     =   bsp_key0_get,

	                        .key[1].init    =   bsp_key1_init,
	                        .key[1].get     =   bsp_key1_get,       };

/**
 * @brief UI initialization.
 */
void	ui_init( void )
{
	ui.led[0].init();
	ui.led[1].init();
	ui.led[2].init();

	ui.key[0].init();
	ui.key[1].init();
}
