QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    NodeDrawing.cpp \
    scanner.cpp \
    SyntaxTree.cpp \
    SyntaxTreeWidget.cpp \
    compiler.cpp \
    description.cpp \
    errors.cpp \
    fileeditor.cpp \
    main.cpp \
    mainwindow.cpp \
    parser.cpp \
    runtimevariables.cpp

HEADERS += \
    NodeDrawing.hpp \
    SyntaxTree.hpp \
    SyntaxTreeWidget.hpp \
    compiler.hpp \
    description.hpp \
    errors.hpp \
    fileeditor.hpp \
    headers.hpp \
    mainwindow.hpp \
    parser.hpp \
    runtimevariables.hpp \
    scanner.hpp

FORMS += \
    compiler.ui \
    description.ui \
    errors.ui \
    fileeditor.ui \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES +=

RESOURCES += \
    Resources.qrc
