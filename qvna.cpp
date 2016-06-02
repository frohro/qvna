#include "qvna.h"
#include "ui_qvna.h"
#include "config.h"
#include "lib.h"
#include "assert.h"
#include "console.h"
#include "settingsdialog.h"

static const char* rangeName[]={"Full","160 m","80 m","40 m","30 m","20 m","17 m","15 m", "12 m","10 m", "6 m"};
static double bandRange[][2]={
    { 0.000000,61.440000},
    { 1.810000, 2.000000},
    { 3.500000, 3.800000},
    { 7.000000, 7.200000},
    {10.100000,10.150000},
    {14.000000,14.350000},
    {18.068000,18.168000},
    {21.000000,21.450000},
    {24.890000,24.990000},
    {28.000000,29.700000},
    {50.000000,52.000000}
};


qvna::qvna(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::qvna)
{
    fMin = 10;
    fMax = 20;
    points = 1000;
    memset (re,0, sizeof(re));
    memset (im,0, sizeof(re));
    running = false;
    mode = 1;
    pos = 0;
    averageSamples = 1 ;
    delay = 0;
    resetSamples();

    for (int i=0;i<CAL_POINTS;i++) {
        rCalOpen[i]  = dcomplex(1,0);
        rCalShort[i] = dcomplex(-1,0);
        rCalMatch[i] = dcomplex(0,0);
        cRe[i] = 1;
        cIm[i] = 0;
    }

    for (int i=0;i<MAX_RANGE;i++) {
        range[i].name = rangeName[i];
        range[i].from = bandRange[i][0];
        range[i].to   = bandRange[i][1];
    }

    hiqsdrIP = QString(HIQIP);

    ui->setupUi(this);
    //console = new Console;
    console = ui->console;
    serial = new QSerialPort(this);
    serialSettingsDialog = new SettingsDialog;
    readSettings();
    setVNAType();
    status = new QLabel;
    ui->statusBar->addWidget(status);
    initActionsConnections();

    connect(serial, static_cast<void (QSerialPort::*)(QSerialPort::SerialPortError)>(&QSerialPort::error),
            this, &qvna::handleError);
    connect(serial, &QSerialPort::readyRead, this, &qvna::readData);
    connect(console, &Console::getData, this, &qvna::writeData);
    for (int i=0;i < ui->comboBoxColor->count(); i++)
        colors[ui->comboBoxColor->itemText(i)] = QColor("White");
    colors["Background"] = QColor("Black");
    colors["Line real"]  = QColor("Blue");
    colors["Line imag"]  = QColor("Green");
    colors["Grid"]       = QColor(0,0,64);
    colors["Smith real"] = QColor(0,0,128);
    colors["Smith imag"] = QColor(128,0,0);
    colors["Text"]       = QColor("Gray");

    readSettings();
    hiqsdr = new HiqsdrCtl( hiqsdrIP);
    for (int i=0;i<MAX_RANGE;i++)
        ui->comboBoxRange->addItem(QString(range[i].name));
    ui->pushButtonColor->setPalette( QPalette(colors[ui->comboBoxColor->currentText()]));

    ui->doubleSpinBoxFMin->setValue(fMin);
    ui->doubleSpinBoxFMax->setValue(fMax);
    ui->comboBoxMode->setCurrentIndex(mode);
    on_comboBoxMode_activated(mode);
    ui->lineEditIP->setText(hiqsdrIP);
    ui->spinBoxAverage->setValue(averageSamples);

    setPoints(points);

    vnaSocket = new QUdpSocket(this);
    vnaSocket->bind(HIQSDR_RX_PORT);

    // no autostart
    //parChanged();
    //vnaSocket->writeDatagram("rr", 2, QHostAddress(hiqsdrIP), HIQSDR_RX_PORT);

    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(timeout()));
    timer->start(100);		// 100ms

    connect(vnaSocket, SIGNAL(readyRead()), this, SLOT(readVNA()));
    connect(ui->actionQuit, SIGNAL(triggered()), this, SLOT(onExit()));
    connect(ui->actionSave_calibration, SIGNAL(triggered()), this, SLOT(saveCalibration()));
    connect(ui->actionLoad_calibration, SIGNAL(triggered()), this, SLOT(loadCalibration()));
    connect(ui->actionSave, SIGNAL(triggered()), this, SLOT(saveMeasurement()));

    calcSMatrix();

}

qvna::~qvna()
{
    hiqsdrIP = ui->lineEditIP->text();
    writeSettings();
    hiqsdr->resetVNA();
    vnaSocket->writeDatagram("ss", 2, QHostAddress(hiqsdrIP), HIQSDR_RX_PORT);
    vnaSocket->close();
    delete hiqsdr;
    delete serialSettingsDialog;
    delete ui;
}


