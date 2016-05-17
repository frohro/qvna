/********************************************************************************
** Form generated from reading UI file 'qvna.ui'
**
** Created by: Qt User Interface Compiler version 5.4.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_QVNA_H
#define UI_QVNA_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QSplitter>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_qvna
{
public:
    QAction *actionExit;
    QAction *actionScreenshot;
    QAction *actionAbout;
    QAction *actionSave_calibration;
    QAction *actionLoad_calibration;
    QAction *actionSave;
    QWidget *centralWidget;
    QGridLayout *gridLayout_9;
    QSplitter *splitter;
    QTabWidget *tabWidget;
    QWidget *tab;
    QGridLayout *gridLayout_6;
    QGroupBox *groupBoxDisplay;
    QGridLayout *gridLayout_4;
    QLabel *label;
    QComboBox *comboBoxMode;
    QLabel *labelPoints;
    QComboBox *comboBoxPoints;
    QPushButton *pushButtonStart;
    QSpinBox *spinBoxAverage;
    QLabel *label_4;
    QGroupBox *groupBoxFreq;
    QGridLayout *gridLayout;
    QComboBox *comboBoxRange;
    QPushButton *pushButtonRangeStore;
    QDoubleSpinBox *doubleSpinBoxFMin;
    QLabel *label1_2;
    QDoubleSpinBox *doubleSpinBoxFMax;
    QLabel *label1;
    QGroupBox *groupBoxAtt;
    QGridLayout *gridLayout_5;
    QLabel *labelRFAtt;
    QComboBox *comboBoxRFAtt;
    QLabel *labelTXAtt;
    QComboBox *comboBoxTXAtt;
    QPushButton *pushButtonNewPlot;
    QSpacerItem *horizontalSpacer;
    QWidget *tab_2;
    QGridLayout *gridLayout_12;
    QGroupBox *groupBoxLCMatch;
    QGridLayout *gridLayout_11;
    QLabel *label_5;
    QDoubleSpinBox *doubleSpinBoxLCMatchRG;
    QLabel *label_7;
    QDoubleSpinBox *doubleSpinBoxLCMatchAntReal;
    QDoubleSpinBox *doubleSpinBoxLCMatchAntImag;
    QLabel *label_6;
    QLabel *label_10;
    QDoubleSpinBox *doubleSpinBoxLCMatchFreq;
    QLabel *label_11;
    QLabel *labelLCMatchHP;
    QLabel *labelLCMatchTP;
    QSpacerItem *verticalSpacer;
    QWidget *tab_3;
    QGridLayout *gridLayout_8;
    QGroupBox *groupBox;
    QGridLayout *gridLayout_2;
    QLabel *label_2;
    QLineEdit *lineEditIP;
    QGroupBox *groupBox_3;
    QGridLayout *gridLayout_7;
    QComboBox *comboBoxColor;
    QPushButton *pushButtonColor;
    QSpacerItem *verticalSpacer_2;
    QMenuBar *menuBar;
    QMenu *menuDatei;
    QMenu *menuHelp;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *qvna)
    {
        if (qvna->objectName().isEmpty())
            qvna->setObjectName(QStringLiteral("qvna"));
        qvna->resize(340, 547);
        actionExit = new QAction(qvna);
        actionExit->setObjectName(QStringLiteral("actionExit"));
        actionScreenshot = new QAction(qvna);
        actionScreenshot->setObjectName(QStringLiteral("actionScreenshot"));
        actionAbout = new QAction(qvna);
        actionAbout->setObjectName(QStringLiteral("actionAbout"));
        actionSave_calibration = new QAction(qvna);
        actionSave_calibration->setObjectName(QStringLiteral("actionSave_calibration"));
        actionLoad_calibration = new QAction(qvna);
        actionLoad_calibration->setObjectName(QStringLiteral("actionLoad_calibration"));
        actionSave = new QAction(qvna);
        actionSave->setObjectName(QStringLiteral("actionSave"));
        centralWidget = new QWidget(qvna);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        gridLayout_9 = new QGridLayout(centralWidget);
        gridLayout_9->setSpacing(6);
        gridLayout_9->setContentsMargins(11, 11, 11, 11);
        gridLayout_9->setObjectName(QStringLiteral("gridLayout_9"));
        splitter = new QSplitter(centralWidget);
        splitter->setObjectName(QStringLiteral("splitter"));
        splitter->setOrientation(Qt::Horizontal);
        tabWidget = new QTabWidget(splitter);
        tabWidget->setObjectName(QStringLiteral("tabWidget"));
        tabWidget->setEnabled(true);
        tab = new QWidget();
        tab->setObjectName(QStringLiteral("tab"));
        gridLayout_6 = new QGridLayout(tab);
        gridLayout_6->setSpacing(6);
        gridLayout_6->setContentsMargins(11, 11, 11, 11);
        gridLayout_6->setObjectName(QStringLiteral("gridLayout_6"));
        groupBoxDisplay = new QGroupBox(tab);
        groupBoxDisplay->setObjectName(QStringLiteral("groupBoxDisplay"));
        gridLayout_4 = new QGridLayout(groupBoxDisplay);
        gridLayout_4->setSpacing(6);
        gridLayout_4->setContentsMargins(11, 11, 11, 11);
        gridLayout_4->setObjectName(QStringLiteral("gridLayout_4"));
        label = new QLabel(groupBoxDisplay);
        label->setObjectName(QStringLiteral("label"));

        gridLayout_4->addWidget(label, 0, 0, 1, 1);

        comboBoxMode = new QComboBox(groupBoxDisplay);
        comboBoxMode->setObjectName(QStringLiteral("comboBoxMode"));

        gridLayout_4->addWidget(comboBoxMode, 0, 1, 1, 1);

        labelPoints = new QLabel(groupBoxDisplay);
        labelPoints->setObjectName(QStringLiteral("labelPoints"));

        gridLayout_4->addWidget(labelPoints, 2, 0, 1, 1);

        comboBoxPoints = new QComboBox(groupBoxDisplay);
        comboBoxPoints->setObjectName(QStringLiteral("comboBoxPoints"));

        gridLayout_4->addWidget(comboBoxPoints, 2, 1, 1, 2);

        pushButtonStart = new QPushButton(groupBoxDisplay);
        pushButtonStart->setObjectName(QStringLiteral("pushButtonStart"));
        pushButtonStart->setCheckable(true);
        pushButtonStart->setChecked(false);

        gridLayout_4->addWidget(pushButtonStart, 0, 2, 1, 1);

        spinBoxAverage = new QSpinBox(groupBoxDisplay);
        spinBoxAverage->setObjectName(QStringLiteral("spinBoxAverage"));
        spinBoxAverage->setMinimum(1);
        spinBoxAverage->setMaximum(1000);

        gridLayout_4->addWidget(spinBoxAverage, 3, 1, 1, 2);

        label_4 = new QLabel(groupBoxDisplay);
        label_4->setObjectName(QStringLiteral("label_4"));

        gridLayout_4->addWidget(label_4, 3, 0, 1, 1);


        gridLayout_6->addWidget(groupBoxDisplay, 0, 0, 1, 2);

        groupBoxFreq = new QGroupBox(tab);
        groupBoxFreq->setObjectName(QStringLiteral("groupBoxFreq"));
        gridLayout = new QGridLayout(groupBoxFreq);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        comboBoxRange = new QComboBox(groupBoxFreq);
        comboBoxRange->setObjectName(QStringLiteral("comboBoxRange"));
        comboBoxRange->setEditable(true);

        gridLayout->addWidget(comboBoxRange, 0, 0, 1, 1);

        pushButtonRangeStore = new QPushButton(groupBoxFreq);
        pushButtonRangeStore->setObjectName(QStringLiteral("pushButtonRangeStore"));

        gridLayout->addWidget(pushButtonRangeStore, 0, 1, 1, 1);

        doubleSpinBoxFMin = new QDoubleSpinBox(groupBoxFreq);
        doubleSpinBoxFMin->setObjectName(QStringLiteral("doubleSpinBoxFMin"));
        doubleSpinBoxFMin->setDecimals(6);
        doubleSpinBoxFMin->setMaximum(61.44);

        gridLayout->addWidget(doubleSpinBoxFMin, 1, 0, 1, 1);

        label1_2 = new QLabel(groupBoxFreq);
        label1_2->setObjectName(QStringLiteral("label1_2"));

        gridLayout->addWidget(label1_2, 1, 1, 1, 1);

        doubleSpinBoxFMax = new QDoubleSpinBox(groupBoxFreq);
        doubleSpinBoxFMax->setObjectName(QStringLiteral("doubleSpinBoxFMax"));
        doubleSpinBoxFMax->setDecimals(6);
        doubleSpinBoxFMax->setMaximum(61.44);

        gridLayout->addWidget(doubleSpinBoxFMax, 2, 0, 1, 1);

        label1 = new QLabel(groupBoxFreq);
        label1->setObjectName(QStringLiteral("label1"));

        gridLayout->addWidget(label1, 2, 1, 1, 1);


        gridLayout_6->addWidget(groupBoxFreq, 1, 0, 1, 2);

        groupBoxAtt = new QGroupBox(tab);
        groupBoxAtt->setObjectName(QStringLiteral("groupBoxAtt"));
        gridLayout_5 = new QGridLayout(groupBoxAtt);
        gridLayout_5->setSpacing(6);
        gridLayout_5->setContentsMargins(11, 11, 11, 11);
        gridLayout_5->setObjectName(QStringLiteral("gridLayout_5"));
        labelRFAtt = new QLabel(groupBoxAtt);
        labelRFAtt->setObjectName(QStringLiteral("labelRFAtt"));

        gridLayout_5->addWidget(labelRFAtt, 0, 0, 1, 1);

        comboBoxRFAtt = new QComboBox(groupBoxAtt);
        comboBoxRFAtt->setObjectName(QStringLiteral("comboBoxRFAtt"));

        gridLayout_5->addWidget(comboBoxRFAtt, 0, 1, 1, 1);

        labelTXAtt = new QLabel(groupBoxAtt);
        labelTXAtt->setObjectName(QStringLiteral("labelTXAtt"));

        gridLayout_5->addWidget(labelTXAtt, 1, 0, 1, 1);

        comboBoxTXAtt = new QComboBox(groupBoxAtt);
        comboBoxTXAtt->setObjectName(QStringLiteral("comboBoxTXAtt"));

        gridLayout_5->addWidget(comboBoxTXAtt, 1, 1, 1, 1);


        gridLayout_6->addWidget(groupBoxAtt, 2, 0, 1, 2);

        pushButtonNewPlot = new QPushButton(tab);
        pushButtonNewPlot->setObjectName(QStringLiteral("pushButtonNewPlot"));

        gridLayout_6->addWidget(pushButtonNewPlot, 3, 0, 1, 1);

        horizontalSpacer = new QSpacerItem(227, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_6->addItem(horizontalSpacer, 3, 1, 1, 1);

        tabWidget->addTab(tab, QString());
        tab_2 = new QWidget();
        tab_2->setObjectName(QStringLiteral("tab_2"));
        gridLayout_12 = new QGridLayout(tab_2);
        gridLayout_12->setSpacing(6);
        gridLayout_12->setContentsMargins(11, 11, 11, 11);
        gridLayout_12->setObjectName(QStringLiteral("gridLayout_12"));
        groupBoxLCMatch = new QGroupBox(tab_2);
        groupBoxLCMatch->setObjectName(QStringLiteral("groupBoxLCMatch"));
        gridLayout_11 = new QGridLayout(groupBoxLCMatch);
        gridLayout_11->setSpacing(6);
        gridLayout_11->setContentsMargins(11, 11, 11, 11);
        gridLayout_11->setObjectName(QStringLiteral("gridLayout_11"));
        label_5 = new QLabel(groupBoxLCMatch);
        label_5->setObjectName(QStringLiteral("label_5"));

        gridLayout_11->addWidget(label_5, 0, 0, 1, 1);

        doubleSpinBoxLCMatchRG = new QDoubleSpinBox(groupBoxLCMatch);
        doubleSpinBoxLCMatchRG->setObjectName(QStringLiteral("doubleSpinBoxLCMatchRG"));
        doubleSpinBoxLCMatchRG->setDecimals(1);
        doubleSpinBoxLCMatchRG->setMaximum(1e+06);
        doubleSpinBoxLCMatchRG->setValue(50);

        gridLayout_11->addWidget(doubleSpinBoxLCMatchRG, 0, 1, 1, 2);

        label_7 = new QLabel(groupBoxLCMatch);
        label_7->setObjectName(QStringLiteral("label_7"));

        gridLayout_11->addWidget(label_7, 1, 0, 1, 1);

        doubleSpinBoxLCMatchAntReal = new QDoubleSpinBox(groupBoxLCMatch);
        doubleSpinBoxLCMatchAntReal->setObjectName(QStringLiteral("doubleSpinBoxLCMatchAntReal"));
        doubleSpinBoxLCMatchAntReal->setDecimals(1);
        doubleSpinBoxLCMatchAntReal->setMaximum(1e+06);
        doubleSpinBoxLCMatchAntReal->setValue(50);

        gridLayout_11->addWidget(doubleSpinBoxLCMatchAntReal, 1, 1, 1, 1);

        doubleSpinBoxLCMatchAntImag = new QDoubleSpinBox(groupBoxLCMatch);
        doubleSpinBoxLCMatchAntImag->setObjectName(QStringLiteral("doubleSpinBoxLCMatchAntImag"));
        doubleSpinBoxLCMatchAntImag->setDecimals(1);
        doubleSpinBoxLCMatchAntImag->setMinimum(-999999);
        doubleSpinBoxLCMatchAntImag->setMaximum(1e+06);

        gridLayout_11->addWidget(doubleSpinBoxLCMatchAntImag, 1, 2, 1, 1);

        label_6 = new QLabel(groupBoxLCMatch);
        label_6->setObjectName(QStringLiteral("label_6"));

        gridLayout_11->addWidget(label_6, 1, 3, 1, 1);

        label_10 = new QLabel(groupBoxLCMatch);
        label_10->setObjectName(QStringLiteral("label_10"));

        gridLayout_11->addWidget(label_10, 2, 0, 1, 1);

        doubleSpinBoxLCMatchFreq = new QDoubleSpinBox(groupBoxLCMatch);
        doubleSpinBoxLCMatchFreq->setObjectName(QStringLiteral("doubleSpinBoxLCMatchFreq"));
        doubleSpinBoxLCMatchFreq->setDecimals(3);

        gridLayout_11->addWidget(doubleSpinBoxLCMatchFreq, 2, 1, 1, 2);

        label_11 = new QLabel(groupBoxLCMatch);
        label_11->setObjectName(QStringLiteral("label_11"));

        gridLayout_11->addWidget(label_11, 2, 3, 1, 1);

        labelLCMatchHP = new QLabel(groupBoxLCMatch);
        labelLCMatchHP->setObjectName(QStringLiteral("labelLCMatchHP"));

        gridLayout_11->addWidget(labelLCMatchHP, 3, 0, 1, 5);

        labelLCMatchTP = new QLabel(groupBoxLCMatch);
        labelLCMatchTP->setObjectName(QStringLiteral("labelLCMatchTP"));

        gridLayout_11->addWidget(labelLCMatchTP, 4, 0, 1, 5);


        gridLayout_12->addWidget(groupBoxLCMatch, 0, 0, 1, 1);

        verticalSpacer = new QSpacerItem(20, 274, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout_12->addItem(verticalSpacer, 1, 0, 1, 1);

        tabWidget->addTab(tab_2, QString());
        tab_3 = new QWidget();
        tab_3->setObjectName(QStringLiteral("tab_3"));
        gridLayout_8 = new QGridLayout(tab_3);
        gridLayout_8->setSpacing(6);
        gridLayout_8->setContentsMargins(11, 11, 11, 11);
        gridLayout_8->setObjectName(QStringLiteral("gridLayout_8"));
        groupBox = new QGroupBox(tab_3);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        gridLayout_2 = new QGridLayout(groupBox);
        gridLayout_2->setSpacing(6);
        gridLayout_2->setContentsMargins(11, 11, 11, 11);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        label_2 = new QLabel(groupBox);
        label_2->setObjectName(QStringLiteral("label_2"));

        gridLayout_2->addWidget(label_2, 0, 0, 1, 1);

        lineEditIP = new QLineEdit(groupBox);
        lineEditIP->setObjectName(QStringLiteral("lineEditIP"));

        gridLayout_2->addWidget(lineEditIP, 0, 1, 1, 1);


        gridLayout_8->addWidget(groupBox, 0, 0, 1, 1);

        groupBox_3 = new QGroupBox(tab_3);
        groupBox_3->setObjectName(QStringLiteral("groupBox_3"));
        gridLayout_7 = new QGridLayout(groupBox_3);
        gridLayout_7->setSpacing(6);
        gridLayout_7->setContentsMargins(11, 11, 11, 11);
        gridLayout_7->setObjectName(QStringLiteral("gridLayout_7"));
        comboBoxColor = new QComboBox(groupBox_3);
        comboBoxColor->setObjectName(QStringLiteral("comboBoxColor"));

        gridLayout_7->addWidget(comboBoxColor, 0, 0, 1, 1);

        pushButtonColor = new QPushButton(groupBox_3);
        pushButtonColor->setObjectName(QStringLiteral("pushButtonColor"));

        gridLayout_7->addWidget(pushButtonColor, 1, 0, 1, 1);


        gridLayout_8->addWidget(groupBox_3, 1, 0, 1, 1);

        verticalSpacer_2 = new QSpacerItem(20, 410, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout_8->addItem(verticalSpacer_2, 2, 0, 1, 1);

        tabWidget->addTab(tab_3, QString());
        splitter->addWidget(tabWidget);

        gridLayout_9->addWidget(splitter, 0, 0, 1, 1);

        qvna->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(qvna);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 340, 21));
        menuDatei = new QMenu(menuBar);
        menuDatei->setObjectName(QStringLiteral("menuDatei"));
        menuHelp = new QMenu(menuBar);
        menuHelp->setObjectName(QStringLiteral("menuHelp"));
        qvna->setMenuBar(menuBar);
        statusBar = new QStatusBar(qvna);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        qvna->setStatusBar(statusBar);

        menuBar->addAction(menuDatei->menuAction());
        menuBar->addAction(menuHelp->menuAction());
        menuDatei->addAction(actionLoad_calibration);
        menuDatei->addSeparator();
        menuDatei->addAction(actionSave);
        menuDatei->addAction(actionSave_calibration);
        menuDatei->addSeparator();
        menuDatei->addAction(actionExit);
        menuHelp->addAction(actionAbout);

        retranslateUi(qvna);

        tabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(qvna);
    } // setupUi

    void retranslateUi(QMainWindow *qvna)
    {
        qvna->setWindowTitle(QApplication::translate("qvna", "QVna", 0));
        actionExit->setText(QApplication::translate("qvna", "Exit", 0));
        actionScreenshot->setText(QApplication::translate("qvna", "Save screenshot", 0));
        actionAbout->setText(QApplication::translate("qvna", "About", 0));
        actionSave_calibration->setText(QApplication::translate("qvna", "Save calibration", 0));
        actionLoad_calibration->setText(QApplication::translate("qvna", "Load calibration", 0));
        actionSave->setText(QApplication::translate("qvna", "Save measurement", 0));
        groupBoxDisplay->setTitle(QApplication::translate("qvna", "Display", 0));
        label->setText(QApplication::translate("qvna", "Mode", 0));
        comboBoxMode->clear();
        comboBoxMode->insertItems(0, QStringList()
         << QApplication::translate("qvna", "Transmission", 0)
         << QApplication::translate("qvna", "Reflection", 0)
         << QApplication::translate("qvna", "Calibrate through", 0)
         << QApplication::translate("qvna", "Calibrate open ", 0)
         << QApplication::translate("qvna", "Calibrate match", 0)
         << QApplication::translate("qvna", "Calibrate short", 0)
        );
        labelPoints->setText(QApplication::translate("qvna", "Points", 0));
        comboBoxPoints->clear();
        comboBoxPoints->insertItems(0, QStringList()
         << QApplication::translate("qvna", "500", 0)
         << QApplication::translate("qvna", "1000", 0)
         << QApplication::translate("qvna", "2000", 0)
         << QApplication::translate("qvna", "5000", 0)
         << QApplication::translate("qvna", "10000", 0)
         << QApplication::translate("qvna", "20000", 0)
        );
        pushButtonStart->setText(QApplication::translate("qvna", "Start", 0));
        label_4->setText(QApplication::translate("qvna", "Average", 0));
        groupBoxFreq->setTitle(QApplication::translate("qvna", "Range", 0));
        pushButtonRangeStore->setText(QApplication::translate("qvna", "Store", 0));
        label1_2->setText(QApplication::translate("qvna", "MHz", 0));
        label1->setText(QApplication::translate("qvna", "MHz", 0));
        groupBoxAtt->setTitle(QApplication::translate("qvna", "Att", 0));
        labelRFAtt->setText(QApplication::translate("qvna", "RF Attentuator (dB)", 0));
        comboBoxRFAtt->clear();
        comboBoxRFAtt->insertItems(0, QStringList()
         << QApplication::translate("qvna", "0", 0)
         << QApplication::translate("qvna", "-10", 0)
         << QApplication::translate("qvna", "-20", 0)
         << QApplication::translate("qvna", "-30", 0)
         << QApplication::translate("qvna", "-40", 0)
        );
        labelTXAtt->setText(QApplication::translate("qvna", "TX Attentuator (dB)", 0));
        comboBoxTXAtt->clear();
        comboBoxTXAtt->insertItems(0, QStringList()
         << QApplication::translate("qvna", "0", 0)
         << QApplication::translate("qvna", "10", 0)
         << QApplication::translate("qvna", "20", 0)
        );
        pushButtonNewPlot->setText(QApplication::translate("qvna", "new Plot", 0));
        tabWidget->setTabText(tabWidget->indexOf(tab), QApplication::translate("qvna", "Parameter", 0));
        groupBoxLCMatch->setTitle(QApplication::translate("qvna", "LC Match", 0));
        label_5->setText(QApplication::translate("qvna", "RG", 0));
        label_7->setText(QApplication::translate("qvna", "Ant", 0));
        label_6->setText(QApplication::translate("qvna", "j", 0));
        label_10->setText(QApplication::translate("qvna", "Freq", 0));
        label_11->setText(QApplication::translate("qvna", "MHz", 0));
        labelLCMatchHP->setText(QApplication::translate("qvna", "HP:", 0));
        labelLCMatchTP->setText(QApplication::translate("qvna", "TP:", 0));
        tabWidget->setTabText(tabWidget->indexOf(tab_2), QApplication::translate("qvna", "Calc", 0));
        groupBox->setTitle(QApplication::translate("qvna", "Device", 0));
        label_2->setText(QApplication::translate("qvna", "HIQSDR-IP", 0));
#ifndef QT_NO_TOOLTIP
        lineEditIP->setToolTip(QApplication::translate("qvna", "restart to make changes valid", 0));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_STATUSTIP
        lineEditIP->setStatusTip(QString());
#endif // QT_NO_STATUSTIP
#ifndef QT_NO_WHATSTHIS
        lineEditIP->setWhatsThis(QString());
#endif // QT_NO_WHATSTHIS
        groupBox_3->setTitle(QApplication::translate("qvna", "Colors", 0));
        comboBoxColor->clear();
        comboBoxColor->insertItems(0, QStringList()
         << QApplication::translate("qvna", "Background", 0)
         << QApplication::translate("qvna", "Line real", 0)
         << QApplication::translate("qvna", "Line imag", 0)
         << QApplication::translate("qvna", "Label real", 0)
         << QApplication::translate("qvna", "Label imag", 0)
         << QApplication::translate("qvna", "Label freq", 0)
         << QApplication::translate("qvna", "Marker", 0)
         << QApplication::translate("qvna", "Grid", 0)
         << QApplication::translate("qvna", "Smith real", 0)
         << QApplication::translate("qvna", "Smith imag", 0)
         << QApplication::translate("qvna", "Text", 0)
        );
        pushButtonColor->setText(QApplication::translate("qvna", "Color", 0));
        tabWidget->setTabText(tabWidget->indexOf(tab_3), QApplication::translate("qvna", "Settings", 0));
        menuDatei->setTitle(QApplication::translate("qvna", "File", 0));
        menuHelp->setTitle(QApplication::translate("qvna", "Help", 0));
    } // retranslateUi

};

namespace Ui {
    class qvna: public Ui_qvna {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_QVNA_H
