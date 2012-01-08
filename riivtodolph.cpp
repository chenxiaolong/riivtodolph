#include "riivtodolph.h"
//#include "riivxmlparse.cpp"

#include <QtCore/QStringList>
#include <QtCore/QRegExp>
#include <QtCore/QFileInfo>
#include <QtCore/QDir>
#include <cstdlib>

/* Return values; values higher than 0 are errors */
static const int NO_ERROR = 0;
static const int NO_VALUE = -1;
static const int DEFAULT_VALUE = -2;
static const int INVALID_VALUE = -3;

/* What to check */
static const int CHK_EXIST = 32;
static const int CHK_FILE = 16;
static const int CHK_DIR = 8;
static const int CHK_READ = 4;
static const int CHK_WRITE = 2;
static const int CHK_EXEC = 1;

/* Use powers of 2 similar to Unix permissions to represent errors */
static const int PATH_NOT_EXIST = 32;
static const int PATH_IS_FILE = 16;
static const int PATH_IS_DIR = 8;
static const int PATH_NO_READ = 4;
static const int PATH_NO_WRITE = 2;
static const int PATH_NO_EXEC = 1;


riivtodolph::riivtodolph() {
  bytes = 4; // Default to dword
  file_riiv = "";
  file_iso = "";
  file_wit = "";
  dir_output = "";
  dir_config = "";

#ifdef Q_WS_WIN
  windows = true;
#else
  windows = false;
#endif
}

int riivtodolph::check(const QString &path, int checkthis) {
  if(path == "") {
    return NO_VALUE;
  }
  
  QFileInfo temp(path);
  int result = 0;
  int check = checkthis;

  /* Check if path exists */
  if(check >= CHK_EXIST) {
    check -= CHK_EXIST;
    if(!temp.exists()) {
      result += PATH_NOT_EXIST;
    }
  }
  /* Check if path is a file */
  if(check >= CHK_FILE) {
    check -= CHK_FILE;
    if(!temp.isFile()) {
      result += PATH_IS_DIR;
    }
  }
  /* Check if path is a directory */
  if(check >= CHK_DIR) {
    check -= CHK_DIR;
    if(!temp.isDir()) {
      result += PATH_IS_FILE;
    }
  }
  /* Check if path is readable */
  if(check >= CHK_READ) {
    check -= CHK_READ;
    if(!temp.isReadable()) {
      result += PATH_NO_READ;
    }
  }
  /* Check if path is writable */
  if(check >= CHK_WRITE) {
    check -= CHK_WRITE;
    if(!temp.isWritable()) {
      result += PATH_NO_WRITE;
    }
  }
  /* Check if path is executable */
  if(check >= CHK_EXEC) {
    check -= CHK_EXEC;
    if(!temp.isExecutable()) {
      result += PATH_NO_EXEC;
    }
  }

  return result;
}

int riivtodolph::displayErrors (int errors) {
  // Umm...hi?
}

QString riivtodolph::getValueSize() {
  switch(bytes) {
    case 4:
      return "dword";
    case 2:
      return "word";
    case 1:
      return "byte";
    default:
      return "Invalid";
  }
}

QString riivtodolph::getFile_riiv() {
  return file_riiv;
}

QString riivtodolph::getFile_iso() {
  return file_iso;
}

QString riivtodolph::getFile_wit() {
  return file_wit;
}

QString riivtodolph::getDir_output() {
  return dir_output;
}

int riivtodolph::setValueSize(const QString & size) {
  /* No value specified */
  if(size == "") {
    return DEFAULT_VALUE;
  }
  else if(size == "byte") {
    bytes = 1;
  }
  else if(size == "word") {
    bytes = 2;
  }
  else if(size == "dword") {
    bytes = 4;
  }
  /* Invalid value */
  else {
    return INVALID_VALUE;
  }
  /* Okay */
  return NO_ERROR;
}

int riivtodolph::setFile_riiv(const QString & filename) {
  /* No value specified */
  if(filename == "") {
    return NO_VALUE;
  }
  int errors = check(filename, CHK_EXIST + CHK_FILE + CHK_READ);
  if(errors > 0) {
    displayErrors(errors);
    return INVALID_VALUE;
  }
  
  /* Okay */
  file_riiv = filename;
  return NO_ERROR;
}

int riivtodolph::setFile_iso(const QString & filename) {
  /* No value specified */
  if(filename == "") {
    return NO_VALUE;
  }
  int errors = check(filename, CHK_EXIST + CHK_FILE + CHK_READ);
  if(errors > 0) {
    displayErrors(errors);
    return INVALID_VALUE;
  }
  
  /* Okay */
  file_iso = filename;
  return NO_ERROR;
}

int riivtodolph::setDir_output(const QString & directory) {
  /* If output directory isn't provided, set it to the current directory */
  if(directory == "") {
    /* Get current directory */
    QString cwd = QDir::currentPath();
    dir_output = cwd;
    /* Default value used */
    return DEFAULT_VALUE;
    /* CWD should already exist, so we can return now */
  }
  
  /* Check if provided directory exists */
  int errors = check(directory, CHK_EXIST);
  /* If not, then create it */
  if(errors == PATH_NOT_EXIST) {
    QDir newpath(directory);
    newpath.mkdir(directory);
  }
  /* If it already exists, perform the other checks */
  else {
    errors = check(directory, CHK_DIR + CHK_READ + CHK_WRITE);
    if(errors > 0) {
      displayErrors(errors);
      return INVALID_VALUE;
    }
  }
  
  /* Okay */
  dir_output = directory;
  return NO_ERROR;
}

int riivtodolph::setDir_config(const QString & directory) {
  /* Config directory is required if memory patches are used */
  return NO_ERROR;
}

int riivtodolph::setDir_wit(const QString & directory) {
  QString wit;
  QString witname;
  if(windows) {
    witname = "wit.exe";
  }
  else {
    witname = "wit";
  }

  /* If the path to wit wasn't specified, search for it in PATH */
  if(directory == "") {
    QString path = getenv("PATH");

    /* The stupid PATH delimiter is different between Linux/Mac/Unix and Windows */
    QRegExp delim(";|:");
    QStringList paths = path.split(delim, QString::SkipEmptyParts);
    bool found = false;

    /* Search for wit in PATH */
    for(int i = 0; i < paths.length(); i++) {
      QString temp = paths[i];

      /* Check if directory ends in a '/' */
      if(temp.at(temp.length() - 1) == '/') {
        wit = temp + witname;
      }
      else {
        wit = temp + "/" + witname;
      }

      /* Check if file exists */
      int errors = check(wit, CHK_EXIST);
      if(errors == 0) { // No error: found wit
        found = true;
        break;
      }
    }

    int errors = 0;
    if(!found) {
      errors += PATH_NOT_EXIST;
    }
    else {
      /* Perform some checks on the wit binary */
      errors = check(directory, CHK_FILE + CHK_EXEC);
    }

    if(errors > 0) {
      displayErrors(errors);
      return INVALID_VALUE;
    }

    /* Okay */
    file_wit = wit;
    /* Return "default value" if wit exists and is executable */
    return DEFAULT_VALUE;
  }
  /* If directory was given */
  else {
    /* Check if directory ends with '/' */
    if(directory.at(directory.length() - 1) == '/') {
      wit = directory + witname;
    }
    else {
      wit = directory + "/" + witname;
    }

    int errors = check(wit, CHK_EXIST + CHK_FILE + CHK_EXEC);
    if(errors > 0) {
      displayErrors(errors);
      return INVALID_VALUE;
    }

    /* Okay */
    file_wit = wit;
    return NO_ERROR;
  }
}