void qvna::openSerialPort()
{
    SettingsDialog::Settings p = serialSettingsDialog->settings();
    serial->setPortName(p.name);
    serial->setBaudRate(p.baudRate);
    serial->setDataBits(p.dataBits);
    serial->setParity(p.parity);
    serial->setStopBits(p.stopBits);
    serial->setFlowControl(p.flowControl);
    if (serial->open(QIODevice::ReadWrite)) {
        console->setEnabled(true);
        console->show();
        console->setLocalEchoEnabled(p.localEchoEnabled);
        ui->actionConnect->setEnabled(false);
        ui->actionDisconnect->setEnabled(true);
        ui->actionConfigure->setEnabled(false);
                showStatusMessage(tr("Connected to %1 : %2, %3, %4, %5, %6")
                                  .arg(p.name).arg(p.stringBaudRate).arg(p.stringDataBits)
                                  .arg(p.stringParity).arg(p.stringStopBits).arg(p.stringFlowControl));
    } else {
        QMessageBox::critical(this, tr("Error"), serial->errorString());
        showStatusMessage(tr("Open error"));
    }
}

void qvna::closeSerialPort()
{
    if (serial->isOpen())
        serial->close();
    console->setEnabled(false);
    ui->actionConnect->setEnabled(true);
    ui->actionDisconnect->setEnabled(false);
    ui->actionConfigure->setEnabled(true);
    showStatusMessage(tr("Disconnected"));
}

//void qvna::writeDataArray(unsigned char *data)
//{
//    qint64 numBytesWritten;
//    console->setTextColor(Qt::yellow);
//    console->putData(QByteArray((char*)data,-1));
//    if((numBytesWritten = serial->writeData((const char*)data,256)) == -1)
//        qDebug("Error writing to serial port!/n");
//    qDebug ( "Wrote %lld bytes to serial port.\n",numBytesWritten);
//}

void qvna::writeData(const QByteArray &data)
{
    qint64 numBytesWritten;
   // qDebug("Setting colorto yellow.\n");
    console->setTextColor(Qt::yellow);
    console->putData(data);
    if((numBytesWritten = serial->write(data)) == -1)
        qDebug("Error writing to serial port!/n");
    qDebug ( "Wrote %lld bytes to serial port.\n",numBytesWritten);
}

void qvna::readData()
{
    QByteArray data = serial->readAll();
    //qDebug("Setting color to green.\n");
    console->setTextColor(Qt::green);
    console->putData(data);
}

void qvna::handleError(QSerialPort::SerialPortError error)
{
    QMessageBox qMB;
    if (error == QSerialPort::ResourceError) {
        qMB.critical(this, tr("Critical Error"), serial->errorString());
        closeSerialPort();
    }
}

void qvna::setVNAType() // Setup GUI according to what VNA we are using.
{
    if(ui->hiqsdrRadioButton->isChecked())
    {
        vnaType = VNA_TYPE_HIQSDR;
        ui->groupBoxAtt->show();
        ui->groupBoxHIQSDR->show();
        ui->groupBoxSerial->hide();
        ui->actionConfigure->setEnabled(false);
        ui->actionConnect->setEnabled(false);
        ui->actionDisconnect->setEnabled(false);
        ui->actionClear->setEnabled(false);
    }
    else if (ui->serialVNARadioButton->isChecked())
    {
        vnaType = VNA_TYPE_SERIAL;
        console->setEnabled(false);
        ui->actionConfigure->setEnabled(true);
        ui->groupBoxAtt->hide();
        ui->groupBoxHIQSDR->hide();
        ui->groupBoxSerial->show();
        ui->actionConfigure->setEnabled(true);
        ui->actionConnect->setEnabled(true);
        ui->actionDisconnect->setEnabled(false);
    }
}

void qvna::initActionsConnections()
{
    connect(ui->actionConnect, &QAction::triggered, this, &qvna::openSerialPort);
    connect(ui->actionDisconnect, &QAction::triggered, this, &qvna::closeSerialPort);
    connect(ui->actionQuit, &QAction::triggered, this, &qvna::close);
    connect(ui->actionClear, &QAction::triggered, console, &Console::clear);
    connect(ui->actionAbout, &QAction::triggered, this, &qvna::on_actionAbout_triggered);
    connect(ui->actionAbout_Qt, &QAction::triggered, qApp, &QApplication::aboutQt);
}

void qvna::showStatusMessage(const QString &message)
{
    status->setText(message);
}


void qvna::changeEvent(QEvent *e)
{
    QMainWindow::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
        ui->retranslateUi(this);
        break;
    default:
        break;
    }
}

QString toDebug(const QByteArray & line)
{
    QString s;
    uchar c;

    for ( int i=0 ; i < line.size() ; i++ ){
        c = line[i];

        s.append(QString("0x%1, ").arg(c, 2, 16, QChar('0')));
    }
    return s;
}

//void qvna::serialWriteVNACommand(void)
//{
//    QByteArray byteArray;
//    uint16_t n;

