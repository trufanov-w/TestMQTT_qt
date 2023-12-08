#ifndef REPOSITORY_H
#define REPOSITORY_H

#include <QObject>

#include <QtMqtt/QMqttClient>
#include <QtMqtt/QMqttMessage>
#include <QtMqtt/QMqttSubscription>

#include "filereader.h"
#include "../general/types.h"

class Repository : public QObject {
  Q_OBJECT
  public:
  Repository(QObject *parent = nullptr);
  ~Repository();

  public slots:
  void run(const connectData &data);
  void onThreadStarted();

  private:
  QMqttClient *m_mqttClient;
      QMqttTopicName m_topic;
  FileReader *m_reader;

  uint m_lineReadCount;
  uint m_messageSentCount;

  bool m_processRead;
  bool m_processSent;

  QString m_errorMessage;

  private slots:
  void onLineRead(const QByteArray &data);
  void onReadFinished();
  void onFileError(const QString &errorMessage);

  void onConnected();
  void onDisconnected();

  signals:
  void error(QString errorMessage);

  void connected();
  void disconnected();

  void finish(uint linesCount, uint messageCount);

};

#endif // REPOSITORY_H
