#include "chatwidget.h"
#include "ui_chatwidget.h"
#include "notice.h"
#include "tcpsocketmanager.h"

ChatWidget::ChatWidget(const QString& id, const QString& name, QWidget *parent) :
    QWidget(parent),
    m_id(id),
    m_name(name),
    ui(new Ui::ChatWidget)
{
    ui->setupUi(this);

    setWindowTitle(name);
    ui->textEdit->setFocus();
    m_self = SelfInformation::getInstance();
    m_messageManager = MessageDataManager::getInstance();

    loadMessageData();
    connect(Notice::getInstance(), &Notice::receiveMessageRequest, this, &ChatWidget::receiveMessage);
}

ChatWidget::~ChatWidget()
{
    delete ui;
}

void ChatWidget::loadMessageData()
{
    QJsonArray arr = m_messageManager->readAllMessage(m_id);

    for (auto it = arr.begin(); it != arr.end(); it++)
    {
        QJsonObject messageBody = it->toObject();
        showMessage(messageBody);
    }
}

void ChatWidget::receiveMessage()
{
    QJsonObject messageBody = TcpSocketManager::getInstance()->readBody();
    showMessage(messageBody);
    m_messageManager->addMessage(m_id, messageBody);
}

void ChatWidget::showMessage(const QJsonObject &messageBody)
{
    QString name = messageBody.value("fromId").toString();
    QString time = messageBody.value("time").toString("");
    QString messageContent = messageBody.value("content").toString("");
    ui->textBrowser->append(name + " " + time);
    ui->textBrowser->append(messageContent);
}

void ChatWidget::on_sendBtn_clicked()
{
    QJsonObject head;
    head.insert("type", "request");
    head.insert("requestType", "SendMessage");
    QJsonObject body;
    body.insert("fromId", m_self->id());
    body.insert("toId", m_id);
    body.insert("time", QTime::currentTime().toString("hh:mm:ss"));
    body.insert("content", ui->textEdit->toPlainText());
    QJsonArray arr;
    arr.append(head);
    arr.append(body);

    ui->textEdit->clear();
    TcpSocketManager::getInstance()->write(arr);
    showMessage(body);
    m_messageManager->addMessage(m_id, body);
}

