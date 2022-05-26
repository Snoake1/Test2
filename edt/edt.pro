TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += editor.c \
    mcursor.c \
    load.c \
    save.c \
    show.c \
    rc.c \
    mwbb.c \
    append_line.c \
    create_text.c \
    process_forward.c \
    remove_all.c 
    
HEADERS += \
    myfunc.h \
    _text.h \
    text.h 

DISTFILES

QMAKE_CFLAGS += -Wall -Wextra

# gcov
QMAKE_CFLAGS += -fprofile-arcs -ftest-coverage
LIBS += -lgcov
