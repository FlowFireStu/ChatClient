#include "mainwidget.h"
#include "ui_mainwidget.h"
#include "addfrienddialog.h"
#include "notice.h"

MainWidget::MainWidget(const QJsonObject& json) :
    ui(new Ui::MainWidget)
{
    ui->setupUi(this);

    m_socketManager = TcpSocketManager::getInstance();
    QString id = json.value("id").toString();
    QString name = json.value("name").toString();
    m_self = SelfInformation::getInstance();
    m_self->init(id);
    m_self->setName(name);
    ui->label->setText(name);
    m_messageManager = MessageDataManager::getInstance();
    m_messageManager->init(id);

    QJsonArray friendArray= json.value("friend").toArray();
    m_friendCount = friendArray.count();
    initFriendList(friendArray);

    connect(Notice::getInstance(), &Notice::receiveMessageRequest, this, &MainWidget::receiveMessage);
}

MainWidget::~MainWidget()
{
    for (auto it = m_chatMap.begin(); it != m_chatMap.end(); it++)
    {
        it.value()->close();
        it.value()->deleteLater();
    }

    delete ui;
}

void MainWidget::initFriendList(const QJsonArray& arr)
{
    m_friendListLayout = new QVBoxLayout(ui->friendListWidget);
    ui->friendListWidget->setLayout(m_friendListLayout);

    m_friendListCount = 0;
    while (m_friendListCount < m_friendCount)
    {
        QString id = arr[m_friendListCount].toObject().value("id").toString();
        QString name = arr[m_friendListCount].toObject().value("name").toString();

        insertFriendItem(id, name);
    }

    AccountItem* item = new AccountItem(ui->friendListWidget);
    item->setName("添加好友");

    m_friendListLayout->addWidget(item);
    m_friendListLayout->addSpacerItem(new QSpacerItem(20, 20, QSizePolicy::Expanding,QSizePolicy::Expanding));
    connect(item, &AccountItem::clicked, this, &MainWidget::showAddFriendDialog);
}

void MainWidget::openChatWidget(const QString &id, const QString &name)
{
    if (m_chatMap.contains(id))
    {
        ChatWidget* widget = m_chatMap.value(id);
        widget->show();
    }
    else
    {
        ChatWidget* widget = new ChatWidget(id, name);
        widget->setAttribute(Qt::WA_DeleteOnClose);
        widget->show();

        AccountItem* item = m_itemMap.value(id);
        item->setCount(0);
        m_chatMap.insert(id, widget);
        connect(widget, &ChatWidget::destroyed, this, [=](){
            m_chatMap.remove(id);
        });
    }
}

void MainWidget::showAddFriendDialog()
{
    AddFriendDialog dia(m_self->id(), this);
    connect(&dia, &AddFriendDialog::addFriendSuccess, this, &MainWidget::addFriend);
            dia.exec();
}

void MainWidget::addFriend(QJsonObject infomation)
{
    QString id = infomation.value("id").toString();
    QString name = infomation.value("name").toString();

    m_friendCount++;
    insertFriendItem(id, name);
}

void MainWidget::receiveMessage()
{
    TcpSocketManager* socketManager = TcpSocketManager::getInstance();
    QJsonObject messageBody = socketManager->readBody();
    QString fromId = messageBody.value("fromId").toString();

    AccountItem* item = m_itemMap.value(fromId, nullptr);
    if (!item)
    {
        item = insertFriendItem(fromId, "id: " + fromId);
    }

    ChatWidget* widget = m_chatMap.value(fromId, nullptr);
    if (!widget)
    {
        m_messageManager->addMessage(fromId, messageBody);
        item->setCount(item->count() + 1);
        m_friendListLayout->removeWidget(item);
        m_friendListLayout->insertWidget(0, item);
    }
}

AccountItem* MainWidget::insertFriendItem(const QString &id, const QString &name)
{
    AccountItem* item = new AccountItem(ui->friendListWidget);
    item->setId(id);
    item->setName(name);
    m_friendListLayout->insertWidget(m_friendListCount, item);

    m_friendListCount++;
    m_itemMap.insert(id, item);
    connect(item, &AccountItem::clicked, this, &MainWidget::openChatWidget);

    return item;
}
