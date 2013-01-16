#include <QString>

#ifndef RIIVTODOLPH_H
#define RIIVTODOLPH_H

class riivtodolph {
public:
  riivtodolph();

  void set_dir_config(const QString &directory);
  void set_dir_output(const QString &directory);
  void set_file_iso(const QString &filename);
  void set_file_riiv(const QString &filename);
  void set_file_wit(const QString &filename);
  void set_value_size(const QString &size);

  QString get_dir_config() const;
  QString get_dir_output() const;
  QString get_file_iso() const;
  QString get_file_riiv() const;
  QString get_file_wit() const;
  QString get_value_size() const;

private:
  QString dir_config;
  QString dir_output;
  QString file_iso;
  QString file_riiv;
  QString file_wit;

  int bytes;
};

#endif // RIIVTODOLPH_H
