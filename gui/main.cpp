#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include "imageinfo.h"

ImageInfo Obj1;
int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);
    QQmlApplicationEngine engine;

    qmlRegisterType<ImageInfo>("imageInfo", 1, 0,"ImageInfo");

    ImageInfo imageInfo;

    engine.rootContext()->setContextProperty("_imageInfo", &imageInfo);

    QObject::connect(
        &engine,
        &QQmlApplicationEngine::objectCreationFailed,
        &app,
        []() { QCoreApplication::exit(-1); },
        Qt::QueuedConnection);
    engine.loadFromModule("Chameleon", "Main");


    //Obj1.filepath;

    return app.exec();
}
