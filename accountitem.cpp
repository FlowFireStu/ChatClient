#include "accountitem.h"
#include "ui_accountitem.h"

AccountItem::AccountItem(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AccountItem)
{
    ui->setupUi(this);

    m_id = "";
    m_name = "";
    m_count = 0;
    setAutoFillBackground(true);
    defaultPal = this->palette();
    enterPal.setColor(QPalette::Window, QColor(0x6c, 0xcf, 0x70));
}

AccountItem::~AccountItem()
{
    delete ui;
}

QString AccountItem::name() const
{
    return m_name;
}

void AccountItem::setName(const QString &name)
{
    m_name = name;
    ui->nameLabel->setText(m_name);
}

int AccountItem::count() const
{
    return m_count;
}

void AccountItem::setCount(int count)
{
    m_count = count;
    if (m_count != 0)
    {
        ui->countLabel->setText(QString::number(m_count));
    }
    else
    {
        ui->countLabel->setText("");
    }
}

void AccountItem::update()
{
    ui->nameLabel->setText(m_name);
    setCount(m_count);
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
