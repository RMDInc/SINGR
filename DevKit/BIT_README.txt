Project: SINGR
Date: 4/18/2019
includes: updated trigger module for more accurate total count
		  SPI
		  
Data Product:
			LPF:[LPF_HEADER,event_count,{TTL_in,TTLOn,TTLOff},i1,i2,i3,32'd7,32'd8]
			DFF:[DFF_HEADER,time,time_rollover,event_count,i1,i2,32'd7,32'd8]
			AA:	[AA_HEADER,total_count,event_count,i1,i2,i3,i4,32'd8]