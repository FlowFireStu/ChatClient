#include "createdialog.h"
#include "ui_createdialog.h"
#include "clientexceptrion.h"
#include "tcpsocketmanager.h"
#include "notice.h"
#include <QMessageBox>

CreateDialog::CreateDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CreateDialog)
{
    ui->setupUi(this);

    setTabOrder(ui->passwordEdit, ui->nicknameEdit);
    setTabOrder(ui->nicknameEdit, ui->pushButton);

    socketManager = TcpSocketManager::getInstance();
    connect(Notice::getInstance(), &Notice::createResponse, this, &CreateDialog::createResponse);
}

CreateDialog::~CreateDialog()
{
    TcpSocketManager::getInstance()->disconnectFromServer();
    delete ui;
}

void CreateDialog::on_pushButton_clicked()
{
    try
    {
        m_password = ui->passwordEdit->text();
        if (m_password.isEmpty())
            throw ClientExceptrion("密码不能为空");
        m_nickname = ui->nicknameEdit->text();
        if (m_nickname.isEmpty())
            throw ClientExceptrion("昵称不能为空");

        QJsonObject requestHead;
        requestHead.insert("type", "request");
        requestHead.insert("requestType", "CreateAccount");
        QJsonObject requestBody;
        requestBody.insert("password", m_password);
        requestBody.insert("nickname", m_nickname);
        QJsonArray requestArray;
        requestArray.append(requestHead);
        requestArray.append(requestBody);

        socketManager->connectToServer();
        socketManager->write(requestArray);
    }
    catch (ClientExceptrion& e)
    {
        QMessageBox::critical(this, "错误", e.show());
    }
}

void CreateDialog::createResponse()
{
    QJsonObject responseHead = socketManager->readHead();
    QJsonObject responseBody = socketManager->readBody();
    if (responseHead.value("success").toBool())
    {
        QString id = responseBody.value("id").toString();
        QMessageBox::information(this, "成功", QString("注册成功\n账号：").append(id));
    }
    else
    {
        QMessageBox::critical(this, "错误", responseBody.value("content").toString());
    }
}
