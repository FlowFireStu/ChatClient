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
public:
    explicit AccountItem(QWidget *parent = nullptr);
    ~AccountItem();

    void setName(const QString& name);
    void setCount(int count);

    QString id() const;
    void setId(const QString &newId);

    void enterEvent(QEnterEvent* e) override;
    void mouseDoubleClickEvent(QMouseEvent* e) override;
    void leaveEvent(QEvent* e) override;

    void setColor(const QColor& color);

private:
    Ui::AccountItem *ui;

    QPalette defaultPal;
    QPalette enterPal;

signals:
    void clicked(const QString& id, const QString& name);
};

#endif // ACCOUNTITEM_H
