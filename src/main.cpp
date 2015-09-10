#include <QApplication>

#include <notepad.h>

int main (int argc, char *argv[])
{
    QApplication app(argc, argv);
    TextEditor ted;
    ted.show();

    return app.exec();
}
