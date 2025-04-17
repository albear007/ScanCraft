#include "MainWindow.hpp"
#include "MeshDisplay.hpp"
#include "PipelineController.hpp"
#include <QFileDialog>
#include <QScrollBar>

// Main GUI Window: Contains the GUI elements and other logic and controls.
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), meshDisplay(new MeshDisplay(this)),
      pipeline(new PhotogrammetryPipeline(this)),
      meshLoader(new MeshLoader(this)),
      dockPipelineController(new PipelineController(this)),
      dockLog(new QDockWidget(tr("Log"), this)),
      openAction(new QAction(tr("&Open Mesh"), this)),
      processAction(new QAction(tr("&Process Images"), this)),
      setWorkspaceAction(new QAction(tr("&Set Workspace"), this)) {

  setupMenus();
  setupLog();
  setupPipelineController();

  statusBar();

  this->setCentralWidget(meshDisplay);
}

void MainWindow::setupPipelineController() {
  this->addDockWidget(Qt::LeftDockWidgetArea, dockPipelineController);
}
void MainWindow::setupLog() {
  this->addDockWidget(Qt::BottomDockWidgetArea, dockLog);
  dockLog->setWidget(logBox = new QPlainTextEdit(this));
  logBox->setReadOnly(true);
  logBox->setPlainText("Log: std::ccout for colmap, other logs will be here.");
  connect(this, &MainWindow::logMessage, this, &MainWindow::appendLog);
  this->logMessage("Welcome to ScanCraft!");
  this->logMessage("ScanCraft is a photogrammetry software.");
  this->logMessage("Please select a mesh file to get started.");
  this->logMessage(dockPipelineController->getOptions().toString());
}

void MainWindow::setupMenus() {
  fileMenu = menuBar()->addMenu(tr("&File"));
  setupOpenAction();
  fileMenu->addAction(openAction);
  setupProcessAction();
  fileMenu->addAction(processAction);
  setupSetWorkspaceAction();
  fileMenu->addAction(setWorkspaceAction);
}

void MainWindow::setupOpenAction() {
  connect(openAction, &QAction::triggered, this, [this]() {
    // Open a file dialog to let the user select a mesh file.
    QString fileName = QFileDialog::getOpenFileName(
        this, tr("Open Mesh File"), QString(),
        tr("Mesh Files (*.stl *.ply);;All Files (*)"));

    // If a valid file was selected, load it into the mesh display.
    if (!fileName.isEmpty()) {
      vtkAlgorithmOutput *mesh = meshLoader->loadSTL(fileName);
      if (mesh != nullptr) {
        meshDisplay->displayMesh(mesh);
        logBox->appendPlainText("Loaded mesh: " + fileName);
      } else {
        logBox->appendPlainText("Failed to load mesh: " + fileName);
      }
    }
  });
}

void MainWindow::setupProcessAction() {
  connect(processAction, &QAction::triggered, pipeline,
          &PhotogrammetryPipeline::processImages);
}

void MainWindow::setupSetWorkspaceAction() {
  connect(setWorkspaceAction, &QAction::triggered, this, [this]() {
    // Open a dialog to let the user select a directory for the workspace.
    QString workspacePath = QFileDialog::getExistingDirectory(
        this, tr("Select Workspace Directory"), QString(),
        QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);

    // If a valid path was selected, call setWorkspace on the pipeline.
    if (!workspacePath.isEmpty()) {
      pipeline->setWorkspacePath(workspacePath);
      logBox->appendPlainText("Workspace set to: " + workspacePath);
    }
  });
}
void MainWindow::appendLog(const QString &message) {
  logBox->appendPlainText(message);
}
// void MainWindow::createDocks() {
//   dockImageProcessing = new QDockWidget(tr("Image Processing"), this);
//   dockSystemControl = new QDockWidget(tr("System Control"), this);
//   addDockWidget(Qt::LeftDockWidgetArea, dockImageProcessing);
//   addDockWidget(Qt::RightDockWidgetArea, dockSystemControl);
// }
