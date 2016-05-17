#ifndef QVNA_H
#define QVNA_H

#include <QtGui>
#include <QUdpSocket>
#include "config.h"
#include "hiqsdr_ctl.h"
#include "diag.h"
#include "ui_qvna.h"
#include "ui_diag.h"
#include <QColorDialog>
#include <QMessageBox>
#include <QFileDialog>
#include <QGraphicsView>
#include <QScrollBar>
#include <QtCore>

typedef struct {
    QString name;
	double from;
	double to;
} Range;

namespace Ui {
    class qvna;
}

class qvna : public QMainWindow {
    Q_OBJECT
public:
    qvna(QWidget *parent = 0);
    ~qvna();

protected:
    void changeEvent(QEvent *e);

private:
	dcomplex getInterpolation(dcomplex* data, double freq);
	void calcSMatrix();
    Ui::qvna *ui;
	QUdpSocket *vnaSocket;
	QString hiqsdrIP;
	QByteArray rawData;
    HiqsdrCtl *hiqsdr;
	QHash<QString, QColor> colors;
	QTimer *timer;
	double fMax;
	double fMin;
	double delay;
	int points;
	double re[MAX_SAMPLE_SIZE];
	double im[MAX_SAMPLE_SIZE];
	double re_a[MAX_SAMPLE_SIZE];
	double im_a[MAX_SAMPLE_SIZE];
	double cRe[CAL_POINTS];
	double cIm[CAL_POINTS];
	dcomplex rCalShort[CAL_POINTS];
	dcomplex rCalMatch[CAL_POINTS];
	dcomplex rCalOpen[CAL_POINTS];
	dcomplex s11[CAL_POINTS];
	dcomplex s21[CAL_POINTS];
	dcomplex s22[CAL_POINTS];
	Range range[MAX_RANGE];
	int rxAtt;
	int txAtt;
	bool running;
	int mode;
	int samples, averageSamples;
	int pos;
	QList<Diag*> diags;

signals:
	void setFreq(double min, double max);
	void modeChanged(int mode);
	void plot();
	void setDiagPoints(int n);
	void setMarker(int n);

private slots:
    void on_pushButtonNewPlot_clicked();
    void on_pushButtonRangeStore_clicked();
    void on_comboBoxRange_activated(int index);
    void on_comboBoxTXAtt_activated(QString );
    void on_comboBoxRFAtt_activated(QString );
    void on_comboBoxMode_activated(int);
    void on_comboBoxPoints_activated(QString );
    void on_doubleSpinBoxFMin_valueChanged(double);
    void on_doubleSpinBoxFMax_valueChanged(double);
	void on_doubleSpinBoxLCMatchRG_valueChanged(double arg1);
	void on_doubleSpinBoxLCMatchAntReal_valueChanged(double arg1);
	void on_doubleSpinBoxLCMatchAntImag_valueChanged(double arg1);
	void on_doubleSpinBoxLCMatchFreq_valueChanged(double arg1);
	Diag *createDiag();
	void readVNA();
	void parChanged();
	void readSettings();
	void writeSettings();
	void onExit();
	void timeout();
	void on_pushButtonStart_toggled(bool checked);
	void setPoints(int);
	void markerChanged(int);
	void on_comboBoxColor_activated(const QString &arg1);
	void on_pushButtonColor_clicked();
	void on_actionAbout_triggered();
	void on_spinBoxAverage_valueChanged(int arg1);
	void loadCalibration();
	void saveCalibration();
	void saveMeasurement();
	void resetSamples(bool all=false);
	void diagDestroyed(Diag*);
	void closeEvent(QCloseEvent*);
	void calcLCMatch();
};

#endif // QVNA_H
