######################################################################

QT += widgets

TEMPLATE = app

DESTDIR = ./bin
TARGET = TED
INCLUDEPATH += ./include

MOC_DIR += ./obj
OBJECTS_DIR += ./obj

# Input
VPATH += ./src ./include
HEADERS += notepad.h crypto.h
SOURCES += main.cpp notepad.cpp crypto.cpp

LIBS += -lgcrypt
