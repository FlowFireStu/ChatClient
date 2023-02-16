#include "messagedatamanager.h"
#include <QJsonDocument>
#include <QMessageBox>

MessageDataManager* MessageDataManager::m_manager = nullptr;

MessageDataManager::MessageDataManager()
{
}

MessageDataManager *MessageDataManager::getInstance()
{
    if (!m_manager)
    {
        m_manager = new MessageDataManager;
    }
    return m_manager;
}

void MessageDataManager::init(const QString &id)
{
    m_selfId = id;

    m_database = QSqlDatabase::addDatabase("QSQLITE", "message");
    m_database.setUserName(m_selfId);
    m_database.setPassword("password");
    if (!m_database.open())
    {
        QMessageBox::critical(nullptr, "错误", "数据库打开失败");
        return;
    }

    QString createDatabase("create database if not exists " + m_selfId + ";");
    m_lock.lockForWrite();
    m_database.exec(createDatabase);
    m_lock.unlock();

    m_database.setDatabaseName(m_selfId);
}

int MessageDataManager::addMessage(const QString &fromId, const QJsonObject &message)
{
    m_database.open();
    QSqlQuery query(m_database);

    QString addMessageTable("create table if not exists "
                               + fromId +
                               "message(id int primary key, "
                               "messagebody varchar(1000));");
    QString getId("select id from " + fromId + "message;");

    m_lock.lockForWrite();
    query.exec(addMessageTable);
    query.exec(getId);
    m_lock.unlock();

    if (query.size() > 100)
    {
        query.first();
        int id = query.value(0).toInt();
        m_lock.lockForWrite();
        query.exec("delete from " + fromId + "message where id = " + QString::number(id));
        m_lock.unlock();
    }

    int id = 0;
    if (query.last())
    {
        id = (query.value(0).toInt() + 1) % 100;
    }

    QString messageStr = QJsonDocument(message).toVariant().toString();
    QString addMessage("insert into " + fromId + "message values( "
                       + QString::number(id) + ", \""
                       + messageStr + "\");");
    m_database.open();
    m_lock.lockForWrite();
    query.exec(addMessage);
    m_lock.unlock();
    m_database.close();
    return id;
}

void MessageDataManager::removeMessage(const QString &fromId, int id)
{

}

QJsonObject MessageDataManager::readMessage(const QString &fromId, int id)
{
    m_database.open();
    QSqlQuery query(m_database);

    QString existTable("show tables like " + fromId + "message;");
    m_lock.lockForRead();
    query.exec(existTable);
    m_lock.unlock();

    if (query.size() == 0)
    {
        return QJsonObject();
    }

    QString readComd("select messagebody from " + fromId + "message where id = " + QString::number(id) + ";");
    m_lock.lockForRead();
    query.exec(readComd);
    m_lock.unlock();
    query.next();

    QJsonObject messageBody = query.value(0).toJsonObject();
    m_database.close();
    return messageBody;
}

QJsonArray MessageDataManager::readAllMessage(const QString &fromId)
{
    m_database.open();
    QSqlQuery query(m_database);

    QString existTable("show tables like " + fromId + "message;");
    m_lock.lockForRead();
    query.exec(existTable);
    m_lock.unlock();

    if (query.size() == 0)
    {
        return QJsonArray();
    }

    QString readComd("select messagebody from " + fromId + "message;");
    m_lock.lockForRead();
    query.exec(readComd);
    m_lock.unlock();

    QJsonArray arr;
    while (query.next())
    {
        arr.append(query.value(0).toJsonObject());
    }

    m_database.close();
    return arr;
}
