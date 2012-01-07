#include "riivtodolph.h"
//#include "riivxmlparse.cpp"
#include <sys/stat.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <sstream>
#include <vector>

//#ifdef MINGW32
//#include <getopt.h>
//#define off64_t long
//#include <direct.h>
//#endif

/* int function return values
 * 0 : Okay, no errors
 * 1 : No value specified
 * 2 : Default value used
 * 3 : Invalid value
 * 4 : File/directory not found
 * 5 : File/directory not readable
 * 6 : File/directory not writable
 * 7 : File/directory not executable
 * 8 : Is a file (directory expected)
 * 9 : Is a directory (file expected)
 */

riivtodolph::riivtodolph() {
  bytes = 4; // Default to dword
  file_riiv = "";
  file_iso = "";
  file_wit = "";
  dir_output = "";
  dir_config = "";
}

std::string riivtodolph::getValueSize() {
  switch(bytes) {
    case 4:
      return (char *)"dword";
    case 2:
      return (char *)"word";
    case 1:
      return (char *)"byte";
    default:
      return (char *)"Invalid";
  }
}

std::string riivtodolph::getFile_riiv() {
  return file_riiv;
}

std::string riivtodolph::getFile_iso() {
  return file_iso;
}

std::string riivtodolph::getFile_wit() {
  return file_wit;
}

std::string riivtodolph::getDir_output() {
  return dir_output;
}

int riivtodolph::setValueSize(std::string size) {
  /* No value specified */
  if(size == "") {
    return 2;
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
    return 3;
  }
  /* Okay */
  return 0;
}

int riivtodolph::setFile_riiv(std::string filename) {
  /* No value specified */
  if(filename == "") {
    return 1;
  }
  /* File not found */
  else if(stat(filename.c_str(), &info) != 0) {
    return 4;
  }
  /* File not readable */
  else if(access(filename.c_str(), R_OK) != 0) {
    return 5;
  }
  /* Path is directory, not file */
  else if(S_ISDIR(info.st_mode)) {
    return 9;
  }
  /* Okay */
  file_riiv = filename;
  return 0;
}

int riivtodolph::setFile_iso(std::string filename) {
  /* No value specified */
  if(filename == "") {
    return 1;
  }
  /* File not found */
  else if(stat(filename.c_str(), &info) != 0) {
    return 4;
  }
  /* File not readable */
  else if(access(filename.c_str(), R_OK) != 0) {
    return 5;
  }
  /* Path is a directory, not a file */
  else if(S_ISDIR(info.st_mode)) {
    return 9;
  }
  /* Okay */
  file_iso = filename;
  return 0;
}

int riivtodolph::setDir_output(std::string directory) {
  /* If output directory isn't provided, set it to the current directory */
  if(directory == "") {
    /* Get current directory */
    int size = pathconf(".", _PC_PATH_MAX);
    char buf[size];
    getcwd(buf, size);
    dir_output = buf;
    /* Default value used */
    return 2;
    /* CWD should already exist, so we can return now */
  }
  /* Check if directory exists */
  else if(stat(directory.c_str(), &info) == 0) {
    if(!S_ISDIR(info.st_mode)) {
      /* Path is a file, not a directory */
      return 8;
    }
  }
  /* Directory does not exist */
  else {
    /* Create directory with 755 privileges */
    mkdir(directory.c_str(), S_IRUSR | S_IWUSR | S_IXUSR | // User
                             S_IRGRP |           S_IXGRP | // Group
                             S_IROTH |           S_IXOTH); // Other
                           //  Read  |  Write  | Execute
  }
  /* Check if directory is readable */
  if(access(directory.c_str(), R_OK) != 0) {
    return 5;
  }
  /* Check if directory is writable */
  else if(access(directory.c_str(), W_OK) != 0) {
    return 6;
  }
  /* Okay */
  dir_output = directory;
  return 0;
}

int riivtodolph::setDir_config(std::string directory) {
  /* Config directory is required if memory patches are used */
  return 0;
}

int riivtodolph::setDir_wit(std::string directory) {  
  /* If the path to wit wasn't specified, search for it in PATH */
  if(directory == "") {
    std::string path = getenv("PATH");
    
    bool directory = false;
    
    /* Split PATH and search in each of those directories */
    std::stringstream ss(path);
    std::string temp;
    while(std::getline(ss, temp, ':')) {
      std::string wit = "";
      /* Check if directory ends in a '/' */
      if(temp.at(temp.length() - 1) == '/') {
        wit = temp + "wit";
      }
      else {
        wit = temp + "/wit";
      }
      /* Check if file exists */
      if(stat(wit.c_str(), &info) == 0) {
        /* Check if path is a directory */
        if(S_ISDIR(info.st_mode)) {
          /* Do not return if there is a directory named 'wit' as other directories could contain a useful 'wit' binary */
          directory  = true;
          continue;
        }
        /* Check if file is executable */
        if(access(wit.c_str(), X_OK) == 0) {
          /* Set value */
          file_wit = wit;
          /* Return "default value" if wit exists and is executable */
          return 2;
        }
        /* Return "file not executable" if wit exists, but is not executable */
        return 7;
      }
    }
    if(directory) {
      return 9;
    }
    /* If while loop completes, then a wit binary was not found in PATH */
  }
  /* If directory was given */
  else {
    std::string wit;
    /* Check if directory ends with '/' */
    if(stat(wit.c_str(), &info) == 0) {
      wit = directory + "wit";
    }
    else {
      wit = directory + "/wit";
    }
    /* Check if file exists */
    if(stat(wit.c_str(), &info) == 0) {
      /* Check if path is a directory */
      if(S_ISDIR(info.st_mode)) {
        return 9;
      }
      /* Check if file is executable */
      if(access(wit.c_str(), X_OK) == 0) {
        /* Set value */
        file_wit = wit;
        /* Okay */
        return 0;
      }
      /* Return "file not executable" */
      return 7;
    }
  }
  /* At this point, the file must not exist */
  return 4;
}