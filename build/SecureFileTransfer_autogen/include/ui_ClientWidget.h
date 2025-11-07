/********************************************************************************
** Form generated from reading UI file 'ClientWidget.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CLIENTWIDGET_H
#define UI_CLIENTWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPlainTextEdit>
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ClientWidget
{
public:
    QVBoxLayout *verticalLayout;
    QFormLayout *formLayout;
    QLabel *labelHost;
    QLineEdit *hostEdit;
    QLabel *labelPort;
    QLineEdit *portEdit;
    QLabel *labelKey;
    QLineEdit *keyEdit;
    QHBoxLayout *fileLayout;
    QLabel *fileLabel;
    QPushButton *selectButton;
    QSpacerItem *hSpacer1;
    QPushButton *sendButton;
    QProgressBar *progressBar;
    QPlainTextEdit *log;

    void setupUi(QWidget *ClientWidget)
    {
        if (ClientWidget->objectName().isEmpty())
            ClientWidget->setObjectName("ClientWidget");
        ClientWidget->setMinimumSize(QSize(400, 300));
        verticalLayout = new QVBoxLayout(ClientWidget);
        verticalLayout->setObjectName("verticalLayout");
        formLayout = new QFormLayout();
        formLayout->setObjectName("formLayout");
        formLayout->setLabelAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        labelHost = new QLabel(ClientWidget);
        labelHost->setObjectName("labelHost");

        formLayout->setWidget(0, QFormLayout::ItemRole::LabelRole, labelHost);

        hostEdit = new QLineEdit(ClientWidget);
        hostEdit->setObjectName("hostEdit");

        formLayout->setWidget(0, QFormLayout::ItemRole::FieldRole, hostEdit);

        labelPort = new QLabel(ClientWidget);
        labelPort->setObjectName("labelPort");

        formLayout->setWidget(1, QFormLayout::ItemRole::LabelRole, labelPort);

        portEdit = new QLineEdit(ClientWidget);
        portEdit->setObjectName("portEdit");

        formLayout->setWidget(1, QFormLayout::ItemRole::FieldRole, portEdit);

        labelKey = new QLabel(ClientWidget);
        labelKey->setObjectName("labelKey");

        formLayout->setWidget(2, QFormLayout::ItemRole::LabelRole, labelKey);

        keyEdit = new QLineEdit(ClientWidget);
        keyEdit->setObjectName("keyEdit");

        formLayout->setWidget(2, QFormLayout::ItemRole::FieldRole, keyEdit);


        verticalLayout->addLayout(formLayout);

        fileLayout = new QHBoxLayout();
        fileLayout->setObjectName("fileLayout");
        fileLabel = new QLabel(ClientWidget);
        fileLabel->setObjectName("fileLabel");

        fileLayout->addWidget(fileLabel);

        selectButton = new QPushButton(ClientWidget);
        selectButton->setObjectName("selectButton");

        fileLayout->addWidget(selectButton);

        hSpacer1 = new QSpacerItem(0, 0, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        fileLayout->addItem(hSpacer1);

        sendButton = new QPushButton(ClientWidget);
        sendButton->setObjectName("sendButton");

        fileLayout->addWidget(sendButton);


        verticalLayout->addLayout(fileLayout);

        progressBar = new QProgressBar(ClientWidget);
        progressBar->setObjectName("progressBar");
        progressBar->setTextVisible(true);
        progressBar->setMinimumHeight(18);

        verticalLayout->addWidget(progressBar);

        log = new QPlainTextEdit(ClientWidget);
        log->setObjectName("log");
        log->setReadOnly(true);
        QSizePolicy sizePolicy(QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(1);
        sizePolicy.setHeightForWidth(log->sizePolicy().hasHeightForWidth());
        log->setSizePolicy(sizePolicy);

        verticalLayout->addWidget(log);


        retranslateUi(ClientWidget);

        QMetaObject::connectSlotsByName(ClientWidget);
    } // setupUi

    void retranslateUi(QWidget *ClientWidget)
    {
        labelHost->setText(QCoreApplication::translate("ClientWidget", "Server IP:", nullptr));
        hostEdit->setText(QCoreApplication::translate("ClientWidget", "127.0.0.1", nullptr));
        labelPort->setText(QCoreApplication::translate("ClientWidget", "Port:", nullptr));
        portEdit->setText(QCoreApplication::translate("ClientWidget", "9000", nullptr));
        labelKey->setText(QCoreApplication::translate("ClientWidget", "Key:", nullptr));
        fileLabel->setText(QCoreApplication::translate("ClientWidget", "No file selected", nullptr));
        selectButton->setText(QCoreApplication::translate("ClientWidget", "Select File", nullptr));
        sendButton->setText(QCoreApplication::translate("ClientWidget", "Send File", nullptr));
        (void)ClientWidget;
    } // retranslateUi

};

namespace Ui {
    class ClientWidget: public Ui_ClientWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CLIENTWIDGET_H
