TEMPLATE = app
CONFIG += console c++14
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp

HEADERS += \
    tensorlib.h \
    sparsecootensor.h \
    cootensoritem.h \
    typedefs.h \
    kruskaltensor.h

QMAKE_CXXFLAGS+= -fopenmp
QMAKE_LFLAGS +=  -fopenmp

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/dep/release/ -lsplatt
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/dep/debug/ -lsplatt
else:unix: LIBS += -L$$PWD/dep/ -lsplatt

INCLUDEPATH += $$PWD/dep
DEPENDPATH += $$PWD/dep

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/dep/release/libsplatt.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/dep/debug/libsplatt.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/dep/release/splatt.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/dep/debug/splatt.lib
else:unix: PRE_TARGETDEPS += $$PWD/dep/libsplatt.a

unix|win32: LIBS += -llapack

unix|win32: LIBS += -lblas
