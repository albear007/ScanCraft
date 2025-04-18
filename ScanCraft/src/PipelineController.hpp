#pragma once

#include "ReconstructionOptions.hpp"
#include <QCheckBox>
#include <QComboBox>
#include <QDockWidget>
#include <QLineEdit>
#include <QPushButton>
#include <QSpinBox>

class PipelineController : public QDockWidget {
  Q_OBJECT

public:
  explicit PipelineController(QWidget *parent = nullptr);
  ~PipelineController() override;
  PipelineController(const PipelineController &) = delete;
  PipelineController(PipelineController &&) = delete;
  PipelineController &operator=(const PipelineController &) = delete;
  PipelineController &operator=(PipelineController &&) = delete;

  [[nodiscard]] ReconstructionOptions getOptions() const;

signals:
  void runReconstruction();
  void logMessage(const QString &message);

public slots:
  void onRunButtonClicked();
  void setWorkspacePath(const QString &workspacePath);

private:
  ReconstructionOptions reconOpts;

  QSpinBox *randomSeedField;
  QCheckBox *logToStdErrCheck;
  QSpinBox *logLevelField;
  QLineEdit *projectPathField;
  QLineEdit *workspacePathField;
  QLineEdit *imagePathField;
  QLineEdit *maskPathField;
  QLineEdit *vocabTreePathField;
  QComboBox *dataTypeMenu;
  QComboBox *qualityMenu;
  QLineEdit *cameraModelField;
  QCheckBox *singleCameraCheck;
  QCheckBox *singleCameraPerFolderCheck;
  QLineEdit *cameraParamsField;
  QCheckBox *extractionCheck;
  QCheckBox *matchingCheck;
  QCheckBox *sparseCheck;
  QCheckBox *denseCheck;
  QComboBox *mesherMenu;
  QSpinBox *numThreadsField;
  QCheckBox *useGPUCheck;
  QSpinBox *gpuIndexField;
  QPushButton *runButton;

  void logChange(const QString &label, const QString &value);
  void logChange(const QString &label, int value);
  void logChange(const QString &label, bool value);
};
