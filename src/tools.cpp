#include "tools.h"
#include "sprites/mouse.h"

Tools::Tools() {}

bool Tools::isObjectOfClass(QGraphicsItem *i, const QString clsName)
{
    QString toc = QString(typeid(i).name());

    Mouse *m = dynamic_cast<Mouse*>(i);

    qDebug() << "Class: " << m;

    // return (toc.right(5) == clsName);

    return m != nullptr;
}
