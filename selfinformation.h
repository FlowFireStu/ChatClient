#ifndef SELFINFORMATION_H
#define SELFINFORMATION_H

#include <QString>

class SelfInformation
{
private:
    QString m_id;
    QString m_name;
    static SelfInformation* m_manager;

private:
    SelfInformation();

public:
    SelfInformation(const SelfInformation&) = delete;
    SelfInformation& operator=(const SelfInformation&) = delete;
    static SelfInformation* getInstance();

    void init(const QString& id = "default");
    QString id() const;
    QString name() const;
    void setName(const QString &newName);
};

#endif // SELFINFORMATION_H
