#ifndef MESSAGEDATAMANAGER_H
#define MESSAGEDATAMANAGER_H

#include <QSqlDatabase>
#include <QSqlQuery>
#include <QReadWriteLock>
#include <QJsonObject>
#include <QJsonArray>

class MessageDataManager
{
private:
    static MessageDataManager* m_manager;
    QSqlDatabase m_database;
    QReadWriteLock m_lock;
    QString m_selfId;

private:
    MessageDataManager();

public:
    MessageDataManager(const MessageDataManager&) = delete;
    MessageDataManager& operator=(const MessageDataManager&) = delete;
    static MessageDataManager* getInstance();

    void init(const QString& id = "default");
    int addMessage(const QString &fromId, const QJsonObject& message);
    void removeMessage(const QString &fromId, int id);
    QJsonObject readMessage(const QString &fromId, int id);
    QJsonArray readAllMessage(const QString& fromId);
};

#endif // MESSAGEDATAMANAGER_H
