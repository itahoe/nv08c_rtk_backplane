/**
  * @file    nmea_recv.c
  * @brief   NMEA recieve service
  * @author  Igor T. <research.tahoe@gmail.com>
  */

#include	<stdio.h>
#include	"nmea.h"

/**
 * @brief NMEA sentence recieve
 */
bool nmea_recv(                             nmea_t *            nmea,
                                    const   char *              str )
{
	bool            resp    =   false;
	uint8_t         chksum;
	int             est;
	size_t          len;


	len             =   nmea_chksum( &chksum, str, '*' );
	len++;
	sscanf( str + len, "*%02X", &est );

	if(  chksum != (uint8_t) est )
	{
		return( resp );
	}

	if(         str[0] == 'G' ) //sentence type: general
	{
		switch( str[1] )
		{
			case 'A':       nmea->nsid  =   NMEA_NSID_GALILEO;      break;
			case 'L':       nmea->nsid  =   NMEA_NSID_GLONASS;      break;
			case 'P':       nmea->nsid  =   NMEA_NSID_GPS;          break;
			case 'N':       nmea->nsid  =   NMEA_NSID_MULTI;        break;
			default:        nmea->nsid  =   NMEA_NSID_INVALID;      break;
		}

		if(         strncmp( &str[2], "GGA", 3) == 0 )
		{
			resp    =   nmea_recv_gga( nmea, &str[5] );
		}
		else if(    strncmp( &str[2], "GSA", 3) == 0 )
		{
			resp    =   nmea_recv_gsa( nmea, &str[5] );
		}
		else if(    strncmp( &str[2], "GSV", 3) == 0 )
		{
			resp    =   nmea_recv_gsv( nmea, &str[5] );
		}
		else if(    strncmp( &str[2], "RMC", 3) == 0 )
		{
			resp    =   nmea_recv_rmc( nmea, &str[5] );
		}
		else
		{
			resp    =   true;
		}

	}
	else if(    str[0] == 'P' ) //sentence type: proprietary
	{
		resp    =   true;
	}
	else                        //sentence type: unsupported
	{
	}


	return( resp );
}
