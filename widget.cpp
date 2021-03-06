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

QString arg;
int xx = 0;

int main(int argc, char *argv[])
{
    arg = argv[1];
    QApplication a(argc, argv);
    Widget w;
    if (xx != 0) {
        return a.exec();
    }
}

Widget::Widget(QWidget *parent)
    : QWidget(parent)
{

    QMimeDatabase db;
    QMimeType mime = db.mimeTypeForFile(arg);

    QAction *act = nullptr;
    QMenu *menu = new QMenu;
    QPoint p = QCursor::pos();
    const KService::List offers = KApplicationTrader::queryByMimeType(mime.name());
    for (const auto &service : offers) {
        qDebug() << service->entryPath();
        act = menu->addAction(QIcon::fromTheme(service->icon()), service->name());
        act->setData(service->entryPath());
    }
    menu->addSeparator();
    QAction *other_act = nullptr;
    other_act = menu->addAction("其他应用程序打开");
    other_act->setData(QString());
    connect(other_act, &QAction::triggered, this, [=]() { xx = 1; });

    connect(menu, &QMenu::triggered, this, &Widget::open);
    connect(menu, &QMenu::aboutToHide, this, [=]() { qApp->exit(); });
    menu->exec(p);
}

Widget::~Widget()
{
}
void Widget::open(QAction *act)
{
    QList<QUrl> list;
    list << QUrl(arg);
    KService::Ptr app = KService::serviceByDesktopPath(act->data().toString());
    // If app is null, ApplicationLauncherJob will invoke the open-with dialog
    auto *job = new KIO::ApplicationLauncherJob(app);
    job->setUrls(list);
    job->setUiDelegate(new KIO::JobUiDelegate(KJobUiDelegate::AutoHandlingEnabled, this));
    job->start();
}
