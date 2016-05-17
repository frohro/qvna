#ifndef  HIQSDR_CTL_H
#define  HIQSDR_CTL_H

#include <QUdpSocket>
#include "config.h"

#define TX_OFF		0
#define TX_CW		1
#define TX_SSB		2
#define TX_VNA		4
#define USE_EXT_IO	4
#define TX_PTT		8


class HiqsdrCtl : public QObject {
	Q_OBJECT
	public:
		HiqsdrCtl(QString addr); 
		~HiqsdrCtl();
		void setRXFreq(int f);
		void setTXFreq(int f);
		int setSampleRate(int rate);
		void setPtt(bool on);
		void setTXLevel(int l);
		void setAnt(bool);
		void setPreamp(bool);
		void setAttenuator(int);
		void setVNACount(int n);
		int setVNA(int min, int max, int n);
		void resetVNA();
		int getFirmwareVersion();
	private slots:
		void readPending();

	private:
		void hiqSend();
		QString hostIP;
		QUdpSocket *udpSocket;
		unsigned char ctlBuf[22];
		int firmVersion;
};

#endif
