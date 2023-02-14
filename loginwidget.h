#ifndef LOGINWIDGET_H
#define LOGINWIDGET_H

#include <QWidget>
#include "tcpsocketmanager.h"

QT_BEGIN_NAMESPACE
namespace Ui { class LoginWidget; }
QT_END_NAMESPACE

class LoginWidget : public QWidget
{
    Q_OBJECT

    QString m_id;
    QString m_password;
    TcpSocketManager* socketManager;
public:
    LoginWidget(QWidget *parent = nullptr);
    ~LoginWidget();

private slots:
    void on_loginBtn_clicked();
    void on_createBtn_clicked();

private:
    Ui::LoginWidget *ui;
    void loginResponse();
};
#endif // LOGINWIDGET_H
