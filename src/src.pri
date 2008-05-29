###########
## This file is part of Blind Camaleon.
##
## Blind Camaleon is free software: you can redistribute it and/or modify
## it under the terms of the GNU Lesser General Public License as published by
## the Free Software Foundation, either version 3 of the License, or
## (at your option) any later version.
##
## Blind Camaleon is distributed in the hope that it will be useful,
## but WITHOUT ANY WARRANTY; without even the implied warranty of
## MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
## GNU Lesser General Public License for more details.
##
## You should have received a copy of the GNU Lesser General Public License
## along with Blind Camaleon.  If not, see <http://www.gnu.org/licenses/lgpl-3.0.txt>.
###########


# files
HEADERS += \
    pidmain.h \
    about.h \
    help.h \
    histogram.h \
    imagetabs.h \
    complex.h \
    simplefilter.h \
    simplefilteredimage.h \
    fft.h \
    basicfilter.h \
    passaalta.h \
    passabaixa.h \
    idealfilter.h \
    idealfilteredimage.h \
    butterworth.h

SOURCES += \
    pidmain.cpp \
    about.cpp \
    help.cpp \
    histogram.cpp \
    imagetabs.cpp \
    complex.cpp \
    simplefilter.cpp \
    simplefilteredimage.cpp \
    fft.cpp \
    passabaixa.cpp \
    passaalta.cpp \
    basicfilter.cpp \
    idealfilter.cpp \
    idealfilteredimage.cpp \
    butterworth.cpp

FORMS += \
    main.ui \
    about.ui \
    help.ui \
    simplefilter.ui \
    ideal.ui

RESOURCES += images/images.qrc

RCC_DIR = .rcc
UI_DIR = .ui
MOC_DIR = .moc
OBJECTS_DIR = .obj

# configurations
TEMPLATE = app
CONFIG += qt warn_on
