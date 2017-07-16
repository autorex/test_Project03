QT += widgets

SOURCES += main.cpp \
           smdialog.cpp

HEADERS += smdialog.h

# Forms and resources
FORMS += smdialog.ui

EXAMPLE_FILES = *.png

# install
target.path = $$[QT_INSTALL_EXAMPLES]/corelib/ipc/sharedmemory
INSTALLS += target
