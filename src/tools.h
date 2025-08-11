#ifndef TOOLS_H
#define TOOLS_H

#include <QGraphicsItem>
#include <QString>

class Tools
{
public:
    Tools();

    static bool isObjectOfClass(QGraphicsItem *i, const QString clsName);
};

#endif // TOOLS_H
