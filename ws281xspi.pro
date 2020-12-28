include($$[QT_INSTALL_PREFIX]/include/nymea/plugin.pri)


QMAKE_CXXFLAGS -= -Werror

INCLUDEPATH += $$_PRO_FILE_PWD_/rpi_ws281x

SOURCES += \
    integrationpluginws281xspi.cpp \
    ws281xspicontroller.cpp \
    rpi_ws281x/mailbox.c \
    rpi_ws281x/pwm.c \
    rpi_ws281x/rpihw.c \
    rpi_ws281x/ws2811.c \
    rpi_ws281x/dma.c \
    rpi_ws281x/pcm.c

HEADERS += \
    integrationpluginws281xspi.h \
    ws281xspicontroller.h \
    rpi_ws281x/rpihw.h \
    rpi_ws281x/pwm.h \
    rpi_ws281x/ws2811.h \
    rpi_ws281x/dma.h \
    rpi_ws281x/pcm.h

