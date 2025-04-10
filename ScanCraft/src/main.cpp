
#include "MainWindow.hpp"
#include <QApplication>
#include <QStyle>
#include <QVTKOpenGLNativeWidget.h>
#include <qsurfaceformat.h>

auto main(int argc, char **argv) -> int {

  QSurfaceFormat::setDefaultFormat(QVTKOpenGLNativeWidget::defaultFormat());

  QApplication app(argc, argv);
  QApplication::setStyle("Fusion");

  MainWindow mainWindow;
  mainWindow.showMaximized();

  return QApplication::exec();
}
