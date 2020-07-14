#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>

#include "BLE_device.h"
#include "BLE_Valve.h"


int main(int argc, char *argv[])
{

    QGuiApplication app(argc, argv);

    BLE_device d;


    QQmlApplicationEngine engine;
    const QUrl url(QStringLiteral("qrc:/main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);

    d.startDeviceDiscovery();


        engine.rootContext()->setContextProperty("BLEdevice", &d);

    engine.load(url);



    return app.exec();
}
