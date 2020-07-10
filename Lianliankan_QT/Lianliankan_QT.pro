QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    CBasicGame.cpp \
    CEasyGame.cpp \
    CGameControl.cpp \
    CGameDlg.cpp \
    CGameLogic.cpp \
    CGraph.cpp \
    CHelpDialog.cpp \
    CLLKDlg.cpp \
    CLevelGame.cpp \
    CRankDlg.cpp \
    CScoreDao.cpp \
    CScoreLogic.cpp \
    CSettingDlg.cpp \
    CTest.cpp \
    main.cpp

HEADERS += \
    CBasicGame.h \
    CEasyGame.h \
    CGameControl.h \
    CGameDlg.h \
    CGameLogic.h \
    CGraph.h \
    CHelpDialog.h \
    CLLKDlg.h \
    CLevelGame.h \
    CRankDlg.h \
    CScoreDao.h \
    CScoreLogic.h \
    CSettingDlg.h \
    CTest.h \
    global.h

FORMS += \
    CGameDlg.ui \
    CHelpDialog.ui \
    CLLKDlg.ui \
    CRankDlg.ui \
    CSettingDlg.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    res.qrc

RC_ICONS = "res/LLK.ico"

QMAKE_TARGET_COMPANY = "J.Y"

QMAKE_TARGET_DESCRIPTION = "LLK"

QMAKE_TARGET_COPYRIGHT = "Copyright (C) 2020."

QMAKE_TARGET_PRODUCT = "LLK"
