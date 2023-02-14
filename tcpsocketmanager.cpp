#include "tcpsocketmanager.h"
#include "notice.h"
#include <QDebug>

TcpSocketManager* TcpSocketManager::m_manager = new TcpSocketManager;

TcpSocketManager::TcpSocketManager()
{
    m_socket = nullptr;
    m_addr = "localhost";
    m_port = 63425;
}

void TcpSocketManager::process()
{
    QByteArray tempArr = m_socket->readAll();
    QJsonArray arr = QJsonDocument::fromJson(tempArr).array();
    m_head = arr[0].toObject();
    m_body = arr[1].toObject();

    Notice* noti = Notice::getInstance();
    noti->setSocket(m_socket);
    noti->notify(m_head);
}

TcpSocketManager *TcpSocketManager::getInstance()
{
    return m_manager;
}

QTcpSocket *TcpSocketManager::socket() const
{
    return m_socket;
}

QString TcpSocketManager::addr() const
{
    return m_addr;
}

void TcpSocketManager::setAddr(const QString &newAddr)
{
    m_addr = newAddr;
}

ushort TcpSocketManager::port() const
{
    return m_port;
}

void TcpSocketManager::setPort(ushort newPort)
{
    m_port = newPort;
}

QTcpSocket *TcpSocketManager::connectToServer()
{
    if (m_socket)
    {
        m_socket->disconnect();
    }
    else
    {
        m_socket = new QTcpSocket(this);
        connect(m_socket, &QTcpSocket::readyRead, this, &TcpSocketManager::process);
    }
    m_socket->connectToHost(m_addr, m_port);
    return m_socket;
}

void TcpSocketManager::disconnectFromServer()
{
    if (m_socket)
    {
        m_socket->disconnectFromHost();
        m_socket->disconnect(m_socket, &QTcpSocket::readyRead, this, &TcpSocketManager::process);
        m_socket->deleteLater();
        m_socket = nullptr;
    }
}

void TcpSocketManager::write(const QJsonArray &request)
{
    if (m_socket)
    {
        QByteArray arr = QJsonDocument(request).toJson();
        m_socket->write(arr);
    }
}

QJsonObject TcpSocketManager::readHead()
{
    return m_head;
}

QJsonObject TcpSocketManager::readBody()
{
    return m_body;
}
