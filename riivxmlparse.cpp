//LICENSE INFO

/* Special thanks to:
 *   Greg Ippolito - http://www.yolinux.com/TUTORIALS/XML-Xerces-C.html
 *   Steve Litt - http://www.troubleshooters.com/tpromag/200103/codexercises.htm#_domwalkerjava
 *   The Riivolution Team - http://rvlution.net/riiv/Patch_Format
 */
#include "riivxmlparse.h"
#include <iostream>
#include <fstream>

using namespace xercesc;
using namespace std;

riivxmlparse::riivxmlparse(char &a, char &b, char &c, char &d, string &e) {
  valuesize = &a;
  riivfilename = &b;
  isofilename = &c;
  outputdirectoryname = &d;
  witbin = e;
  
  //Perform a few checks on the Riivolution XML file
  
  
  //Initialize xerces libraries
  try {
    XMLPlatformUtils::Initialize();
  }
  catch(XMLException &error) {
    fprintf(stderr, "Failed to initialize Xerces-c:\n  %s", XMLString::transcode(error.getMessage()));
  }
  
  //Tags
  TAG_wiidisc = XMLString::transcode("wiidisc");
  TAG_id = XMLString::transcode("id");
  TAG_region = XMLString::transcode("region");
  TAG_options = XMLString::transcode("options");
  TAG_macro = XMLString::transcode("macro");
  TAG_section = XMLString::transcode("section");
  TAG_option = XMLString::transcode("option");
  TAG_choice = XMLString::transcode("choice");
  TAG_patch = XMLString::transcode("patch");
  TAG_file = XMLString::transcode("file");
  TAG_folder = XMLString::transcode("folder");
  TAG_savegame = XMLString::transcode("savegame");
  TAG_memory = XMLString::transcode("memory");
  
  //Attributes
  ATTR_version = XMLString::transcode("version");
  ATTR_path = XMLString::transcode("path");
  ATTR_game = XMLString::transcode("game");
  ATTR_developer = XMLString::transcode("developer");
  ATTR_disc = XMLString::transcode("disc");
  ATTR_id = XMLString::transcode("id");
  ATTR_name = XMLString::transcode("name");
  ATTR_default = XMLString::transcode("default");
  ATTR_patch = XMLString::transcode("patch");
  ATTR_root = XMLString::transcode("root");
  ATTR_external = XMLString::transcode("external");
  ATTR_resize = XMLString::transcode("resize");
  ATTR_create = XMLString::transcode("create");
  ATTR_offset = XMLString::transcode("offset");
  ATTR_length = XMLString::transcode("length");
  ATTR_recursive = XMLString::transcode("recursive");
  ATTR_clone = XMLString::transcode("clone");
  ATTR_value = XMLString::transcode("value");
  ATTR_valuefile = XMLString::transcode("valuefile");
  ATTR_original = XMLString::transcode("original");
  ATTR_ocarina = XMLString::transcode("ocarina");
  ATTR_align = XMLString::transcode("align");
  ATTR_search = XMLString::transcode("search");
  ATTR_type = XMLString::transcode("type");
  
  //Create DOM parser
  XMLParser = new XercesDOMParser;
  

}

riivxmlparse::~riivxmlparse() {
  //Free memory
  
  //Tags
  XMLString::release(&TAG_wiidisc);
  XMLString::release(&TAG_id);
  XMLString::release(&TAG_region);
  XMLString::release(&TAG_options);
  XMLString::release(&TAG_macro);
  XMLString::release(&TAG_section);
  XMLString::release(&TAG_option);
  XMLString::release(&TAG_choice);
  XMLString::release(&TAG_patch);
  XMLString::release(&TAG_file);
  XMLString::release(&TAG_folder);
  XMLString::release(&TAG_savegame);
  XMLString::release(&TAG_memory);
  
  //Attributes
  XMLString::release(&ATTR_version);
  XMLString::release(&ATTR_path);
  XMLString::release(&ATTR_game);
  XMLString::release(&ATTR_developer);
  XMLString::release(&ATTR_disc);
  XMLString::release(&ATTR_id);
  XMLString::release(&ATTR_name);
  XMLString::release(&ATTR_default);
  XMLString::release(&ATTR_patch);
  XMLString::release(&ATTR_root);
  XMLString::release(&ATTR_external);
  XMLString::release(&ATTR_resize);
  XMLString::release(&ATTR_create);
  XMLString::release(&ATTR_offset);
  XMLString::release(&ATTR_length);
  XMLString::release(&ATTR_recursive);
  XMLString::release(&ATTR_clone);
  XMLString::release(&ATTR_value);
  XMLString::release(&ATTR_valuefile);
  XMLString::release(&ATTR_original);
  XMLString::release(&ATTR_ocarina);
  XMLString::release(&ATTR_align);
  XMLString::release(&ATTR_search);
  XMLString::release(&ATTR_type);
  
  //Terminal xerces
  delete XMLParser;
  XMLPlatformUtils::Terminate();
}

