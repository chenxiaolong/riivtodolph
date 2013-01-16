#-------------------------------------------------
#
# Project created by QtCreator 2013-01-14T11:36:25
#
#-------------------------------------------------

QT       += core

QT       -= gui

QT       += xml

TARGET = riivtodolph-qt
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += main.cpp \
    riivtodolph.cpp \
    riivxmlparse.cpp \
    xml_wiidisc.cpp \
    xml_section.cpp \
    xml_option.cpp \
    xml_choice.cpp

HEADERS += \
    riivtodolph.h \
    riivxmlparse.h \
    xml_wiidisc.h \
    xml_section.h \
    xml_option.h \
    xml_choice.h
