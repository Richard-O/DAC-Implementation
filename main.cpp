#include "filemanagerwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    FileManagerWindow w;
    w.show();

    return a.exec();
}
