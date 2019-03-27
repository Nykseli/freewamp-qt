#ifndef KEYBOARDEVENT_H
#define KEYBOARDEVENT_H

#include <QWidget>

#include "playercontrols.h"
class PlayerControls;

class KeyboardEvent : public QObject
{
    Q_OBJECT

public:
    void setControls(PlayerControls *controls);


protected:
    virtual bool eventFilter(QObject* obj, QEvent* event) override;


private:
    PlayerControls *playerControls = nullptr;

};

#endif // KEYBOARDEVENT_H
