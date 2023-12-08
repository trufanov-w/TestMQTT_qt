QT += testlib
QT -= gui

CONFIG += qt console warn_on depend_includepath testcase
CONFIG -= app_bundle

TEMPLATE = app

SOURCES +=  \
    ../../../mqtt/src/repository/filereader.cpp \
    tst_filereadertest.cpp

HEADERS += \
    ../../../mqtt/src/repository/filereader.h

DISTFILES += \
    existing_file.txt

copydata.commands = $(COPY_DIR) $$PWD/existing_file.txt $$OUT_PWD
first.depends = $(first) copydata
export(first.depends)
export(copydata.commands)
QMAKE_EXTRA_TARGETS += first copydata
