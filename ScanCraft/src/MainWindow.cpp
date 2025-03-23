#include "MainWindow.hpp"
#include "MeshDisplay.hpp"
#include <QFileDialog>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), meshDisplay(new MeshDisplay(this)) {

  createMenus();

  statusBar();

  this->setCentralWidget(meshDisplay);
}

void MainWindow::createMenus() {
  fileMenu = menuBar()->addMenu(tr("&File"));
  setupOpenAction();
  fileMenu->addAction(openAction);
}

void MainWindow::setupOpenAction() {
  openAction = new QAction(tr("&Open"), this);
  connect(openAction, &QAction::triggered, this, &MainWindow::openSTL);
}

void MainWindow::openSTL() {
  QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"), "",
                                                  tr("STL Files (*.stl)"));

  meshDisplay->displaySTL(fileName);
}

// void MainWindow::createDocks() {
//   dockImageProcessing = new QDockWidget(tr("Image Processing"), this);
//   dockSystemControl = new QDockWidget(tr("System Control"), this);
//   addDockWidget(Qt::LeftDockWidgetArea, dockImageProcessing);
//   addDockWidget(Qt::RightDockWidgetArea, dockSystemControl);
// }
