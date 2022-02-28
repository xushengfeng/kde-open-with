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
#include <QVBoxLayout>
#include <QtWidgets>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Widget w;
    QMimeDatabase db;
    QMimeType mime = db.mimeTypeForFile("./main.cpp");

    QVBoxLayout *layout = new QVBoxLayout;

    const KService::List offers = KApplicationTrader::queryByMimeType(mime.name());
    for (const auto &service : offers) {
        qDebug()<<service->entryPath();
        QPushButton *button = new QPushButton;
        button->setIcon(QIcon::fromTheme(service->icon()));
        button->setText(service->name());
        layout->addWidget(button);
    }
    w.setLayout(layout);
    w.show();
    QList<QUrl> list;
    list << QUrl(argv[1]);
    auto *job = new KIO::ApplicationLauncherJob();
    job->setUrls(list);
    job->setUiDelegate(new KIO::JobUiDelegate(KJobUiDelegate::AutoHandlingEnabled, &w));
//    job->start();
    return a.exec();
}
