#ifndef TOOLS_TRAPHOLE_H
#define TOOLS_TRAPHOLE_H

#include "../tool.h"

namespace Tools {

class TrapHole : public Tool
{
    Q_OBJECT

public:
    explicit TrapHole(QObject *parent = nullptr);

protected:
    void collition(QGraphicsItem *);
};

}

#endif // TOOLS_TRAPHOLE_H
