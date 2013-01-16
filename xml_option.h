#include "xml_choice.h"
#include <QList>
#include <QString>

#ifndef XML_OPTION_H
#define XML_OPTION_H

class xml_option {
public:
  xml_option();

  /* <option> attributes */
  void set_id(const QString &option);
  QString get_id();
  void set_name(const QString &option);
  QString get_option();
  void set_default(int value);
  int get_default();

  /* <choice> */
  void add_choice(xml_choice *choice);
  QList<xml_choice *> * get_choice();

private:
  /*** <option> attributes ***/

  /* I'm confused */
  QString id;

  /* Option name */
  QString name;

  /* Default (0 = disabled) */
  int default_choice;

  /*** <choice> ***/
  QList<xml_choice *> *choices;
};

#endif // XML_OPTION_H
