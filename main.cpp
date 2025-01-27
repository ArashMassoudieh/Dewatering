#include "SludgeAnalyzer.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    SludgeAnalyzer w;
    w.show();
    return a.exec();
}
