#pragma once

#include "ReconstructionOptions.hpp"
#include <QCheckBox>
#include <QLineEdit>
#include <QPushButton>
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
  QLineEdit *databasePathEdit;
  QLineEdit *imagePathEdit;
  QCheckBox *siftOptionCheck;
  QPushButton *runButton;
};