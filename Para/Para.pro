TEMPLATE = app
CONFIG += console c++17
CONFIG -= app_bundle
CONFIG -= qt

QMAKE_CXXFLAGS+= -openmp
QMAKE_LFLAGS +=  -openmp

SOURCES += \
        main.cpp
