#include "plot.h"

#include <QGraphicsScene>
#include <QPainter>
#include <QStyleOption>
#include <QDebug>
#include <QGraphicsSceneMouseEvent>
#include <math.h>
#include <stdlib.h>
#include "lib.h"

using namespace std;

Plot::Plot(int x, int y, double *re, double *im, dcomplex *f11, dcomplex *f21, dcomplex *f22, QHash<QString, QColor> *c) {
	xSize = x; 
	ySize = y;
	points = x;
	reData = re;
	imData = im;
	s11 = f11;
	s21 = f21;
	s22 = f22;
    colors = c; 
	yScale = 10;
	mode = 0;
	plotPixmap = new QPixmap(xSize, ySize);
	plotPixmap->fill(Qt::white);
	markerPos = 0;
	fMin = 0;
	fMax = RX_CLOCK/2;
	textSpace = 5;
}

Plot::~Plot() {
}

void Plot::setMarkerPos(int p) {
	markerPos = p;
	plot();
}


void Plot::paint (QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *) {
	painter->drawPixmap(0,0,*plotPixmap);
}

void Plot::setPoints(int n) {
	xSize = n;
	points = n;
	delete plotPixmap;
	plotPixmap = new QPixmap(xSize, ySize);
	plotPixmap->fill(Qt::white);
}

QRectF Plot::boundingRect() const {
	return QRectF(0, 0, xSize, ySize);
}


void Plot::setMode(int m) {
	mode = m;
	plot();
}

void Plot::setScale(int sc) {
	yScale = sc;
	plot();
}

dcomplex Plot::getInterpolation(dcomplex* data, double freq) {
	double fx,mod;
	int imod;

	fx = freq*1e6*CAL_POINTS/CAL_F_MAX;
	fx = modf(fx, &mod);
	imod = (int)mod;
	return data[imod] + (data[imod+1]-data[imod])*fx;
}

void Plot::setFreq(double min, double max) {
	fMin = min;
	fMax = max;
}

