#include "notice.h"

Notice* Notice::m_manager = new Notice;

Notice::Notice()
{
    m_socket = nullptr;
}

Notice *Notice::getInstance()
{
     return m_manager;
}

QTcpSocket *Notice::socket() const
{
    return m_socket;
}

void Notice::setSocket(QTcpSocket *newSocket)
{
    m_socket = newSocket;
}

void Notice::notify(const QJsonObject &head)
{
    QString firstType = head.value("type").toString();
    if (firstType == "response")
    {
        QString responseType = head.value("responseType").toString();
        responseNotify(responseType);
    }
    else if (firstType == "request")
    {
        QString requestType = head.value("requestType").toString();
        requestNotify(requestType);
    }
}

void Notice::requestNotify(const QString &requestType)
{
    if (requestType == "Message") {
        emit receiveMessageRequest();
    }
}

void Notice::responseNotify(const QString &responseType)
{
    if (responseType == "LoginAccount") {
        emit loginResponse();
    }
    else if (responseType == "CreateAccount") {
        emit createResponse();
    }
    else if (responseType == "AddFriend") {
        emit addFriendResponse();
    }
    else if (responseType == "GetOfflineMessage") {
        emit offlineMessageResponse();
    }
}
