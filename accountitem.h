#ifndef ACCOUNTITEM_H
#define ACCOUNTITEM_H

#include <QWidget>

namespace Ui {
class AccountItem;
}

class AccountItem : public QWidget
{
    Q_OBJECT

    QString m_id;
    QString m_name;
    int m_count;
public:
    explicit AccountItem(QWidget *parent = nullptr);
    ~AccountItem();

    QString id() const;
    void setId(const QString &newId);
    QString name() const;
    void setName(const QString& name);
    int count() const;
    void setCount(int count);
    void update();

    void enterEvent(QEnterEvent* e) override;
    void mouseDoubleClickEvent(QMouseEvent* e) override;
    void leaveEvent(QEvent* e) override;

private:
    Ui::AccountItem *ui;

    QPalette defaultPal;
    QPalette enterPal;

signals:
    void clicked(const QString& id, const QString& name);
};

#endif // ACCOUNTITEM_H
