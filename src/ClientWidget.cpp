#include "ClientWidget.h"
#include "ui_ClientWidget.h"
#include "Encryption.h"

#include <QFileDialog>
#include <QDataStream>
#include <QHostAddress>

ClientWidget::ClientWidget(QWidget *parent)
    : QWidget(parent), ui(new Ui::ClientWidget) {
    ui->setupUi(this);
    m_socket = new QTcpSocket(this);
    connect(ui->selectButton, &QPushButton::clicked, this, &ClientWidget::onSelectFile);
    connect(ui->sendButton, &QPushButton::clicked, this, &ClientWidget::onSendFile);
    connect(m_socket, &QTcpSocket::connected, this, &ClientWidget::onConnected);
    connect(m_socket, &QTcpSocket::bytesWritten, this, &ClientWidget::onBytesWritten);
    connect(m_socket, QOverload<QAbstractSocket::SocketError>::of(&QAbstractSocket::errorOccurred),
            this, &ClientWidget::onErrorOccurred);
}

ClientWidget::~ClientWidget() {
    if (m_file && m_file->isOpen()) m_file->close();
    delete ui;
}

void ClientWidget::appendLog(const QString &msg) {
    ui->log->appendPlainText(msg);
}

void ClientWidget::onSelectFile() {
    m_filePath = QFileDialog::getOpenFileName(this, "Select file to send");
    if (!m_filePath.isEmpty()) {
        ui->fileLabel->setText(m_filePath);
        appendLog(QString("Selected: %1").arg(m_filePath));
    }
}

void ClientWidget::onSendFile() {
    if (m_filePath.isEmpty()) {
        appendLog("No file selected");
        return;
    }
    bool ok = false;
    quint16 port = static_cast<quint16>(ui->portEdit->text().toUShort(&ok));
    if (!ok) { appendLog("Invalid port"); return; }
    QString host = ui->hostEdit->text();
    m_key = ui->keyEdit->text().toUtf8();

    m_file = new QFile(m_filePath, this);
    if (!m_file->open(QIODevice::ReadOnly)) { appendLog("Failed to open file"); delete m_file; m_file = nullptr; return; }
    m_totalSize = m_file->size();
    m_bytesSent = 0;
    appendLog(QString("Connecting to %1:%2...").arg(host).arg(port));
    m_socket->connectToHost(host, port);
}

void ClientWidget::onConnected() {
    appendLog("Connected. Sending header...");
    sendHeader();
}

void ClientWidget::sendHeader() {
    if (!m_file) return;
    QByteArray fname = QFileInfo(m_filePath).fileName().toUtf8();
    QByteArray header;
    QDataStream ds(&header, QIODevice::WriteOnly);
    ds.setByteOrder(QDataStream::LittleEndian);
    qint32 flen = fname.size();
    ds << flen;
    header.append(fname);
    qint64 fsize = m_totalSize;
    QDataStream ds2(&header, QIODevice::Append);
    ds2.setByteOrder(QDataStream::LittleEndian);
    ds2 << fsize;
    qint64 written = m_socket->write(header);
    if (written != header.size()) {
        appendLog("Failed to write header");
        m_socket->disconnectFromHost();
        return;
    }
    appendLog("Header sent. Starting payload...");
    sendChunk();
}

void ClientWidget::sendChunk() {
    if (!m_file || !m_socket->isOpen()) return;
    const qint64 chunkSize = 64 * 1024;
    QByteArray data = m_file->read(chunkSize);
    if (data.isEmpty()) {
        appendLog("File fully read and sent");
        m_file->close();
        return;
    }
    QByteArray enc = Encryption::xorEncrypt(data, m_key);
    qint64 written = m_socket->write(enc);
    if (written < 0) {
        appendLog("Socket write error");
        m_socket->disconnectFromHost();
        return;
    }
    // bytesWritten signal will trigger further chunks
}

void ClientWidget::onBytesWritten(qint64 bytes) {
    Q_UNUSED(bytes);
    m_bytesSent += bytes;
    ui->progressBar->setValue(static_cast<int>((double)m_bytesSent / (double)qMax<qint64>(1, m_totalSize) * 100.0));
    if (m_bytesSent < m_totalSize) {
        sendChunk();
    } else {
        appendLog("All bytes queued for sending");
        // Wait for server to close
    }
}

void ClientWidget::onErrorOccurred(QAbstractSocket::SocketError socketError) {
    Q_UNUSED(socketError);
    appendLog(QString("Socket error: %1").arg(m_socket->errorString()));
}
