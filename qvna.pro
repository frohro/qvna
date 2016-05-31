TEMPLATE = app
CONFIG += qt \
    debug_and_release
QT += network \
    svg \
    widgets \
    serialport
SOURCES += main.cpp \
    qvna.cpp \
    hiqsdr_ctl.cpp \
    lib.cpp \
    plot.cpp \
    scale.cpp \
    diag.cpp \
    settingsdialog.cpp \
    console.cpp
HEADERS += qvna.h \
    plot.h \
    scale.h \
    hiqsdr_ctl.h \
    diag.h \
    settingsdialog.h \
    console.h \
    config.h
FORMS += qvna.ui \
    diag.ui \
    settingsdialog.ui
debug { 
    TARGET = qvna.debug
    OBJECTS_DIR = .obj_debug
}
release { 
    TARGET = qvna
    OBJECTS_DIR = .obj_release
}
win32:RC_FILE = qvna.rc
UI_DIR = .ui
MOC_DIR = .moc
