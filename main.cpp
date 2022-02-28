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
    QMimeDatabase db;
    QMimeType mime = db.mimeTypeForFile("./main.cpp");

    QAction *act = nullptr;
    QMenu menu;
    QPoint p = QCursor::pos();
    const KService::List offers = KApplicationTrader::queryByMimeType(mime.name());
    for (const auto &service : offers) {
        qDebug() << service->entryPath();
        act = menu.addAction(QIcon::fromTheme(service->icon()), service->name());
        act->setData(service->entryPath());
    }
    act = menu.addAction("其他");
    act->setData(QString());

    menu.exec(p);
    return a.exec();
}

void Widget::open(QAction *act,int argc, char *argv[])
{
    QList<QUrl> list;
    list << QUrl(argv[1]);
    KService::Ptr app = KService::serviceByDesktopPath(act->data().toString());
    // If app is null, ApplicationLauncherJob will invoke the open-with dialog
    auto *job = new KIO::ApplicationLauncherJob(app);
    job->setUrls(list);
    job->setUiDelegate(new KIO::JobUiDelegate(KJobUiDelegate::AutoHandlingEnabled, this));
    job->start();
}
