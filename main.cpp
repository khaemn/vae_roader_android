#include <QGuiApplication>
#include <QQuickView>
#include <QQmlEngine>

//#include <fdeep/fdeep.hpp>

#include <opencv2/highgui/highgui.hpp>
#include "desktopvideoproducer.h"

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    DesktopVideoProducer::registerQmlType();

    QGuiApplication app(argc, argv);

    QQuickView viewer;
    viewer.setResizeMode(QQuickView::SizeRootObjectToView);
    viewer.setSource(QUrl(QStringLiteral("qrc:///main.qml")));
    viewer.showFullScreen();

    return app.exec();
}
