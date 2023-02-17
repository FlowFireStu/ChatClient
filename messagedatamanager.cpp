#include "messagedatamanager.h"
#include <QDir>
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
    QDir dir;
    if (!dir.exists("./data"))
    {
        dir.mkdir("./data");
    }

    m_database = QSqlDatabase::addDatabase("QSQLITE", "message");
    m_database.setDatabaseName("./data/" + id + ".db");
    if (!m_database.open())
    {
        QMessageBox::critical(nullptr, "错误", "数据库打开失败");
        return;
    }
    m_database.close();
}

int MessageDataManager::addMessage(const QString &fromId, const QJsonObject &message)
{
    m_database.open();
    QSqlQuery query(m_database);

    QString addMessageTable("create table if not exists messageWith"
                            + fromId +
                            "(messageId int primary key, "
                            "time varchar(20),"
                            "fromId varchar(20),"
                            "toId varchar(20),"
                            "content varchar(1000));");
    m_lock.lockForWrite();
    query.exec(addMessageTable);
    m_lock.unlock();

    m_lock.lockForRead();
    query.exec("select messageId from messageWith" + fromId + ";");
    m_lock.unlock();

    if (query.size() > 100)
    {
        query.first();
        m_lock.lockForWrite();
        query.exec("delete from messageWith" + fromId + " where messageId = " + query.value(0).toString());
        m_lock.unlock();
    }

    int id = 0;
    if (query.last())
    {
        id = (query.value(0).toInt() + 1) % 100;
    }

    query.prepare("insert into messageWith" + fromId +
                  " values(:messageId, :time, :fromId, :toId, :content);");
    query.bindValue(":messageId", id);
    query.bindValue(":time", message.value("time").toString());
    query.bindValue(":fromId", message.value("fromId").toString());
    query.bindValue(":toId", message.value("toId").toString());
    query.bindValue(":content", message.value("content").toString());
    m_lock.lockForWrite();
    query.exec();
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

    QString existTable("show tables like messageWith" + fromId + ";");
    m_lock.lockForRead();
    query.exec(existTable);
    m_lock.unlock();

    if (query.size() == 0)
    {
        m_database.close();
        return QJsonObject();
    }

    QString readComd("select * from messageWith" + fromId + " where id = " + QString::number(id) + ";");
    m_lock.lockForRead();
    query.exec(readComd);
    m_lock.unlock();

    query.next();
    QJsonObject messageBody;
    messageBody.insert("time", query.value(1).toString());
    messageBody.insert("fromId", query.value(2).toString());
    messageBody.insert("toId", query.value(3).toString());
    messageBody.insert("content", query.value(4).toString());

    m_database.close();
    return messageBody;
}

QJsonArray MessageDataManager::readAllMessage(const QString &fromId)
{
    m_database.open();
    QSqlQuery query(m_database);

    QString existTable("show tables like messageWith" + fromId + ";");
    m_lock.lockForRead();
    query.exec(existTable);
    m_lock.unlock();

    if (query.size() == 0)
    {
        m_database.close();
        return QJsonArray();
    }

    QString readMessage("select * from messageWith" + fromId + ";");
    m_lock.lockForRead();
    query.exec(readMessage);
    m_lock.unlock();

    QJsonObject messageBody;
    QJsonArray messageArray;
    while (query.next())
    {
        messageBody.insert("time", query.value(1).toString());
        messageBody.insert("fromId", query.value(2).toString());
        messageBody.insert("toId", query.value(3).toString());
        messageBody.insert("content", query.value(4).toString());
        messageArray.append(messageBody);
    }

    m_database.close();
    return messageArray;
}
