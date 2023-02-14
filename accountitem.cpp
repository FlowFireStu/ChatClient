#include "accountitem.h"
#include "ui_accountitem.h"

AccountItem::AccountItem(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AccountItem)
{
    ui->setupUi(this);

    setAutoFillBackground(true);
    defaultPal = this->palette();
    enterPal.setColor(QPalette::Window, QColor(0x6c, 0xcf, 0x70));
}

AccountItem::~AccountItem()
{
    delete ui;
}

void AccountItem::setName(const QString &name)
{
    ui->nameLabel->setText(name);
}

void AccountItem::setCount(int count)
{
    ui->countLabel->setText(QString::number(count));
}

QString AccountItem::id() const
{
    return m_id;
}

void AccountItem::setId(const QString &newId)
{
    m_id = newId;
}

void AccountItem::enterEvent(QEnterEvent *e)
{
    setPalette(enterPal);
}

void AccountItem::mouseDoubleClickEvent(QMouseEvent *e)
{
    emit clicked(m_id, ui->nameLabel->text());
    setPalette(defaultPal);
}

void AccountItem::leaveEvent(QEvent *e)
{
    setPalette(defaultPal);
}
