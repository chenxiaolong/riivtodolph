#include <QtCore/QString>

#include <unistd.h>
#include <cstdio>

#include "riivtodolph.cpp"

int main(int argc, char **argv) {
  QString valuesize; // byte, word, or dword
  QString fileRiiv;  // Riivolution XML file
  QString fileIso;   // ISO rip of Wii game
  QString dirOutput; // Dolphin config file and ISO image output directory
  QString dirConfig; // Path to Dolphin GameConfig directory
  QString dirWit;    // path to Wit tools
  
  int argument = 0;

  //BEGIN: Parsing arguments
  while((argument = getopt(argc, argv, "r:i:o:c:w:s:")) != -1) {
    switch(argument) {
      case 'r':
	fileRiiv = optarg;
	break;
      case 'i':
	fileIso = optarg;
	break;
      case 'o':
	dirOutput = optarg;
	break;
      case 'c':
	dirConfig = optarg;
	break;
      case 'w':
	dirWit = optarg;
	break;
      case 's':
	valuesize = optarg;
	break;
    }
  }
  //END: Parsing arguments
  
  riivtodolph *parser = new riivtodolph();
  fprintf(stdout, "Set value: %i\n", parser->setValueSize(valuesize));
  fprintf(stdout, "Set riiv: %i\n", parser->setFile_riiv(fileRiiv));
  fprintf(stdout, "Set iso: %i\n", parser->setFile_iso(fileIso));
  fprintf(stdout, "Set output: %i\n", parser->setDir_output(dirOutput));
  
  fprintf(stdout, "Set wit: %i\n", parser->setDir_wit(dirWit));

  fprintf(stdout, "Value: %s\n", parser->getValueSize().data());
  parser->getFile_riiv();
  fprintf(stdout, "HI!!!\n");
  fprintf(stdout, "Riiv: %s\n", parser->getFile_riiv().data());
  fprintf(stdout, "ISO: %s\n", parser->getFile_iso().data());
  fprintf(stdout, "Output: %s\n", parser->getDir_output().data());
  fprintf(stdout, "Config: %s\n", dirConfig.data());
  fprintf(stdout, "Wit: %s\n", parser->getFile_wit().data());
}
