#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include <QWidget>
#include "accountitem.h"
#include "chatwidget.h"
#include "tcpsocketmanager.h"
#include <QVBoxLayout>
#include <QMap>

namespace Ui {
class MainWidget;
}

class MainWidget : public QWidget
{
    Q_OBJECT
    TcpSocketManager* m_socketManager;
    QVBoxLayout* m_friendListLayout;

    QString m_selfId;
    int friendCount;
    QMap<QString, AccountItem*> m_itemMap;
    QMap<QString, ChatWidget*> m_chatMap;
public:
    explicit MainWidget(const QJsonObject& json);
    ~MainWidget();

private:
    Ui::MainWidget *ui;

    void initMainWidget();
    void initFriendList(const QJsonArray& arr);
    void openChatWidget(const QString& id, const QString& name);
    void showAddFriendDialog();
    void addFriendItem(QJsonObject infomation);
};

#endif // MAINWIDGET_H
