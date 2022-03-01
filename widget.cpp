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
Widget::Widget(QWidget *parent)
    : QWidget(parent)
{

    QMimeDatabase db;
    QMimeType mime = db.mimeTypeForFile("./main.cpp");

    QAction *act = nullptr;
    QMenu *menu=new QMenu;
    QPoint p = QCursor::pos();
    const KService::List offers = KApplicationTrader::queryByMimeType(mime.name());
    for (const auto &service : offers) {
        qDebug() << service->entryPath();
        act = menu->addAction(QIcon::fromTheme(service->icon()), service->name());
        act->setData(service->entryPath());
    }
    act = menu->addAction("其他");
    act->setData(QString());

    connect(menu, &QMenu::triggered,this
            , &Widget::open);
    menu->exec(p);
}

Widget::~Widget()
{
}
void Widget::open(QAction *act)
{
    QList<QUrl> list;
    list << QUrl();
    KService::Ptr app = KService::serviceByDesktopPath(act->data().toString());
    // If app is null, ApplicationLauncherJob will invoke the open-with dialog
    auto *job = new KIO::ApplicationLauncherJob(app);
    job->setUrls(list);
    job->setUiDelegate(new KIO::JobUiDelegate(KJobUiDelegate::AutoHandlingEnabled, this));
    job->start();
}
