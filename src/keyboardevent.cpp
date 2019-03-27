#include "keyboardevent.h"

#include "playercontrols.h"

#include <QApplication>
#include <QMediaPlayer>
#include <QKeyEvent>

void KeyboardEvent::setControls(PlayerControls *controls) {
    this->playerControls = controls;
}

bool KeyboardEvent::eventFilter(QObject* obj, QEvent* event)
{

    // Playlist handles these by default:
    // enter key selects (plays) the selected track
    // arrow up selects the previous track
    // arrow down selects the next track
    // so we don't need to handle them in here

    if (event->type()==QEvent::KeyRelease){
        QKeyEvent* key = static_cast<QKeyEvent*>(event);
        switch (key->key())
        {
            case Qt::Key_Space:
                // TODO: start playing the first track if none is selected
                playerControls->togglePlayPause();
                break;
            case Qt::Key_Left:
                playerControls->decreaseVolume(5);
                break;
            case Qt::Key_Right:
                playerControls->increaseVolume(5);
                break;
            default:
                return false;
                break;
        }
        return true;
    } else {
        return QObject::eventFilter(obj, event);
    }

    return false;
}

