//LICENSE INFO

/* Special thanks to:
 *   The Riivolution Team - http://rvlution.net/riiv/Patch_Format
 */

#include "riivxmlparse.h"

#include <QtCore/QFile>

#include <iostream>
#include <fstream>

const QString
  riivxmlparse::TAG_choice      ("choice"),
  riivxmlparse::TAG_file        ("file"),
  riivxmlparse::TAG_folder      ("folder"),
  riivxmlparse::TAG_id          ("id"),
  riivxmlparse::TAG_macro       ("macro"),
  riivxmlparse::TAG_memory      ("memory"),
  riivxmlparse::TAG_option      ("option"),
  riivxmlparse::TAG_options     ("options"),
  riivxmlparse::TAG_patch       ("patch"),
  riivxmlparse::TAG_region      ("region"),
  riivxmlparse::TAG_savegame    ("savegame"),
  riivxmlparse::TAG_section     ("section"),
  riivxmlparse::TAG_wiidisc     ("wiidisc");

const QString
  riivxmlparse::ATTR_align      ("allign"),
  riivxmlparse::ATTR_clone      ("clone"),
  riivxmlparse::ATTR_create     ("create"),
  riivxmlparse::ATTR_default    ("default"),
  riivxmlparse::ATTR_developer  ("developer"),
  riivxmlparse::ATTR_disc       ("disc"),
  riivxmlparse::ATTR_external   ("external"),
  riivxmlparse::ATTR_game       ("game"),
  riivxmlparse::ATTR_id         ("id"),
  riivxmlparse::ATTR_length     ("length"),
  riivxmlparse::ATTR_name       ("id"),
  riivxmlparse::ATTR_ocarina    ("ocarina"),
  riivxmlparse::ATTR_offset     ("offset"),
  riivxmlparse::ATTR_original   ("original"),
  riivxmlparse::ATTR_patch      ("patch"),
  riivxmlparse::ATTR_path       ("path"),
  riivxmlparse::ATTR_recursive  ("recursive"),
  riivxmlparse::ATTR_resize     ("resize"),
  riivxmlparse::ATTR_root       ("root"),
  riivxmlparse::ATTR_search     ("search"),
  riivxmlparse::ATTR_type       ("type"),
  riivxmlparse::ATTR_valuefile  ("valuefile"),
  riivxmlparse::ATTR_value      ("value"),
  riivxmlparse::ATTR_version    ("version");


riivxmlparse::riivxmlparse() {
  //(const QString)riivxmlparse::TAG_wiidisc = "wiidisc";
  
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
      if(traverser.nodeName() == TAG_wiidisc) {
        std::cout << "This is a wiidisc node" << std::endl;
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