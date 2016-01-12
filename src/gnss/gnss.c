/**
  * @file    gnss.c
  * @brief   GNSS service
  * @author  Igor T. <research.tahoe@gmail.com>
  */

#include	<stdio.h>
#include	<string.h>
#include	"bsp_gnss.h"
#include	"gnss.h"

/**
 * @brief GNSS initialization
 */
void	gnss_init( void )
{
	bsp_gnss_init();
}

/**
 * @brief GNSS control
 */
void gnss_set(                              bool                bval )
{
	bsp_gnss_power_enable( bval );
}

/**
 * @brief GNSS send
 */
void gnss_send(                             gnss_t *            gnss,
                                    const   char *              str )
{
	size_t          len;
	uint8_t         chksum;
	gnss_xfer_t *	xmit        =   &gnss->xmit;
	char *          xmit_buf    =   xmit->buf[ xmit->pingpong++ & 1 ];


	len	        =   nmea_chksum( &chksum, str, '\0' );
	xmit_buf[0]     =   '$';
	memcpy( &xmit_buf[1], str, len++ );
	xmit_buf[len++]   =   '*';
	sprintf( &xmit_buf[len], "%02X\r\n", chksum );
	len             +=  4;

	bsp_gnss_xmit( xmit_buf, len );

}

/**
 * @brief GNSS recieve char hook
 */
bool gnss_recv_hook(                        gnss_t *            gnss,
                                    const   char                c )
{
	bool            resp        =   false;
	gnss_xfer_t *	recv        =   &gnss->recv;
	char *          recv_buf    =   recv->buf[ recv->pingpong & 1 ];


	switch( c )
	{
		case    '\r':
			resp    =   nmea_recv(  &gnss->nmea, recv_buf );
			recv->pingpong++;
			break;

		case    '$':
			recv->len       =   0;
			break;

		default:
			if(recv->len < NMEA_STR_SIZE_MAX_OCT-1)
			{
				*(recv_buf + recv->len++)   =   c;
			}
			break;
	}

	return( resp );
}
