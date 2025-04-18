#pragma once
#include "ReconstructionOptions.hpp"
#include <QObject>
#include <QProcess>

class PhotogrammetryPipeline : public QObject {
  Q_OBJECT
public:
  explicit PhotogrammetryPipeline(QObject *parent = nullptr);

signals:
  /* forwarded to MainWindow for display */
  void logMessage(const QString &text);

public slots:
  /* connected to PipelineController::runReconstruction */
  void runReconstruction(const ReconstructionOptions &opts);

private:
  void startProcess(const QStringList &args);
  static QStringList toColmapArgs(const ReconstructionOptions &o);
};