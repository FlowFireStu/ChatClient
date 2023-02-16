#include "selfinformation.h"

SelfInformation* SelfInformation::m_manager = nullptr;

SelfInformation::SelfInformation()
{
}

SelfInformation *SelfInformation::getInstance()
{
    if (!m_manager)
    {
        m_manager = new SelfInformation;
    }
    return m_manager;
}

void SelfInformation::init(const QString &id)
{
   m_id = id;
   m_name = "";
}

QString SelfInformation::id() const
{
    return m_id;
}

QString SelfInformation::name() const
{
    return m_name;
}

void SelfInformation::setName(const QString &newName)
{
    m_name = newName;
}
