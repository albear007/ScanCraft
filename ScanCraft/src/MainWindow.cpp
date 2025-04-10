#include "MainWindow.hpp"
#include "MeshDisplay.hpp"
#include "MeshLoader.hpp"
#include "PhotogrammetryPipeline.hpp"
#include <QFileDialog>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), meshDisplay(new MeshDisplay(this)) {

  setupMenus();

  statusBar();

  this->setCentralWidget(meshDisplay);
}

void MainWindow::setupMenus() {
  fileMenu = menuBar()->addMenu(tr("&File"));
  setupOpenAction();
  fileMenu->addAction(openAction);
  setupProcessAction();
  fileMenu->addAction(processAction);
}

void MainWindow::setupOpenAction() {
  openAction = new QAction(tr("&Open Mesh"), this);
  connect(openAction, &QAction::triggered, this, &MainWindow::openMesh);
}

void MainWindow::setupProcessAction() {
  processAction = new QAction(tr("&Process Images"), this);
  connect(processAction, &QAction::triggered, this, &MainWindow::processImages);
}

void MainWindow::processImages() {
  pipeline = std::make_unique<PhotogrammetryPipeline>();
  QString workspace = QFileDialog::getExistingDirectory(
      this, tr("Select Directory"),
      "", // Optional: default path
      QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);
  QString meshPath = QString::fromStdString(pipeline->createMesh(workspace));
  meshDisplay->displayMesh(MeshLoader().loadPLY(meshPath));
}

void MainWindow::openMesh() {
  QString fileName = QFileDialog::getOpenFileName(
      this, tr("Open File"), "", tr("Mesh Files (*.stl *.ply)"));
  if (fileName.endsWith(".stl", Qt::CaseInsensitive)) {
    meshDisplay->displayMesh(MeshLoader().loadSTL(fileName));
  } else if (fileName.endsWith(".ply", Qt::CaseInsensitive)) {
    meshDisplay->displayMesh(MeshLoader().loadPLY(fileName));
  } else {
    QMessageBox::warning(this, tr("Unsupported File"),
                         tr("The selected file format is not supported."));
  }
}

// void MainWindow::createDocks() {
//   dockImageProcessing = new QDockWidget(tr("Image Processing"), this);
//   dockSystemControl = new QDockWidget(tr("System Control"), this);
//   addDockWidget(Qt::LeftDockWidgetArea, dockImageProcessing);
//   addDockWidget(Qt::RightDockWidgetArea, dockSystemControl);
// }
