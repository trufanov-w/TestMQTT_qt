#include "filereader.h"
#include "qdebug.h"
#include "qurl.h"

FileReader::FileReader(QObject *parent):
    QThread(parent)
{}

FileReader::FileReader(const QString &filePath, QObject *parent):
    QThread(parent),
    m_file(filePath)
{}

FileReader::~FileReader() {
  if (m_file.isOpen()) m_file.close();
}

bool FileReader::setFilePath(const QString &filePath) {
  m_file.setFileName(QUrl(filePath).toLocalFile());
  return m_file.exists();
}

QString FileReader::getFilePath() {
  return m_file.fileName();
}

void FileReader::run() {
  if (!m_file.open(QIODevice::ReadOnly)) {
    qDebug() << m_file.errorString();
    QString error = m_file.errorString();
    emit readFinished();
    emit fileError(error);
    return;
  }

  QTextStream in(&m_file);
  while (!in.atEnd()) {
    QString line = in.readLine();
    emit lineRead(line.toUtf8());
  }

  m_file.close();
  emit readFinished();
}


