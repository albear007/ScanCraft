#include "MainWindow.hpp"
#include <QApplication>
#include <QVTKOpenGLNativeWidget.h>
#include <qsurfaceformat.h>

auto main(int argc, char **argv) -> int {

  QSurfaceFormat::setDefaultFormat(QVTKOpenGLNativeWidget::defaultFormat());

  QApplication::setStyle("Fusion");
  QApplication app(argc, argv);

  MainWindow mainWindow;
  mainWindow.showMaximized();

  return QApplication::exec();
}