//    qDebug("In serialWriteVNACommand.\n");
//    if((mode == MODE_REFLECTION)||(mode== MODE_CAL_MATCH)||
//            (mode==MODE_CAL_OPEN)||(mode==MODE_CAL_SHORT))
//    {
//        qDebug("Wrote 0 for reflection mode.\n");
//        byteArray.append('0');
//    }
//    else if((mode == MODE_TRANSMISSION)||(mode==MODE_CAL_THROUGH))
//    {
//        byteArray.append('1');
//    }
//    byteArray.append(0x0d);
//    n = (uint16_t)(fMin);  // KHz units
//    qDebug("n is: %d",n);
//    qDebug("n is: 0x%x",n);
//    for(int i = 0; i != sizeof(n); ++i)
//    {
//        qDebug("The byte is: 0x%02x",(unsigned char)((n & (0xFF << (i*8))) >> (i*8)));
//        byteArray.append((unsigned char)((n & (0xFF << (i*8))) >> (i*8)));
//    } // uint16_t little endian
//    byteArray.append(0x0d);
//    n = (uint16_t)(points);
//    qDebug("n is: %d",n);
//    qDebug("n is: 0x%x",n);
//    for(int i = 0; i != sizeof(n); ++i)
//    {
//        qDebug("The byte is: 0x%02x",(unsigned char)((n & (0xFF << (i*8))) >> (i*8)));
//        byteArray.append((unsigned char)((n & (0xFF << (i*8))) >> (i*8)));
//    }
//    byteArray.append(0x0d);
//    n = (uint16_t)(fMax);
//    qDebug("n is: %d",n);
//    qDebug("n is: 0x%x",n);
//    for(int i = 0; i != sizeof(n); ++i)
//    {
//        qDebug("The byte is: 0x%02x",(unsigned char)((n & (0xFF << (i*8))) >> (i*8)));
//        byteArray.append((unsigned char)((n & (0xFF << (i*8))) >> (i*8)));
//    }
//    byteArray.append(0x0d);
//    qDebug ("The byteArray is: ");
//    qDebug() << toDebug(byteArray);
//    emit console->getData(byteArray);
//    //writeData(byteArray);
//}

void qvna::serialWriteVNACommand(void)
{
    QByteArray byteArray;
    uint16_t n;

    qDebug("In serialWriteVNACommand.\n");
    if((mode == MODE_REFLECTION)||(mode== MODE_CAL_MATCH)||
            (mode==MODE_CAL_OPEN)||(mode==MODE_CAL_SHORT))
    {
        qDebug("Wrote 0 for reflection mode.\n");
        byteArray.append('0');
    }
    else if((mode == MODE_TRANSMISSION)||(mode==MODE_CAL_THROUGH))
    {
        byteArray.append('1');
    }
   // byteArray.append(0x0d);
    n = (uint16_t)(fMin*1000);  // KHz units
    qDebug("n is: %d",n);
    qDebug("n is: 0x%x",n);
    for(int i = 0; i != sizeof(n); ++i)
    {
        qDebug("The byte is: 0x%02x",(unsigned char)((n & (0xFF << (i*8))) >> (i*8)));
        byteArray.append((unsigned char)((n & (0xFF << (i*8))) >> (i*8)));
    } // uint16_t little endian
    //byteArray.append(0x0d);
    n = (uint16_t)(points);
    qDebug("n is: %d",n);
    qDebug("n is: 0x%x",n);
    for(int i = 0; i != sizeof(n); ++i)
    {
        qDebug("The byte is: 0x%02x",(unsigned char)((n & (0xFF << (i*8))) >> (i*8)));
        byteArray.append((unsigned char)((n & (0xFF << (i*8))) >> (i*8)));
    }
    //byteArray.append(0x0d);
    n = (uint16_t)(fMax*1000);
    qDebug("n is: %d",n);
    qDebug("n is: 0x%x",n);
    for(int i = 0; i != sizeof(n); ++i)
    {
        qDebug("The byte is: 0x%02x",(unsigned char)((n & (0xFF << (i*8))) >> (i*8)));
        byteArray.append((unsigned char)((n & (0xFF << (i*8))) >> (i*8)));
    }
    byteArray.append(0x0d);
    qDebug ("The byteArray is: ");
    qDebug() << toDebug(byteArray);
    emit console->getData(byteArray);
    //writeData(byteArray);
}

