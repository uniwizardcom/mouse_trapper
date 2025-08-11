#ifndef MENUBUTTON_H
#define MENUBUTTON_H

#include <QToolButton>
#include <QPaintEvent>

class MenuButton : public QToolButton
{
    Q_OBJECT

public:
 /*   explicit MenuButton(QWidget *parent = nullptr);
    explicit MenuButton(const QString &text, QWidget *parent = nullptr);
    MenuButton(const QIcon& icon, const QString &text, QWidget *parent = nullptr);*/

    explicit MenuButton(QWidget *parent = nullptr);

    void setBackgroundImage(const QString &fileName);

protected:
    void enterEvent(QEnterEvent *);
    void leaveEvent(QEvent *);
private:
    QString backgroundImage;
};

#endif // MENUBUTTON_H
