#include "headers/mainclient.h"
#include <QApplication>
#include <QIcon>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.setWindowIcon(QIcon("./icons/server_icon.ico"));
    MainClient w;
    w.show();

    return a.exec();
}
