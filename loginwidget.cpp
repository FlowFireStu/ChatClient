#include "loginwidget.h"
#include "ui_loginwidget.h"
#include "createdialog.h"
#include "mainwidget.h"
#include "notice.h"
#include <QMessageBox>

LoginWidget::LoginWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::LoginWidget)
{
    ui->setupUi(this);

    setTabOrder(ui->idEdit, ui->passwordEdit);
    setTabOrder(ui->passwordEdit, ui->loginBtn);
    setTabOrder(ui->loginBtn, ui->createBtn);
    ui->loginBtn->setDefault(true);

    socketManager = TcpSocketManager::getInstance();
    connect(ui->idEdit, &QLineEdit::returnPressed, ui->loginBtn, &QPushButton::click);
    connect(ui->passwordEdit, &QLineEdit::returnPressed, ui->loginBtn, &QPushButton::click);
    connect(Notice::getInstance(), &Notice::loginResponse, this, &LoginWidget::loginResponse);
}

LoginWidget::~LoginWidget()
{
    delete ui;
}

void LoginWidget::loginResponse()
{
    QJsonObject responseHead = socketManager->readHead();
    QJsonObject responseBody = socketManager->readBody();
    if (responseHead.value("success").toBool())
    {
        MainWidget* widget = new MainWidget(responseBody);
        widget->setAttribute(Qt::WA_DeleteOnClose);
        widget->show();
        this->close();
    }
    else
    {
        socketManager->disconnectFromServer();
        QMessageBox::critical(this, "错误", responseBody.value("content").toString());
    }
}

void LoginWidget::on_loginBtn_clicked()
{
    m_id = ui->idEdit->text();
    m_password = ui->passwordEdit->text();

    QJsonObject requestHead;
    requestHead.insert("type", "request");
    requestHead.insert("requestType", "LoginAccount");
    QJsonObject requestBody;
    requestBody.insert("id", m_id);
    requestBody.insert("password", m_password);
    QJsonArray requestArray;
    requestArray.append(requestHead);
    requestArray.append(requestBody);

    socketManager->connectToServer();
    socketManager->write(requestArray);
}


void LoginWidget::on_createBtn_clicked()
{
    CreateDialog registerDialog(this);
    registerDialog.exec();
}
