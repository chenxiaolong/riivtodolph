#ifndef RIIVXMLPARSE_H
#define RIIVXMLPARSE_H

//Xerces-c XML parser
#include <xercesc/util/OutOfMemoryException.hpp>
#include <xercesc/dom/DOMException.hpp>

#include <xercesc/dom/DOM.hpp>
#include <xercesc/dom/DOMDocument.hpp>
#include <xercesc/dom/DOMDocumentType.hpp>
#include <xercesc/dom/DOMElement.hpp>
#include <xercesc/dom/DOMImplementation.hpp>
#include <xercesc/dom/DOMImplementationLS.hpp>
#include <xercesc/dom/DOMNodeIterator.hpp>
#include <xercesc/dom/DOMNodeList.hpp>
#include <xercesc/dom/DOMText.hpp>
#include <xercesc/parsers/XercesDOMParser.hpp>
#include <xercesc/util/XMLUni.hpp>

#include <string>

using namespace std;

class riivxmlparse {
private:
  /* Begin variables */
  char *valuesize;
  char *riivfilename;
  char *isofilename;
  char *outputdirectoryname;
  string witbin;
  
  //Tags
  XMLCh *TAG_wiidisc;
  XMLCh *TAG_id;
  XMLCh *TAG_region;
  XMLCh *TAG_options;
  XMLCh *TAG_macro;
  XMLCh *TAG_section;
  XMLCh *TAG_option;
  XMLCh *TAG_choice;
  XMLCh *TAG_patch;
  XMLCh *TAG_file;
  XMLCh *TAG_folder;
  XMLCh *TAG_savegame;
  XMLCh *TAG_memory;
  
  //Attributes
  XMLCh *ATTR_version;
  XMLCh *ATTR_path;
  XMLCh *ATTR_game;
  XMLCh *ATTR_developer;
  XMLCh *ATTR_disc;
  XMLCh *ATTR_id;
  XMLCh *ATTR_name;
  XMLCh *ATTR_default;
  XMLCh *ATTR_patch;
  XMLCh *ATTR_root;
  XMLCh *ATTR_external;
  XMLCh *ATTR_resize;
  XMLCh *ATTR_create;
  XMLCh *ATTR_offset;
  XMLCh *ATTR_length;
  XMLCh *ATTR_recursive;
  XMLCh *ATTR_clone;
  XMLCh *ATTR_value;
  XMLCh *ATTR_valuefile;
  XMLCh *ATTR_original;
  XMLCh *ATTR_ocarina;
  XMLCh *ATTR_align;
  XMLCh *ATTR_search;
  XMLCh *ATTR_type;
  
  xercesc::XercesDOMParser *XMLParser;
  /* End variables */
  
public:
  riivxmlparse(char &, char &, char &, char &, string &);
  ~riivxmlparse();
  void parseRiivXML();
};
#endif
