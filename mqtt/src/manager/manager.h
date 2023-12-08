#ifndef MANAGER_H
#define MANAGER_H

#include <QObject>
#include "../general/types.h"
#include "../repository/repository.h"

class Manager : public QObject {
  Q_OBJECT

  Q_PROPERTY (QString filePath READ getFilePath WRITE setFilePath NOTIFY filePathChanged)
  Q_PROPERTY (QString host READ getHost WRITE setHost NOTIFY hostChanged)
  Q_PROPERTY (int port READ getPort WRITE setPort NOTIFY portChanged)
  Q_PROPERTY (QString userName READ getUserName WRITE setUserName NOTIFY userNameChanged)
  Q_PROPERTY (QString password READ getPassword WRITE setPassword NOTIFY passwordChanged)
  Q_PROPERTY (QString topic READ getTopic WRITE setTopic NOTIFY topicChanged)

  Q_PROPERTY (bool isConnected READ getIsConnected NOTIFY isConnectedChanged)

  Q_PROPERTY (uint linesCount READ getLinesCount NOTIFY linesCountChanged)
  Q_PROPERTY (uint messagesCount READ getMessagesCount NOTIFY messagesCountChanged)

  public:
  Manager(QObject *parent = nullptr);
  ~Manager();

  Q_INVOKABLE void run();

  public slots:
  void onConnected();
  void onDisconnected();

  void onError(QString errorMessage);

  void onFinish(uint linesCount, uint messagesCount);

  private:
  Repository *m_pRepository;
  QThread *m_pRepositoryThread;

  connectData m_data;

  bool m_isConnected;
  uint m_linesCount;
  uint m_messagesCount;

  void setFilePath(const QString &filePath);
  QString getFilePath();

  void setHost(const QString &host);
  QString getHost();

  void setPort(const int port);
  int getPort();

  void setUserName(const QString &userName);
  QString getUserName();

  void setPassword(const QString &password);
  QString getPassword();

  void setTopic(const QString &topic);
  QString getTopic();

  void setIsConnected(bool isConnected);
  bool getIsConnected();

  void setLinesCount(const uint &linesCount);
  bool getLinesCount();

  void setMessagesCount(const uint &messagesCount);
  bool getMessagesCount();

  signals:
  void filePathChanged();
  void hostChanged();
  void portChanged();
  void userNameChanged();
  void passwordChanged();
  void topicChanged();

  void isConnectedChanged();

  void linesCountChanged();
  void messagesCountChanged();

  void error(QString errorMessage);
  void finish(int linesCount, int messagesCount);

  void repositoryRun(connectData data);


};

#endif // MANAGER_H
