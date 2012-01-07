#ifndef RIIVTODOLPH_H
#define RIIVTODOLPH_H

#include <QtCore/QString>

class riivtodolph {
public:
  /* Constructors */
  riivtodolph();
  
  /* File and directory info functions */
  int setFile_riiv(QString);
  int setFile_iso(QString);
  int setDir_output(QString);
  int setDir_config(QString);
  int setDir_wit(QString);
  int setValueSize(QString);
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
  int check(QString, int);
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