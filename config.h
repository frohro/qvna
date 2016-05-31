#ifndef __CONFIG_H__
#define __CONFIG_H__

#include <iostream>
#include <complex>
using namespace std;

typedef complex<double> dcomplex;

#define VERSION        "0.9.3"

#define HIQIP			"192.168.2.196"

#define MODE_TRANSMISSION	0
#define MODE_REFLECTION		1
#define MODE_CAL_THROUGH	2
#define MODE_CAL_OPEN		3
#define MODE_CAL_MATCH		4
#define MODE_CAL_SHORT		5

#define VNA_TYPE_HIQSDR     0
#define VNA_TYPE_SERIAL     1

#define MAX_SAMPLE_SIZE	(32*1024)
#define CAL_POINTS		1000

#define RX_CLOCK	122880000LL
#define CAL_F_MIN	0
#define CAL_F_MAX	(RX_CLOCK/2)

#define HIQSDR_RX_PORT		0xbc77
#define HIQSDR_CTL_PORT		0xbc78
#define HIQSDR_TX_PORT		0xbc79
#define HIQSDR_RAW_PORT		0xbc7a

#define HIQSCOPE_RAW_PORT	22222


#define HIQ_PREAMP		0x10
#define HIQ_ANT			0x01

#define Y_SIZE			1000
#define PHASE_SCALE		20		// 10 Scalenteile

#define MAX_RANGE		11

#define SMITH_SIZE		10

#define MODE_CAL		0
#define MODE_TRANS		1
#define MODE_TRANS_LIN	2
#define MODE_TRANS_TEXT	3
#define MODE_Z			4
#define MODE_R			5
#define MODE_RR			6
#define MODE_RR_LOG		7
#define MODE_SWR		8
#define MODE_SMITH		9
#define MODE_TEXT		10

#endif
