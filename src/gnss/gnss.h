/**
  * @file    gnss.h
  * @brief   GNSS service
  * @author  Igor T. <research.tahoe@gmail.com>
  */

#ifndef  GNSS_H
#define  GNSS_H

#include	"nmea.h"
#include	"config.h"


typedef	struct	gnss_xfer_s
{
	size_t                  len;
	size_t                  pingpong;
	char                    buf[2][ NMEA_STR_SIZE_MAX_OCT ];
} gnss_xfer_t;

typedef	struct	gnss_s
{
	nmea_t                  nmea;
	gnss_xfer_t             recv;
	gnss_xfer_t             xmit;
} gnss_t;


void	gnss_init( void );

void	gnss_set(                       bool                    bval );

void	gnss_send(                      gnss_t *                gnss,
	                        const   char *                  str );

bool	gnss_recv_hook(                 gnss_t *                gnss,
	                        const   char                    c );

#endif	//GNSS_H
