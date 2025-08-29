#ifndef TOOLS_TRAPHOLEAUTO_H
#define TOOLS_TRAPHOLEAUTO_H

#include "../tool.h"

namespace Tools {

class TrapHoleAuto : public Tool
{
    Q_OBJECT

public:
    explicit TrapHoleAuto(QObject *parent = nullptr);

protected:
    void collition(QGraphicsItem *);
};

}

#endif // TOOLS_TRAPHOLEAUTO_H
