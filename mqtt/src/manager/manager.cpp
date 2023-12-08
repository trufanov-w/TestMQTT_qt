#include "manager.h"
#include <QDebug>

Manager::Manager(QObject *parent):
    QObject(parent)
{
  m_isConnected = false;
  m_messagesCount = 0;
  m_linesCount = 0;

  m_pRepositoryThread = new QThread(this);
  m_pRepository = new Repository();
  m_pRepository->moveToThread(m_pRepositoryThread);
  QObject::connect(m_pRepositoryThread, &QThread::finished, m_pRepository, &Repository::deleteLater);
  QObject::connect(m_pRepository, &Repository::destroyed, m_pRepositoryThread, &QThread::quit);
  QObject::connect(m_pRepositoryThread, &QThread::started, m_pRepository, &Repository::onThreadStarted);
  m_pRepositoryThread->start();

  QObject::connect(this, &Manager::repositoryRun, m_pRepository, &Repository::run);

  QObject::connect(m_pRepository, &Repository::connected, this, &Manager::onConnected);
  QObject::connect(m_pRepository, &Repository::disconnected, this, &Manager::onDisconnected);
  QObject::connect(m_pRepository, &Repository::finish, this, &Manager::onFinish);
  QObject::connect(m_pRepository, &Repository::error, this, &Manager::onError);

  setPort(1883);

  qInfo() << "Manager constructed";
}

Manager::~Manager() {
  m_pRepositoryThread->quit();
  m_pRepositoryThread->wait();
  delete m_pRepository;
  qInfo() << "Manager destructed";
}

void Manager::run() {
  qInfo() << "Manager run";
  emit repositoryRun(m_data);
}

void Manager::onConnected() {
  setIsConnected(true);
}

void Manager::onDisconnected() {
  setIsConnected(false);
}

void Manager::onError(QString errorMessage) {
  qWarning() << "Manager error -" << errorMessage;
  emit error(errorMessage);
}

void Manager::onFinish(uint linesCount, uint messagesCount) {
  setLinesCount(linesCount);
  setMessagesCount(messagesCount);
  emit finish(linesCount, messagesCount);
  qInfo() << "Manager finish - linesCount :" << linesCount << "messagesCount :" << messagesCount;
}

void Manager::setFilePath(const QString &filePath) {
  m_data.filePath = filePath;
  emit filePathChanged();
}

QString Manager::getFilePath() {
  return m_data.filePath;
}

void Manager::setHost(const QString &host) {
  m_data.host = host;
  emit hostChanged();
}

QString Manager::getHost() {
  return m_data.host;
}

void Manager::setPort(const int port) {
  m_data.port = port;
  emit portChanged();
}

int Manager::getPort() {
  return m_data.port;
}

void Manager::setUserName(const QString &userName) {
  m_data.userName = userName;
  emit userNameChanged();
}

QString Manager::getUserName() {
  return m_data.userName;
}

void Manager::setPassword(const QString &password) {
  m_data.password = password;
  emit passwordChanged();
}

QString Manager::getPassword() {
  return m_data.password;
}

void Manager::setTopic(const QString &topic) {
  m_data.topic = topic;
  emit topicChanged();
}

QString Manager::getTopic() {
  return m_data.topic;
}

void Manager::setIsConnected(bool isConnected) {
  m_isConnected = isConnected;
  emit isConnectedChanged();
}

bool Manager::getIsConnected() {
  return m_isConnected;
}

void Manager::setLinesCount(const uint &linesCount) {
  m_linesCount = linesCount;
  emit linesCountChanged();
}

bool Manager::getLinesCount() {
  return m_linesCount;
}

void Manager::setMessagesCount(const uint &messagesCount) {
  m_messagesCount = messagesCount;
  emit messagesCountChanged();
}

bool Manager::getMessagesCount() {
  return m_messagesCount;
}
