#ifndef RIIVTODOLPH_H
#define RIIVTODOLPH_H

#include <sys/stat.h>
#include <string>

class riivtodolph {
public:
  /* Constructors */
  riivtodolph();
  
  /* File and directory info functions */
  int setFile_riiv(std::string);
  int setFile_iso(std::string);
  int setDir_output(std::string);
  int setDir_config(std::string);
  int setDir_wit(std::string);
  int setValueSize(std::string);
  std::string getFile_riiv();
  std::string getFile_iso();
  std::string getFile_wit();
  std::string getDir_output();
  std::string getDir_config();
  std::string getValueSize();
  
  /* Parsing functions */
  
private:
  /* File and directory info */
  std::string file_wit;
  std::string file_riiv;
  std::string file_iso;
  std::string dir_output;
  std::string dir_config;
  struct stat info;
  
  /* Memory patch size */
  int bytes;
};

#endif