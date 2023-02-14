#include "mainwidget.h"
#include "ui_mainwidget.h"
#include "addfrienddialog.h"

MainWidget::MainWidget(const QJsonObject& json) :
    ui(new Ui::MainWidget)
{
    ui->setupUi(this);

    m_socketManager = TcpSocketManager::getInstance();
    m_selfId = json.value("id").toString();
    QString name = json.value("name").toString();
    ui->label->setText(name);
    QJsonArray friendArray= json.value("friend").toArray();

    initFriendList(friendArray);

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

    friendCount = arr.count();
    for (int i = 0; i < friendCount; i++)
    {
        QString id = arr[i].toObject().value("id").toString();
        QString name = arr[i].toObject().value("name").toString();

        AccountItem* item = new AccountItem(ui->friendListWidget);
        item->setId(id);
        item->setName(name);
        m_friendListLayout->addWidget(item);

        m_itemMap.insert(id, item);
        connect(item, &AccountItem::clicked, this, &MainWidget::openChatWidget);
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
        widget->raise();
    }
    else
    {
        ChatWidget* widget = new ChatWidget(id, name);
        widget->show();

        m_chatMap.insert(id, widget);
        widget->setAttribute(Qt::WA_DeleteOnClose);
        connect(widget, &ChatWidget::destroyed, this, [=](){
            m_chatMap.remove(id);
        });
    }
}

void MainWidget::showAddFriendDialog()
{
    AddFriendDialog dia(m_selfId, this);
    connect(&dia, &AddFriendDialog::addFriendSuccess, this, &MainWidget::addFriendItem);
            dia.exec();
}

void MainWidget::addFriendItem(QJsonObject infomation)
{
    QString id = infomation.value("id").toString();
    QString name = infomation.value("name").toString();

    AccountItem* item = new AccountItem(ui->friendListWidget);
    item->setId(id);
    item->setName(name);
    m_friendListLayout->insertWidget(friendCount, item);

    friendCount++;
    m_itemMap.insert(id, item);
    connect(item, &AccountItem::clicked, this, &MainWidget::openChatWidget);
}
