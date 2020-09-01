include($$[QT_INSTALL_PREFIX]/include/nymea/plugin.pri)

QMAKE_PRE_LINK = scons -C $$_PRO_FILE_PWD_/rpi_ws281x libws2811.a

QMAKE_CXXFLAGS -= -Werror

LIBS += -L$$_PRO_FILE_PWD_/rpi_ws281x/ -lws2811
INCLUDEPATH += $$_PRO_FILE_PWD_/rpi_ws281x

SOURCES += \
    integrationpluginws281xspi.cpp \
    ws281xspicontroller.cpp

HEADERS += \
    integrationpluginws281xspi.h \
    ws281xspicontroller.h

