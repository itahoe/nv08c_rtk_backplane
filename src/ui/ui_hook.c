/**
  * @file    ui_hook.h
  * @brief   User Iinterface - hook
  * @author  Igor T. <research.tahoe@gmail.com>
  */

#include "ui_led.h"


/**
 * @brief UI LED hook.
 */
bool ui_led_hook(ui_led_t *p)
{
	bool resp = false;

	if (p->tick > 0) {
		p->tick--;

		if (p->tick == 0) {
			ui_led_toggle(p);
			resp = true;
		}
	}

	return resp;
}
