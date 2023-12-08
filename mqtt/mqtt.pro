TEMPLATE = app

QT += core quick mqtt

CONFIG += c++17

SOURCES += src/main.cpp \
    src/logger/logger.cpp \
    src/manager/manager.cpp \
    src/repository/filereader.cpp \
    src/repository/repository.cpp

RESOURCES += \
    images.qrc \
    qml.qrc

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

HEADERS += \
    src/general/types.h \
    src/logger/logger.h \
    src/manager/manager.h \
    src/repository/filereader.h \
    src/repository/repository.h

