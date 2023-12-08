#include <QtTest>
#include <QDir>
#include "../../../mqtt/src/repository/filereader.h"

class FileReaderTest : public QObject
{
  Q_OBJECT

  private slots:
  void testFilePathSetting();
};

void FileReaderTest::testFilePathSetting() {
  FileReader fileReader;

  QString path = QDir().currentPath()+"/not_existing_file.txt";
  QVERIFY(!fileReader.setFilePath("file://" + path));

  path = QDir().currentPath()+"/existing_file.txt";
  QVERIFY(fileReader.setFilePath("file://" + path));
}

QTEST_APPLESS_MAIN(FileReaderTest)

#include "tst_filereadertest.moc"