void Plot::plot() {
	int i,y;
	dcomplex r,u,s;
	dcomplex z,zl(50,0);
	dcomplex f11,f21,f22;
	dcomplex rm;
	double freq;
	int lx=0,ly=0;
//	bool ontx;
//	double l,c;
//	QString lUnit, cUnit;
//	double scale;
// int pa;
	int sp1,sp2;

	sp1 = yScale*0+2;
	sp2 = yScale*5;

	QPainter painter(plotPixmap);
	QPen pen;
	pen.setWidth(2);
	painter.setPen(pen);
	switch (mode) {
		case MODE_CAL:
			plotPixmap->fill((*colors)["Background"]);
			pen.setColor((*colors)["Line real"]);
			painter.setPen(pen);
			for(i=1; i < points; i++) 
				painter.drawLine(i-1,-log10(reData[i-1])*20*yScale/5  + yScale*2,i,-log10(reData[i])*20*yScale/5  + yScale*2);
			pen.setColor((*colors)["Line imag"]);
			painter.setPen(pen);
			for(i=1; i < points; i++) 
				if (abs(imData[i-1]-imData[i])<M_PI) 
					painter.drawLine(i-1,-imData[i-1]/M_PI*yScale*PHASE_SCALE/2+yScale*PHASE_SCALE/2,i,-imData[i]/M_PI*yScale*PHASE_SCALE/2+yScale*PHASE_SCALE/2);
			break;
		case MODE_TRANS:
			plotPixmap->fill((*colors)["Background"]);
			pen.setColor((*colors)["Line real"]);
			painter.setPen(pen);
			for(i=1; i < points; i++) 
				painter.drawLine(i-1,-log10(reData[i-1])*20*yScale/5  + yScale*2,i,-log10(reData[i])*20*yScale/5  + yScale*2);
			pen.setColor((*colors)["Line imag"]);
			painter.setPen(pen);
			for(i=1; i < points; i++) 
				if (abs(imData[i-1]-imData[i])<M_PI) 
					painter.drawLine(i-1,-imData[i-1]/M_PI*yScale*PHASE_SCALE/2+yScale*PHASE_SCALE/2,i,-imData[i]/M_PI*yScale*PHASE_SCALE/2+yScale*PHASE_SCALE/2);
			break;
		case MODE_TRANS_LIN:
			plotPixmap->fill((*colors)["Background"]);
			pen.setColor((*colors)["Line real"]);
			painter.setPen(pen);
			for(i=1; i < points; i++) 
				painter.drawLine(i-1,20*yScale-(reData[i-1])*yScale*20, i,20*yScale-(reData[i])*yScale*20);

			pen.setColor((*colors)["Line imag"]);
			painter.setPen(pen);
			for(i=1; i < points; i++) 
				if (abs(imData[i-1]-imData[i])<M_PI) 
					painter.drawLine(i-1,-imData[i-1]/M_PI*yScale*PHASE_SCALE/2+yScale*PHASE_SCALE/2,i,-imData[i]/M_PI*yScale*PHASE_SCALE/2+yScale*PHASE_SCALE/2);


			break;
		case MODE_TRANS_TEXT:
			plotPixmap->fill((*colors)["Background"]);
			pen.setColor((*colors)["Text"]);
			painter.setPen(pen);
			painter.setFont(QFont("Arial", yScale));

			y = yScale + textSpace;
			freq = fMin + markerPos*(fMax-fMin)/points;
			painter.drawText(sp1,y, QString("Freq:"));
			painter.drawText(sp2,y, QString("%1Hz").arg(engOut(freq*1e6, 4)));

			y += yScale + textSpace;
			painter.drawText(sp1,y, QString("s21 (x,y)"));
			painter.drawText(sp2,y, QString("(%1, %2)").arg(engOut(reData[markerPos],3)).arg(engOut(imData[markerPos],3)));

			y += yScale + textSpace;
			painter.drawText(0,y, QString("abs(s21)"));
			painter.drawText(sp2,y, QString("%1 dB").arg(engOut(log10(reData[markerPos])*20,3)));
			break;

		case MODE_Z:
		case MODE_R:
		case MODE_RR:
		case MODE_RR_LOG:
		case MODE_SWR:
		case MODE_SMITH:
		case MODE_TEXT:
			for(i=0; i < points; i++) {
				freq = fMin + i*(fMax-fMin)/points;

				u = polar(reData[i],imData[i]);
				z = (1.0+u)/(1.0-u)*zl;
				rm = (z-zl)/(z+zl);

				// rm: gemessener Reflektionsfaktor
				// r : korrigierter Reflektionsfaktor

				f11 = getInterpolation(s11, freq);
				f21 = getInterpolation(s21, freq);
				f22 = getInterpolation(s22, freq);

				r = (rm-f11)/(f22*(rm-f11)+f21);
				rc[i] = r;
				zc[i] = (1.0+r)/(1.0-r)*zl;
				sc[i] = (1.0+abs(r))/(1.0-abs(r));
				if (real(sc[i])<0)
					sc[i]=dcomplex(100,0);
				if (real(sc[i])>100)
					sc[i]=dcomplex(100,0);

			}
			plotPixmap->fill((*colors)["Background"]);
			switch (mode) {
				case MODE_Z:
					pen.setColor((*colors)["Line real"]);
					painter.setPen(pen);
					for(i=1; i < points; i++)
						painter.drawLine(i-1,-real(zc[i-1])/10*yScale+15*yScale,i,-real(zc[i])/10*yScale+15*yScale);

					pen.setColor((*colors)["Line imag"]);
					painter.setPen(pen);
					for(i=1; i < points; i++)
						painter.drawLine(i-1,-imag(zc[i-1])/10*yScale+15*yScale,i,-imag(zc[i])/10*yScale+15*yScale);
					break;

				case MODE_R:
					pen.setColor((*colors)["Line real"]);
					painter.setPen(pen);
					for(i=1; i < points; i++)
						painter.drawLine(i-1,10*yScale-real(rc[i-1])*10*yScale,i,10*yScale-real(rc[i])*10*yScale);

					pen.setColor((*colors)["Line imag"]);
					painter.setPen(pen);
					for(i=1; i < points; i++)
						painter.drawLine(i-1,10*yScale-imag(rc[i-1])*10*yScale,i,10*yScale-imag(rc[i])*10*yScale);
					break;
				case MODE_RR:
					pen.setColor((*colors)["Line real"]);
					painter.setPen(pen);
					for(i=1; i < points; i++)
						painter.drawLine(i-1,20*yScale-abs(rc[i-1])*20*yScale,i,20*yScale-abs(rc[i])*20*yScale);

					pen.setColor((*colors)["Line imag"]);
					painter.setPen(pen);
					for(i=1; i < points; i++)
						if (abs(arg(rc[i-1])-arg(rc[i]))<M_PI) 
							painter.drawLine(i-1,-arg(rc[i-1])/M_PI*yScale*PHASE_SCALE/2+yScale*PHASE_SCALE/2,i,-arg(rc[i])/M_PI*yScale*PHASE_SCALE/2+yScale*PHASE_SCALE/2);
					break;
				case MODE_RR_LOG:
					pen.setColor((*colors)["Line real"]);
					painter.setPen(pen);
					for(i=1; i < points; i++)
						painter.drawLine(i-1,-log10(abs(rc[i-1]))*20*yScale/5  + yScale*2,i,-log10(abs(rc[i]))*20*yScale/5  + yScale*2);

					pen.setColor((*colors)["Line imag"]);
					painter.setPen(pen);
					for(i=1; i < points; i++)
						if (abs(arg(rc[i-1])-arg(rc[i]))<M_PI) 
							painter.drawLine(i-1,-arg(rc[i-1])/M_PI*yScale*PHASE_SCALE/2+yScale*PHASE_SCALE/2,i,-arg(rc[i])/M_PI*yScale*PHASE_SCALE/2+yScale*PHASE_SCALE/2);
					break;
				case MODE_SWR:
					pen.setColor((*colors)["Line real"]);
					painter.setPen(pen);
					for(i=1; i < points; i++)
						painter.drawLine(i-1,20*yScale-real(sc[i-1])*yScale,i,20*yScale-real(sc[i])*yScale);
					break;
				case MODE_SMITH:
					// smith
					pen.setColor((*colors)["Line real"]);
					painter.setPen(pen);
					for(i=0; i < points; i++) {
						int x = real(rc[i])*yScale*SMITH_SIZE+yScale*SMITH_SIZE;
						int y = -imag(rc[i])  *yScale*SMITH_SIZE+yScale*SMITH_SIZE;
						if (i>0) {
							if (abs(x-lx)<yScale*SMITH_SIZE/2 && abs(ly-y)<yScale*SMITH_SIZE/2)
								painter.drawLine(lx,ly,x,y);
							else
								painter.drawPoint(x,y);
						}
						lx = x;
						ly = y;
					}
					pen.setColor((*colors)["Marker"]);
					painter.setPen(pen);
					painter.drawPoint(real(rc[markerPos])*yScale*SMITH_SIZE+yScale*SMITH_SIZE,-imag(rc[markerPos])  *yScale*SMITH_SIZE+yScale*SMITH_SIZE);
					painter.drawRect( real(rc[markerPos])*yScale*SMITH_SIZE+yScale*SMITH_SIZE-5,-imag(rc[markerPos])  *yScale*SMITH_SIZE+yScale*SMITH_SIZE-5, 10, 10);
					break;
				case MODE_TEXT:
					pen.setColor((*colors)["Text"]);
					painter.setPen(pen);
					painter.setFont(QFont("Arial", yScale));

					y = yScale + textSpace;
					freq = fMin + markerPos*(fMax-fMin)/points;
					painter.drawText(sp1,y, QString("Freq:"));
					painter.drawText(sp2,y, QString("%1Hz").arg(engOut(freq*1e6, 4)));

					y += yScale + textSpace;
					painter.drawText(sp1,y, QString("Z:"));
					painter.drawText(sp2,y, QString("(%1, %2)").arg(engOut(real(zc[markerPos]),3)).arg(engOut(imag(zc[markerPos]),3)));
/*
					y += yScale + textSpace;
					if (imag(zc[markerPos])>0)
						painter.drawText(0,y, QString(" -> L: : %1H").arg(engOut(imag(zc[markerPos])/(2.0*M_PI*freq*1e6),3)));
					if (imag(zc[markerPos])<0)
						painter.drawText(0,y, QString(" -> C: : %1F").arg(engOut(1.0/(-imag(zc[markerPos])*2.0*M_PI*freq*1e6),3)));
*/
					y += yScale + textSpace;
					painter.drawText(sp1,y, QString("r(x,y):"));
					painter.drawText(sp2,y, QString("(%1, %2)").arg(engOut(real(rc[markerPos]),3)).arg(engOut(imag(rc[markerPos]),3)));

					y += yScale + textSpace;
					painter.drawText(sp1,y, QString("r(r,phi):"));
					painter.drawText(sp2,y, QString("(%1, %2)").arg(engOut(abs(rc[markerPos]),3)).arg(engOut(arg(rc[markerPos]),3)));

					y += yScale + textSpace;
					painter.drawText(sp1,y, QString("abs(r):"));
					painter.drawText(sp2,y, QString("%1 dB").arg(log10(abs(rc[markerPos]))*20));

					y += yScale + textSpace;
					painter.drawText(sp1,y, QString("swr:"));
					painter.drawText(sp2,y, QString("%1").arg(engOut(real(sc[markerPos]),3)));

#if 0
					y += yScale*2 + textSpace;
					painter.drawText(0,y, QString("LC match:"));
					y += yScale + textSpace;

					scale = (double)yScale/10;
					painter.setFont(QFont("Arial", scale*8));

					zCompensation(zc[markerPos], 50, freq*1e6, true, l, c, ontx);
					lUnit = "H"; cUnit = "F";
					if (l<0) { l = -l; lUnit = "F"; }
					if (c<0) { c = -c; cUnit = "H"; }
					
					ontx ?  pa = scale*10 : pa = scale*70;

					painter.drawLine(0,y,scale*20,y);
					painter.drawLine(scale*60,y,scale*80,y);
					painter.drawLine(pa,y,pa,y+scale*10);
					painter.drawLine(pa,y+scale*30,pa,y+scale*40);
					painter.drawLine(0,y+scale*40,scale*80,y+scale*40);
					painter.drawText(22*scale,y+scale*2, QString("%1%2").arg(engOut(l,3)).arg(lUnit));
					painter.drawText(pa-5*scale, y+22*scale, QString("%1%2").arg(engOut(c,3)).arg(cUnit));

					y += yScale*5;
					zCompensation(zc[markerPos], 50, freq*1e6, false, l, c, ontx);
					lUnit = "H"; cUnit = "F";
					if (l<0) { l = -l; lUnit = "F"; }
					if (c<0) { c = -c; cUnit = "H"; }

					ontx ?  pa = scale*10 : pa = scale*70;

					painter.drawLine(0,y,scale*20,y);
					painter.drawLine(scale*60,y,scale*80,y);
					painter.drawLine(pa,y,pa,y+scale*10);
					painter.drawLine(pa,y+scale*30,pa,y+scale*40);
					painter.drawLine(0,y+scale*40,scale*80,y+scale*40);
					painter.drawText(22*scale,y+scale*2, QString("%1%2").arg(engOut(c,3)).arg(cUnit));
					painter.drawText(pa-5*scale, y+22*scale, QString("%1%2").arg(engOut(l,3)).arg(lUnit));
#endif
			}
			break;
		default:
			;
	}
	update();
}
