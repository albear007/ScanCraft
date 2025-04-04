#pragma once
#include "MeshDisplay.hpp"
#include "PhotogrammetryPipeline.hpp"
#include <QAction>
#include <QDockWidget>
#include <QMainWindow>
#include <QMenu>
#include <QMenuBar>
#include <QToolBar>
#include <memory>
#include <qaction.h>

class MainWindow : public QMainWindow {
  Q_OBJECT
public:
  explicit MainWindow(QWidget *parent = nullptr);
  MainWindow(const MainWindow &) = delete;
  MainWindow &operator=(const MainWindow &) = delete;
  MainWindow(MainWindow &&) = delete;
  MainWindow &operator=(MainWindow &&) = delete;
  ~MainWindow() override = default;

signals:
public slots:

protected:
private:
  // Menus
  QMenu *fileMenu = nullptr;

  // // Docks
  // QDockWidget *dockImageProcessing = nullptr;
  // QDockWidget *dockSystemControl = nullptr;

  // // Toolbar
  // QToolBar *toolBar = nullptr;

  // //  User defined mesh plot
  // MeshDisplay *meshDisplay = nullptr;

  // Actions
  QAction *openAction = nullptr;
  MeshDisplay *meshDisplay = nullptr;
  QAction *processAction = nullptr;
  std::unique_ptr<PhotogrammetryPipeline> pipeline;

  // // Initlize UI elements through these helpers.
  void createMenus();
  void openMesh();
  void setupProcessAction();
  void processImages();
  // void createDocks();
  // void createToolBar();
  // void createStatusBar();
  // void createCentralWidget();
  void setupOpenAction();
};