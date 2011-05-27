#ifndef ECUCONSTANTS
#define ECUCONSTANTS

// OBD1 - These adresses are for Crome <= 1.2 dataloger plugin
#define ECT_CROME12     0x10
#define IAT_CROME12     0x11
#define O2_CROME12      0x12
#define BARO_CROME12    0x13
#define MAP_CROME12     0x14
#define TPS_CROME12     0x15
#define RPMLOW_CROME12  0x16
#define RPMHIGH_CROME12 0x17
#define LOCAM_CROME12   0x19
#define HICAM_CROME12   0x1A
#define COL_CROME12     0x1B
#define VSS_CROME12     0x20
#define VTEC_CROME12    0x18
#define IGN_CROME12     0x23
#define INJLOW_CROME12  0x21
#define INJHIGH_CROME12 0x08
#define KNOCK_CROME12   0x24
#define CRANK_CROME12   0x25

// OBD1 - These adresses are for Crome >= 1.4 dataloger plugin aka QD2
#define ECT_CROME14     0x1D
#define IAT_CROME14     0x1B
#define O2_CROME14      0x20
#define BARO_CROME14    0x1E
#define MAP_CROME14     0x14
#define TPS_CROME14     0x15
#define RPMLOW_CROME14  0x10
#define RPMHIGH_CROME14 0x11
#define LOCAM_CROME14   0x12
#define HICAM_CROME14   0x13
#define COL_CROME14     0x16
#define VSS_CROME14     0x1C
#define VTEC_CROME14    0x22
#define IGN_CROME14     0x19
#define INJLOW_CROME14  0x17
#define INJHIGH_CROME14 0x18
#define KNOCK_CROME14   0x1A
//#define CRANK_CROME14   0x00
#define BATT_CROME14    0x22

// OBD0 - These adresses are for NG60 maps
#define ECT_NG60     0x30
#define IAT_NG60     0x32
#define O2_NG60      0xFB
#define BARO_NG60    0x34
#define MAP_NG60     0x36
#define TPS_NG60     0x39
#define RPMLOW_NG60  0xFA
#define RPMHIGH_NG60 0x17
#define LOCAM_NG60   0xFE
//#define HICAM_NG60   0x00
#define COL_NG60     0xFD
#define VSS_NG60     0x6C
#define VTEC_NG60    0x18
//#define IGN_NG60     0x00
//#define INJLOW_NG60  0x00
//#define INJHIGH_NG60 0x00
//#define KNOCK_NG60   0x00
//#define CRANK_NG60   0x00
//#define BATT_NG60    0x00

// OBD0
#define ECT_PMx 0x30
#define IAT_PMx 0x32
#define O2_PMx 0xFB
#define BARO_PMx 0x34
#define MAP_PMx  0xF8
#define TPS_PMx  0x39
#define RPMLOW_PMx  0x48
#define RPMHIGH_PMx 0xFA
#define ROW_PMx 0xFE
#define COL_PMx 0xFD
#define VSS_PMx 0x6C

#define ECT_IDX     0
#define IAT_IDX     1
#define O2_IDX      2
#define BARO_IDX    3
#define MAP_IDX     4
#define TPS_IDX     5
#define RPMLOW_IDX  6
#define RPMHIGH_IDX 7
#define LOCAM_IDX   8
#define HICAM_IDX   9
#define COL_IDX     10
#define VSS_IDX     11
#define VTEC_IDX    12
#define IGN_IDX	    13
#define INJLOW_IDX  14
#define INJHIGH_IDX 15
#define KNOCK_IDX   16
#define CRANK_IDX   17


#define  NO_MODE_SELECTED 0
#define  PR3 1
#define  PMx 2
#define  CROME12 3
#define  CROME14 4
#define  NG60 5

static int NG60_ARRAY[] = {
			   ECT_NG60,
			   IAT_NG60,
			   O2_NG60,
			   BARO_NG60,
			   MAP_NG60,
			   TPS_NG60,
			   RPMLOW_NG60,
			   RPMHIGH_NG60,
			   LOCAM_NG60,
			   0x00, /* doesn't exist*/
			   COL_NG60,
			   VSS_NG60,
			   VTEC_NG60,
			   0x00, /* doesn't exist*/
			   0x00, /* doesn't exist*/
			   0x00, /* doesn't exist*/
			   0x00, /* doesn't exist*/
			   0x00, /* doesn't exist*/
			   };


static int PMx_ARRAY[] = {
			   ECT_PMx,
			   IAT_PMx,
			   O2_PMx,
			   BARO_PMx,
			   MAP_PMx,
			   TPS_PMx,
			   RPMLOW_PMx,
			   RPMHIGH_PMx,
			   0x00, /* doesn't exist*/
			   ROW_PMx,
			   COL_PMx,
			   VSS_PMx,
			   0x00, /* doesn't exist*/
			   0x00, /* doesn't exist*/
			   0x00, /* doesn't exist*/
			   0x00, /* doesn't exist*/
			   0x00, /* doesn't exist*/
			   0x00, /* doesn't exist*/
			   };

static int CROME12_ARRAY[] = {
	                   ECT_CROME12,
	                   IAT_CROME12,
			   O2_CROME12,
			   BARO_CROME12,
			   MAP_CROME12,
			   TPS_CROME12,
			   RPMLOW_CROME12,
			   RPMHIGH_CROME12,
			   LOCAM_CROME12,
			   HICAM_CROME12,
			   COL_CROME12,
			   VSS_CROME12,
			   VTEC_CROME12,
			   IGN_CROME12,
			   INJLOW_CROME12,
			   INJHIGH_CROME12,
			   KNOCK_CROME12,
			   CRANK_CROME12
			   };

static int CROME14_ARRAY[] = {
	                   ECT_CROME14,
	                   IAT_CROME14,
			   O2_CROME14,
			   BARO_CROME14,
			   MAP_CROME14,
			   TPS_CROME14,
			   RPMLOW_CROME14,
			   RPMHIGH_CROME14,
			   LOCAM_CROME14,
			   HICAM_CROME14,
			   COL_CROME14,
			   VSS_CROME14,
			   VTEC_CROME14,
			   IGN_CROME14,
			   INJLOW_CROME14,
			   INJHIGH_CROME14,
			   KNOCK_CROME14,
			   0x00 /* doesn't exist*/
			   };
#endif

