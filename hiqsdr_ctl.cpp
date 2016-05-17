#include "QDebug"
#include "hiqsdr_ctl.h"
#include "config.h"

HiqsdrCtl::HiqsdrCtl (QString host) {
	hostIP = host;
	firmVersion=1;
	memset(ctlBuf, 0, sizeof(ctlBuf));
	strncpy((char*)ctlBuf, "St", 2);
	ctlBuf[13]=firmVersion;

	// create socket
	udpSocket = new QUdpSocket(this);
	udpSocket->bind(HIQSDR_CTL_PORT);
	connect(udpSocket, SIGNAL(readyRead()), this, SLOT(readPending()));
	hiqSend();
}

HiqsdrCtl::~HiqsdrCtl() {

	udpSocket->close();
}

int HiqsdrCtl::getFirmwareVersion() {
	return firmVersion;
}

void HiqsdrCtl::hiqSend() {
	if (ctlBuf[13]>0)
		udpSocket->writeDatagram((const char*)ctlBuf, 22, QHostAddress(hostIP), HIQSDR_CTL_PORT);
	else
		udpSocket->writeDatagram((const char*)ctlBuf, 14, QHostAddress(hostIP), HIQSDR_CTL_PORT);
}

void HiqsdrCtl::setRXFreq(int f) {
	f = f % RX_CLOCK;
	if (f > RX_CLOCK/2)
		f = RX_CLOCK - f;

	unsigned int ph = ((int)((float)(f) / RX_CLOCK*0x100000000LL+0.5)) & 0xffffffff;

	ctlBuf[2] = (ph >> 0 ) & 0xff; 
	ctlBuf[3] = (ph >> 8 ) & 0xff; 
	ctlBuf[4] = (ph >> 16) & 0xff; 
	ctlBuf[5] = (ph >> 24) & 0xff; 

	hiqSend();
}

void HiqsdrCtl::setTXFreq(int f) {
	unsigned int ph = ((int)((float)(f) / RX_CLOCK*0x100000000LL+0.5)) & 0xffffffff;

	ctlBuf[6] = (ph >> 0 ) & 0xff; 
	ctlBuf[7] = (ph >> 8 ) & 0xff; 
	ctlBuf[8] = (ph >> 16) & 0xff; 
	ctlBuf[9] = (ph >> 24) & 0xff; 

	hiqSend();
}

int HiqsdrCtl::setSampleRate(int rate) {
	switch (rate) {
		case 48000:
		case 96000:
		case 192000:
		case 240000:
		case 384000:
		case 480000:
		case 960000:
			ctlBuf[12] = (RX_CLOCK / 64 / rate) - 1;
			hiqSend();
			return rate;
			break;
		default:
			return 0;
	}
}

void HiqsdrCtl::setPtt(bool on) {
	if (on) 
		ctlBuf[11] = TX_SSB | TX_PTT; 
	else
		ctlBuf[11] = 0;
	if (firmVersion>0) 
		ctlBuf[11] |= USE_EXT_IO; 
	hiqSend();
}

void HiqsdrCtl::setTXLevel(int l) {
	ctlBuf[10] = l;
	hiqSend();
}

void HiqsdrCtl::setAttenuator(int n) {
	ctlBuf[15]=0;
	if (n>0) 
		ctlBuf[15] = ((n/10)<<3) + (((n % 10)>>2)&7) ; 
	if (n==40)
		ctlBuf[15] = (((n-1)/10)<<3) + 5; 

	hiqSend();
}

void HiqsdrCtl::setPreamp(bool on) {

	ctlBuf[14] = 3;
	if (on)
		ctlBuf[14] |= HIQ_PREAMP; 
	else
		ctlBuf[14] &= ~HIQ_PREAMP; 
	hiqSend();
}

void HiqsdrCtl::setAnt(bool on) {
	if (on)
		ctlBuf[16] |= HIQ_ANT; 
	else
		ctlBuf[16] &= ~HIQ_ANT; 
	hiqSend();
}

void HiqsdrCtl::setVNACount(int n) {
	ctlBuf[18] = 0; 
	ctlBuf[19] = 0;
	ctlBuf[11] &= ~TX_PTT; 
	hiqSend();

	ctlBuf[18] = (n >> 0 ) & 0xff; 
	ctlBuf[19] = (n >> 8 ) & 0xff; 
	if (n>0) 
		ctlBuf[11] = TX_PTT; 
	else
		ctlBuf[11] = 0; 
	if (firmVersion>0) 
		ctlBuf[11] |= USE_EXT_IO; 
	hiqSend();
}

void HiqsdrCtl::resetVNA() {
	ctlBuf[18] = 0; 
	ctlBuf[19] = 0;
	ctlBuf[11] &= ~TX_PTT; 
	hiqSend();
}

int HiqsdrCtl::setVNA(int fmin, int fmax, int n) {
	if (fmax<fmin) 
		return -1;
	int dx = ((fmax-fmin)+n/2)/n;

	setRXFreq(fmin);
	setTXFreq(dx);
	setSampleRate(960000);

	ctlBuf[11] &= ~(TX_CW | TX_SSB); 
	ctlBuf[11] |= TX_PTT | USE_EXT_IO; 

	ctlBuf[18] = (n >> 0 ) & 0xff; 
	ctlBuf[19] = (n >> 8 ) & 0xff; 

	hiqSend();
	return fmin+dx*n;
}

void HiqsdrCtl::readPending() {
	QByteArray datagram;
	QHostAddress sender;
	quint16 senderPort;

	while (udpSocket->hasPendingDatagrams()>0) {
		datagram.resize(udpSocket->pendingDatagramSize());
		int ret = udpSocket->readDatagram(datagram.data(), datagram.size(), &sender, &senderPort);
		if (ret>12)
			firmVersion = *(char*)(datagram.data()+13);
	}
	ctlBuf[13] = firmVersion; 
	if (firmVersion>0) 
		ctlBuf[11] |= USE_EXT_IO; 
}
