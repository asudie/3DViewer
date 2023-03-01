#ifndef GRAPHICS_H
#define GRAPHICS_H

#include <QOpenGLBuffer>
#include <QOpenGLFunctions>
#include <QOpenGLShader>
#include <QOpenGLVertexArrayObject>
#include <QOpenGLWidget>
#include <QVector3D>
// #include <QVector4D>
#include <QDir>
#include <QMatrix4x4>

#ifdef __cplusplus
extern "C" {
#endif

#include "parser.h"

#ifdef __cplusplus
}
#endif

class Graphics : public QOpenGLWidget, protected QOpenGLFunctions {
  Q_OBJECT

 public:
  explicit Graphics(QWidget *parent = nullptr);
  virtual ~Graphics();

  virtual void initializeGL() override;
  virtual void resizeGL(int width, int height) override;
  virtual void paintGL() override;

  void OBJParser(const char *path);
  void ChangeBackColor(QColor color);
  void ChangeVertexColor(QColor color);
  void TranslateX(double value);
  void TranslateY(double value);
  void TranslateZ(double value);
  void RotateX(double value);
  void RotateY(double value);
  void RotateZ(double value);
  void Scale(double value);
  void ToggleEdge(bool flag);
  void ToggleVertex(bool flag);

 private:
  Model *m_obj = nullptr;
  QColor chosen_back_;
  QColor m_vertex_color;
  QVector3D m_translate;
  QVector3D m_rotate;
  QVector3D m_scale;
  bool m_edge = true;
  bool m_vertex = false;

  QOpenGLShaderProgram m_shader;

  QOpenGLVertexArrayObject VAO;
  QOpenGLBuffer VBO, EBO;

  QMatrix4x4 m_model, m_view, m_projection, m_normalaze;
};

#endif  // GRAPHICS_H
