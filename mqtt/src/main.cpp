#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QtQml>
#include <QDebug>

#include "manager/manager.h"
#include "logger/logger.h"


static Logger *pLogger = nullptr;

void myMessageOutput(QtMsgType type, const QMessageLogContext &context, const QString &msg) {
  pLogger->logOutput(type, context, msg);
}

int main(int argc, char *argv[]) {

  QGuiApplication app(argc, argv);

  pLogger = new Logger();

  qInstallMessageHandler(myMessageOutput);

  qInfo() << ":start:";

  QQmlApplicationEngine engine;

  Manager *pManager = new Manager(&app);

  const QUrl url(QStringLiteral("qrc:/qml/main.qml"));
  QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
      &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
          QCoreApplication::exit(-1);
      }, Qt::QueuedConnection);

  engine.rootContext()->setContextProperty("manager", pManager);

  engine.load(url);

  return app.exec();
}
