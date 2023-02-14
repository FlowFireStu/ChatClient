#ifndef NOTICE_H
#define NOTICE_H

#include <QObject>
#include <QTcpSocket>
#include <QJsonObject>

class Notice: public QObject
{
    Q_OBJECT

    static Notice* m_manager;
    QTcpSocket* m_socket;
public:
    Notice(const Notice&) = delete;
    Notice& operator=(const Notice&) = delete;
    static Notice* getInstance();

    QTcpSocket *socket() const;
    void setSocket(QTcpSocket *newSocket);
    void notify(const QJsonObject& head);

private:
    Notice();

    void requestNotify(const QString& requestType);
    void responseNotify(const QString& responseType);

signals:
    void loginResponse();
    void createResponse();
    void addFriendResponse();


};

#endif // NOTICE_H
