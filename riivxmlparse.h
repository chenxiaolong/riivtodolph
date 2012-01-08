#ifndef RIIVXMLPARSE_H
#define RIIVXMLPARSE_H

#include <QtXml/QDomDocument>

class riivxmlparse {
private:
  /* Tags */
  static const QString
    TAG_choice,
    TAG_file,
    TAG_folder,
    TAG_id,
    TAG_macro,
    TAG_memory,
    TAG_option,
    TAG_options,
    TAG_patch,
    TAG_region,
    TAG_savegame,
    TAG_section,
    TAG_wiidisc;
  
  /* Attributes */
  static const QString
    ATTR_align,
    ATTR_clone,
    ATTR_create,
    ATTR_default,
    ATTR_developer,
    ATTR_disc,
    ATTR_external,
    ATTR_game,
    ATTR_id,
    ATTR_length,
    ATTR_name,
    ATTR_ocarina,
    ATTR_offset,
    ATTR_original,
    ATTR_patch,
    ATTR_path,
    ATTR_recursive,
    ATTR_resize,
    ATTR_root,
    ATTR_search,
    ATTR_type,
    ATTR_value,
    ATTR_valuefile,
    ATTR_version;

  
public:
  riivxmlparse();
  ~riivxmlparse();
  bool readfile(const QString & filename);
};
#endif
