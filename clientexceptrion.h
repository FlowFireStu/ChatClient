#ifndef CLIENTEXCEPTRION_H
#define CLIENTEXCEPTRION_H

#include <QString>

class ClientExceptrion
{
    QString m_information;

public:
    ClientExceptrion(QString information = "未知错误");
    virtual QString show();

};

#endif // CLIENTEXCEPTRION_H
