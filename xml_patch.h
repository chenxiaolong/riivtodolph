#include "xml_file.h"
#include "xml_folder.h"
#include "xml_memory.h"
#include "xml_savegame.h"
#include <QList>
#include <QString>

#ifndef XML_PATCH_H
#define XML_PATCH_H

class xml_patch {
public:
  xml_patch();

  /* <patch> attributes */
  void set_id(const QString &patch);
  QString get_id();
  void set_root(const QString &directory);
  QString get_root();

  /* <file */
  void add_file_patch(xml_file *file);
  QList<xml_file *> * get_file_patches();

  /* <folder> */
  void add_folder_patch(xml_folder *directory);
  QList<xml_folder *> * get_folder_patches();

  /* <memory> */
  void add_memory_patch(xml_memory *patch);
  QList<xml_memory *> * get_memory_patches();

  /* <savegame> */
  void add_savegame_patch(xml_savegame *savegame);
  QList<xml_savegame *> * get_savegame_patches();


private:
  /*** <patch> attributes ***/

  /* Patch ID */
  QString id;

  /* Relative root for all paths in the subnodes */
  QString root;

  /*** <file> ***/
  QList<xml_file *> *file_patches;

  /*** <folder> ***/
  QList<xml_folder *> *folder_patches;

  /*** <savegame> ***/
  QList<xml_savegame *> *savegame_patches;

  /*** <memory> ***/
  QList<xml_memory *> *memory_patches;
};

#endif // XML_PATCH_H
