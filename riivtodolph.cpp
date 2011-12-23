#include "riivtodolph.h"
#include "riivxmlparse.cpp"
#include <iostream>
#include <fstream>
#include <string.h>
#include <stdio.h>
#include <sys/stat.h>
#include <cstdlib>
#include <string>
#include <vector>
#include <sstream>

#ifdef MINGW32
#include <getopt.h>
#define off64_t long
#include <direct.h>
#endif

using namespace std;

int main(int argc, char* argv[]) {
  
  char *valuesize = NULL; //byte, word, or dword
  char *riivfilename = NULL; //Riivolution XML file
  char *isofilename = NULL; //ISO rip of Wii game
  char *outputdirectoryname = NULL; //Dolphin config file and ISO image output directory
  char *witpath = NULL; //path to Wit tools
  
  int argument = 0;

  /* Begin parsing arguments */
  while((argument = getopt(argc, argv, "r:i:o:w:s:")) != -1) {
    switch(argument) {
      case 'r':
	riivfilename = optarg;
	break;
      case 'i':
	isofilename = optarg;
	break;
      case 'o':
	outputdirectoryname = optarg;
	break;
      case 'w':
	witpath = optarg;
	break;
      case 's':
	valuesize = optarg;
	break;
    }
  }
  /* End parsing arguments */
  
  /* Begin checking arguments */
  
  //Default to dword for valuesize
  if(valuesize == NULL) {
    valuesize = (char*)"dword";
  }
  //Exit if Riivolution XML file isn't provided
  if(riivfilename == NULL) {
    fprintf(stderr, "No Riivolution XML file was specified\n");
    return 1;
  }
  //Exit if ISO game image isn't provided
  if(isofilename == NULL) {
    fprintf(stderr, "No Wii game ISO image was specified\n");
    return 1;
  }
  //If output directory isn't provided, set it to the current directory
  if(outputdirectoryname == NULL) {
    char *buf;
    long size;
#ifdef _PC_PATH_MAX
    size = pathconf(".", _PC_PATH_MAX); //Allocate memory for buf with the maximum path size
#else
    size = 999999;
#endif
    if ((buf = (char *)malloc((size_t)size)) != NULL) {
      outputdirectoryname = getcwd(buf, (size_t)size);
    }
  }
  
  struct stat check;
  
  //Data type can only be dword, word, or byte
  if(!(strcasecmp(valuesize, "dword") == 0 || strcasecmp(valuesize, "word") == 0 || strcasecmp(valuesize, "byte") == 0)) {
    fprintf(stderr, "Invalid argument for -s: %s\n", valuesize);
    return 1;
  }
  
  //Check if Riivolution XML file exists
  if(stat(riivfilename, &check) != 0) {
    fprintf(stderr, "The Riivolution XML file does not exist:\n  %s\n", riivfilename);
    return 1;
  }
  else {
    if(access(riivfilename, R_OK) == -1) {
      fprintf(stderr, "The Riivolution XML file is not readable:\n  %s\n", riivfilename);
      return 1;
    }
  }
  
  //Check if Wii ISO exists
  if(stat(isofilename, &check) != 0) {
    fprintf(stderr, "The Wii game ISO image does not exist:\n  %s\n", isofilename);
    return 1;
  }
  else {
    if(access(isofilename, R_OK) == -1) {
      fprintf(stderr, "The Wii game ISO image is not readable:\n  %s\n", isofilename);
      return 1;
    }
  }
  
  //Check is output directory exists
  if(stat(outputdirectoryname, &check) == 0) { //If path exists
    if(!S_ISDIR(check.st_mode)) { //Check if path is a directory
      fprintf(stderr, "The output path chosen exists, but it is not a directory:\n  %s\n", outputdirectoryname);
      return 1;
    }
  }
  else {
    fprintf(stderr, "The output directory does not exist. Creating it...\n  %s\n", outputdirectoryname);
#ifdef MINGW32
    mkdir(outputdirectoryname);
#else
    mkdir(outputdirectoryname, S_IRUSR | S_IWUSR | S_IXUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH); //Create directory with 755 privileges (read, write, and execute)
#endif
  }
  
  //Find wit
  string witbin;
  if(witpath == NULL) { //If user did not specify path
    //Check if wit exists in the system's PATH
    string path = getenv("PATH"); //get PATH environment variable
    stringstream tempss(path); //allow string to be treated as a stream
    vector<string> paths; //Dynamic array to hold the paths
    string temppath;
    char delim = ':';
    while(getline(tempss, temppath, delim)) {
      paths.push_back(temppath);
    }
    for(int i = 0; i < paths.size(); i++) {
      temppath = paths[i];
      temppath.append("/wit");
      if(access(temppath.c_str(), X_OK) == 0) { //Test access to file as well as the executable bit
	witbin = temppath;
	break;
      }
    }
  }
  else {
    string temppath;
    if(witpath[strlen(witpath) - 1] != '/') { //If the last character of the path is not a slash
      temppath = witpath;
      temppath.append("/wit");
    }
    else {
      temppath = witpath;
      temppath.append("wit");
    }
    if(access(temppath.c_str(), X_OK) == 0) { //Test access to file as well as the executable bit
      witbin = temppath;
    }
    else {
      fprintf(stderr, "wit was not found in the directory specified:\n  %s\n", witpath);
      return 1;
    }
  }
  
  /* End checking arguments */
  
  /* Begin outputting summary */
  cout << "Data type: " << valuesize << endl
       << "Riivolution XML file: " << riivfilename << endl
       << "ISO file: " << isofilename << endl
       << "Output directory: " << outputdirectoryname << endl
       << "Path to wit: " << witbin << endl;
  /* End outputting summary */
  
  /* Begin Riivolution XML parsing */
  riivxmlparse *parseThis = new riivxmlparse(*valuesize, *riivfilename, *isofilename, *outputdirectoryname, witbin);
  parseThis->parseRiivXML();
  /* End Riivolution XML parsing */
}

void riivtodolph::usage() {
  cout << "Blah" << endl
       << "Line 2 " << endl;
}
