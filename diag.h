#ifndef DIAG_H
#define DIAG_H

#include <QtGui>
#include "config.h"
#include "plot.h"
#include "scale.h"

namespace Ui {
    class Diag;
}

class Diag : public QWidget {
    Q_OBJECT
public:
    Diag(int points, QHash<QString, QColor> *colors, double *re, double *im, dcomplex *s11, dcomplex *s21, dcomplex *s22, QWidget *parent = 0);
    ~Diag();
	void writeSettings(QSettings *settings);
	void readSettings(QSettings *settings);
public slots:
	void plot();
	void setFreq(double min, double max) ;
	void setMode(int m);
	void setPoints(int n);
	void setMarker(int pos);

signals:
	void markerChanged(int pos);
	void destroyed(Diag*);
protected:
    void changeEvent(QEvent *e);

private slots:
        void on_pushButtonScreenShot_clicked();
 void on_comboBoxMode_activated(int index);
	void on_horizontalSliderScale_valueChanged(int value);
	void scaleMarkerChanged(int markerPos);
	void setDispMode(int m);
	void setScale(int);
	void closeEvent(QCloseEvent *event);
private:
    Ui::Diag *ui;
	QGraphicsScene *sceneVNA;
	Plot *plt;
	Scale *scale;
	int yScale;
	double fMin,fMax;
	int dispModeTrans;
	int dispModeRef;
	int dispModeCal;
	int mode, points;
};

#endif // DIAG_H
