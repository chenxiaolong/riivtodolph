#include <QString>

#ifndef XML_FILE_H
#define XML_FILE_H

class xml_file {
public:
  xml_file();

  /* <file> attributes */
  void set_disc_file(const QString &file);
  QString get_disc_file();
  void set_external_file(const QString &file);
  QString get_external_file();
  void set_resize(bool choice);
  bool get_resize();
  void set_create(bool choice);
  bool get_create();
  void set_offset(int hex);
  int get_offset();
  void set_length(int hex);
  int get_length();

private:
  /*** <file> attributes ***/

  /* The file on disc to replace */
  QString disc_file;

  /* The file to replace the disc file with */
  QString external_file;

  /* Unused: Resize the disc file to the size of the external file */
  bool resize;

  /* Whether or not to create the file on the disc if it does not exist */
  bool create;

  /* Offset of the disc to begin replacement */
  int offset;

  /* How much of the file to patch */
  int length;
};

#endif // XML_FILE_H
