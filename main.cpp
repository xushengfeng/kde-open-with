#include "widget.h"

#include <KApplicationTrader>
#include <KIO/ApplicationLauncherJob>
#include <KIO/Job>
#include <KIO/JobUiDelegate>
#include <QApplication>
#include <QCursor>
#include <QDebug>
#include <QList>
#include <QMenu>
#include <QMimeDatabase>
#include <QtWidgets>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Widget w;
    return a.exec();
}

