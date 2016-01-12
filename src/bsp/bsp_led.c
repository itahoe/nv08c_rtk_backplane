/**
  * @file    bsp_led.h
  * @brief   Board Support Package - LED services
  * @author  Igor T. <research.tahoe@gmail.com>
  */

#include	<string.h>
#include	"bsp_led.h"
#include	"bsp.h"

/**
 * @brief LED0 pin initialization
 */
void	bsp_led0_init( void )
{
	GPIO_InitTypeDef        gpio_led0   =   {    .Pin       =    GPIO_PIN_4,
	                                             .Mode      =    GPIO_MODE_OUTPUT_PP,
	                                             .Pull      =    GPIO_NOPULL,
	                                             .Speed     =    GPIO_SPEED_FREQ_LOW };

	__HAL_RCC_GPIOA_CLK_ENABLE();

	HAL_GPIO_Init( GPIOA, &gpio_led0 );
}

/**
 * @brief LED1 pin initialization
 */
void	bsp_led1_init( void )
{
	GPIO_InitTypeDef        gpio_led1   =   {    .Pin       =    GPIO_PIN_3,
	                                             .Mode      =    GPIO_MODE_OUTPUT_PP,
	                                             .Pull      =    GPIO_NOPULL,
	                                             .Speed     =    GPIO_SPEED_FREQ_LOW };

	__HAL_RCC_GPIOA_CLK_ENABLE();

	HAL_GPIO_Init( GPIOA, &gpio_led1 );
}

/**
 * @brief LED2 pin initialization
 */
void	bsp_led2_init( void )
{
	GPIO_InitTypeDef        gpio_led2   =   {    .Pin       =    GPIO_PIN_2,
	                                             .Mode      =    GPIO_MODE_OUTPUT_PP,
	                                             .Pull      =    GPIO_NOPULL,
	                                             .Speed     =    GPIO_SPEED_FREQ_LOW };

	__HAL_RCC_GPIOA_CLK_ENABLE();

	HAL_GPIO_Init( GPIOA, &gpio_led2 );
}

/**
 * @brief LED0 pin get
 */
bool	bsp_led0_get( void )
{
	return( HAL_GPIO_ReadPin( GPIOA, GPIO_PIN_4) ? true : false );
}

/**
 * @brief LED1 pin get
 */
bool	bsp_led1_get( void )
{
	return( HAL_GPIO_ReadPin( GPIOA, GPIO_PIN_3) ? true : false );
}

/**
 * @brief LED2 pin get
 */
bool	bsp_led2_get( void )
{
	return( HAL_GPIO_ReadPin( GPIOA, GPIO_PIN_2) ? true : false );
}

/**
 * @brief LED0 pin set
 */
void	bsp_led0_set( bool val )
{
	HAL_GPIO_WritePin( GPIOA, GPIO_PIN_4, val ? GPIO_PIN_SET : GPIO_PIN_RESET );
}

/**
 * @brief LED1 pin set
 */
void	bsp_led1_set( bool val )
{
	HAL_GPIO_WritePin( GPIOA, GPIO_PIN_3, val ? GPIO_PIN_SET : GPIO_PIN_RESET );
}

/**
 * @brief LED2 pin set
 */
void	bsp_led2_set( bool val )
{
	HAL_GPIO_WritePin( GPIOA, GPIO_PIN_2, val ? GPIO_PIN_SET : GPIO_PIN_RESET );
}

/**
 * @brief LED0 pin toggle
 */
void	bsp_led0_toggle( void )
{
	HAL_GPIO_TogglePin( GPIOA, GPIO_PIN_4 );
}

/**
 * @brief LED1 pin toggle
 */
void	bsp_led1_toggle( void )
{
	HAL_GPIO_TogglePin( GPIOA, GPIO_PIN_3 );
}

/**
 * @brief LED2 pin toggle
 */
void	bsp_led2_toggle( void )
{
	HAL_GPIO_TogglePin( GPIOA, GPIO_PIN_2 );
}