void qvna::readVNA() {
    QByteArray datagram;
    QByteArray syncPattern("\x00\x00\x00\x00\x00\x00",6);
    QHostAddress sender;
    quint16 senderPort;
    static bool inSync=false;;
    int st;
    unsigned char *p;
    static const int NBITS = 32;          // # of bits in a sample
    double r,phi;

    if(ui->hiqsdrRadioButton->isChecked())
    {

        while (vnaSocket->hasPendingDatagrams()>0) {
            datagram.resize(vnaSocket->pendingDatagramSize());

            vnaSocket->readDatagram(datagram.data(), datagram.size(),
                                    &sender, &senderPort);

            rawData.append(datagram.mid(2));
        }

        if (rawData.size() > points*6*3) {
            rawData.clear();
            PDEBUG(ERR1, "VNA: read nonsense");
        }
        PDEBUG(MSG3, "VNA: new parse %i", rawData.size());
        while(rawData.size() >= points*6+6) {
            PDEBUG(MSG3, "VNA: parse %i", rawData.size());
            if (!inSync) {
                st = rawData.indexOf(syncPattern);
                if (rawData.indexOf(syncPattern,st+1)>0)
                    st = rawData.indexOf(syncPattern,st+1);
                if (rawData.indexOf(syncPattern,st+1)>0)
                    st = rawData.indexOf(syncPattern,st+1);
                if (st>0) {
                    rawData = rawData.mid(st+6);
                    inSync = true;
                    PDEBUG(MSG3, "VNA: in sync");
                } else {
                    PDEBUG(MSG3, "VNA: no sync");
                    break;
                }
            } else {
                if (rawData.mid(points*6,6) == syncPattern) {
                    double f,freq;
                    double mod, calRe, calIm;
                    int imod, i_re, i_im;

                    PDEBUG(MSG2, "VNA: sync");
                    p = (unsigned char*)rawData.data();
                    for (int i=0; i < points; i++) {
                        i_re =  ((p[i*6+0]<<8) + (p[i*6+1]<<16) + (p[i*6+2]<<24));
                        i_im =  ((p[i*6+3]<<8) + (p[i*6+4]<<16) + (p[i*6+5]<<24));
                        re_a[i] += (double) i_re * (1.0 / (double) ((1LL << (NBITS-1)) - 1));
                        im_a[i] += (double) i_im * (1.0 / (double) ((1LL << (NBITS-1)) - 1));
                    }
                    if (samples == averageSamples-1) {
                        for (int i=0; i < points; i++) {
                            re[i] = re_a[i] / averageSamples;
                            im[i] = im_a[i] / averageSamples;

                            r  = sqrt(re[i] * re[i] + im[i] * im[i]);
                            phi  = atan2(im[i], re[i]);
                            freq = fMin + i*(fMax-fMin)/points;
                            f = freq*1e6*CAL_POINTS/CAL_F_MAX;

                            f = modf(f,&mod);
                            imod = (int)mod;

                            switch (mode) {
                            case MODE_TRANSMISSION:
                                calRe = cRe[imod] + (cRe[imod+1]-cRe[imod])*f;
                                if ((cIm[imod+1]-cIm[imod])>M_PI)
                                    calIm = cIm[imod] + (cIm[imod+1]-cIm[imod]-2*M_PI)*f;
                                else if ((cIm[imod+1] -cIm[imod])<-M_PI)
                                    calIm = cIm[imod] + (cIm[imod+1]-cIm[imod]+2*M_PI)*f;
                                else
                                    calIm = cIm[imod] + (cIm[imod+1]-cIm[imod])*f;

                                r   /= calRe;
                                phi -= calIm;
                                phi += delay*freq/500.0;

                                break;
                            case MODE_REFLECTION:
                            case MODE_CAL_THROUGH:
                            case MODE_CAL_OPEN:
                            case MODE_CAL_MATCH:
                            case MODE_CAL_SHORT:
                                break;
                            }
                            phi += delay*freq/500.0;
                            while (phi >  M_PI) phi -= 2*M_PI;
                            while (phi < -M_PI) phi += 2*M_PI;
                            re[i] = r;
                            im[i] = phi;
                        }
                        emit plot();
                        resetSamples();
                        if (mode >= MODE_CAL_THROUGH) {
                            ui->pushButtonStart->setText("Store");
                            ui->pushButtonStart->setChecked(false);
                        }
                    } else {
                        samples++;
                        assert(samples <= averageSamples);
                    }
                    rawData = rawData.mid(points*6+6);
                } else {
                    inSync = false;
                    PDEBUG(MSG2, "VNA: out of sync");
                }
            }
        }
    }
    else if(ui->serialVNARadioButton->isChecked())
    {

    }
}

void qvna::on_doubleSpinBoxFMin_valueChanged(double v)
{
    fMin = v;
    //	if (fMin>fMax)
    //		ui->doubleSpinBoxFMax->setValue(fMin);
    parChanged();
}

void qvna::on_doubleSpinBoxFMax_valueChanged(double v)
{
    fMax = v;
    //	if (fMax<fMin)
    //		ui->doubleSpinBoxFMin->setValue(fMax);
    parChanged();
}

void qvna::parChanged() {
    int fRoundMax;
    if (running) {
        fRoundMax = hiqsdr->setVNA(fMin*1e6, fMax*1e6, points);
        emit setFreq(fMin, fRoundMax/1e6);
    } else {
        emit setFreq(fMin, fMax);
    }
}

void qvna::readSettings() {

    serialSettingsDialog->readSettings();
    QSettings settings("sdr","qvna");

    settings.beginGroup("Common");
    vnaType  = settings.value("vnaType",vnaType).toInt();
    mode     = settings.value("mode",mode).toInt();
    fMin     = settings.value("fmin",fMin).toDouble();
    fMax     = settings.value("fmax",fMax).toDouble();
    points   = settings.value("points",points).toInt();
    hiqsdrIP = settings.value("hiqsdrIP",hiqsdrIP).toString();
    averageSamples = settings.value("average",averageSamples).toInt();

    settings.endGroup();

    settings.beginGroup("Layout");
    if(settings.value("checkLayout").toInt()) {
        restoreGeometry(settings.value("Geometry").toByteArray());
        resize(settings.value("Size",sizeHint()).toSize());
        restoreState(settings.value("Properties").toByteArray());
    }
    settings.endGroup();

    int l = settings.beginReadArray("Colors");
    for (int i=0;i<l;i++) {
        settings.setArrayIndex(i);
        QString key = settings.value("Name").toString();
        colors[key] = settings.value("Color").value<QColor>();
    }
    settings.endArray();

    settings.beginReadArray("Range");
    for(int i=0;i<MAX_RANGE;i++) {
        settings.setArrayIndex(i);
        range[i].name = settings.value("name",range[i].name).toString();
        range[i].from = settings.value("from",range[i].from).toDouble();
        range[i].to   = settings.value("to"  ,range[i].to  ).toDouble();
    }
    settings.endArray();

    settings.beginReadArray("Calibration");
    for(int i=0;i<CAL_POINTS;i++) {
        settings.setArrayIndex(i);
        cRe[i] = settings.value("throughMag", cRe[i]).toDouble();
        cIm[i] = settings.value("throughPhase", cIm[i]).toDouble();
        rCalMatch[i] = dcomplex(settings.value("rCalMatch_re", real(rCalMatch[i])).toDouble(), settings.value("rCalMatch_im", imag(rCalMatch[i])).toDouble());
        rCalOpen[i]  = dcomplex(settings.value("rCalOpen_re", real(rCalOpen[i])).toDouble(), settings.value("rCalOpen_im", imag(rCalOpen[i])).toDouble());
        rCalShort[i] = dcomplex(settings.value("rCalShort_re", real(rCalShort[i])).toDouble(), settings.value("rCalShort_im", imag(rCalShort[i])).toDouble());
    }
    settings.endArray();

    settings.beginReadArray("Measure");
    for(int i=0;i<CAL_POINTS;i++) {
        settings.setArrayIndex(i);
        re[i] = settings.value("real", re[i]).toDouble();
        im[i] = settings.value("imag", im[i]).toDouble();
    }
    settings.endArray();

    int n = settings.beginReadArray("Diagrams");
    for(int i=0;i<n;i++) {
        settings.setArrayIndex(i);
        createDiag()->readSettings(&settings);
    }
    settings.endArray();
}

