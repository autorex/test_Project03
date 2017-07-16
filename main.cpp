#include "smdialog.h"
#include <QApplication>
int main(int argc, char *argv[])
{
QApplication a(argc, argv);
SMDialog w;
w.show();
return a.exec();
}
