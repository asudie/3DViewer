#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <QColorDialog>
#include <QFileDialog>
#include <QMainWindow>

#include "./ui_View.h"
#include "graphics.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class View;
}
QT_END_NAMESPACE

class Controller : public QMainWindow {
  Q_OBJECT

 public:
  Controller(QWidget *parent = nullptr);
  ~Controller();

 private slots:
  void on_btn_open_file_clicked();
  void on_btn_background_color_clicked();

  void on_position_x_valueChanged(double arg1);
  void on_position_y_valueChanged(double arg1);
  void on_position_z_valueChanged(double arg1);
  void on_change_size_valueChanged(double arg1);
  void on_rotate_x_valueChanged(int value);
  void on_rotate_y_valueChanged(int value);
  void on_rotate_z_valueChanged(int value);
  void on_cb_edge_on_toggled(bool checked);

  void on_cb_vertex_on_toggled(bool checked);

  void on_btn_vertex_color_clicked();

 private:
  Ui::View *ui;
};
#endif  // CONTROLLER_H
