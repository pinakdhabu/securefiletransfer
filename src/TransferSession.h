#pragma once

#include <QObject>
#include <QTcpSocket>
#include <QFile>

// Handles a single client connection on the server.
// Reads the custom protocol and writes the decrypted file.
class TransferSession : public QObject {
    Q_OBJECT
public:
    explicit TransferSession(QTcpSocket *socket, const QByteArray &key, QObject *parent = nullptr);
    ~TransferSession() override;

signals:
    void logMessage(const QString &msg);

private slots:
    void onReadyRead();
    void onDisconnected();

private:
    QTcpSocket *m_socket;
    QByteArray m_key;
    QFile *m_outFile = nullptr;

    enum class State { ReadingFilenameLength, ReadingFilename, ReadingFileSize, ReadingPayload, Done };
    State m_state = State::ReadingFilenameLength;

    qint32 m_filenameLen = 0;
    QString m_filename;
    qint64 m_fileSize = 0;
    qint64 m_bytesReceived = 0;
    QByteArray m_buffer;
};
