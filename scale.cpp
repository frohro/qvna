#include <QGraphicsScene>
#include <QPainter>
#include <QStyleOption>
#include <QDebug>
#include <QGraphicsSceneMouseEvent>
#include <math.h>
#include "config.h"
#include "scale.h"
#include "plot.h"

#define MIN(a,b)  a>b ? b:a


Scale::Scale(int x, int y,  QHash<QString, QColor> *c) {
    xSize = x; 
    ySize = y;
    points = x;
	colors = c;
	yScale = 10;
	mode = 0;

    fMin = 10000000;
    fMax = 20000000;

    xViewPos = 0;
    yViewPos = 0;
    this->setPos(QPoint(xViewPos,yViewPos));
    this->setAcceptHoverEvents(true);
	//svg = new QSvgRenderer();
	//qDebug() << svg->load(QString("smith.svg"));

}

Scale::~Scale() {
}


void Scale::setPoints(int p) {
    points = p;
	xSize = p;
    
    //xViewPos = 0;
    //yViewPos = 0;
    //this->setPos(QPoint(xViewPos,yViewPos));
}

void Scale::plotImagCircle(QPainter *p, double r, QString) {

	QRect rec;
	float rd=yScale*SMITH_SIZE;
	double w =  2*atan(rd/r)*360*16/(2*M_PI);

	rec = QRect(-xViewPos+2*rd-r,-yViewPos+rd,r*2,r*2);
	p->drawArc(rec,90*16, +w);
	rec = QRect(-xViewPos+2*rd-r,-yViewPos+rd,r*2,-r*2);
	p->drawArc(rec,270*16,-w);
}

void Scale::plotRealCircle(QPainter *p, double r, QString label) {
	QRect rec;
	float rd=yScale*SMITH_SIZE;
	rec = QRect(-xViewPos+2*rd-2*r,-yViewPos+rd-r,r*2,r*2);
	p->drawArc(rec,0, 360*16);
	p->drawText(-xViewPos+2*rd-2*r,-yViewPos+rd, label);
}

void Scale::paint (QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *) {

	if ((mode == MODE_TEXT) || (mode == MODE_TRANS_TEXT))
		return;

	painter->setPen((*colors)["Marker"]);
	painter->drawLine(markerPos-xViewPos, 0, markerPos-xViewPos, ySize);
	
	painter->setPen((*colors)["Label freq"]);

	int marker;
	int st = (fMax-fMin)/points*100;
	int step=1000; // min 1kHz
	while(step*10 < st) step*=10;
	while(step*5 < st) step*=5;
	while(step*2 < st) step*=2;

	int start = fMin - fMin % step ;
	for (marker = start; marker < fMax; marker += step) {
		int x = (long long int)(marker-fMin)*points/(fMax-fMin);
		painter->drawLine(x-xViewPos,0,x-xViewPos,20);
		painter->drawText(x-xViewPos+2,11,QString ("%1").arg(int((marker+500)/1000)));

	}

	if (mode == MODE_SMITH) {
		float rd=yScale*SMITH_SIZE;
		//svg->render(painter, QRect(0,0,rd*2, rd*2));
		dcomplex r,z,zl(1,0);
		painter->setPen((*colors)["Grid"]);

		QRectF rec(-xViewPos,-yViewPos,rd*2,rd*2);
		painter->drawArc(rec,0,360*16);

		painter->setPen((*colors)["Smith real"]);
		for (int re=0;re<=10;re++) {
			z = dcomplex(re,0);
			r = (zl-z)/(zl+z);
			plotRealCircle(painter,((1.0+real(r))*rd/2), QString("%1").arg(re));	
			z = dcomplex(((double)re)/10.0,0);
			r = (zl-z)/(zl+z);
			plotRealCircle(painter,((1.0+real(r))*rd/2), QString("%1").arg(re/10.0));	
		}
		painter->setPen((*colors)["Smith imag"]);
		painter->drawLine(-xViewPos,-yViewPos+rd, -xViewPos+2*rd, -yViewPos+rd);
		for (int im=-10;im<1 ;im++) {
			z = dcomplex(((double)im)/10.0,0);
			r = (zl-z)/(zl+z);
			plotImagCircle(painter,((1.0+real(r))*rd/2), QString("%1").arg(1+im/10.0));	
		}
		for (int im=0;im<10 ;im++) {
			z = dcomplex(im,0);
			r = (zl-z)/(zl+z);
			plotImagCircle(painter,((1.0+real(r))*rd/2), QString("%1").arg(im+1));	
		}
		return;
	}

	for (int i=0;i<=30;i+=1) {
		int y = i*yScale;
		painter->setPen((*colors)["Grid"]);
		painter->drawLine(0,y - yViewPos, xSize, y - yViewPos);
		if (i<xStrings1.size()) {
			painter->setPen((*colors)["Label real"]);
			painter->drawText(0,y - yViewPos, xStrings1.at(i));
		}
		if (i<xStrings2.size()) {
			painter->setPen((*colors)["Label imag"]);
			painter->drawText(60,y - yViewPos, xStrings2.at(i));
		}
	}
}

