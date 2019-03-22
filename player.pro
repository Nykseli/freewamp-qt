TEMPLATE = app
TARGET = player

OBJECTS_DIR = build/objects/
MOC_DIR = build/moc/

QT += network \
      xml \
      multimedia \
      multimediawidgets \
      widgets

HEADERS = \
    src/player.h \
    src/playercontrols.h \
    src/playlistmodel.h \
    src/histogramwidget.h
SOURCES = src/main.cpp \
    src/player.cpp \
    src/playercontrols.cpp \
    src/playlistmodel.cpp \
    src/histogramwidget.cpp

target.path = player

INSTALLS += target
