#ifndef ADDFRIENDDIALOG_H
#define ADDFRIENDDIALOG_H

#include <QDialog>
#include "tcpsocketmanager.h"

namespace Ui {
class AddFriendDialog;
}

class AddFriendDialog : public QDialog
{
    Q_OBJECT
    TcpSocketManager* m_socketManager;

    QString m_friendId;
    QString m_selfId;
public:
    explicit AddFriendDialog(const QString& selfId, QWidget *parent = nullptr);
    ~AddFriendDialog();

private slots:
    void on_addBtn_clicked();

private:
    Ui::AddFriendDialog *ui;

    void addFriendResponse();

signals:
    void addFriendSuccess(QJsonObject obj);
};

#endif // ADDFRIENDDIALOG_H
