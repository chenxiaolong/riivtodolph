#include <QString>

#ifndef XML_FOLDER_H
#define XML_FOLDER_H

class xml_folder {
public:
  xml_folder();

  /* <folder> attributes */
  void set_disc_folder(const QString &directory);
  QString get_disc_folder();
  void set_external_folder(const QString &directory);
  QString get_external_folder();
  void set_resize(bool choice);
  bool get_resize();
  void set_create(bool choice);
  bool get_create();
  void set_recursive(bool choice);
  bool get_recursive();
  void set_length(int hex);
  int get_length();

private:
  /*** <folder> attributes ***/

  /* The folder on the disc to replace */
  QString disc_folder;

  /* The folder to replace the disc folder with */
  QString external_folder;

  /* Unused: Resize the disc file to the size of the external file */
  bool resize;

  /* Whether or not to create the file on the disc if it does not exist */
  bool create;

  /* Whether or not to look into subfolders */
  bool recursive;

  /* How much of the files to patch */
  int length;
};

#endif // XML_FOLDER_H
