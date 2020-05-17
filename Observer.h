#ifndef HELICOPTER_OBSERVER_H
#define HELICOPTER_OBSERVER_H

#include "Bat.h"

class Observer {
private:
    Bat* bat;
public:
    Observer(Bat* bat):bat(bat){ bat->addObserver(this); }
    Observer()  {}
    virtual void update() = 0;
    virtual void updateBonus() = 0;

protected:
    void setBat(Bat* bat) { this->bat = bat; bat->addObserver(this); }
    Bat* getBat() { return bat; }
};


#endif //HELICOPTER_OBSERVER_H
