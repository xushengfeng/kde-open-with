#include "mainwindow.h"

#include <QApplication>
#include <KIO/ApplicationLauncherJob>
#include <KIO/Job>
#include <KIO/JobUiDelegate>
#include <QList>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    QList<QUrl> list;
    list << QUrl(argv[1]);
    auto *job = new KIO::ApplicationLauncherJob();
    job->setUrls(list);
    job->setUiDelegate(new KIO::JobUiDelegate(KJobUiDelegate::AutoHandlingEnabled, &w));
    job->start();
    return a.exec();
}
