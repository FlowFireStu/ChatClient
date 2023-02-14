#ifndef TCPSOCKETMANAGER_H
#define TCPSOCKETMANAGER_H

#include <QObject>
#include <QTcpSocket>
#include <QJsonArray>
#include <QJsonObject>
#include <QJsonDocument>

class TcpSocketManager: public QObject
{
    Q_OBJECT

private:
    static TcpSocketManager* m_manager;
    QTcpSocket* m_socket;
    QString m_addr;
    ushort m_port;
    QJsonObject m_head;
    QJsonObject m_body;

    TcpSocketManager();
    void process();
public:
    TcpSocketManager(const TcpSocketManager&) = delete;
    TcpSocketManager& operator=(const TcpSocketManager&) = delete;
    static TcpSocketManager* getInstance();

    QTcpSocket *socket() const;
    QString addr() const;
    void setAddr(const QString &newAddr);
    ushort port() const;
    void setPort(ushort newPort);

    QTcpSocket* connectToServer();
    void disconnectFromServer();
    void write(const QJsonArray& request);
    QJsonObject readHead();
    QJsonObject readBody();

signals:
    void ReadyRead(QString type);
};

#endif // TCPSOCKETMANAGER_H
