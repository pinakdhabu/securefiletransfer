/********************************************************************************
** Form generated from reading UI file 'ServerWidget.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SERVERWIDGET_H
#define UI_SERVERWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPlainTextEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ServerWidget
{
public:
    QVBoxLayout *verticalLayout;
    QFormLayout *formLayout;
    QLabel *labelPort;
    QLineEdit *portEdit;
    QLabel *labelKey;
    QLineEdit *keyEdit;
    QHBoxLayout *buttonLayout;
    QPushButton *startButton;
    QPushButton *stopButton;
    QSpacerItem *hSpacer;
    QPushButton *selectFolderButton;
    QPlainTextEdit *log;

    void setupUi(QWidget *ServerWidget)
    {
        if (ServerWidget->objectName().isEmpty())
            ServerWidget->setObjectName("ServerWidget");
        ServerWidget->setMinimumSize(QSize(400, 300));
        verticalLayout = new QVBoxLayout(ServerWidget);
        verticalLayout->setObjectName("verticalLayout");
        formLayout = new QFormLayout();
        formLayout->setObjectName("formLayout");
        formLayout->setLabelAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        labelPort = new QLabel(ServerWidget);
        labelPort->setObjectName("labelPort");

        formLayout->setWidget(0, QFormLayout::ItemRole::LabelRole, labelPort);

        portEdit = new QLineEdit(ServerWidget);
        portEdit->setObjectName("portEdit");

        formLayout->setWidget(0, QFormLayout::ItemRole::FieldRole, portEdit);

        labelKey = new QLabel(ServerWidget);
        labelKey->setObjectName("labelKey");

        formLayout->setWidget(1, QFormLayout::ItemRole::LabelRole, labelKey);

        keyEdit = new QLineEdit(ServerWidget);
        keyEdit->setObjectName("keyEdit");

        formLayout->setWidget(1, QFormLayout::ItemRole::FieldRole, keyEdit);


        verticalLayout->addLayout(formLayout);

        buttonLayout = new QHBoxLayout();
        buttonLayout->setObjectName("buttonLayout");
        startButton = new QPushButton(ServerWidget);
        startButton->setObjectName("startButton");

        buttonLayout->addWidget(startButton);

        stopButton = new QPushButton(ServerWidget);
        stopButton->setObjectName("stopButton");

        buttonLayout->addWidget(stopButton);

        hSpacer = new QSpacerItem(0, 0, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        buttonLayout->addItem(hSpacer);

        selectFolderButton = new QPushButton(ServerWidget);
        selectFolderButton->setObjectName("selectFolderButton");

        buttonLayout->addWidget(selectFolderButton);


        verticalLayout->addLayout(buttonLayout);

        log = new QPlainTextEdit(ServerWidget);
        log->setObjectName("log");
        log->setReadOnly(true);
        QSizePolicy sizePolicy(QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(1);
        sizePolicy.setHeightForWidth(log->sizePolicy().hasHeightForWidth());
        log->setSizePolicy(sizePolicy);

        verticalLayout->addWidget(log);


        retranslateUi(ServerWidget);

        QMetaObject::connectSlotsByName(ServerWidget);
    } // setupUi

    void retranslateUi(QWidget *ServerWidget)
    {
        labelPort->setText(QCoreApplication::translate("ServerWidget", "Port:", nullptr));
        portEdit->setText(QCoreApplication::translate("ServerWidget", "9000", nullptr));
        labelKey->setText(QCoreApplication::translate("ServerWidget", "Key:", nullptr));
        startButton->setText(QCoreApplication::translate("ServerWidget", "Start Server", nullptr));
        stopButton->setText(QCoreApplication::translate("ServerWidget", "Stop Server", nullptr));
        selectFolderButton->setText(QCoreApplication::translate("ServerWidget", "Select Save Folder", nullptr));
        (void)ServerWidget;
    } // retranslateUi

};

namespace Ui {
    class ServerWidget: public Ui_ServerWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SERVERWIDGET_H
