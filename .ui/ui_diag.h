/********************************************************************************
** Form generated from reading UI file 'diag.ui'
**
** Created by: Qt User Interface Compiler version 5.7.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DIAG_H
#define UI_DIAG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGraphicsView>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Diag
{
public:
    QGridLayout *gridLayout;
    QGraphicsView *graphicsView;
    QLabel *label;
    QHBoxLayout *horizontalLayout;
    QSlider *horizontalSliderScale;
    QPushButton *pushButtonScreenShot;
    QComboBox *comboBoxMode;

    void setupUi(QWidget *Diag)
    {
        if (Diag->objectName().isEmpty())
            Diag->setObjectName(QStringLiteral("Diag"));
        Diag->resize(640, 480);
        gridLayout = new QGridLayout(Diag);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        graphicsView = new QGraphicsView(Diag);
        graphicsView->setObjectName(QStringLiteral("graphicsView"));

        gridLayout->addWidget(graphicsView, 0, 0, 1, 2);

        label = new QLabel(Diag);
        label->setObjectName(QStringLiteral("label"));

        gridLayout->addWidget(label, 1, 0, 1, 1);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalSliderScale = new QSlider(Diag);
        horizontalSliderScale->setObjectName(QStringLiteral("horizontalSliderScale"));
        horizontalSliderScale->setMinimum(10);
        horizontalSliderScale->setMaximum(50);
        horizontalSliderScale->setPageStep(1);
        horizontalSliderScale->setValue(20);
        horizontalSliderScale->setOrientation(Qt::Horizontal);

        horizontalLayout->addWidget(horizontalSliderScale);

        pushButtonScreenShot = new QPushButton(Diag);
        pushButtonScreenShot->setObjectName(QStringLiteral("pushButtonScreenShot"));

        horizontalLayout->addWidget(pushButtonScreenShot);

        comboBoxMode = new QComboBox(Diag);
        comboBoxMode->setObjectName(QStringLiteral("comboBoxMode"));

        horizontalLayout->addWidget(comboBoxMode);


        gridLayout->addLayout(horizontalLayout, 1, 1, 1, 1);


        retranslateUi(Diag);

        QMetaObject::connectSlotsByName(Diag);
    } // setupUi

    void retranslateUi(QWidget *Diag)
    {
        Diag->setWindowTitle(QApplication::translate("Diag", "Plot", Q_NULLPTR));
        label->setText(QApplication::translate("Diag", "Scale", Q_NULLPTR));
        pushButtonScreenShot->setText(QApplication::translate("Diag", "Screenshot", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class Diag: public Ui_Diag {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DIAG_H
