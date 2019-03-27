
#include "player.h"

#include "keyboardevent.h"

#include <QApplication>
#include <QCommandLineParser>
#include <QCommandLineOption>
#include <QDir>

// Minimum width of the window
#define WINDOW_MIN_WIDTH 380

// The base style for the whole project
#define BASE_STYLE "background-color: #373751; color: #1e2b34"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    QCoreApplication::setApplicationName("Player Example");
    QCoreApplication::setOrganizationName("QtProject");
    QCoreApplication::setApplicationVersion(QT_VERSION_STR);
    QCommandLineParser parser;
    QCommandLineOption customAudioRoleOption("custom-audio-role",
                                             "Set a custom audio role for the player.",
                                             "role");
    parser.addHelpOption();
    parser.addVersionOption();
    parser.addOption(customAudioRoleOption);
    parser.addPositionalArgument("url", "The URL(s) to open.");
    parser.process(app);

    KeyboardEvent *k_event = new KeyboardEvent();
    app.installEventFilter(k_event);

    Player player;

    player.setStyleSheet(BASE_STYLE);
    player.setMinimumWidth(WINDOW_MIN_WIDTH);

    if (parser.isSet(customAudioRoleOption))
        player.setCustomAudioRole(parser.value(customAudioRoleOption));

    if (!parser.positionalArguments().isEmpty() && player.isPlayerAvailable()) {
        QList<QUrl> urls;
        for (auto &a: parser.positionalArguments())
            urls.append(QUrl::fromUserInput(a, QDir::currentPath(), QUrl::AssumeLocalFile));
        player.addToPlaylist(urls);
    }

    player.setKeyboardEventListener(k_event);

    player.show();
    return app.exec();
}
