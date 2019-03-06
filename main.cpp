#include <QGuiApplication>
#include <QQuickView>
#include <QQmlEngine>

#include <iostream>
#include <complex>

#include <fdeep/fdeep.hpp>

#include <opencv2/highgui/highgui.hpp>
#include "desktopvideoproducer.h"

void fourteen ()
{
    auto func = [](auto input) { return input * input; };

    // Usage examples:
    // square of an int
    std::cout << func(10) << std::endl;

    // square of a double
    std::cout << func(2.345) << std::endl;

    // square of a complex number
    std::cout << func(std::complex<double>(3, -2)) << std::endl;
}

int main(int argc, char *argv[])
{
    fourteen();

    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    DesktopVideoProducer::registerQmlType();
    //auto model = fdeep::load_model("qrc:/micro_model_yolike_roader.json");

    QGuiApplication app(argc, argv);

    QQmlEngine engine;
    QQuickView viewer(&engine, nullptr);
    viewer.setResizeMode(QQuickView::SizeRootObjectToView);
    viewer.setSource(QUrl(QStringLiteral("qrc:///main.qml")));
    viewer.showFullScreen();

    return app.exec();
}