// ---------------------------------------------
void qvna::writeSettings() {

    QSettings settings("sdr","qvna");
    settings.beginGroup("Common");

    settings.setValue("vnaType",vnaType);
    settings.setValue("mode", mode);
    settings.setValue("fmin", fMin);
    settings.setValue("fmax", fMax);
    settings.setValue("points", points);
    settings.setValue("hiqsdrIP", hiqsdrIP);
    settings.setValue("average", averageSamples);
    settings.endGroup();

    settings.beginGroup("Layout");
    settings.setValue("Geometry",saveGeometry());
    settings.setValue("Size",size());
    settings.setValue("Properties",saveState());
    settings.setValue("checkLayout", 1);
    settings.endGroup();

    settings.beginWriteArray("Diagrams");
    for (int i=0;i<diags.size();i++) {
        settings.setArrayIndex(i);
        diags[i]->writeSettings(&settings);
    }
    settings.endArray();

    settings.beginWriteArray("Colors");
    QHashIterator<QString, QColor> qi(colors);
    int i=0;
    while (qi.hasNext()) {
        settings.setArrayIndex(i++);
        qi.next();
        settings.setValue("Name",qi.key());
        settings.setValue("Color", qi.value());
    }
    settings.endArray();

    settings.beginWriteArray("Range");
    for(i=0;i<MAX_RANGE;i++) {
        settings.setArrayIndex(i);
        settings.setValue("name", range[i].name);
        settings.setValue("to"  , range[i].to  );
        settings.setValue("from", range[i].from);
    }
    settings.endArray();

    settings.beginWriteArray("Calibration");
    for(i=0;i<CAL_POINTS;i++) {
        settings.setArrayIndex(i);
        settings.setValue("throughMag",   cRe[i]);
        settings.setValue("throughPhase", cIm[i]);
        settings.setValue("rCalMatch_re", real(rCalMatch[i]));
        settings.setValue("rCalMatch_im", imag(rCalMatch[i]));
        settings.setValue("rCalOpen_re",  real(rCalOpen[i]));
        settings.setValue("rCalOpen_im",  imag(rCalOpen[i]));
        settings.setValue("rCalShort_re", real(rCalShort[i]));
        settings.setValue("rCalShort_im", imag(rCalShort[i]));
    }
    settings.endArray();

    settings.beginWriteArray("Measure");
    for(i=0;i<points;i++) {
        settings.setArrayIndex(i);
        settings.setValue("real",   re[i]);
        settings.setValue("imag",   im[i]);
    }
    settings.endArray();
}

void qvna::onExit() {
    qApp->exit(0);
}

void qvna::on_comboBoxMode_activated(int n)
{
    mode = n;
    switch (mode) {
    case MODE_TRANSMISSION:
        ui->pushButtonStart->setChecked(false);
        ui->pushButtonStart->setText("Start");
        break;
    case MODE_REFLECTION:
        ui->pushButtonStart->setChecked(false);
        ui->pushButtonStart->setText("Start");
        break;
    case MODE_CAL_THROUGH:
    case MODE_CAL_OPEN:
    case MODE_CAL_MATCH:
    case MODE_CAL_SHORT:
        delay = 0;
        ui->pushButtonStart->setChecked(false);
        ui->pushButtonStart->setText("Store");
        ui->doubleSpinBoxFMin->setValue(CAL_F_MIN/1e6);
        ui->doubleSpinBoxFMax->setValue(CAL_F_MAX/1e6);
        setPoints(CAL_POINTS);
        break;
    }
    emit modeChanged(mode);
    emit plot();
}

void qvna::on_comboBoxRFAtt_activated(QString s)
{
    rxAtt = s.toInt();
    hiqsdr->setAttenuator(-rxAtt);

}

