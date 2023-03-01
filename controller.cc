#include "controller.h"

#include <QDebug>

#include "./ui_View.h"

Controller::Controller(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::View) {
  ui->setupUi(this);
}

Controller::~Controller() { delete ui; }

void Controller::on_btn_open_file_clicked() {
    QString path = QFileDialog::getOpenFileName(this, tr("Open File"), "\\", tr("3D model(*.obj)"));
    ui->statusbar->showMessage(path);
    ui->GL_Graphics->OBJParser(path.toStdString().c_str());
}

void Controller::on_btn_background_color_clicked() {
    QColorDialog color_dialog;
    color_dialog.setWindowTitle("Background color");
    if (color_dialog.exec() == QColorDialog::Accepted) {
        ui->GL_Graphics->ChangeBackColor(color_dialog.selectedColor());
    }
}

void Controller::on_btn_vertex_color_clicked() {
    QColorDialog color_dialog;
    color_dialog.setWindowTitle("Vertex color");
    if (color_dialog.exec() == QColorDialog::Accepted) {
        ui->GL_Graphics->ChangeVertexColor(color_dialog.selectedColor());
    }
}

void Controller::on_position_x_valueChanged(double arg1) {
    ui->GL_Graphics->TranslateX(arg1);
}

void Controller::on_position_y_valueChanged(double arg1) {
    ui->GL_Graphics->TranslateY(arg1);
}

void Controller::on_position_z_valueChanged(double arg1) {
    ui->GL_Graphics->TranslateZ(arg1);
}

void Controller::on_change_size_valueChanged(double arg1) {
    ui->GL_Graphics->Scale(arg1);
}

void Controller::on_rotate_x_valueChanged(int value) {
    ui->show_rX->setText(QString::number(value));
    ui->GL_Graphics->RotateX(value);
}

void Controller::on_rotate_y_valueChanged(int value) {
    ui->show_rY->setText(QString::number(value));
    ui->GL_Graphics->RotateY(value);
}

void Controller::on_rotate_z_valueChanged(int value) {
    ui->show_rZ->setText(QString::number(value));
    ui->GL_Graphics->RotateZ(value);
}

void Controller::on_cb_edge_on_toggled(bool checked) {
    ui->GL_Graphics->ToggleEdge(checked);
}


void Controller::on_cb_vertex_on_toggled(bool checked) {
    ui->GL_Graphics->ToggleVertex(checked);
}
