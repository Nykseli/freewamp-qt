
#include "playercontrols.h"

#include <QBoxLayout>
#include <QSlider>
#include <QStyle>
#include <QToolButton>
#include <QComboBox>
#include <QAudio>

PlayerControls::PlayerControls(QWidget *parent)
    : QWidget(parent)
{
    m_playButton = new QToolButton(this);
    m_playButton->setIcon(style()->standardIcon(QStyle::SP_MediaPlay));

    connect(m_playButton, &QAbstractButton::clicked, this, &PlayerControls::playClicked);

    m_pauseButton = new QToolButton(this);
    m_pauseButton->setIcon(style()->standardIcon(QStyle::SP_MediaPause));

    connect(m_pauseButton, &QAbstractButton::clicked, this, &PlayerControls::pauseClicked);

    m_stopButton = new QToolButton(this);
    m_stopButton->setIcon(style()->standardIcon(QStyle::SP_MediaStop));
    m_stopButton->setEnabled(false);

    connect(m_stopButton, &QAbstractButton::clicked, this, &PlayerControls::stop);

    m_nextButton = new QToolButton(this);
    m_nextButton->setIcon(style()->standardIcon(QStyle::SP_MediaSkipForward));

    connect(m_nextButton, &QAbstractButton::clicked, this, &PlayerControls::next);

    m_previousButton = new QToolButton(this);
    m_previousButton->setIcon(style()->standardIcon(QStyle::SP_MediaSkipBackward));

    connect(m_previousButton, &QAbstractButton::clicked, this, &PlayerControls::previous);

    m_muteButton = new QToolButton(this);
    m_muteButton->setIcon(style()->standardIcon(QStyle::SP_MediaVolume));

    connect(m_muteButton, &QAbstractButton::clicked, this, &PlayerControls::muteClicked);

    m_volumeSlider = new QSlider(Qt::Horizontal, this);
    m_volumeSlider->setRange(0, 100);

    connect(m_volumeSlider, &QSlider::valueChanged, this, &PlayerControls::onVolumeSliderValueChanged);

    QBoxLayout *layout = new QHBoxLayout;
    layout->setMargin(0);
    layout->addWidget(m_previousButton);
    layout->addWidget(m_playButton);
    layout->addWidget(m_pauseButton);
    layout->addWidget(m_stopButton);
    layout->addWidget(m_nextButton);
    layout->addWidget(m_muteButton);
    layout->addWidget(m_volumeSlider);
    setLayout(layout);
}

QMediaPlayer::State PlayerControls::state() const
{
    return m_playerState;
}

void PlayerControls::setState(QMediaPlayer::State state)
{
    if (state != m_playerState) {
        m_playerState = state;

        switch (state) {
        case QMediaPlayer::StoppedState:
            m_stopButton->setEnabled(false);
            break;
        case QMediaPlayer::PlayingState:
            m_stopButton->setEnabled(true);
            break;
        case QMediaPlayer::PausedState:
            m_stopButton->setEnabled(true);
            break;
        }
    }
}

int PlayerControls::volume() const
{
    qreal linearVolume =  QAudio::convertVolume(m_volumeSlider->value() / qreal(100),
                                                QAudio::LogarithmicVolumeScale,
                                                QAudio::LinearVolumeScale);

    return qRound(linearVolume * 100);
}

void PlayerControls::setVolume(int volume)
{
    qreal logarithmicVolume = QAudio::convertVolume(volume / qreal(100),
                                                    QAudio::VolumeScale::LinearVolumeScale,
                                                    QAudio::LogarithmicVolumeScale);

    m_volumeSlider->setValue(qRound(logarithmicVolume * 100));
}

#include <iostream>

void PlayerControls::increaseVolume(int amount) {
    // Make sure volume slider has focus so we can change it's value
    m_volumeSlider->setFocus();
    const int c_volume = volume();
    int volume = (c_volume + amount) >= 100 ? 100 : c_volume + amount;
    setVolume(volume);
}

void PlayerControls::decreaseVolume(int amount) {
    // Make sure volume slider has focus so we can change it's value
    m_volumeSlider->setFocus();
    const int c_volume = volume();
    int volume = (c_volume - amount) <= 0 ? 0 : c_volume - amount;
    std::cout << volume << std::endl;
    std::cout << c_volume << std::endl;
    setVolume(volume);
}

bool PlayerControls::isMuted() const
{
    return m_playerMuted;
}

void PlayerControls::setMuted(bool muted)
{
    if (muted != m_playerMuted) {
        m_playerMuted = muted;

        m_muteButton->setIcon(style()->standardIcon(muted
                ? QStyle::SP_MediaVolumeMuted
                : QStyle::SP_MediaVolume));
    }
}

void PlayerControls::togglePlayPause(){
    // Make sure that the whole player app has focus so the play/pause works properly
    this->setFocus();
    playClicked();
}

void PlayerControls::playClicked()
{
    switch (m_playerState) {
    case QMediaPlayer::StoppedState:
    case QMediaPlayer::PausedState:
        emit play();
        break;
    case QMediaPlayer::PlayingState:
        emit pause();
        break;
    }
}

void PlayerControls::pauseClicked()
{
    if (m_playerState == QMediaPlayer::PlayingState) {
        emit pause();
    }
}

void PlayerControls::muteClicked()
{
    emit changeMuting(!m_playerMuted);
}

void PlayerControls::onVolumeSliderValueChanged()
{
    emit changeVolume(volume());
}
