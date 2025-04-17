#pragma once

#include "ReconstructionOptions.hpp"
#include <QCheckBox>
#include <QComboBox>
#include <QLineEdit>
#include <QPushButton>
#include <QSpinBox>
#include <QWidget>

class PipelineController : public QWidget {
  Q_OBJECT
public:
  explicit PipelineController(QWidget *parent = nullptr);
  ~PipelineController() override;
  PipelineController(const PipelineController &) = delete;
  PipelineController(PipelineController &&) = delete;
  PipelineController &operator=(const PipelineController &) = delete;
  PipelineController &operator=(PipelineController &&) = delete;

signals:
  // Signal to indicate that the user has pressed the "Run" button.
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
  [[nodiscard]] ReconstructionOptions getOptions() const;
};
