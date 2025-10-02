#pragma once

#include <QWidget>
#include <QTcpSocket>
#include <QFile>

namespace Ui { class ClientWidget; }

class ClientWidget : public QWidget {
    Q_OBJECT
public:
    explicit ClientWidget(QWidget *parent = nullptr);
    ~ClientWidget() override;

private slots:
    void onSelectFile();
    void onSendFile();
    void onConnected();
    void onBytesWritten(qint64 bytes);
    void onErrorOccurred(QAbstractSocket::SocketError socketError);

private:
    Ui::ClientWidget *ui = nullptr;
    QTcpSocket *m_socket = nullptr;
    QString m_filePath;
    QFile *m_file = nullptr;
    qint64 m_bytesSent = 0;
    qint64 m_totalSize = 0;
    QByteArray m_key;
    void appendLog(const QString &msg);
    void sendHeader();
    void sendChunk();
};