void qvna::on_comboBoxTXAtt_activated(QString s )
{
    int n = s.toInt();
    txAtt = 0;
    if (n==10)
        txAtt = 50;
    if (n==20)
        txAtt = 255;
    hiqsdr->setTXLevel(txAtt);
}


void qvna::setPoints(int n) {
    int i;

    points = n;
    resetSamples();
    if (ui->comboBoxPoints->itemText(ui->comboBoxPoints->currentIndex()).toInt()!=n)
        for (i=0; i<ui->comboBoxPoints->count(); i++)
            if (points == ui->comboBoxPoints->itemText(i).toInt()) {
                ui->comboBoxPoints->setCurrentIndex(i);
                break;
            }

    emit setDiagPoints(points);
    parChanged();
    emit plot();
}

void qvna::on_comboBoxPoints_activated(QString s )
{
    setPoints(s.toInt());
}

void qvna::on_pushButtonStart_toggled(bool checked)
{
    qDebug("In pushButtonStart_toggled!\n");
    if(vnaType==VNA_TYPE_SERIAL)
    {

        serialWriteVNACommand();
    }
    resetSamples();
    switch (mode) {
    case MODE_TRANSMISSION:
            case MODE_REFLECTION:
            running = checked;
        if (checked) {
            ui->pushButtonStart->setText("Stop");
            parChanged();
            if(vnaType==VNA_TYPE_HIQSDR)
                vnaSocket->writeDatagram("rr", 2, QHostAddress(hiqsdrIP), HIQSDR_RX_PORT);
        } else {
            ui->pushButtonStart->setText("Start");
            if(vnaType==VNA_TYPE_HIQSDR)
            {
                hiqsdr->resetVNA();
                vnaSocket->writeDatagram("ss", 2, QHostAddress(hiqsdrIP), HIQSDR_RX_PORT);
            }
        }
        break;
    case MODE_CAL_THROUGH:
    case MODE_CAL_OPEN:
    case MODE_CAL_MATCH:
    case MODE_CAL_SHORT:
        running = checked;
        if (checked) {
            ui->pushButtonStart->setText("wait");
            parChanged();
            vnaSocket->writeDatagram("rr", 2, QHostAddress(hiqsdrIP), HIQSDR_RX_PORT);
        } else {
            for(int i=0;i<CAL_POINTS;i++) {
                dcomplex zl(50,0);
                dcomplex u = polar(re[i],im[i]);
                dcomplex z =  (1.0+u)/(1.0-u)*zl;
                dcomplex r = (z-zl)/(z+zl);

                if (mode == MODE_CAL_SHORT)
                    rCalShort[i] = r;
                if (mode == MODE_CAL_OPEN)
                    rCalOpen[i] = r;
                if (mode == MODE_CAL_MATCH)
                    rCalMatch[i] = r;
                if (mode == MODE_CAL_THROUGH) {
                    cRe[i] = re[i];
                    cIm[i] = im[i];
                }
            }
            calcSMatrix();
            if(vnaType==VNA_TYPE_HIQSDR)
            {
                hiqsdr->resetVNA();
                vnaSocket->writeDatagram("ss", 2, QHostAddress(hiqsdrIP), HIQSDR_RX_PORT);
            }
            writeSettings();
        }
        break;
    }
}

void qvna::on_comboBoxRange_activated(int index)
{
    ui->doubleSpinBoxFMin->setValue(range[index].from);
    ui->doubleSpinBoxFMax->setValue(range[index].to);
}

void qvna::on_pushButtonRangeStore_clicked()
{
    range[ui->comboBoxRange->currentIndex()].from = ui->doubleSpinBoxFMin->value();
    range[ui->comboBoxRange->currentIndex()].to   = ui->doubleSpinBoxFMax->value();
    range[ui->comboBoxRange->currentIndex()].name = ui->comboBoxRange->currentText();

}

void qvna::timeout() {		// 100ms
}

dcomplex qvna::getInterpolation(dcomplex* data, double freq) {
    double fx,mod;
    int imod;

    fx = freq*1e6*CAL_POINTS/CAL_F_MAX;
    fx = modf(fx, &mod);
    imod = (int)mod;
    return data[imod] + (data[imod+1]-data[imod])*fx;
}

void qvna::calcSMatrix() {
    dcomplex rm1,rm2,rm3;
    dcomplex a(1,0),b,c,d(-1,0),e,f;

    // Eintormessung
    // http://www.siart.de/lehre/nwa.pdf
    // Kalibrierung von Netzwerkanalystoren

    // Kalibrierungsdaten:
    // rm1: Reflektionfaktor Anpassung
    // rm2: Reflektionfaktor Leerlauf
    // rm3: Reflektionfaktor Kurzschluss

    for (int i=0;i<CAL_POINTS;i++) {
        rm1 = rCalMatch[i];
        rm2 = rCalOpen[i];
        rm3 = rCalShort[i];

        s11[i] = rm1;

        b = rm2 - s11[i];
        c = rm2 - s11[i];
        e = s11[i] - rm3;
        f = rm3 - s11[i];

        s21[i] = (b*f-c*e)/(b*d-a*e);
        s22[i] = (c*d-a*f)/(b*d-a*e);
    }

}

