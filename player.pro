TEMPLATE = app
TARGET = player

OBJECTS_DIR = build/objects/
MOC_DIR = build/moc/

LIBS += \
    -lavdevice\
    -lavformat\
    -lavfilter\
    -lavcodec\
    -lswresample\
    -lswscale\
    -lavutil\

INCPATH += \
    -Iffmpeg/include \
    -Lffmpeg/lib

QT += network \
      xml \
      multimedia \
      multimediawidgets \
      widgets

HEADERS = \
    src/player.h \
    src/playercontrols.h \
    src/playlistmodel.h \
    src/histogramwidget.h\
    src/metadata.h

SOURCES = src/main.cpp \
    src/player.cpp \
    src/playercontrols.cpp \
    src/playlistmodel.cpp \
    src/histogramwidget.cpp \
    src/metadata.cpp

target.path = player

INSTALLS += target
