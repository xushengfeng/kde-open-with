#include "widget.h"

#include <QApplication>
#include <KIO/ApplicationLauncherJob>
#include <KIO/Job>
#include <KIO/JobUiDelegate>
#include <KApplicationTrader>
#include <QList>
#include <QMenu>
#include <QMimeDatabase>
#include <QDebug>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Widget w;
    QMimeDatabase db;
    QMimeType mime = db.mimeTypeForFile("./main.cpp");

    const KService::List offers = KApplicationTrader::queryByMimeType(mime.name());
    for (const auto &service : offers) {
        qDebug()<<service->name();
    }
//    w.show();
    QList<QUrl> list;
    list << QUrl(argv[1]);
    auto *job = new KIO::ApplicationLauncherJob();
    job->setUrls(list);
    job->setUiDelegate(new KIO::JobUiDelegate(KJobUiDelegate::AutoHandlingEnabled, &w));
//    job->start();
    return a.exec();
}
