/**
  * @file    nmea.h
  * @brief   NMEA service
  * @author  Igor T. <research.tahoe@gmail.com>
  */

#ifndef  NMEA_H
#define  NMEA_H

#include	<stdbool.h>
#include	<stdint.h>
#include	<string.h>
#include	"config.h"

#define	NMEA_STR_SIZE_MAX_OCT           80

typedef	enum nmea_nsid_s
{
	NMEA_NSID_INVALID,
	NMEA_NSID_MULTI,
	NMEA_NSID_GPS,
	NMEA_NSID_GLONASS,
	NMEA_NSID_GALILEO,
} nmea_nsid_t;

typedef	enum nmea_fix_s
{
	NMEA_FIX_NONE           =   0,
	NMEA_FIX_2D             =   1,
	NMEA_FIX_3D             =   2,
	NMEA_FIX_RTK_INT        =   3,
	NMEA_FIX_RTK_FLT        =   4,
} nmea_fix_t;

typedef	struct	nmea_gsv_s
{
	size_t                  msgs_total;
	size_t                  msg_num;
	size_t                  sats_in_view;
	size_t                  sat_num;
	size_t                  elevation_deg;
	size_t                  azimuth_deg;
	size_t                  snr_db;
} nmea_gsv_t;

typedef	struct	nmea_gga_s
{
	uint32_t                timestamp;
	float                   latitude;
	float                   longitude;
	nmea_fix_t              fix;
	size_t                  sats_used;
	float                   hdop;
	float                   altitude;
	float                   geoidal_separation;
	float                   dgps_data_age_sec;
	size_t                  dgps_station_id;
} nmea_gga_t;

typedef	struct	nmea_s
{
	nmea_nsid_t             nsid;
	nmea_gga_t              gga;
	nmea_gsv_t              gsv;
} nmea_t;

void	nmea_init(     nmea_t * nmea );
bool	nmea_recv(     nmea_t * nmea, const char * str );
bool	nmea_recv_gga( nmea_t * nmea, const char * str );
bool	nmea_recv_gsa( nmea_t * nmea, const char * str );
bool	nmea_recv_gsv( nmea_t * nmea, const char * str );
bool	nmea_recv_rmc( nmea_t * nmea, const char * str );
size_t  nmea_chksum(   uint8_t * chksum, const char * str, char eol );

#endif	//GNSS_H
