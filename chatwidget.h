#ifndef CHATWIDGET_H
#define CHATWIDGET_H

#include <QWidget>
#include "messagedatamanager.h"
#include "selfinformation.h"

namespace Ui {
class ChatWidget;
}

class ChatWidget : public QWidget
{
    Q_OBJECT

    SelfInformation* m_self;
    QString m_id;
    QString m_name;
    MessageDataManager* m_messageManager;

public:
    explicit ChatWidget(const QString& id, const QString& name, QWidget *parent = nullptr);
    ~ChatWidget();

private slots:
    void on_sendBtn_clicked();

private:
    Ui::ChatWidget *ui;

    void loadMessageData();
    void receiveMessage();
    void showMessage(const QJsonObject& messageBody);
};

#endif // CHATWIDGET_H
