#include "TransferSession.h"
#include "Encryption.h"

#include <QDir>
#include <QDataStream>
#include <QFileDialog>

TransferSession::TransferSession(QTcpSocket *socket, const QByteArray &key, QObject *parent)
    : QObject(parent), m_socket(socket), m_key(key) {
    connect(m_socket, &QTcpSocket::readyRead, this, &TransferSession::onReadyRead);
    connect(m_socket, &QTcpSocket::disconnected, this, &TransferSession::onDisconnected);
}

void TransferSession::setSaveFolder(const QString &folder) {
    m_saveFolder = folder;
}

TransferSession::~TransferSession() {
    if (m_outFile) {
        if (m_outFile->isOpen()) m_outFile->close();
        delete m_outFile;
    }
    if (m_socket) {
        m_socket->deleteLater();
    }
}

void TransferSession::onDisconnected() {
    emit logMessage(QStringLiteral("Client disconnected"));
    deleteLater();
}

void TransferSession::onReadyRead() {
    QDataStream in(m_socket);
    in.setByteOrder(QDataStream::LittleEndian);

    while (m_socket->bytesAvailable() > 0) {
        if (m_state == State::ReadingFilenameLength) {
            if (m_socket->bytesAvailable() < 4) return; // wait for full length
            QByteArray lenBytes = m_socket->read(4);
            QDataStream ds(lenBytes);
            ds.setByteOrder(QDataStream::LittleEndian);
            ds >> m_filenameLen;
            if (m_filenameLen <= 0 || m_filenameLen > 4096) {
                emit logMessage(QStringLiteral("Invalid filename length"));
                m_socket->disconnectFromHost();
                return;
            }
            m_state = State::ReadingFilename;
        }

        if (m_state == State::ReadingFilename) {
            if (m_socket->bytesAvailable() < m_filenameLen) return;
            QByteArray fname = m_socket->read(m_filenameLen);
            m_filename = QString::fromUtf8(fname);
            // Prepare output file
            QString outPath;
            if (!m_saveFolder.isEmpty()) {
                QDir outDir(m_saveFolder);
                outPath = outDir.filePath(m_filename);
            } else {
                // Ask user where to save this file (Save As)
                QString defaultDir = QDir::currentPath();
                QString selected = QFileDialog::getSaveFileName(nullptr, "Save received file as", QDir(defaultDir).filePath(m_filename));
                if (selected.isEmpty()) {
                    emit logMessage("Save cancelled by user; closing connection");
                    m_socket->disconnectFromHost();
                    return;
                }
                outPath = selected;
            }
            QDir parentDir = QFileInfo(outPath).absoluteDir();
            if (!parentDir.exists()) parentDir.mkpath(".");
            m_outFile = new QFile(outPath);
            m_outFile = new QFile(outPath);
            if (!m_outFile->open(QIODevice::WriteOnly)) {
                emit logMessage(QStringLiteral("Failed to open output file: %1").arg(outPath));
                m_socket->disconnectFromHost();
                return;
            }
            m_state = State::ReadingFileSize;
        }

        if (m_state == State::ReadingFileSize) {
            if (m_socket->bytesAvailable() < 8) return;
            QByteArray sizeBytes = m_socket->read(8);
            QDataStream ds(sizeBytes);
            ds.setByteOrder(QDataStream::LittleEndian);
            ds >> m_fileSize;
            if (m_fileSize < 0) {
                emit logMessage(QStringLiteral("Invalid file size"));
                m_socket->disconnectFromHost();
                return;
            }
            m_state = State::ReadingPayload;
            m_bytesReceived = 0;
        }

        if (m_state == State::ReadingPayload) {
            qint64 toRead = qMin<qint64>(m_socket->bytesAvailable(), m_fileSize - m_bytesReceived);
            if (toRead > 0) {
                QByteArray enc = m_socket->read(toRead);
                QByteArray dec = Encryption::xorEncrypt(enc, m_key);
                qint64 written = m_outFile->write(dec);
                m_bytesReceived += enc.size();
                if (written != dec.size()) {
                    emit logMessage(QStringLiteral("Write error while saving file"));
                    m_socket->disconnectFromHost();
                    return;
                }
                if (m_bytesReceived >= m_fileSize) {
                    m_outFile->flush();
                    emit logMessage(QStringLiteral("Received file: %1 (%2 bytes)").arg(m_filename).arg(m_fileSize));
                    m_state = State::Done;
                    m_socket->disconnectFromHost();
                    return;
                }
            } else {
                return;
            }
        }
    }
}