QRectF Scale::boundingRect() const {
    return QRectF(0, 0, xSize, ySize);
}

void Scale::setFreq(int from, int to) {
    fMin = from;
    fMax = to;
}

void Scale::setScale(int sc) {
	yScale = sc;
	update();
}

void Scale::mousePressEvent(QGraphicsSceneMouseEvent* /*event*/) {
	//markerPos = event->pos().x() + xViewPos;
	//emit markerChanged(markerPos);
}

void Scale::mouseMoveEvent(QGraphicsSceneMouseEvent *) {
}

void Scale::wheelEvent(QGraphicsSceneWheelEvent *) {
}

void Scale::hoverMoveEvent(QGraphicsSceneHoverEvent *event) {
	if ((mode == MODE_TEXT) || (mode == MODE_TRANS_TEXT))
		return;
	markerPos = event->pos().x() + xViewPos;
	emit markerChanged(markerPos);
	update();
}

void Scale::setMarker(int pos) {
	markerPos = pos;
	update();
}

void Scale::setViewPosX(int x) {
    xViewPos = x;
    this->setPos(QPoint(xViewPos,yViewPos));
}

void Scale::setViewPosY(int y) {
    yViewPos = y;
    this->setPos(QPoint(xViewPos,yViewPos));
}

void Scale::setMode(int m) {
	mode = m;
	xStrings1.clear();
	xStrings2.clear();
	if ((mode == MODE_TRANS) | (mode == MODE_RR_LOG) | (mode == MODE_CAL)) {
		for (int i=0;i<30;i++) 	
			xStrings1 += QString("%1 dB").arg((2-i)*5);
		for (int i=0;i<=360;i+=360/PHASE_SCALE) 	
			xStrings2 += QString("%1").arg(180-i);
	}
	if (mode == MODE_TRANS_LIN) {
		for (int i=0;i<=20;i++) 	
			xStrings1 += QString("%1").arg((20-i)/20.0);
		for (int i=0;i<=360;i+=360/PHASE_SCALE) 	
			xStrings2 += QString("%1").arg(180-i);
	}
	if (mode == MODE_Z) {
		for (int i=0;i<30;i++) 	
			xStrings1 += QString("%1 Ohm").arg(-(i-15)*10);
	}
	if (mode == MODE_R) {
		for (int i=0;i<=20;i++) 	
			xStrings1 += QString("%1").arg((10-i)/10.0);
	}
	if (mode == MODE_RR) {
		for (int i=0;i<=20;i++) 	
			xStrings1 += QString("%1").arg((20-i)/20.0);
		for (int i=0;i<=360;i+=360/PHASE_SCALE) 	
			xStrings2 += QString("%1").arg(180-i);
	}
	if (mode == MODE_SWR) {
		for (int i=0;i<20;i++) 	
			xStrings1 += QString("%1").arg((20-i));
	}
	update();
}
