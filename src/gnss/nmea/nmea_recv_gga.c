/**
  * @file    nmea_recv_gga.c
  * @brief   NMEA GGA sentence recieve
  * @author  Igor T. <research.tahoe@gmail.com>
  */

#include	<stdlib.h>
#include	"nmea.h"

/**
 * @brief Global Positioning System Fix Data. Time, Position and fix related data for a GPS receiver
 */
bool nmea_recv_gga(                         nmea_t *            nmea,
                                    const   char *              str )
{
	bool            resp    =   true;


	while( *str++ != ',' );

	nmea->gga.timestamp	=   atoi( str );

	while( *str++ != ',' );

	nmea->gga.latitude	=   atof( str );

	while( *str++ != ',' );

	if( *str++ == 'S')
	{
		nmea->gga.latitude	=   -( nmea->gga.latitude );
	}

	while( *str++ != ',' );

	nmea->gga.longitude     =   atof( str );

	while( *str++ != ',' );

	if( *str++ == 'W')
	{
		nmea->gga.longitude     =   -( nmea->gga.longitude );
	}

	while( *str++ != ',' );

	switch( atoi( str ) )
	{
		case 0:     nmea->gga.fix       =   NMEA_FIX_NONE;          break;
		case 1:     nmea->gga.fix       =   NMEA_FIX_2D;            break;
		case 2:     nmea->gga.fix       =   NMEA_FIX_3D;            break;
		case 3:     nmea->gga.fix       =   NMEA_FIX_RTK_INT;       break;
		case 4:     nmea->gga.fix       =   NMEA_FIX_RTK_FLT;       break;
		default:                                                    break;
	}

	while( *str++ != ',' );

	nmea->gga.sats_used             =   atoi( str );

	while( *str++ != ',' );

	nmea->gga.hdop                  =   atof( str );

	while( *str++ != ',' );

	nmea->gga.altitude              =   atof( str );

	while( *str++ != ',' );

	while( *str++ != ',' );	//skip next field, it's always 'M'

	nmea->gga.geoidal_separation    =   atof( str );

	while( *str++ != ',' );

	while( *str++ != ',' );	//skip next field, it's always 'M'

	nmea->gga.dgps_data_age_sec     =   atof( str );

	while( *str++ != ',' );

	nmea->gga.dgps_data_age_sec     =   atof( str );


	return( resp );
}
