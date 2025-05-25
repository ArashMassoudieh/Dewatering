
#include <QtWidgets/QApplication>
#include "Parameters_dialog.h"



int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
	Parameters_dialog w;
    w.show();
    return a.exec();
}
