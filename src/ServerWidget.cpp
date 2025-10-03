#include "ServerWidget.h"
#include "ui_ServerWidget.h"
#include "TransferSession.h"

#include <QHostAddress>
#include <QDataStream>
#include <QFileDialog>
#include <QDir>

ServerWidget::ServerWidget(QWidget *parent)
    : QWidget(parent), ui(new Ui::ServerWidget) {
    ui->setupUi(this);
    m_server = new QTcpServer(this);
    connect(ui->startButton, &QPushButton::clicked, this, &ServerWidget::onStartClicked);
    // stopButton/selectFolderButton are optional depending on the UI generation; locate them dynamically on 'this'
    if (QPushButton *stopBtn = this->findChild<QPushButton *>("stopButton")) {
        connect(stopBtn, &QPushButton::clicked, this, &ServerWidget::onStopClicked);
    }
    if (QPushButton *selBtn = this->findChild<QPushButton *>("selectFolderButton")) {
        connect(selBtn, &QPushButton::clicked, this, &ServerWidget::onSelectFolderClicked);
    }
}

ServerWidget::~ServerWidget() {
    if (m_server->isListening()) m_server->close();
    delete ui;
}

void ServerWidget::onStartClicked() {
    bool ok = false;
    quint16 port = static_cast<quint16>(ui->portEdit->text().toUInt(&ok));
    if (!ok) {
        appendLog("Invalid port");
        return;
    }
    m_key = ui->keyEdit->text().toUtf8();
    if (!m_server->listen(QHostAddress::Any, port)) {
        appendLog(QString("Failed to start server: %1").arg(m_server->errorString()));
        return;
    }
    appendLog(QString("Server listening on port %1").arg(port));
    connect(m_server, &QTcpServer::newConnection, this, &ServerWidget::onNewConnection);
}

void ServerWidget::onStopClicked() {
    if (m_server->isListening()) {
        m_server->close();
        appendLog("Server stopped");
    } else {
        appendLog("Server is not running");
    }
}

void ServerWidget::onSelectFolderClicked() {
    QString folder = QFileDialog::getExistingDirectory(this, "Select folder to save incoming files", QDir::currentPath());
    if (!folder.isEmpty()) {
        m_saveFolder = folder;
        appendLog(QString("Save folder set to: %1").arg(m_saveFolder));
    }
}

void ServerWidget::onNewConnection() {
    while (m_server->hasPendingConnections()) {
        QTcpSocket *sock = m_server->nextPendingConnection();
        appendLog(QString("New connection from %1:%2").arg(sock->peerAddress().toString()).arg(sock->peerPort()));
        TransferSession *session = new TransferSession(sock, m_key, this);
        // If a save folder was chosen, tell the session to use it (session will use current directory if empty)
        if (!m_saveFolder.isEmpty()) session->setSaveFolder(m_saveFolder);
        connect(session, &TransferSession::logMessage, this, &ServerWidget::appendLog);
    }
}

void ServerWidget::appendLog(const QString &msg) {
    ui->log->appendPlainText(msg);
}
