#pragma once
#include "MeshDisplay.hpp"
#include "MeshLoader.hpp"
#include "PhotogrammetryPipeline.hpp"
#include <QAction>
#include <QDockWidget>
#include <QMainWindow>
#include <QMenu>
#include <QMenuBar>
#include <Qplaintextedit.h>

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
  void logMessage(const QString &message);
public slots:
  void appendLog(const QString &message);

protected:
private:
  // Menus
  QMenu *fileMenu = nullptr;

  // // Docks
  QDockWidget *dockImageProcessing = nullptr;
  // QDockWidget *dockSystemControl = nullptr;
  QDockWidget *dockLog = nullptr;
  QDockWidget *dockPipelineController = nullptr;

  // // Toolbar
  // QToolBar *toolBar = nullptr;

  // //  User defined
  MeshDisplay *meshDisplay = nullptr;
  PhotogrammetryPipeline *pipeline = nullptr;
  MeshLoader *meshLoader = nullptr;

  // Log box
  QPlainTextEdit *logBox = nullptr;

  // Actions
  QAction *openAction = nullptr;
  QAction *processAction = nullptr;
  QAction *setWorkspaceAction = nullptr;

  // // Initlize UI elements through these helpers.
  void setupMenus();
  void setupLog();
  void setupImageProcessing();
  void setupProcessAction();
  void setupSetWorkspaceAction();
  void setupOpenAction();
  void setupPipelineController();
  // void createDocks();
  // void createToolBar();
  // void createStatusBar();
  // void createCentralWidget();
};