#ifndef RIIVTODOLPH_H
#define RIIVTODOLPH_H

#include <QtCore/QString>

class riivtodolph {
public:
  /* Constructors */
  riivtodolph();
  
  /* File and directory info functions */
  int setFile_riiv(const QString &);
  int setFile_iso(const QString &);
  int setDir_output(const QString &);
  int setDir_config(const QString &);
  int setDir_wit(const QString &);
  int setValueSize(const QString &);
  QString getFile_riiv();
  QString getFile_iso();
  QString getFile_wit();
  QString getDir_output();
  QString getDir_config();
  QString getValueSize();
  
  /* Parsing functions */
  
private:
  /* Operating system */
  bool windows;
  
  /* File and directory info */
  int check(const QString &, int);
  int displayErrors(int);
  QString file_wit;
  QString file_riiv;
  QString file_iso;
  QString dir_output;
  QString dir_config;
  
  /* Memory patch size */
  int bytes;
};

#endif