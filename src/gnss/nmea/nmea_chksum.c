/**
  * @file    nmea_chcksum.c
  * @brief   NMEA checksum calc
  * @author  Igor T. <research.tahoe@gmail.com>
  */

#include	"nmea.h"

/**
  * @brief The checksum field consists of a "*" and two hex digits representing
  *        the exclusive OR of all characters between, but not including, the "$" and "*".
  *
  * @retval length of sentence, before '*' char
  */
size_t nmea_chksum(                         uint8_t *           chksum,
                                    const   char *              str,
                                            char                eol )
{
	size_t          len     =   0;


	*chksum =   0;

	while( *str != eol )
	{
		if( len++ < NMEA_STR_SIZE_MAX_OCT )
		{
			*chksum ^=  *str++;
		}
		else
		{
			break;
		}
	}

	return( len );
}
