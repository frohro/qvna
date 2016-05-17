#ifndef SCALE_H
#define SCALE_H

#include <QGraphicsItem>
#include <QWidget>
#include <QSvgRenderer>
#include "config.h"

class Scale: public QObject, public QGraphicsItem  {
	Q_OBJECT
		Q_INTERFACES(QGraphicsItem)
	public:
		Scale(int x,int y, QHash<QString, QColor> *c);
		~Scale();
		QRectF boundingRect() const;
		void setFreq(int from, int to);
		void setPoints(int p);
		void setScale(int sc);
		void setMode(int);
		void setMarker(int);
	public slots:
		void setViewPosX(int);
		void setViewPosY(int);
	signals:
		void markerChanged(int pos);
	private:
		void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
		void mousePressEvent(QGraphicsSceneMouseEvent *event);
		void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
		void wheelEvent( QGraphicsSceneWheelEvent *event);
		void hoverMoveEvent(QGraphicsSceneHoverEvent *event);
		void plotImagCircle(QPainter *p, double r, QString);
		void plotRealCircle(QPainter *p, double r, QString);
		QPointF mousePos;
		QHash<QString, QColor> *colors;
		QStringList xStrings1, xStrings2, yStrings;
		QSvgRenderer *svg;
		int fftFreqMarkerPos;

		int xSize, ySize;
		int xViewPos, yViewPos;
		int fMax, fMin;
		int points;
		int markerPos;
		int yScale;
		int mode;

};
#endif
