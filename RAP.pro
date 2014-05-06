QT       += core gui script
QMAKE_CXXFLAGS += -std=c++0x

TARGET = RAP
TEMPLATE = app

OBJECTS_DIR = .obj
MOC_DIR = .moc
RCC_DIR = .qrc
UI_DIR = .ui

SOURCES += $$system(find src -name *.cpp -print)

HEADERS  += $$system(find src -name *.h -print)

INCLUDEPATH += $$system(find src -type d)

#FORMS    += widget.ui
