#include <QString>

#ifndef XML_MEMORY_H
#define XML_MEMORY_H

class xml_memory {
public:
  xml_memory();

  /* <memory> attributes */
  void set_offset(int hex);
  int get_offset();
  void set_value(const QString &hex);
  QString get_value();
  void set_valuefile(const QString &file);
  QString get_valuefile();
  void set_original(const QString &hex);
  QString get_original();

private:
  /*** <memory> attributes ***/

  /* Memory offset */
  int offset;

  /* Hexadecimal string to write at the offset */
  QString value;

  /* Hexadecimal string stored in a file */
  QString valuefile;

  /* Unsupported by dolphin-emu: Replace only if original memory matches */
  QString original;
};

#endif // XML_MEMORY_H
