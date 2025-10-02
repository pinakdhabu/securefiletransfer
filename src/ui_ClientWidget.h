// Minimal ui header for ClientWidget
#pragma once
#include <QtWidgets>
namespace Ui { class ClientWidget { public:
    QLineEdit *hostEdit=nullptr; QLineEdit *portEdit=nullptr; QLineEdit *keyEdit=nullptr;
    QLabel *fileLabel=nullptr; QPushButton *selectButton=nullptr; QPushButton *sendButton=nullptr;
    QProgressBar *progressBar=nullptr; QPlainTextEdit *log=nullptr;
    void setupUi(QWidget *w) {
        QVBoxLayout *v=new QVBoxLayout(w);
        QFormLayout *form=new QFormLayout();
        hostEdit=new QLineEdit(w); hostEdit->setText("127.0.0.1");
        portEdit=new QLineEdit(w); portEdit->setText("9000");
        keyEdit=new QLineEdit(w);
        form->addRow(new QLabel("Server IP:"), hostEdit);
        form->addRow(new QLabel("Port:"), portEdit);
        form->addRow(new QLabel("Key:"), keyEdit);
        v->addLayout(form);
        QHBoxLayout *h=new QHBoxLayout();
        fileLabel=new QLabel("No file selected", w);
        selectButton=new QPushButton("Select File", w);
        sendButton=new QPushButton("Send File", w);
        h->addWidget(fileLabel); h->addWidget(selectButton); h->addWidget(sendButton);
        v->addLayout(h);
        progressBar=new QProgressBar(w); v->addWidget(progressBar);
        log=new QPlainTextEdit(w); log->setReadOnly(true); v->addWidget(log);
    }
}; }
