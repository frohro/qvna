#ifndef PLOT_H
#define PLOT_H

#include <QGraphicsItem>
#include <QTimer>
#include <QWheelEvent>
#include "config.h"

#define PLOT_NONE	0
#define PLOT_RE_IM	1

class Plot: public QObject, public QGraphicsItem  {
    Q_OBJECT
	Q_INTERFACES(QGraphicsItem)
    public:
	Plot(int x,int y, double *reData, double *imData, dcomplex*, dcomplex*, dcomplex*, QHash<QString, QColor> *c);
	~Plot();
	QRectF boundingRect() const;
    public slots:
	void plot(); 
	void setFreq(double min, double max);
	void setMode(int m);
	void setPoints(int size);
	void setScale(int sc);
	void setMarkerPos(int);

    private:
	void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
	void updateLine();
	dcomplex getInterpolation(dcomplex* data, double freq);

	double *reData, *imData;
	dcomplex *s11,*s21,*s22;
	QColor colorTab[256];
	QPixmap *plotPixmap;
	QHash<QString, QColor> *colors;

	int points;
	int xSize, ySize;
	int mode;
	int yScale;
	dcomplex zc[MAX_SAMPLE_SIZE];
	dcomplex sc[MAX_SAMPLE_SIZE];
	dcomplex rc[MAX_SAMPLE_SIZE];
	int markerPos;
	double fMin,fMax;
	int textSpace;
};

#endif
