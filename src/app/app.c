/**
  * @file    app.c
  * @brief   App
  * @author  Igor T. <research.tahoe@gmail.com>
  */

#include <stdbool.h>
#include "ui.h"
#include "gnss.h"
#include "app.h"


extern	ui_t            ui;
	gnss_t          gnss;
	app_t           app;

/**
  * @brief  This function is executed in case of error occurrence.
  */
static
void	app_error( void )
{
	ui_led_t *      led_0       =   &ui.led[0];
	ui_led_t *      led_1       =   &ui.led[1];
	ui_led_t *      led_2       =   &ui.led[2];
	uint32_t        delay_msec  =   CFG_UI_LED_FLSH_SHRT_mSEC;

	while( true )
	{
		ui_led_set( led_2, UI_LED_MODE_FLSH_SHRT );
		ui_led_set( led_1, UI_LED_MODE_FLSH_SHRT );
		ui_led_set( led_0, UI_LED_MODE_FLSH_SHRT );
		HAL_Delay( delay_msec );
	}
}

/**
  * @brief  Switch the PLL source from HSI to HSE bypass, and select the PLL as SYSCLK
  */
static
void	app_clock_config( void )
{
	RCC_ClkInitTypeDef      clk     =   {0};
	RCC_OscInitTypeDef      osc     =   {0};

	//-1- Select HSI as system clock source to allow modification of the PLL configuration
	clk.ClockType       =   RCC_CLOCKTYPE_SYSCLK;
	clk.SYSCLKSource    =   RCC_SYSCLKSOURCE_HSI;

	if( HAL_RCC_ClockConfig( &clk, FLASH_LATENCY_2 ) != HAL_OK )
	{
		app_error();
	}

	//-2- Enable HSE Oscillator, select it as PLL source and finally activate the PLL
	osc.OscillatorType  = RCC_OSCILLATORTYPE_HSE;
	osc.HSEState        = RCC_HSE_ON;
  
	osc.PLL.PLLSource   = RCC_PLLSOURCE_HSE;
	osc.PLL.PLLState    = RCC_PLL_ON;
	osc.HSEPredivValue  = RCC_HSE_PREDIV_DIV2;
	osc.PLL.PLLMUL      = RCC_PLL_MUL9;

	if( HAL_RCC_OscConfig( &osc ) != HAL_OK )
	{
		app_error();
	}

	//-3- Select the PLL as system clock source and configure the HCLK, PCLK1 and PCLK2 clocks dividers
	clk.ClockType       = (RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2);
	clk.SYSCLKSource    = RCC_SYSCLKSOURCE_PLLCLK;
	clk.AHBCLKDivider   = RCC_SYSCLK_DIV1;
	clk.APB1CLKDivider  = RCC_HCLK_DIV2;
	clk.APB2CLKDivider  = RCC_HCLK_DIV1;

	if( HAL_RCC_ClockConfig( &clk, FLASH_LATENCY_2 ) != HAL_OK )
	{
		app_error();
	}

	//-4- Optional: Disable HSI Oscillator (if the HSI is no more needed by the application)
	osc.OscillatorType  = RCC_OSCILLATORTYPE_HSI;
	osc.HSIState        = RCC_HSI_OFF;
	osc.PLL.PLLState    = RCC_PLL_NONE;

	if( HAL_RCC_OscConfig( &osc ) != HAL_OK )
	{
		app_error();
	}

	SystemCoreClockUpdate();
}

/**
 * @brief App entry
 */
int	main( void )
{
	ui_led_t *      led_0   =   &ui.led[0];
	ui_led_t *      led_1   =   &ui.led[1];
	ui_led_t *      led_2   =   &ui.led[2];


	app_clock_config();
	SysTick_Config(SystemCoreClock / BSP_SYSTICK_HZ);
	HAL_Init();
	ui_init();
	gnss_init();
	gnss_set( true );

	ui_led_set( led_2, UI_LED_MODE_FLSH_LONG );
	ui_led_set( led_1, UI_LED_MODE_FLSH_LONG );
	ui_led_set( led_0, UI_LED_MODE_FLSH_LONG );

	__enable_irq();


	while( true )
	{
		if( app.evt.ui_key0 )
		{
			app.evt.ui_key0 =    false;
		}

		if( app.evt.ui_key1 )
		{
			app.evt.ui_key1 =    false;
			gnss_send( &gnss, CFG_GNSS_NMEA_MSG1 );
		}

		if( app.evt.tick_1hz )
		{
			app.evt.tick_1hz    =   false;

			#ifndef NDEBUG
			printf( "SAT's: %d\tFIX: %d\n", gnss.nmea.gsv.sats_in_view, gnss.nmea.gga.fix );
			#endif
		}

		if( app.evt.gnss )
		{
			app.evt.gnss        =   false;

			switch( gnss.nmea.gga.fix )
			{
				case NMEA_FIX_RTK_FLT:
					ui_led_set( led_2, UI_LED_MODE_ON );
					ui_led_set( led_1, UI_LED_MODE_OFF );
					ui_led_set( led_0, UI_LED_MODE_OFF );
					break;

				case NMEA_FIX_RTK_INT:
					ui_led_set( led_2, UI_LED_MODE_OFF );
					ui_led_set( led_1, UI_LED_MODE_ON );
					ui_led_set( led_0, UI_LED_MODE_ON );
					break;

				case NMEA_FIX_3D:
					ui_led_set( led_2, UI_LED_MODE_OFF );
					ui_led_set( led_1, UI_LED_MODE_ON );
					ui_led_set( led_0, UI_LED_MODE_OFF );
					break;

				case NMEA_FIX_2D:
					ui_led_set( led_2, UI_LED_MODE_OFF );
					ui_led_set( led_1, UI_LED_MODE_OFF );
					ui_led_set( led_0, UI_LED_MODE_ON );
					break;

				default:
					ui_led_set( led_2, UI_LED_MODE_OFF );
					ui_led_set( led_1, UI_LED_MODE_OFF );
					ui_led_set( led_0, UI_LED_MODE_OFF );
					break;
			}
		}
	}
}