void qvna::markerChanged(int mpos) {
    dcomplex rm,r,u;
    dcomplex z,zl;
    dcomplex f11,f21,f22;
    double freq;

    pos = mpos;
    emit setMarker(pos);

    freq = fMin + pos*(fMax-fMin)/points;
    zl = ui->doubleSpinBoxLCMatchRG->value();

    u = polar(re[pos],im[pos]);
    z = (1.0+u)/(1.0-u)*zl;
    rm = (z-zl)/(z+zl);

    f11 = getInterpolation(s11, freq);
    f21 = getInterpolation(s21, freq);
    f22 = getInterpolation(s22, freq);

    r = (rm-f11)/(f22*(rm-f11)+f21);
    z = (1.0+r)/(1.0-r)*zl;

    ui->doubleSpinBoxLCMatchAntReal->setValue(real(z));
    ui->doubleSpinBoxLCMatchAntImag->setValue(imag(z));
    ui->doubleSpinBoxLCMatchFreq->setValue(freq);
}

void qvna::on_comboBoxColor_activated(const QString &arg1)
{
    ui->pushButtonColor->setPalette( QPalette(colors[arg1]));
}

void qvna::on_pushButtonColor_clicked()
{
    QString s = ui->comboBoxColor->currentText();
    colors[s] = QColorDialog::getColor(colors[s]);
    ui->pushButtonColor->setPalette( QPalette(colors[s]));
    emit plot();
}

void qvna::on_actionAbout_triggered()
{
    QMessageBox msg;
    msg.setText(QString("QVNA Version " VERSION));
    msg.exec();
}

void qvna::loadCalibration() {
    QRegExp rxrem( "^#.*$");
    QRegExp rxCal("^([-\\.\\de]+)[\t ]+([-\\.\\de]+)[\t ]+([-\\.\\de]+)[\t ]+([-\\.\\de]+)[\t ]([-\\.\\de]+)[\t ]+([-\\.\\de]+)[\t ]+([-\\.\\de]+)[\t ]+([-\\.\\de]+).*$" );
    int i=0;

    QString s = QFileDialog::getOpenFileName( this,  "open calibration", "", "Calibration (*.cal)");
    if (s==QString(""))
        return;

    QFile f(s);
    if ( f.open(QIODevice::ReadOnly) ) {
        while (!f.atEnd()) {
            QString line = f.readLine();
            if (rxrem.indexIn(line)>=0) continue; 	// skip remarks
            if (rxCal.indexIn(line)>=0) {
                cRe[i] = rxCal.cap(1).toDouble();
                cIm[i] = rxCal.cap(2).toDouble();
                rCalMatch[i] = dcomplex(rxCal.cap(3).toDouble(), rxCal.cap(4).toDouble());
                rCalOpen[i]  = dcomplex(rxCal.cap(5).toDouble(), rxCal.cap(6).toDouble());
                rCalShort[i] = dcomplex(rxCal.cap(7).toDouble(), rxCal.cap(8).toDouble());
                i++;
            }
        }
        calcSMatrix();
        if (i>0 && i!=CAL_POINTS)
            QMessageBox::information( 0, tr("Error"), "invalid calibration data !\ncurrent calibration currupted");
        if (i==0)
            QMessageBox::information( 0, tr("Error"), "no calibration data");
        f.close();
    } else {
        QMessageBox::information( 0, tr("Error"), "read files" + s);
        return;
    }
}

void qvna::saveCalibration() {
    QString s = QFileDialog::getSaveFileName( this,  "save calibration", "", "Calibration (*.cal)");
    if (s==QString(""))
        return;

    QRegExp rx(".*\\.cal");
    if (rx.indexIn(s)<0)
        s+=QString(".cal");

    QFile f(s);
    if ( f.open(QIODevice::WriteOnly) ) {    // file opened successfully
        QTextStream t( &f );        // use a text stream


        t << "[Calibration 1]" << endl;
        for (int i=0;i<CAL_POINTS;i++) {
            t << QString("%1 %2 %3 %4 %5 %6 %7 %8")
                 .arg(cRe[i]).arg(cIm[i])
                 .arg(real(rCalMatch[i])).arg(imag(rCalMatch[i]))
                 .arg(real(rCalOpen[i])).arg(imag(rCalOpen[i]))
                 .arg(real(rCalShort[i])).arg(imag(rCalShort[i])) << endl;
        }
        f.close();
    } else {

        QMessageBox::information( 0, tr("Error"), "write file" + s);
    }
}

