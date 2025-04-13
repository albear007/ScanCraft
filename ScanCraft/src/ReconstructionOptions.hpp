#pragma once
#include <QString>

struct ReconstructionOptions {
  int randomSeed = 0;
  int logLevel = 2;
  bool logToStderr = false;
  QString projectPath;
  QString workspacePath;
  QString databasePath;
  QString imagePath;
  bool singleCamera = false;
  bool singleCameraPerFolder = false;
  enum class ColorMode { Individual, Video, Internet };
  ColorMode colorMode = ColorMode::Individual;
  enum class Quality { Low, Medium, High, Extreme };
  Quality quality = Quality::Medium;
  enum class MeshType { Poisson, Delaunay };
  MeshType meshType = MeshType::Poisson;

  ReconstructionOptions() = default;
  ReconstructionOptions(int randomSeed, int logLevel, int logtoStdErr,
                        const QString &projectPath, const QString &dbPath,
                        const QString &imgPath, bool useSift, int maxFeatures,
                        float peakThresh, bool globalBA, bool refineIntrinsics)
      : randomSeed(0), logLevel(2), logToStderr(false), projectPath(""),
        workspacePath(""), databasePath(dbPath), imagePath(imgPath),
        singleCamera(useSift), singleCameraPerFolder(useSift),
        colorMode(ColorMode::Individual), quality(Quality::Medium),
        meshType(MeshType::Poisson) {}
};