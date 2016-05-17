#include "diag.h"
#include "ui_diag.h"
#include "qvna.h"

#define DISP_MODES_REF		7
#define DISP_MODES_TRANS	3
#define DISP_MODES_CAL		1
static const char* buttonNameRef[]   = {"Z","r (kart)","r (polar)","r (polar log)","SVR","Smith","Text"};
static const char* buttonNameTrans[] = {"Trans (log)","Trans (lin)","Text"};
static const char* buttonNameCal[]   = {"Raw"};

Diag::Diag(int p, QHash<QString, QColor> *colors, double *re, double *im, dcomplex *s11, dcomplex *s21, dcomplex *s22, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Diag)
{
    ui->setupUi(this);
	fMin = 1.0;
	fMax = 10.0;
	yScale = 20;

	mode = MODE_TRANSMISSION;
	dispModeTrans = MODE_TRANS;
	dispModeRef   = MODE_Z;
	dispModeCal   = MODE_CAL;

	points = p;

	sceneVNA = new QGraphicsScene();

	scale = new Scale(points, Y_SIZE, colors);
	scale->setFreq(fMin*1e6, fMax*1e6);
	scale->setScale(yScale);
	connect(scale, SIGNAL(markerChanged(int)), this, SLOT(scaleMarkerChanged(int)));
	connect(ui->graphicsView->verticalScrollBar(), SIGNAL(valueChanged(int)), scale, SLOT(setViewPosY(int)));
	connect(ui->graphicsView->horizontalScrollBar(), SIGNAL(valueChanged(int)), scale, SLOT(setViewPosX(int)));

	plt = new Plot(points, Y_SIZE, re, im, s11, s21, s22, colors);
	plt->setScale(yScale);
	plt->setFreq(fMin, fMax);

	sceneVNA->setItemIndexMethod(QGraphicsScene::NoIndex);
	sceneVNA->addItem(plt);
	sceneVNA->addItem(scale);
	ui->graphicsView->setMouseTracking(true);
	ui->graphicsView->setScene(sceneVNA);
	ui->graphicsView->setSceneRect(QRect(0, 0, points, Y_SIZE));
	ui->graphicsView->centerOn(points/2, 0);
	ui->horizontalSliderScale->setValue(yScale);
	
	plot();
}

Diag::~Diag()
{
	emit destroyed(this);
    delete ui;
}

void Diag::changeEvent(QEvent *e)
{
    QWidget::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
        ui->retranslateUi(this);
        break;
    default:
        break;
    }
}

void Diag::readSettings(QSettings *settings) {
	restoreGeometry(settings->value("Geometry").toByteArray()); 
	resize(settings->value("Size",sizeHint()).toSize()); 
	dispModeTrans = settings->value("dispModeTrans",dispModeTrans).toInt();
	dispModeRef   = settings->value("dispModeRef",dispModeRef).toInt();
	dispModeCal   = settings->value("dispModeCal",dispModeCal).toInt();
	setScale(settings->value("yScale",yScale).toInt());
}

void Diag::writeSettings(QSettings *settings) {
	settings->setValue("Geometry",saveGeometry()); 
	settings->setValue("Size",size());
	settings->setValue("dispModeTrans", dispModeTrans);
	settings->setValue("dispModeRef", dispModeRef);
	settings->setValue("dispModeCal", dispModeCal);
	settings->setValue("yscale", yScale);
}

void Diag::setFreq(double min, double max) {
	fMin = min;
	fMax = max;
	scale->setFreq(fMin*1e6, fMax*1e6);
	plt->setFreq(fMin, fMax);
}

void Diag::scaleMarkerChanged(int markerPos) {
	emit markerChanged(markerPos);
}

void Diag::setDispMode(int m) {

	if (mode == MODE_TRANSMISSION)
		dispModeTrans = m;
	else if (mode == MODE_REFLECTION)
		dispModeRef = m;
	else
		dispModeCal = m;
	plt->setMode(m);
	scale->setMode(m);
	if ((m == MODE_SMITH) || (m == MODE_TEXT) || (m == MODE_TRANS_TEXT)) 
		ui->graphicsView->centerOn(0,0);
	plot();
}

void Diag::plot() {
	plt->plot();
}

void Diag::setMode(int m) {
	int i;
	mode = m;

	ui->comboBoxMode->clear();
	if (mode == MODE_TRANSMISSION) {
		for (i=0;i<DISP_MODES_TRANS;i++) 
			ui->comboBoxMode->addItem(QString(buttonNameTrans[i]));
		setDispMode(dispModeTrans);
		ui->comboBoxMode->setCurrentIndex(dispModeTrans - DISP_MODES_CAL);
	}
	else if (mode == MODE_REFLECTION) {
		for (i=0;i<DISP_MODES_REF;i++) 
			ui->comboBoxMode->addItem(QString(buttonNameRef[i]));
		setDispMode(dispModeRef);
		ui->comboBoxMode->setCurrentIndex(dispModeRef - DISP_MODES_CAL - DISP_MODES_TRANS);
	} else {
		for (i=0;i<DISP_MODES_CAL;i++) 
			ui->comboBoxMode->addItem(QString(buttonNameCal[i]));
		setDispMode(dispModeCal);
		ui->comboBoxMode->setCurrentIndex(dispModeCal);
	}
}

void Diag::setPoints(int n) {
	points = n;
	sceneVNA->removeItem(plt);
	sceneVNA->removeItem(scale);
	plt->setPoints(points);
	scale->setPoints(points);
	sceneVNA->addItem(plt);
	sceneVNA->addItem(scale);
	ui->graphicsView->setSceneRect(QRect(0, 0, points, Y_SIZE));
//	ui->graphicsView->centerOn(points/2, 0);

	plt->plot();
}

void Diag::on_horizontalSliderScale_valueChanged(int value)
{
	setScale(value);
}

void Diag::setScale(int value) {
	yScale = value;
	scale->setScale(yScale);
	plt->setScale(yScale);
	plot();
}

void Diag::on_comboBoxMode_activated(int index)
{
	if (mode == MODE_TRANSMISSION) {
		index += DISP_MODES_CAL;
	}
	if (mode == MODE_REFLECTION) {
		index += DISP_MODES_CAL + DISP_MODES_TRANS;
	} 
	setDispMode(index);
}

void Diag::setMarker(int pos) {
	scale->setMarker(pos);
	plt->setMarkerPos(pos);
}

void Diag::closeEvent(QCloseEvent*) {
	delete this;
}

void Diag::on_pushButtonScreenShot_clicked()
{
	QImage image(points, Y_SIZE , QImage::Format_RGB32);
	QPainter p(&image);
	QString fileName = QFileDialog::getSaveFileName(this, tr("Save"), "", tr("PNG Files (*.png)"));
	if (fileName == "")
		return;

	QRegExp rx(".*\\.png");
	if (rx.indexIn(fileName)<0) 
		fileName+=QString(".png");

	sceneVNA->render(&p, QRect(0, 0, points, Y_SIZE), QRect(0,0, points, Y_SIZE));
	image.save(fileName);
}
