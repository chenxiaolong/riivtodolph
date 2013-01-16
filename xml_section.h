#include "xml_option.h"
#include <QList>
#include <QString>

#ifndef XML_SECTION_H
#define XML_SECTION_H

class xml_section {
public:
  xml_section();

  /* <section> attributes */
  void set_name(const QString &section);
  QString get_name();

  /* <option> */
  void add_option(xml_option *option);
  QList<xml_option *> * get_options();

private:
  /*** <section> attributes ***/

  /* Name */
  QString name;

  QList<xml_option *> *options;
};

#endif // XML_SECTION_H
