#ifndef CHATWIDGET_H
#define CHATWIDGET_H

#include <QWidget>

namespace Ui {
class ChatWidget;
}

class ChatWidget : public QWidget
{
    Q_OBJECT

    QString m_id;

public:
    explicit ChatWidget(const QString& id, const QString& name, QWidget *parent = nullptr);
    ~ChatWidget();

private:
    Ui::ChatWidget *ui;
};

#endif // CHATWIDGET_H
