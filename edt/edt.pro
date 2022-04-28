TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += editor.c \
    mcursor.c \
    load.c \
    save.c \
    show.c \
    text/append_line.c \
    text/create_text.c \
    text/process_forward.c \
    text/remove_all.c 
    
HEADERS += \
    myfunc.h \
    _text.h \
    text.h 

DISTFILES

QMAKE_CFLAGS += -Wall -Wextra

# gcov
QMAKE_CFLAGS += -fprofile-arcs -ftest-coverage
LIBS += -lgcov
