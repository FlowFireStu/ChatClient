#include "clientexceptrion.h"

ClientExceptrion::ClientExceptrion(QString information)
{
    m_information = information;
}

QString ClientExceptrion::show()
{
    return m_information;
}
