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
#include <QtWidgets>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Widget w;
    QMimeDatabase db;
    QMimeType mime = db.mimeTypeForFile("./main.cpp");

    QAction *act = nullptr;
    QMenu menu;
    QPoint p;
    p.setX(0);
    p.setY(0);
    const KService::List offers = KApplicationTrader::queryByMimeType(mime.name());
    for (const auto &service : offers) {
        qDebug()<<service->entryPath();
        act = menu.addAction(QIcon::fromTheme(service->icon()), service->name());
        act ->setData(service->entryPath());
    }
    act = menu.addAction("其他");

    QList<QUrl> list;
    list << QUrl(argv[1]);
    auto *job = new KIO::ApplicationLauncherJob();
    job->setUrls(list);
    job->setUiDelegate(new KIO::JobUiDelegate(KJobUiDelegate::AutoHandlingEnabled, &w));
//    job->start();

    menu.exec();
    return a.exec();
}
