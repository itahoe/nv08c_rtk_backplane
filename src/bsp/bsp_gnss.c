/**
  * @file    bsp_gnss.c
  * @brief   Board Support Package - GNSS service
  * @author  Igor T. <research.tahoe@gmail.com>
  */

#include	<string.h>
#include	"bsp_gnss.h"
#include	"bsp.h"
#include	"config.h"

static
int     bsp_gnss_init_uart( void )
{
	UART_HandleTypeDef      uart    =   {   .Instance           =   USART1,
	                                        .Init.BaudRate      =   CFG_GNSS_NMEA_UART_BAUDRATE,
	                                        .Init.WordLength    =   UART_WORDLENGTH_8B,
	                                        .Init.StopBits      =   UART_STOPBITS_1,
	                                        .Init.Parity        =   UART_PARITY_NONE,
	                                        .Init.HwFlowCtl     =   UART_HWCONTROL_NONE,
	                                        .Init.Mode          =   UART_MODE_TX_RX };

	int                     resp    =   0;


	__HAL_RCC_USART1_FORCE_RESET();
	__HAL_RCC_USART1_RELEASE_RESET();
	__HAL_RCC_USART1_CLK_ENABLE();

	if( HAL_UART_Init( &uart ) != HAL_OK )
	{
		resp    =   -1;
	}
  
	return( resp );
}

static
void	bsp_gnss_init_uart_io( void )
{
	GPIO_InitTypeDef        gpio_rx     =   {    .Pin       =    GPIO_PIN_7,
	                                             .Mode      =    GPIO_MODE_INPUT,
	                                             .Pull      =    GPIO_NOPULL,
	                                             .Speed     =    GPIO_SPEED_FREQ_LOW };

	GPIO_InitTypeDef        gpio_tx     =   {    .Pin       =    GPIO_PIN_6,
	                                             .Mode      =    GPIO_MODE_AF_PP,
	                                             .Pull      =    GPIO_PULLUP,
	                                             .Speed     =    GPIO_SPEED_FREQ_LOW };

	__HAL_RCC_AFIO_CLK_ENABLE();
	__HAL_RCC_GPIOB_CLK_ENABLE();

	HAL_GPIO_Init( GPIOB, &gpio_rx );
	HAL_GPIO_Init( GPIOB, &gpio_tx );

	__HAL_AFIO_REMAP_USART1_ENABLE();
}

static
void	bsp_gnss_init_power( void )
{
	GPIO_InitTypeDef        gpio_pwr    =   {    .Pin       =    GPIO_PIN_9,
	                                             .Mode      =    GPIO_MODE_OUTPUT_PP,
	                                             .Pull      =    GPIO_NOPULL,
	                                             .Speed     =    GPIO_SPEED_FREQ_LOW };

	__HAL_RCC_GPIOB_CLK_ENABLE();

	HAL_GPIO_Init( GPIOB, &gpio_pwr );
}

/**
 * @brief BSP GNSS initialization
 */
void	bsp_gnss_init( void )
{
	bsp_gnss_init_power();
	bsp_gnss_init_uart();
	bsp_gnss_init_uart_io();

	USART1->CR1     |=  USART_CR1_RXNEIE;
	HAL_NVIC_SetPriority( USART1_IRQn, 0, 1 );
	HAL_NVIC_EnableIRQ( USART1_IRQn );

}

/**
 * @brief BSP GNSS power pin control
 */
void	bsp_gnss_power_enable( bool bval )
{
	HAL_GPIO_WritePin( GPIOB, GPIO_PIN_9, bval ? GPIO_PIN_SET : GPIO_PIN_RESET );
}

/**
 * @brief BSP GNSS xmit block
 */
void	bsp_gnss_xmit( const char * p, size_t len )
{
	while( len-- )
	{
		while( !(USART1->SR & UART_FLAG_TXE) );
		USART1->DR      =   *p++;
	}
}
