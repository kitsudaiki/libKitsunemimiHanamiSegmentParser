include(../../defaults.pri)

QT -= qt core gui

CONFIG -= app_bundle
CONFIG += c++17 console

LIBS += -L../../src -lKitsunemimiHanamiSegmentParser
INCLUDEPATH += $$PWD

LIBS += -L../../../libKitsunemimiCommon/src -lKitsunemimiCommon
LIBS += -L../../../libKitsunemimiCommon/src/debug -lKitsunemimiCommon
LIBS += -L../../../libKitsunemimiCommon/src/release -lKitsunemimiCommon
INCLUDEPATH += ../../../libKitsunemimiCommon/include

SOURCES += \
    main.cpp

