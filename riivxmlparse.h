#include "riivtodolph.h"
#include "xml_section.h"
#include "xml_wiidisc.h"
#include <QtXml/QDomNode>

#ifndef RIIVXMLPARSE_H
#define RIIVXMLPARSE_H

class riivxmlparse {
public:
  riivxmlparse(const riivtodolph *info);
  bool parse();
  QString pretty_print();

private:
  bool process_tag(const QDomNode &current);
  bool process_attrs_wiidisc(const QDomNode &current);
  bool process_children_wiidisc(const QDomNode &current);
  bool process_attrs_id(const QDomNode &current);
  bool process_children_id(const QDomNode &current);
  bool process_attrs_region(const QDomNode &current);
  bool process_children_options(const QDomNode &current);
  bool process_attrs_section(const QDomNode &current, xml_section *section);
  bool process_children_section(const QDomNode &current, xml_section *section);
  bool process_attrs_option(const QDomNode &current, xml_option *option);
  bool process_children_option(const QDomNode &current, xml_option *option);
  bool process_attrs_choice(const QDomNode &current, xml_choice *choice);
  bool process_children_choice(const QDomNode &current, xml_choice *choice);
  bool process_attrs_patch_id(const QDomNode &current, xml_choice *choice);

  riivtodolph *information;
  xml_wiidisc *xmltree;
};

#endif // RIIVXMLPARSE_H
