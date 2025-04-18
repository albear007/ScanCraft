#include "PhotogrammetryPipeline.hpp"
#include <QFileInfo>

PhotogrammetryPipeline::PhotogrammetryPipeline(QObject *parent)
    : QObject(parent) {}

/*------------------------------------------------------------*/
void PhotogrammetryPipeline::runReconstruction(const ReconstructionOptions &o) {
  emit logMessage("▶  Building COLMAP command…");
  startProcess(toColmapArgs(o));
}

/*------------------------------------------------------------*/
void PhotogrammetryPipeline::startProcess(const QStringList &args) {
  const QString exe = QStringLiteral(COLMAP_EXECUTABLE);
  if (!QFileInfo::exists(exe)) {
    emit logMessage("❌  COLMAP executable not found: " + exe);
    return;
  }

  auto *p = new QProcess(this);
  p->setProgram(exe);
  p->setArguments(args);
  p->setProcessChannelMode(QProcess::SeparateChannels);

  connect(p, &QProcess::readyReadStandardOutput, this, [this, p]() {
    emit logMessage(
        QString::fromLocal8Bit(p->readAllStandardOutput()).trimmed());
  });
  connect(p, &QProcess::readyReadStandardError, this, [this, p]() {
    emit logMessage(
        "[stderr] " +
        QString::fromLocal8Bit(p->readAllStandardError()).trimmed());
  });
  connect(p, &QProcess::finished, this,
          [this, p](int c, QProcess::ExitStatus s) {
            emit logMessage(
                QString("[COLMAP finished] exit %1 (%2)")
                    .arg(c)
                    .arg(s == QProcess::NormalExit ? "normal" : "crashed"));
            p->deleteLater();
          });
  connect(p, &QProcess::errorOccurred, this,
          [this, p](QProcess::ProcessError e) {
            emit logMessage(QString("[COLMAP error] %1").arg(int(e)));
            p->deleteLater();
          });

  emit logMessage("▶  Starting COLMAP …");
  emit logMessage("▶  Executing: " + exe + " " + args.join(' '));
  p->start();
}

/*------------------------------------------------------------*/
QStringList
PhotogrammetryPipeline::toColmapArgs(const ReconstructionOptions &o) {
  QStringList args;
  args << "automatic_reconstructor";
  // Helper lambdas
  auto addPath = [&args](const char *flag, const QString &value) {
    if (!value.isEmpty())
      args << flag << value;
  };

  auto addBool = [&args](const char *flag, bool value) {
    args << flag << (value ? "1" : "0");
  };

  auto addInt = [&args](const char *flag, int value) {
    args << flag << QString::number(value);
  };

  // Paths
  addPath("--project_path", o.projectPath);
  addPath("--workspace_path", o.workspacePath);
  addPath("--image_path", o.imagePath);
  addPath("--mask_path", o.maskPath);
  addPath("--vocab_tree_path", o.vocabTreePath);

  // Basic options
  addInt("--random_seed", o.randomSeed);
  addBool("--log_to_stderr", o.logToStderr);
  addInt("--log_level", o.logLevel);

  // Enums
  static const char *typeStr[] = {"individual", "video", "internet"};
  static const char *qualStr[] = {"low", "medium", "high", "extreme"};
  static const char *meshStr[] = {"poisson", "delaunay"};

  args << "--data_type" << typeStr[int(o.type)];
  args << "--quality" << qualStr[int(o.quality)];
  args << "--mesher" << meshStr[int(o.meshType)];

  // Camera
  addBool("--single_camera", o.singleCamera);
  addBool("--single_camera_per_folder", o.singleCameraPerFolder);
  addPath("--camera_model", o.cameraModel);
  addPath("--camera_params", o.cameraParams);

  // Pipeline steps
  addBool("--extraction", o.extraction);
  addBool("--matching", o.matching);
  addBool("--sparse", o.sparse);
  addBool("--dense", o.dense);

  // Performance
  addInt("--num_threads", o.numThreads);
  addBool("--use_gpu", o.useGPU);
  addInt("--gpu_index", o.gpuIndex);

  return args;
}