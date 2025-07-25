#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QUrl>
#include <QEventLoop>

#include "mainwindow.h"


QStringList MainWindow::getReplayFromUrl(const QString &url)
{
    const QString logurl = url + ".log";

    QNetworkAccessManager client;
    QNetworkRequest request;
    request.setUrl(QUrl(logurl));
    QNetworkReply *reply = client.get(request);

    QEventLoop loop;
    QObject::connect(reply, &QNetworkReply::finished, &loop, &QEventLoop::quit);
    loop.exec();

    if (reply->error() != QNetworkReply::NoError) {
        qDebug() << "Request failed:" << reply->errorString();
        reply->deleteLater();
        return QStringList();
    }

    QString buffer = reply->readAll();
    reply->deleteLater();

    return buffer.split('\n', Qt::SkipEmptyParts);


}
