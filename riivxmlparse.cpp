//LICENSE INFO

/* Special thanks to:
 *   The Riivolution Team - http://rvlution.net/riiv/Patch_Format
 */

#include "riivxmlparse.h"

#include <QtCore/QFile>

#include <iostream>
#include <fstream>

riivxmlparse::riivxmlparse() {

}

bool riivxmlparse::readfile(const QString & filename) {
  QFile file(filename);
  if(!file.open(QFile::ReadOnly | QFile::Text)) {
    std::cerr << "Cannot read file" << filename.toStdString() << ": " << file.errorString().toStdString() << std::endl;
    return false;
  }

  QString errormsg;
  int errorline;
  int errorcolumn;

  QDomDocument doc;
  if(!doc.setContent(& file, false, & errormsg, & errorline, & errorcolumn)) {
    std::cerr << "Error: parse error at line " << errorline << ", column " << errorcolumn << ": " << errormsg.toStdString() << std::endl;
    return false;
  }

  file.close();
  QDomElement xmlroot = doc.documentElement();
  QDomNode traverser = xmlroot;

  /* traverse xml tree */
  bool moveToParent = false;

  int spaces = 0;
  
  while(true) {
    if(!moveToParent) {
      QString spc = "";
      for(int i = 0; i < spaces; i++) {
        if(i % 2 == 0) {
          spc = spc + "|";
        }
        else {
          spc = spc + " ";
        }
      }
      std::cout << spc.toStdString() << "ELEMENT: " << traverser.nodeName().toStdString() << std::endl;
      std::cout << spc.toStdString() << "Attributes: " << std::endl;
      QDomNamedNodeMap attr = traverser.attributes();
      for(int i = 0; i < attr.length(); i++) {
        std::cout << spc.toStdString() << "| ATTRIBUTE: " << attr.item(i).nodeName().toStdString() << std::endl;
      }
    }
    if(traverser.hasChildNodes() && !moveToParent) {
      traverser = traverser.firstChild();
      moveToParent = false;
      spaces += 2;
    }
    else if(!traverser.nextSibling().isNull()) {
      traverser = traverser.nextSibling();
      moveToParent = false;
    }
    else if(!traverser.parentNode().isNull()) {
      traverser = traverser.parentNode();
      moveToParent = true;
      spaces -= 2;
    }
    else {
      break;
    }
  }
}

riivxmlparse::~riivxmlparse() {
}