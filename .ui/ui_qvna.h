/********************************************************************************
** Form generated from reading UI file 'qvna.ui'
**
** Created by: Qt User Interface Compiler version 5.7.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_QVNA_H
#define UI_QVNA_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include <console.h>

QT_BEGIN_NAMESPACE

class Ui_qvna
{
public:
    QAction *actionQuit;
    QAction *actionScreenshot;
    QAction *actionAbout;
    QAction *actionSave_calibration;
    QAction *actionLoad_calibration;
    QAction *actionSave;
    QAction *actionConnect;
    QAction *actionDisconnect;
    QAction *actionClear;
    QAction *actionConfigure;
    QAction *actionAbout_Qt;
    QWidget *centralWidget;
    QVBoxLayout *verticalLayout_3;
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
    QGroupBox *groupBox_3;
    QWidget *layoutWidget;
    QHBoxLayout *horizontalLayout_3;
    QComboBox *comboBoxColor;
    QPushButton *pushButtonColor;
    QGroupBox *groupBox_4;
    QWidget *layoutWidget1;
    QHBoxLayout *horizontalLayout;
    QRadioButton *hiqsdrRadioButton;
    QRadioButton *serialVNARadioButton;
    QGroupBox *groupBoxHIQSDR;
    QWidget *layoutWidget2;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_2;
    QLineEdit *lineEditIP;
    QGroupBox *groupBoxSerial;
    QPushButton *serialPortSettingsButton;
    Console *console;
    QCheckBox *showSerialCheckbox;
    QMenuBar *menuBar;
    QMenu *menuDatei;
    QMenu *menuHelp;
    QMenu *menuSerial;
    QStatusBar *statusBar;
    QButtonGroup *buttonGroup;

    void setupUi(QMainWindow *qvna)
    {
        if (qvna->objectName().isEmpty())
            qvna->setObjectName(QStringLiteral("qvna"));
        qvna->resize(369, 759);
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::MinimumExpanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(qvna->sizePolicy().hasHeightForWidth());
        qvna->setSizePolicy(sizePolicy);
        actionQuit = new QAction(qvna);
        actionQuit->setObjectName(QStringLiteral("actionQuit"));
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
        actionConnect = new QAction(qvna);
        actionConnect->setObjectName(QStringLiteral("actionConnect"));
        actionDisconnect = new QAction(qvna);
        actionDisconnect->setObjectName(QStringLiteral("actionDisconnect"));
        actionClear = new QAction(qvna);
        actionClear->setObjectName(QStringLiteral("actionClear"));
        actionConfigure = new QAction(qvna);
        actionConfigure->setObjectName(QStringLiteral("actionConfigure"));
        actionAbout_Qt = new QAction(qvna);
        actionAbout_Qt->setObjectName(QStringLiteral("actionAbout_Qt"));
        centralWidget = new QWidget(qvna);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        verticalLayout_3 = new QVBoxLayout(centralWidget);
        verticalLayout_3->setSpacing(6);
        verticalLayout_3->setContentsMargins(11, 11, 11, 11);
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        tabWidget = new QTabWidget(centralWidget);
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
        doubleSpinBoxLCMatchRG->setMaximum(1e+6);
        doubleSpinBoxLCMatchRG->setValue(50);

        gridLayout_11->addWidget(doubleSpinBoxLCMatchRG, 0, 1, 1, 2);

        label_7 = new QLabel(groupBoxLCMatch);
        label_7->setObjectName(QStringLiteral("label_7"));

        gridLayout_11->addWidget(label_7, 1, 0, 1, 1);

        doubleSpinBoxLCMatchAntReal = new QDoubleSpinBox(groupBoxLCMatch);
        doubleSpinBoxLCMatchAntReal->setObjectName(QStringLiteral("doubleSpinBoxLCMatchAntReal"));
        doubleSpinBoxLCMatchAntReal->setDecimals(1);
        doubleSpinBoxLCMatchAntReal->setMaximum(1e+6);
        doubleSpinBoxLCMatchAntReal->setValue(50);

        gridLayout_11->addWidget(doubleSpinBoxLCMatchAntReal, 1, 1, 1, 1);

        doubleSpinBoxLCMatchAntImag = new QDoubleSpinBox(groupBoxLCMatch);
        doubleSpinBoxLCMatchAntImag->setObjectName(QStringLiteral("doubleSpinBoxLCMatchAntImag"));
        doubleSpinBoxLCMatchAntImag->setDecimals(1);
        doubleSpinBoxLCMatchAntImag->setMinimum(-999999);
        doubleSpinBoxLCMatchAntImag->setMaximum(1e+6);

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
        groupBox_3 = new QGroupBox(tab_3);
        groupBox_3->setObjectName(QStringLiteral("groupBox_3"));
        groupBox_3->setGeometry(QRect(10, 0, 329, 91));
        QSizePolicy sizePolicy1(QSizePolicy::Preferred, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(groupBox_3->sizePolicy().hasHeightForWidth());
        groupBox_3->setSizePolicy(sizePolicy1);
        layoutWidget = new QWidget(groupBox_3);
        layoutWidget->setObjectName(QStringLiteral("layoutWidget"));
        layoutWidget->setGeometry(QRect(17, 25, 204, 29));
        horizontalLayout_3 = new QHBoxLayout(layoutWidget);
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        horizontalLayout_3->setContentsMargins(0, 0, 0, 0);
        comboBoxColor = new QComboBox(layoutWidget);
        comboBoxColor->setObjectName(QStringLiteral("comboBoxColor"));

        horizontalLayout_3->addWidget(comboBoxColor);

        pushButtonColor = new QPushButton(layoutWidget);
        pushButtonColor->setObjectName(QStringLiteral("pushButtonColor"));

        horizontalLayout_3->addWidget(pushButtonColor);

        groupBox_4 = new QGroupBox(tab_3);
        groupBox_4->setObjectName(QStringLiteral("groupBox_4"));
        groupBox_4->setGeometry(QRect(10, 80, 329, 81));
        sizePolicy1.setHeightForWidth(groupBox_4->sizePolicy().hasHeightForWidth());
        groupBox_4->setSizePolicy(sizePolicy1);
        layoutWidget1 = new QWidget(groupBox_4);
        layoutWidget1->setObjectName(QStringLiteral("layoutWidget1"));
        layoutWidget1->setGeometry(QRect(17, 48, 196, 24));
        horizontalLayout = new QHBoxLayout(layoutWidget1);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        hiqsdrRadioButton = new QRadioButton(layoutWidget1);
        buttonGroup = new QButtonGroup(qvna);
        buttonGroup->setObjectName(QStringLiteral("buttonGroup"));
        buttonGroup->addButton(hiqsdrRadioButton);
        hiqsdrRadioButton->setObjectName(QStringLiteral("hiqsdrRadioButton"));

        horizontalLayout->addWidget(hiqsdrRadioButton);

        serialVNARadioButton = new QRadioButton(layoutWidget1);
        buttonGroup->addButton(serialVNARadioButton);
        serialVNARadioButton->setObjectName(QStringLiteral("serialVNARadioButton"));
        serialVNARadioButton->setChecked(true);

        horizontalLayout->addWidget(serialVNARadioButton);

        groupBoxHIQSDR = new QGroupBox(tab_3);
        groupBoxHIQSDR->setObjectName(QStringLiteral("groupBoxHIQSDR"));
        groupBoxHIQSDR->setGeometry(QRect(10, 160, 329, 61));
        QSizePolicy sizePolicy2(QSizePolicy::Expanding, QSizePolicy::Fixed);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(groupBoxHIQSDR->sizePolicy().hasHeightForWidth());
        groupBoxHIQSDR->setSizePolicy(sizePolicy2);
        groupBoxHIQSDR->setMinimumSize(QSize(0, 50));
        layoutWidget2 = new QWidget(groupBoxHIQSDR);
        layoutWidget2->setObjectName(QStringLiteral("layoutWidget2"));
        layoutWidget2->setGeometry(QRect(17, 25, 226, 29));
        horizontalLayout_2 = new QHBoxLayout(layoutWidget2);
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        horizontalLayout_2->setContentsMargins(0, 0, 0, 0);
        label_2 = new QLabel(layoutWidget2);
        label_2->setObjectName(QStringLiteral("label_2"));

        horizontalLayout_2->addWidget(label_2);

        lineEditIP = new QLineEdit(layoutWidget2);
        lineEditIP->setObjectName(QStringLiteral("lineEditIP"));

        horizontalLayout_2->addWidget(lineEditIP);

        groupBoxSerial = new QGroupBox(tab_3);
        groupBoxSerial->setObjectName(QStringLiteral("groupBoxSerial"));
        groupBoxSerial->setGeometry(QRect(10, 220, 331, 411));
        serialPortSettingsButton = new QPushButton(groupBoxSerial);
        serialPortSettingsButton->setObjectName(QStringLiteral("serialPortSettingsButton"));
        serialPortSettingsButton->setGeometry(QRect(10, 50, 149, 27));
        QSizePolicy sizePolicy3(QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding);
        sizePolicy3.setHorizontalStretch(0);
        sizePolicy3.setVerticalStretch(0);
        sizePolicy3.setHeightForWidth(serialPortSettingsButton->sizePolicy().hasHeightForWidth());
        serialPortSettingsButton->setSizePolicy(sizePolicy3);
        console = new Console(groupBoxSerial);
        console->setObjectName(QStringLiteral("console"));
        console->setGeometry(QRect(0, 100, 321, 331));
        QSizePolicy sizePolicy4(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy4.setHorizontalStretch(0);
        sizePolicy4.setVerticalStretch(0);
        sizePolicy4.setHeightForWidth(console->sizePolicy().hasHeightForWidth());
        console->setSizePolicy(sizePolicy4);
        console->setAcceptRichText(false);
        showSerialCheckbox = new QCheckBox(groupBoxSerial);
        showSerialCheckbox->setObjectName(QStringLiteral("showSerialCheckbox"));
        showSerialCheckbox->setGeometry(QRect(180, 50, 141, 22));
        tabWidget->addTab(tab_3, QString());

        verticalLayout_3->addWidget(tabWidget);

        qvna->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(qvna);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 369, 25));
        menuDatei = new QMenu(menuBar);
        menuDatei->setObjectName(QStringLiteral("menuDatei"));
        menuHelp = new QMenu(menuBar);
        menuHelp->setObjectName(QStringLiteral("menuHelp"));
        menuSerial = new QMenu(menuBar);
        menuSerial->setObjectName(QStringLiteral("menuSerial"));
        qvna->setMenuBar(menuBar);
        statusBar = new QStatusBar(qvna);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        qvna->setStatusBar(statusBar);

        menuBar->addAction(menuDatei->menuAction());
        menuBar->addAction(menuSerial->menuAction());
        menuBar->addAction(menuHelp->menuAction());
        menuDatei->addAction(actionLoad_calibration);
        menuDatei->addSeparator();
        menuDatei->addAction(actionSave);
        menuDatei->addAction(actionSave_calibration);
        menuDatei->addSeparator();
        menuDatei->addAction(actionQuit);
        menuHelp->addAction(actionAbout);
        menuHelp->addAction(actionAbout_Qt);
        menuSerial->addAction(actionConnect);
        menuSerial->addAction(actionDisconnect);
        menuSerial->addAction(actionClear);
        menuSerial->addAction(actionConfigure);

        retranslateUi(qvna);
        QObject::connect(actionConfigure, SIGNAL(triggered()), serialPortSettingsButton, SLOT(click()));

        tabWidget->setCurrentIndex(2);


        QMetaObject::connectSlotsByName(qvna);
    } // setupUi

    void retranslateUi(QMainWindow *qvna)
    {
        qvna->setWindowTitle(QApplication::translate("qvna", "QVna", Q_NULLPTR));
        actionQuit->setText(QApplication::translate("qvna", "Quit", Q_NULLPTR));
        actionScreenshot->setText(QApplication::translate("qvna", "Save screenshot", Q_NULLPTR));
        actionAbout->setText(QApplication::translate("qvna", "About", Q_NULLPTR));
        actionSave_calibration->setText(QApplication::translate("qvna", "Save calibration", Q_NULLPTR));
        actionLoad_calibration->setText(QApplication::translate("qvna", "Load calibration", Q_NULLPTR));
        actionSave->setText(QApplication::translate("qvna", "Save measurement", Q_NULLPTR));
        actionConnect->setText(QApplication::translate("qvna", "Connect", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        actionConnect->setToolTip(QApplication::translate("qvna", " Connect", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        actionDisconnect->setText(QApplication::translate("qvna", "Disconnect", Q_NULLPTR));
        actionClear->setText(QApplication::translate("qvna", "Clear", Q_NULLPTR));
        actionConfigure->setText(QApplication::translate("qvna", "Configure", Q_NULLPTR));
        actionAbout_Qt->setText(QApplication::translate("qvna", "About Qt", Q_NULLPTR));
        groupBoxDisplay->setTitle(QApplication::translate("qvna", "Display", Q_NULLPTR));
        label->setText(QApplication::translate("qvna", "Mode", Q_NULLPTR));
        comboBoxMode->clear();
        comboBoxMode->insertItems(0, QStringList()
         << QApplication::translate("qvna", "Transmission", Q_NULLPTR)
         << QApplication::translate("qvna", "Reflection", Q_NULLPTR)
         << QApplication::translate("qvna", "Calibrate through", Q_NULLPTR)
         << QApplication::translate("qvna", "Calibrate open ", Q_NULLPTR)
         << QApplication::translate("qvna", "Calibrate match", Q_NULLPTR)
         << QApplication::translate("qvna", "Calibrate short", Q_NULLPTR)
        );
        labelPoints->setText(QApplication::translate("qvna", "Points", Q_NULLPTR));
        comboBoxPoints->clear();
        comboBoxPoints->insertItems(0, QStringList()
         << QApplication::translate("qvna", "500", Q_NULLPTR)
         << QApplication::translate("qvna", "1000", Q_NULLPTR)
         << QApplication::translate("qvna", "2000", Q_NULLPTR)
         << QApplication::translate("qvna", "5000", Q_NULLPTR)
         << QApplication::translate("qvna", "10000", Q_NULLPTR)
         << QApplication::translate("qvna", "20000", Q_NULLPTR)
        );
        pushButtonStart->setText(QApplication::translate("qvna", "Start", Q_NULLPTR));
        label_4->setText(QApplication::translate("qvna", "Average", Q_NULLPTR));
        groupBoxFreq->setTitle(QApplication::translate("qvna", "Range", Q_NULLPTR));
        pushButtonRangeStore->setText(QApplication::translate("qvna", "Store", Q_NULLPTR));
        label1_2->setText(QApplication::translate("qvna", "MHz", Q_NULLPTR));
        label1->setText(QApplication::translate("qvna", "MHz", Q_NULLPTR));
        groupBoxAtt->setTitle(QApplication::translate("qvna", "Att", Q_NULLPTR));
        labelRFAtt->setText(QApplication::translate("qvna", "RF Attentuator (dB)", Q_NULLPTR));
        comboBoxRFAtt->clear();
        comboBoxRFAtt->insertItems(0, QStringList()
         << QApplication::translate("qvna", "0", Q_NULLPTR)
         << QApplication::translate("qvna", "-10", Q_NULLPTR)
         << QApplication::translate("qvna", "-20", Q_NULLPTR)
         << QApplication::translate("qvna", "-30", Q_NULLPTR)
         << QApplication::translate("qvna", "-40", Q_NULLPTR)
        );
        labelTXAtt->setText(QApplication::translate("qvna", "TX Attentuator (dB)", Q_NULLPTR));
        comboBoxTXAtt->clear();
        comboBoxTXAtt->insertItems(0, QStringList()
         << QApplication::translate("qvna", "0", Q_NULLPTR)
         << QApplication::translate("qvna", "10", Q_NULLPTR)
         << QApplication::translate("qvna", "20", Q_NULLPTR)
        );
        pushButtonNewPlot->setText(QApplication::translate("qvna", "new Plot", Q_NULLPTR));
        tabWidget->setTabText(tabWidget->indexOf(tab), QApplication::translate("qvna", "Parameter", Q_NULLPTR));
        groupBoxLCMatch->setTitle(QApplication::translate("qvna", "LC Match", Q_NULLPTR));
        label_5->setText(QApplication::translate("qvna", "RG", Q_NULLPTR));
        label_7->setText(QApplication::translate("qvna", "Ant", Q_NULLPTR));
        label_6->setText(QApplication::translate("qvna", "j", Q_NULLPTR));
        label_10->setText(QApplication::translate("qvna", "Freq", Q_NULLPTR));
        label_11->setText(QApplication::translate("qvna", "MHz", Q_NULLPTR));
        labelLCMatchHP->setText(QApplication::translate("qvna", "HP:", Q_NULLPTR));
        labelLCMatchTP->setText(QApplication::translate("qvna", "TP:", Q_NULLPTR));
        tabWidget->setTabText(tabWidget->indexOf(tab_2), QApplication::translate("qvna", "Calc", Q_NULLPTR));
        groupBox_3->setTitle(QApplication::translate("qvna", "Colors", Q_NULLPTR));
        comboBoxColor->clear();
        comboBoxColor->insertItems(0, QStringList()
         << QApplication::translate("qvna", "Background", Q_NULLPTR)
         << QApplication::translate("qvna", "Line real", Q_NULLPTR)
         << QApplication::translate("qvna", "Line imag", Q_NULLPTR)
         << QApplication::translate("qvna", "Label real", Q_NULLPTR)
         << QApplication::translate("qvna", "Label imag", Q_NULLPTR)
         << QApplication::translate("qvna", "Label freq", Q_NULLPTR)
         << QApplication::translate("qvna", "Marker", Q_NULLPTR)
         << QApplication::translate("qvna", "Grid", Q_NULLPTR)
         << QApplication::translate("qvna", "Smith real", Q_NULLPTR)
         << QApplication::translate("qvna", "Smith imag", Q_NULLPTR)
         << QApplication::translate("qvna", "Text", Q_NULLPTR)
        );
        pushButtonColor->setText(QApplication::translate("qvna", "Color", Q_NULLPTR));
        groupBox_4->setTitle(QApplication::translate("qvna", "VNA Type", Q_NULLPTR));
        hiqsdrRadioButton->setText(QApplication::translate("qvna", "HIQSDR", Q_NULLPTR));
        serialVNARadioButton->setText(QApplication::translate("qvna", "Serial VNA", Q_NULLPTR));
        groupBoxHIQSDR->setTitle(QApplication::translate("qvna", "HIQSDR", Q_NULLPTR));
        label_2->setText(QApplication::translate("qvna", "HIQSDR-IP", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        lineEditIP->setToolTip(QApplication::translate("qvna", "restart to make changes valid", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_STATUSTIP
        lineEditIP->setStatusTip(QString());
#endif // QT_NO_STATUSTIP
#ifndef QT_NO_WHATSTHIS
        lineEditIP->setWhatsThis(QString());
#endif // QT_NO_WHATSTHIS
        groupBoxSerial->setTitle(QApplication::translate("qvna", "Serial Port", Q_NULLPTR));
        serialPortSettingsButton->setText(QApplication::translate("qvna", "Serial Port Settings", Q_NULLPTR));
        showSerialCheckbox->setText(QApplication::translate("qvna", "Show Serial Data", Q_NULLPTR));
        tabWidget->setTabText(tabWidget->indexOf(tab_3), QApplication::translate("qvna", "Settings", Q_NULLPTR));
        menuDatei->setTitle(QApplication::translate("qvna", "File", Q_NULLPTR));
        menuHelp->setTitle(QApplication::translate("qvna", "Help", Q_NULLPTR));
        menuSerial->setTitle(QApplication::translate("qvna", "Serial", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class qvna: public Ui_qvna {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_QVNA_H
