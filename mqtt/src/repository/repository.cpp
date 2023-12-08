#include "repository.h"

Repository::Repository(QObject *parent):
    QObject(parent)
{
  qRegisterMetaType<connectData>("connectData");

  m_reader = new FileReader(this);
  connect(m_reader, &FileReader::lineRead, this, &Repository::onLineRead);
  connect(m_reader, &FileReader::readFinished, this, &Repository::onReadFinished);
  connect(m_reader, &FileReader::fileError, this, &Repository::onFileError);

  m_messageSentCount = m_lineReadCount = 0;

  qInfo() << "Repository constructed";
}

Repository::~Repository() {
  if (m_mqttClient->state() == QMqttClient::Connected) {
    m_mqttClient->disconnectFromHost();
  }
  m_reader->exit();
  m_reader->deleteLater();
  qInfo() << "Repository destructed";
}

void Repository::run(const connectData &data) {
  qInfo() << "Repository RUN";
  m_messageSentCount = m_lineReadCount = 0;
  m_mqttClient->setHostname(data.host);
  m_mqttClient->setPort(data.port);
  m_mqttClient->setUsername(data.userName);
  m_mqttClient->setPassword(data.password);

  if (!m_reader->setFilePath(data.filePath)) {
    m_errorMessage = "No such file or directory";
    emit error(m_errorMessage);
    return;
  }

  m_topic.setName(data.topic);

  m_mqttClient->connectToHost();
  m_processSent = true;
}

void Repository::onThreadStarted() {
  m_mqttClient = new QMqttClient(this);

  connect(m_mqttClient, &QMqttClient::connected, this, &Repository::onConnected);
  connect(m_mqttClient, &QMqttClient::disconnected, this, &Repository::onDisconnected);
}

void Repository::onLineRead(const QByteArray &data) {
  m_lineReadCount++;
  if (m_mqttClient->publish(m_topic, data, 0, true) >= 0) {
    m_messageSentCount++;
  }
}

void Repository::onReadFinished() {
  qInfo() << "Repository ReadFinish";
  m_processRead = false;
  emit finish(m_lineReadCount, m_messageSentCount);
  m_mqttClient->disconnectFromHost();
}

void Repository::onFileError(const QString &errorMessage) {
  qWarning() << "Repository error -" << errorMessage;
  m_processRead = false;
  m_errorMessage = errorMessage;
  m_mqttClient->disconnectFromHost();
}

void Repository::onConnected() {
  qInfo() << "Repository Connected";
  if (!m_processSent) return;
  m_processRead = true;
  m_reader->start();
  emit connected();
}

void Repository::onDisconnected() {
  qInfo() << "Repository Disconnected";
  m_processSent = false;
  if (m_reader->isRunning()) {
    m_reader->terminate();
    m_processRead = false;
  }
  emit disconnected();
}
