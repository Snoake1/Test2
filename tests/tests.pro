include(gtest_dependency.pri)

TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG += thread
CONFIG -= qt

QMAKE_CXXFLAGS += -Wall -Wextra
QMAKE_CFLAGS += -Wall -Wextra 

# gcov
QMAKE_CXXFLAGS += -fprofile-arcs -ftest-coverage
QMAKE_CFLAGS += -fprofile-arcs -ftest-coverage
LIBS += -lgcov

DEFINES += INPUTDIR=\\\"$$PWD/input/\\\"

HEADERS +=  tests.h \
    ../edt/common.h \
    ../edt/text.h \
    ../edt/_text.h \
    tests_out.h

SOURCES += main.cpp \
   ../edt/mcursor.c \
   ../edt/load.c \
   ../edt/save.c \
   ../edt/show.c \
   ../edt/text/append_line.c \
   ../edt/text/create_text.c \
   ../edt/text/process_forward.c \
   ../edt/text/remove_all.c \
   ../edt/rc.c \
   ../edt/mwbb.c

INCLUDEPATH += ../edt

DISTFILES += \
    input.txt \
    input/test_in.txt \
    input/test_sweb.txt
