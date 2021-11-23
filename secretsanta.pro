QT += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11
DEFINES += QT_DEPRECATED_WARNINGS
TEMPLATE = app
VERSION = 1.0

SOURCES += \
    langdialog.cpp \
    main.cpp \
    mainwindow.cpp

HEADERS += \
    global.h \
    langdialog.h \
    mainwindow.h

FORMS += \
    langdialog.ui \
    mainwindow.ui

unix:!android {
    target.path = $${PREFIX}/bin
    icon.path = /usr/share/pixmaps
    icon.files = icons/santa.png
    desktop.path = /usr/share/applications
    desktop.files = secretsanta.desktop
    INSTALLS += target icon desktop
}

win32 {
    VERSION = $${VERSION}.0.0
    QMAKE_TARGET_COMPANY = DP Software
    QMAKE_TARGET_DESCRIPTION = A multi-player, equal probabilities Secret Santa
    QMAKE_TARGET_COPYRIGHT = \\251 2021 Dimitris Psathas
    QMAKE_TARGET_PRODUCT = SecretSanta
    RC_ICONS = icons/santa.ico
    RC_LANG = 0x408
    RC_CODEPAGE = 1253
}

RESOURCES += \
    secretsanta.qrc

TRANSLATIONS = secretsanta_el_GR.ts
CONFIG += lrelease
CONFIG += embed_translations
