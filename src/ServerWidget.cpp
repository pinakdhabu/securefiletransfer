#include "ServerWidget.h"
#include "ui_ServerWidget.h"
#include "TransferSession.h"

#include <QHostAddress>
#include <QDataStream>

ServerWidget::ServerWidget(QWidget *parent)
    : QWidget(parent), ui(new Ui::ServerWidget) {
    ui->setupUi(this);
    m_server = new QTcpServer(this);
    connect(ui->startButton, &QPushButton::clicked, this, &ServerWidget::onStartClicked);
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

void ServerWidget::onNewConnection() {
    while (m_server->hasPendingConnections()) {
        QTcpSocket *sock = m_server->nextPendingConnection();
        appendLog(QString("New connection from %1:%2").arg(sock->peerAddress().toString()).arg(sock->peerPort()));
        TransferSession *session = new TransferSession(sock, m_key, this);
        connect(session, &TransferSession::logMessage, this, &ServerWidget::appendLog);
    }
}

void ServerWidget::appendLog(const QString &msg) {
    ui->log->appendPlainText(msg);
}