void qvna::saveMeasurement() {
    dcomplex r,s,u;
    dcomplex z,zl(50,0);
    dcomplex f11,f21,f22;
    dcomplex rm;
    double freq;
    QString st = QFileDialog::getSaveFileName( this,  "save measurement", "", "(*.csv)");
    if (st==QString(""))
        return;

    QRegExp rx(".*\\.csv");
    if (rx.indexIn(st)<0)
        st+=QString(".csv");


    QFile f(st);
    if ( f.open(QIODevice::WriteOnly) ) {
        QTextStream t( &f );

        t << QString("Freq, real(u), imag(u), real(s11), imag(s11), real(s21), imag(s21), real(s22), imag(s22), real(r), imag(r), real(z), imag(z), SWR") << endl;
        for (int i=0;i<points;i++) {

            u = polar(re[i],im[i]);
            freq = fMin + i*(fMax-fMin)/points;
            z = (1.0+u)/(1.0-u)*zl;
            rm = (z-zl)/(z+zl);

            f11 = getInterpolation(s11, freq);
            f21 = getInterpolation(s21, freq);
            f22 = getInterpolation(s22, freq);

            r = (rm-f11)/(f22*(rm-f11)+f21);
            z = (1.0+r)/(1.0-r)*zl;
            s = (1.0+abs(r))/(1.0-abs(r));

            t << QString("%1, %2, %3, %4, %5, %6, %7, %8, %9, %10, %11, %12, %13, %14")
                 .arg(freq)
                 .arg(re[i]).arg(im[i])
                 .arg(real(f11)).arg(imag(f11))
                 .arg(real(f21)).arg(imag(f21))
                 .arg(real(f22)).arg(imag(f22))
                 .arg(real(r)) .arg(imag(r))
                 .arg(real(z)) .arg(imag(z))
                 .arg(real(s)) << endl;
        }
        f.close();
    } else {
        QMessageBox::information( 0, tr("Error"), "write file" + st);
    }
}

void qvna::on_spinBoxAverage_valueChanged(int v)
{
    averageSamples = v;
    resetSamples();
}

void qvna::resetSamples(bool all) {
    samples = 0;
    for (int i=0; i < points; i++) {
        re_a[i] = 0;
        im_a[i] = 0;
        if (all) {
            re[i] = 0;
            im[i] = 0;
        }
    }
}

void qvna::diagDestroyed(Diag *d) {
    diags.removeAll(d);
}

void qvna::on_pushButtonNewPlot_clicked()
{
    createDiag();
}

Diag* qvna::createDiag() {
    Diag *diag;
    diag = new Diag(points, &colors, re, im, s11, s21, s22);
    diags.append(diag);
    connect(diag, SIGNAL(markerChanged(int)), this, SLOT(markerChanged(int)));
    connect(diag, SIGNAL(destroyed(Diag*)), this, SLOT(diagDestroyed(Diag*)));
    connect(this, SIGNAL(modeChanged(int)), diag, SLOT(setMode(int)));
    connect(this, SIGNAL(plot()), diag, SLOT(plot()));
    connect(this, SIGNAL(setFreq(double, double)), diag, SLOT(setFreq(double,double)));
    connect(this, SIGNAL(setDiagPoints(int)), diag, SLOT(setPoints(int)));
    connect(this, SIGNAL(setMarker(int)), diag, SLOT(setMarker(int)));
    diag->show();
    diag->setMode(mode);
    diag->setFreq(fMin, fMax);
    diag->setPoints(points);
    diag->plot();
    return diag;
}

void qvna::closeEvent(QCloseEvent*) {
    onExit();
}

void qvna::on_doubleSpinBoxLCMatchRG_valueChanged(double)
{
    calcLCMatch();
}

void qvna::on_doubleSpinBoxLCMatchAntReal_valueChanged(double)
{
    calcLCMatch();
}

void qvna::on_doubleSpinBoxLCMatchAntImag_valueChanged(double)
{
    calcLCMatch();
}

void qvna::on_doubleSpinBoxLCMatchFreq_valueChanged(double)
{
    calcLCMatch();
}

void qvna::calcLCMatch() {
    bool ontx;
    double l,c;
    QString lUnit, cUnit;
    double freq = ui->doubleSpinBoxLCMatchFreq->value()*1e6;
    double rg = ui->doubleSpinBoxLCMatchRG->value();
    dcomplex z = dcomplex( ui->doubleSpinBoxLCMatchAntReal->value(), ui->doubleSpinBoxLCMatchAntImag->value());

    zCompensation(z, rg, freq, true, l, c, ontx);
    lUnit = "H"; cUnit = "F";
    if (l<0) { l = -l; lUnit = "F"; }
    if (c<0) { c = -c; cUnit = "H"; }

    if (ontx)
        ui->labelLCMatchHP->setText(QString("TP: %3%4 %1%2 ----").arg(engOut(l,3)).arg(lUnit).arg(engOut(c,3)).arg(cUnit));
    else
        ui->labelLCMatchHP->setText(QString("TP: ---- %1%2 %3%4").arg(engOut(l,3)).arg(lUnit).arg(engOut(c,3)).arg(cUnit));

    zCompensation(z, rg, freq, false, l, c, ontx);
    lUnit = "H"; cUnit = "F";
    if (l<0) { l = -l; lUnit = "F"; }
    if (c<0) { c = -c; cUnit = "H"; }

    if (ontx)
        ui->labelLCMatchTP->setText(QString("HP: %3%4 %1%2 ----").arg(engOut(c,3)).arg(cUnit).arg(engOut(l,3)).arg(lUnit));
    else
        ui->labelLCMatchTP->setText(QString("HP: ---- %1%2 %3%4").arg(engOut(c,3)).arg(cUnit).arg(engOut(l,3)).arg(lUnit));
}

void qvna::showSerialSettings(void)
{
    serialSettingsDialog->refreshNShow();
}

void qvna::on_serialPortSettingsButton_clicked()
{
    showSerialSettings();
}

void qvna::on_serialVNARadioButton_clicked()
{
    setVNAType();
}

void qvna::on_hiqsdrRadioButton_clicked()
{
    setVNAType();
}

