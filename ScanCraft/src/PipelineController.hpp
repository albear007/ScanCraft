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

public slots:
  void onRunButtonClicked();

private:
  ReconstructionOptions reconOpts;

  QSpinBox *randomSeedBox;
  QCheckBox *logToStderrCheck;
  QSpinBox *logLevelBox;
  QLineEdit *projectPathEdit;
  QLineEdit *workspacePathEdit;
  QLineEdit *imagePathEdit;
  QLineEdit *maskPathEdit;
  QLineEdit *vocabTreePathEdit;
  QComboBox *dataTypeBox;
  QComboBox *qualityBox;
  QLineEdit *cameraModelEdit;
  QCheckBox *singleCameraCheck;
  QCheckBox *singleCameraPerFolderCheck;
  QLineEdit *cameraParamsEdit;
  QCheckBox *extractionCheck;
  QCheckBox *matchingCheck;
  QCheckBox *sparseCheck;
  QCheckBox *denseCheck;
  QComboBox *mesherBox;
  QSpinBox *numThreadsBox;
  QCheckBox *useGPUCheck;
  QSpinBox *gpuIndexBox;
  QPushButton *runButton;

  void logChange(const QString &label, const QString &value);
  void logChange(const QString &label, int value);
  void logChange(const QString &label, bool value);
};
