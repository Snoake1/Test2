TEMPLATE = subdirs

CONFIG -= app_bundle
CONFIG -= qt

QMAKE_CXXFLAGS += -fprofile-arcs -ftest-coverage -O0

SUBDIRS = editor tests

CONFIG += ordered
