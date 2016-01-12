/**
  * @file    app.h
  * @brief   App
  * @author  Igor T. <research.tahoe@gmail.com>
  */


#ifndef APP_H
#define APP_H

typedef	union	app_event_u
{
	uint16_t				whole;
	struct
	{
		bool            tick_1hz        :    1;
		bool            ui_key0         :    1;
		bool            ui_key1         :    1;
		bool            gnss            :    1;
		bool                            :    0;
	};
}	app_event_t;

typedef	struct	app_s
{
	app_event_t     evt;
	size_t          tick_1hz;

	#ifndef	NDEBUG
	size_t          ism_pckts_sent;
	size_t          tick_1hz_cnt;
	#endif

}	app_t;

#endif	//APP_H
