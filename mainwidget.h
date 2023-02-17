#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include <QWidget>
#include "accountitem.h"
#include "chatwidget.h"
#include "selfinformation.h"
#include "messagedatamanager.h"
#include "tcpsocketmanager.h"
#include <QVBoxLayout>
#include <QMap>

namespace Ui {
class MainWidget;
}

class MainWidget : public QWidget
{
    Q_OBJECT
    SelfInformation* m_self;
    MessageDataManager* m_messageManager;
    TcpSocketManager* m_socketManager;
    QVBoxLayout* m_friendListLayout;

    int m_friendCount;
    int m_friendListCount;
    QMap<QString, AccountItem*> m_itemMap;
    QMap<QString, ChatWidget*> m_chatMap;
public:
    explicit MainWidget(const QJsonObject& json);
    ~MainWidget();

private:
    Ui::MainWidget *ui;

    void initMainWidget();
    void initFriendList(const QJsonArray& arr);
    void requestOfflineMessage();
    void loadOfflineMessage();
    void openChatWidget(const QString& id, const QString& name);
    void showAddFriendDialog();
    void addFriend(QJsonObject infomation);
    void receiveMessage();
    AccountItem* insertFriendItem(const QString& id, const QString& name);
};

#endif // MAINWIDGET_H
