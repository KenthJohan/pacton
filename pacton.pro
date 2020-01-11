TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.c

HEADERS += "C:/Program Files (x86)/Kvaser/Canlib/INC/canlib.h"
HEADERS += iup-3.28_Win64_mingw6_lib/include/iup.h
HEADERS += cd-5.12_Win64_mingw6_lib/include/cd.h
HEADERS += csc/csc_basic.h
HEADERS += csc/csc_kvasercan.h
HEADERS += csc/csc_iup.h
HEADERS += csc/csc_debug.h
HEADERS += csc/csc_tcol.h
HEADERS += csc/csc_pacton.h
HEADERS += csc/csc_str.h
HEADERS += misc.h


INCLUDEPATH += csc
INCLUDEPATH += iup-3.28_Win64_mingw6_lib/include
INCLUDEPATH += cd-5.12_Win64_mingw6_lib/include
INCLUDEPATH += "C:\Program Files (x86)\Kvaser\Canlib\INC"

LIBS += -L$$PWD/iup-3.28_Win64_mingw6_lib
LIBS += -L$$PWD/cd-5.12_Win64_mingw6_lib
LIBS += -L"C:\Program Files (x86)\Kvaser\Canlib\Lib\x64"
#LIBS += -lcanlib32 -liup -lgdi32 -lcomdlg32 -lcomctl32 -luuid -loleaut32 -lole32
LIBS += -lcanlib32 -liup -liupcontrols -liupcd -lcd -lcdim -lcdgl -liupimglib -lfreetype6 -lz -lkernel32 -luser32 -lgdi32 -lwinspool -lcomdlg32 -ladvapi32 -lshell32 -lole32 -loleaut32 -luuid -lcomctl32
