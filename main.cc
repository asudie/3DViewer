#include <QApplication>

#include "controller.h"

int main(int argc, char *argv[]) {
  QApplication app(argc, argv);

  Controller window;

  window.show();
  return app.exec();
}
