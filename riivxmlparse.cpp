//LICENSE INFO

/* Special thanks to:
 *   The Riivolution Team - http://rvlution.net/riiv/Patch_Format
 *
 * This program only accepts valid syntactically valid XML files.
 * The Riivolution XML files can be checked at the following website:
 *   http://www.w3schools.com/dom/dom_validate.asp
 */

#include "riivxmlparse.h"

#include <QtCore/QFile>

#include <iostream>
#include <fstream>

const QString
  riivxmlparse::TAG_choice      ("choice"),
  riivxmlparse::TAG_file        ("file"),
  riivxmlparse::TAG_folder      ("folder"),
  riivxmlparse::TAG_id          ("id"),         // Implemented (developer, disc, game, version)
  riivxmlparse::TAG_macro       ("macro"),
  riivxmlparse::TAG_memory      ("memory"),
  riivxmlparse::TAG_option      ("option"),
  riivxmlparse::TAG_options     ("options"),    // Nothing to parse: not needed
  riivxmlparse::TAG_patch       ("patch"),
  riivxmlparse::TAG_region      ("region"),
  riivxmlparse::TAG_savegame    ("savegame"),
  riivxmlparse::TAG_section     ("section"),
  riivxmlparse::TAG_wiidisc     ("wiidisc");    // Implemented (root, version)

const QString
  riivxmlparse::ATTR_align      ("allign"),
  riivxmlparse::ATTR_clone      ("clone"),
  riivxmlparse::ATTR_create     ("create"),
  riivxmlparse::ATTR_default    ("default"),
  riivxmlparse::ATTR_developer  ("developer"),  // Implemented (id)
  riivxmlparse::ATTR_disc       ("disc"),       // Implemented (id)
  riivxmlparse::ATTR_external   ("external"),
  riivxmlparse::ATTR_game       ("game"),       // Implemented (id)
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
  riivxmlparse::ATTR_root       ("root"),       // Implemented (wiidisc)
  riivxmlparse::ATTR_search     ("search"),
  riivxmlparse::ATTR_type       ("type"),
  riivxmlparse::ATTR_valuefile  ("valuefile"),
  riivxmlparse::ATTR_value      ("value"),
  riivxmlparse::ATTR_version    ("version");    // Implemented (wiidisc, id)


riivxmlparse::riivxmlparse() {
  /* Root of the wiidisc should default to / */
  riivinfo.root = "/";
  
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
    //return false;
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
      /*std::cout << spc.toStdString() << "Attributes: " << std::endl;
      QDomNamedNodeMap attr = traverser.attributes();
      for(int i = 0; i < attr.length(); i++) {
        std::cout << spc.toStdString() << "| ATTRIBUTE: " << attr.item(i).nodeName().toStdString() << std::endl;
        std::cout << spc.toStdString() << "| VALUE: " << attr.item(i).nodeValue().toStdString() << std::endl;
      }*/

      /* Parse the options using another function */
      if(traverser.nodeName() == TAG_options) {
        parse_options(traverser);
        /* Prevent looping through the options to save a tiny bit of time */
        /* If theres a sibling move to it, otherwise move up */
        if(!traverser.nextSibling().isNull()) {
          traverser = traverser.nextSibling();
        }
        else {
          moveToParent = true;
        }
        continue;
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

void riivxmlparse::parseTag(const QDomNode & currentNode) {
  //std::cout << "\n\nTESTING: FIRST CHILD'S NODE NAME: " << currentNode.firstChild().nodeName().toStdString() << std::endl;
  QDomNamedNodeMap attr = currentNode.attributes();

  const QString temp = currentNode.nodeName();
  
  if(temp == TAG_choice) {
  }
  else if(temp == TAG_file) {
  }
  else if(temp == TAG_folder) {
  }
  else if(temp == TAG_id) {
    parse_id(attr);
  }
  else if(temp == TAG_macro) {
    parse_macro(attr);
  }
  else if(temp == TAG_memory) {
  }
  else if(temp == TAG_option) {
  }
  else if(temp == TAG_options) {
    /* A pretty useless tag; nothing to parse */
  }
  else if(temp == TAG_patch) {
  }
  else if(temp == TAG_region) {
  }
  else if(temp == TAG_savegame) {
  }
  else if(temp == TAG_section) {
  }
  else if(temp == TAG_wiidisc) {
    parse_wiidisc(attr);
  }
  else {
    /* Unknown tag */
  }
}

void riivxmlparse::parse_options(const QDomNode & node) {
  std::cout << "OPTION NODE!" << std::endl;
}

void riivxmlparse::parse_macro(const QDomNamedNodeMap & attr) {
  //OPTION_macro temp;
  for(int i = 0; i < attr.length(); i++) {
    if(attr.item(i).nodeName() == ATTR_id) {
    }
  }
}

void riivxmlparse::parse_id(const QDomNamedNodeMap & attr) {
  for(int i = 0; i < attr.length(); i++) {
    if(attr.item(i).nodeName() == ATTR_game) {
      riivinfo.game_id = attr.item(i).nodeValue();
    }
    else if(attr.item(i).nodeName() == ATTR_developer) {
      riivinfo.game_dev = attr.item(i).nodeValue();
    }
    else if(attr.item(i).nodeName() == ATTR_disc) {
      riivinfo.game_disc = attr.item(i).nodeValue();
    }
    else if(attr.item(i).nodeName() == ATTR_version) {
      riivinfo.game_ver = attr.item(i).nodeValue();
    }
  }
}

void riivxmlparse::parse_wiidisc(const QDomNamedNodeMap & attr) {
  for(int i = 0; i < attr.length(); i++) {
    if(attr.item(i).nodeName() == ATTR_version) {
      riivinfo.version = attr.item(i).nodeValue();
    }
    else if(attr.item(i).nodeName() == ATTR_root) {
      riivinfo.root = attr.item(i).nodeValue();
    }
  }
}

