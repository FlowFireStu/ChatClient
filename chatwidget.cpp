#include "chatwidget.h"
#include "ui_chatwidget.h"

ChatWidget::ChatWidget(const QString& id, const QString& name, QWidget *parent) :
    QWidget(parent),
    m_id(id),
    ui(new Ui::ChatWidget)
{
    ui->setupUi(this);

    setWindowTitle(name);
    ui->textEdit->setFocus();
}

ChatWidget::~ChatWidget()
{
    delete ui;
}