void riivxmlparse::parseRiivXML() {
  //Attempt parsing file
  try {
    XMLParser->parse(riivfilename);
  }
  //Highly doubt this will happen considering how tiny the Riivolution XML files are
  catch(OutOfMemoryException &error) {
    fprintf(stderr, "An error occured while trying to parse the Riivolution XML file:\n  Ran out of memory");
  }
  catch(XMLException &error) {
    fprintf(stderr, "An error occured while trying to parse the Riivolution XML file:\n  %s", XMLString::transcode(error.getMessage()));
  }
  catch(DOMException &error) {
    fprintf(stderr, "An error occured while trying to parse the Riivolution XML file:\n  %s", XMLString::transcode(error.getMessage()));
  }
  
  DOMDocument *xmlDoc = XMLParser->getDocument();
  //Get root element
  DOMElement *xmlRoot = xmlDoc->getDocumentElement();
  
  //check if XML file is empty
  if(!xmlRoot) {
    fprintf(stderr, "Riivolution XML file is empty!\n");
    exit(1);
  }
  
  DOMNode *traverser = xmlDoc->getDocumentElement();
  bool moveToParent = false;
  
  while(true) {
    if(!moveToParent) {
      cout << "Name: " << XMLString::transcode(traverser->getNodeName()) << endl;
      cout << "Data: " << traverser->getNodeValue() << endl;
    }
    if((traverser->hasChildNodes()) && (!moveToParent)) {
      /* <id game="???">
       *  ^^
       *   \-> Current position (id)
       * 
       *      /-> New position (region) - first child node
       *      |
       *   <region type="P"/>
       *   <region type="E"/>
       *   <region type="J"/>
       * </id>
       */
      traverser = traverser->getFirstChild();
      moveToParent = false;
    }
    else if(traverser->getNextSibling() != NULL) {
      /* <id game="???">
       *   <region type="P"/>
       *     ^^^    ^^
       *      |      \-> New position (type) - get next node
       *      \-> Current position (region)
       *   <region type="E"/>
       *   <region type="J"/>
       * </id>
       *
       * The next loop would move the current position here:
       * 
       * <id game="???">
       *   <region type="P"/>
       *            ^^
       *             \-> Current position (type)
       * 
       *      /-> New position (region) - get next node
       *      |
       *   <region type="E"/>
       *   <region type="J"/>
       * </id>
       */
      traverser = traverser->getNextSibling();
      moveToParent = false;
    }
    else if(traverser->getParentNode() != NULL) {
      /* <id game="???">
       *  ^^
       *   \->New position (id) - move to parent
       *   <region type="P"/>
       *   <region type="E"/>
       *   <retion type="J"/>
       *            ^^
       *             \-> Current position (type) - last child node
       * </id>
       * 
       * The traverser will NOT go back into the child nodes since 
       * the moveToParent variable is now set to true. The if statement
       * above that moves the traverser to the first child node requires
       * that the moveToParent variable be set to false.
       */
      traverser = traverser->getParentNode();
      moveToParent = true;
    }
    else {
      break;
    }
  }
  
  //Get child nodes for current root
  DOMNodeList *xmlChildren = xmlRoot->getChildNodes();
  //Get number of nodes to loop through them
  const XMLSize_t nodeCount = xmlChildren->getLength();
  
  for(XMLSize_t loop = 0; loop < nodeCount; loop++) {
    DOMNode *currentNode = xmlChildren->item(loop);
    if(currentNode->getNodeType() /*not NULL*/ && currentNode->getNodeType() == DOMNode::ELEMENT_NODE) {
      //Cast node as element
      DOMElement *currentElement = dynamic_cast<xercesc::DOMElement*>(currentNode);
      
      //Get disk info
      if(XMLString::equals(currentElement->getTagName(), TAG_id)) {
        cout << XMLString::transcode(currentElement->getAttribute(ATTR_game)) << endl;
      }
    }
  }
}