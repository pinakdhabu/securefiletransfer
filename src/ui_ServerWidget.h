// Minimal ui header for ServerWidget
#pragma once
#include <QtWidgets>
namespace Ui { class ServerWidget { public:
    QLineEdit *portEdit=nullptr; QLineEdit *keyEdit=nullptr; QPushButton *startButton=nullptr; QPlainTextEdit *log=nullptr;
    void setupUi(QWidget *w) {
        QVBoxLayout *v=new QVBoxLayout(w);
        QFormLayout *form=new QFormLayout();
        portEdit=new QLineEdit(w); portEdit->setText("9000"); keyEdit=new QLineEdit(w);
        form->addRow(new QLabel("Port:"), portEdit);
        form->addRow(new QLabel("Key:"), keyEdit);
        v->addLayout(form);
        startButton=new QPushButton("Start Server", w); v->addWidget(startButton);
        log=new QPlainTextEdit(w); log->setReadOnly(true); v->addWidget(log);
    }
}; }
