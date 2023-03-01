#include "graphics.h"

#include <iostream>

Graphics::Graphics(QWidget *parent)
    : QOpenGLWidget(parent),
      VBO(QOpenGLBuffer::VertexBuffer),
      EBO(QOpenGLBuffer::IndexBuffer) {
  m_scale.setX(1.0);
  m_scale.setY(1.0);
  m_scale.setZ(1.0);
  m_vertex_color.setRgb(255, 255, 255);
}

Graphics::~Graphics() {}

void Graphics::initializeGL() {
  initializeOpenGLFunctions();
  glEnable(GL_DEPTH_TEST);

  m_shader.addShaderFromSourceCode(QOpenGLShader::Vertex,
                                   "attribute vec4 position;\n"
                                   "varying vec4 fragColor;\n"
                                   "uniform float pointSize;\n"
                                   "uniform vec4 u_Color;\n"
                                   "uniform mat4 u_MVP;\n"

                                   "void main(void) {\n"
                                   "    gl_Position =  u_MVP * position;\n"
                                   "    gl_PointSize = pointSize;\n"
                                   "    fragColor = u_Color;\n"
                                   "}");

  m_shader.addShaderFromSourceCode(QOpenGLShader::Fragment,
                                   "varying vec4 fragColor;\n"

                                   "void main(void) {\n"
                                   "    gl_FragColor = fragColor;\n"
                                   "}");
}

void Graphics::resizeGL(int width, int height) {
  m_projection.setToIdentity();
  double ratio = this->width() / this->height();
  m_projection.perspective(45.0f, ratio, 0.01f, 5000.0f);
  //  m_projection.ortho(-ratio, ratio, -1.0, 1.0, 0.01f, 1000.0f);
}

void Graphics::paintGL() {
  glClearColor(chosen_back_.redF(), chosen_back_.greenF(), chosen_back_.blueF(),
               chosen_back_.alphaF());
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  if (m_obj) {
    m_shader.bind();
    VAO.bind();
    VBO.bind();
    EBO.bind();

    m_shader.setAttributeBuffer(0, GL_FLOAT, 0, 3, 3 * sizeof(GLfloat));
    m_shader.enableAttributeArray(0);

    m_model.setToIdentity();
    m_model.rotate(m_rotate.x(), 1.0, 0.0, 0.0);
    m_model.rotate(m_rotate.y(), 0.0, 1.0, 0.0);
    m_model.rotate(m_rotate.z(), 0.0, 0.0, 1.0);
    m_model.translate(m_translate);
    m_model.scale(m_scale);

    m_shader.setUniformValue("u_Color", m_vertex_color.redF(),
                             m_vertex_color.greenF(), m_vertex_color.blueF(),
                             1.0);
    m_shader.setUniformValue("u_MVP", m_projection * m_normalaze * m_model);

    if (m_edge) {
      glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
      glDrawElements(GL_TRIANGLES, 3 * m_obj->f_count, GL_UNSIGNED_INT,
                     nullptr);
    }
    if (m_vertex) {
      glDrawArrays(GL_POINTS, 0, 3U * (m_obj->v_count + 1U));
    }

    m_shader.disableAttributeArray(0);
    EBO.release();
    VBO.release();
    VAO.release();
  }
}

void Graphics::OBJParser(const char *path) {
  if (m_obj) {
    VBO.destroy();
    EBO.destroy();
    VAO.destroy();

    free(m_obj->vertexes);
    free(m_obj->faces);
    m_obj->v_count = 0U;
    m_obj->f_count = 0U;

    free(m_obj);
  }

  m_obj = Parser(path);

  m_normalaze.setToIdentity();
  m_normalaze.translate(
      -1.0 * (m_obj->XYZ[0][0] + (m_obj->XYZ[1][0] - m_obj->XYZ[0][0]) / 2.0),
      -1.0 * (m_obj->XYZ[0][1] + (m_obj->XYZ[1][1] - m_obj->XYZ[0][1]) / 2.0),
      -1.0 * m_obj->XYZ[1][2]);

  float ScaleX = this->width() / (m_obj->XYZ[1][0] - m_obj->XYZ[0][0]);
  float ScaleY = this->height() / (m_obj->XYZ[1][1] - m_obj->XYZ[0][1]);

  if (ScaleX > 1) {
    ScaleX = 1.0f;
  }
  if (ScaleY > 1) {
    ScaleY = 1.0f;
  }

  m_normalaze.scale(ScaleX < ScaleY ? ScaleX : ScaleY);

  m_shader.link();
  m_shader.bind();

  VAO.create();
  VAO.bind();

  VBO.create();
  VBO.setUsagePattern(QOpenGLBuffer::StaticDraw);

  VBO.bind();
  VBO.allocate(m_obj->vertexes, 3U * (m_obj->v_count + 1U) * sizeof(GLfloat));

  EBO.create();
  EBO.setUsagePattern(QOpenGLBuffer::StaticDraw);

  EBO.bind();
  EBO.allocate(m_obj->faces, 3 * m_obj->f_count * sizeof(GLuint));

  VAO.release();
  VBO.release();
  EBO.release();
}

void Graphics::ChangeBackColor(QColor color) {
  chosen_back_ = color;
  update();
}

void Graphics::ChangeVertexColor(QColor color) {
  m_vertex_color = color;
  update();
}

void Graphics::TranslateX(double value) {
  m_translate.setX(value);
  update();
}

void Graphics::TranslateY(double value) {
  m_translate.setY(value);
  update();
}

void Graphics::TranslateZ(double value) {
  m_translate.setZ(value);
  update();
}

void Graphics::RotateX(double value) {
  m_rotate.setX(value);
  update();
}

void Graphics::RotateY(double value) {
  m_rotate.setY(value);
  update();
}

void Graphics::RotateZ(double value) {
  m_rotate.setZ(value);
  update();
}

void Graphics::Scale(double value) {
  m_scale.setX(value);
  m_scale.setY(value);
  m_scale.setZ(value);
  update();
}

void Graphics::ToggleEdge(bool flag) {
  m_edge = flag;
  update();
}

void Graphics::ToggleVertex(bool flag) {
  m_vertex = flag;
  update();
}
