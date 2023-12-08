#ifndef FILEREADER_H
#define FILEREADER_H

#include <QThread>
#include <QTextStream>
#include <QFile>

class FileReader : public QThread {
  Q_OBJECT
  public:
  explicit FileReader(QObject *parent = nullptr);
  explicit FileReader(const QString& filePath, QObject *parent = nullptr);
  ~FileReader();

  bool setFilePath(const QString &filepath);
  QString getFilePath();

  private:
  QFile m_file;

  protected:
  void run() override;

  signals:
  void lineRead(const QByteArray data);
  void readFinished();

  void fileError(QString errorMessage);
};

#endif // FILEREADER_H
