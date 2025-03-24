#include "MainWindow.hpp"
#include "MeshDisplay.hpp"
#include "loaders/STLLoader.hpp"
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
  QStringList fileNames = QFileDialog::getOpenFileNames(
      this, tr("Open Files"), "",
      tr("STL Files (*.stl);;PLY Files (*.ply);;All Files (*)"));
  meshDisplay->displayMesh(STLLoader().load(fileNames));
}

// void MainWindow::createDocks() {
//   dockImageProcessing = new QDockWidget(tr("Image Processing"), this);
//   dockSystemControl = new QDockWidget(tr("System Control"), this);
//   addDockWidget(Qt::LeftDockWidgetArea, dockImageProcessing);
//   addDockWidget(Qt::RightDockWidgetArea, dockSystemControl);
// }
