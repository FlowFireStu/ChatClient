#include "addfrienddialog.h"
#include "ui_addfrienddialog.h"
#include "notice.h"
#include <QMessageBox>

AddFriendDialog::AddFriendDialog(const QString& selfId, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddFriendDialog)
{
    ui->setupUi(this);

    m_selfId = selfId;
    m_socketManager = TcpSocketManager::getInstance();
    connect(Notice::getInstance(), &Notice::addFriendResponse, this, &AddFriendDialog::addFriendResponse);
}

AddFriendDialog::~AddFriendDialog()
{
    delete ui;
}

void AddFriendDialog::on_addBtn_clicked()
{
    m_friendId = ui->lineEdit->text();
    QJsonObject head;
    head.insert("type", "request");
    head.insert("requestType", "AddFriend");
    QJsonObject body;
    body.insert("selfId", m_selfId);
    body.insert("friendId", m_friendId);
    QJsonArray arr;
    arr.append(head);
    arr.append(body);

    m_socketManager->write(arr);
}

void AddFriendDialog::addFriendResponse()
{
    QJsonObject responseHead = m_socketManager->readHead();
    QJsonObject responseBody = m_socketManager->readBody();

    if (responseHead.value("success").toBool())
    {
        QMessageBox::information(this, "成功", "添加成功");
        emit addFriendSuccess(responseBody);
        accept();
    }
    else
    {
        QMessageBox::critical(this, "错误", responseBody.value("content").toString());
    }
}

