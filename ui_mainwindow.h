/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QSlider>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include <myglwidget.h>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QHBoxLayout *horizontalLayout;
    MyGLWidget *widget;
    QVBoxLayout *vblControls;
    QGroupBox *gbxRotation;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout_2;
    QSpinBox *sbxRotationZ;
    QSlider *sldRotationZ;
    QLabel *lblRotationZ;
    QLabel *label;
    QSpinBox *sbxTranslateZ;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(706, 418);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        horizontalLayout = new QHBoxLayout(centralWidget);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        widget = new MyGLWidget(centralWidget);
        widget->setObjectName(QStringLiteral("widget"));
        widget->setMinimumSize(QSize(400, 400));

        horizontalLayout->addWidget(widget);

        vblControls = new QVBoxLayout();
        vblControls->setSpacing(6);
        vblControls->setObjectName(QStringLiteral("vblControls"));
        gbxRotation = new QGroupBox(centralWidget);
        gbxRotation->setObjectName(QStringLiteral("gbxRotation"));
        gbxRotation->setMaximumSize(QSize(400, 400));
        verticalLayout = new QVBoxLayout(gbxRotation);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        sbxRotationZ = new QSpinBox(gbxRotation);
        sbxRotationZ->setObjectName(QStringLiteral("sbxRotationZ"));
        sbxRotationZ->setReadOnly(true);
        sbxRotationZ->setMaximum(359);

        horizontalLayout_2->addWidget(sbxRotationZ);

        sldRotationZ = new QSlider(gbxRotation);
        sldRotationZ->setObjectName(QStringLiteral("sldRotationZ"));
        sldRotationZ->setMaximum(359);
        sldRotationZ->setOrientation(Qt::Horizontal);

        horizontalLayout_2->addWidget(sldRotationZ);

        lblRotationZ = new QLabel(gbxRotation);
        lblRotationZ->setObjectName(QStringLiteral("lblRotationZ"));

        horizontalLayout_2->addWidget(lblRotationZ);


        verticalLayout->addLayout(horizontalLayout_2);

        label = new QLabel(gbxRotation);
        label->setObjectName(QStringLiteral("label"));

        verticalLayout->addWidget(label);

        sbxTranslateZ = new QSpinBox(gbxRotation);
        sbxTranslateZ->setObjectName(QStringLiteral("sbxTranslateZ"));
        sbxTranslateZ->setMinimum(-300);
        sbxTranslateZ->setMaximum(100);

        verticalLayout->addWidget(sbxTranslateZ);


        vblControls->addWidget(gbxRotation);


        horizontalLayout->addLayout(vblControls);

        MainWindow->setCentralWidget(centralWidget);

        retranslateUi(MainWindow);
        QObject::connect(sldRotationZ, SIGNAL(valueChanged(int)), sbxRotationZ, SLOT(setValue(int)));
        QObject::connect(sldRotationZ, SIGNAL(valueChanged(int)), widget, SLOT(receiveRotationZ(int)));

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "Praktikum3_n", Q_NULLPTR));
        gbxRotation->setTitle(QApplication::translate("MainWindow", "Rotation", Q_NULLPTR));
        lblRotationZ->setText(QApplication::translate("MainWindow", "Rotation y", Q_NULLPTR));
        label->setText(QApplication::translate("MainWindow", "Zoom", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
