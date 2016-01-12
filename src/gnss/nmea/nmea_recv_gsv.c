/**
  * @file    nmea_recv_gsv.c
  * @brief   NMEA GSV sentence recieve
  * @author  Igor T. <research.tahoe@gmail.com>
  */

#include	<stdlib.h>
#include	"nmea.h"

/**
 * @brief Satellites in view
 */
bool nmea_recv_gsv(                         nmea_t *            nmea,
                                    const   char *              str )

{
	bool            resp    =   true;
	size_t          msg_num;
	nmea_gsv_t *    gsv     =   &nmea->gsv;

	while( *str++ != ',' );

	gsv->msgs_total         =   atoi( str );

	while( *str++ != ',' );

	msg_num                 =   atoi( str );

	while( *str++ != ',' );

	gsv->sats_in_view       =   atoi( str );

	for( size_t i = 0; i < msg_num; i++ )
	{
	}


	return( resp );
}
