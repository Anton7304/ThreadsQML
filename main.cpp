#include <QApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include "parser.h"

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QApplication app(argc, argv);

    QQmlApplicationEngine engine;
    qmlRegisterType<Parser>("ru.test.parser", 1, 0, "Parser");
    engine.load(QUrl(QLatin1String("qrc:/main.qml")));
    engine.thread()->setObjectName("MainThread");

    if (engine.rootObjects().isEmpty())
        return -1;

    return app.exec();
}
