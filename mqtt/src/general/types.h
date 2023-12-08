#ifndef TYPES_H
#define TYPES_H

#include <QString>

struct connectData {
  QString host;
  int port;
  QString userName;
  QString password;
  QString topic;
  QString filePath;
};
#endif // TYPES_H
