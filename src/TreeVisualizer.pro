QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    AVLTree.cpp \
    Pidrevo.cpp \
    RBTree.cpp \
    SplayTree.cpp \
    avltreevisualizer.cpp \
    main.cpp \
    mainwindow.cpp \
    pidrevovisualizer.cpp \
    rbtreevisualizer.cpp \
    splaytreevisualizer.cpp

HEADERS += \
    AVLTree.h \
    Pidrevo.h \
    RBTree.h \
    SplayTree.h \
    avltreevisualizer.h \
    mainwindow.h \
    pidrevovisualizer.h \
    rbtreevisualizer.h \
    splaytreevisualizer.h

FORMS += \
    avltreevisualizer.ui \
    mainwindow.ui \
    pidrevovisualizer.ui \
    rbtreevisualizer.ui \
    splaytreevisualizer.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
