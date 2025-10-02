#pragma once

#include <QWidget>
#include <QTcpServer>
#include <QVBoxLayout>

class TransferSession;

namespace Ui { class ServerWidget; }

class ServerWidget : public QWidget {
    Q_OBJECT
public:
    explicit ServerWidget(QWidget *parent = nullptr);
    ~ServerWidget() override;

private slots:
    void onStartClicked();
    void onNewConnection();
    void appendLog(const QString &msg);

private:
    Ui::ServerWidget *ui = nullptr;
    QTcpServer *m_server = nullptr;
    QByteArray m_key;
};
