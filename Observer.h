#ifndef OBSERVER_H
#define OBSERVER_H

#include "Bat.h"

class Observer {
public:
    Observer()  {}
    virtual void updateScore() = 0;
    virtual void deleteBonus() = 0;

protected:
    void setBat(Bat* bat) { bat->addObserver(this); }
};


#endif //OBSERVER_H
