TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

#`sdl2-config --cflags --libs` -lSDL2 -lSDL2_mixer -lSDL2_image -lSDL2_ttf
LIBS += -lSDL2 -lSDL2_mixer -lSDL2_image -lSDL2_ttf -lsqlite3 -lpthread
TARGET = Pong

SOURCES += \
        src/ball.cpp \
        src/center_line.cpp \
        src/collision_detector.cpp \
        src/court_scene.cpp \
        src/endgame_scene.cpp \
        src/game.cpp \
        src/goal.cpp \
        src/help_scene.cpp \
        src/main.cpp \
        src/paddle.cpp \
        src/register_scene.cpp \
        src/score_indicator.cpp \
        src/wall.cpp \
        src/welcome_scene.cpp

HEADERS += \
    include/ball.h \
    include/center_line.h \
    include/collision_detector.h \
    include/court_scene.h \
    include/endgame_scene.h \
    include/game.h \
    include/goal.h \
    include/help_scene.h \
    include/paddle.h \
    include/register_scene.h \
    include/scene.h \
    include/score_indicator.h \
    include/sqlitedatabase.h \
    include/userinfo.h \
    include/wall.h \
    include/welcome_scene.h
    
    
INCLUDEPATH += /usr/include/SDL2
INCLUDEPATH += $$PWD/include
DEPENDPATH += $$PWD/include
