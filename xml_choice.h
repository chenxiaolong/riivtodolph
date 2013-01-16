#include <QList>
#include <QString>

#ifndef XML_CHOICE_H
#define XML_CHOICE_H

class xml_choice {
public:
  xml_choice();

  /* <choice> attributes */
  void set_name(const QString &choice);
  QString get_name();

  /* <patch> */
  void add_patch_id(const QString &patch);
  QList<QString> * get_patch_ids();

private:
  /*** <choice> attributes ***/
  QString name;

  /* <patch> */
  QList<QString> *patch_ids;
};

#endif // XML_CHOICE_H
