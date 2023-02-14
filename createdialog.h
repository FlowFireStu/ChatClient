#ifndef CREATEDIALOG_H
#define CREATEDIALOG_H

#include <QDialog>
#include "tcpsocketmanager.h"

namespace Ui {
class CreateDialog;
}

class CreateDialog : public QDialog
{
    Q_OBJECT

    QString m_id;
    QString m_password;
    QString m_nickname;
    TcpSocketManager* socketManager;
public:
    explicit CreateDialog(QWidget *parent = nullptr);
    ~CreateDialog();

private slots:
    void on_pushButton_clicked();

private:
    Ui::CreateDialog *ui;
    void createResponse();
};

#endif // CREATEDIALOG_H
