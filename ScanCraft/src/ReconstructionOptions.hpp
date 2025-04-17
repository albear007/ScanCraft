#pragma once
#include <QString>

struct ReconstructionOptions {
  int randomSeed = 0;
  bool logToStderr = true;
  int logLevel = 0;
  QString projectPath;
  QString workspacePath;
  QString imagePath;
  QString maskPath;
  QString vocabTreePath;
  enum class dataType { Individual, Video, Internet };
  dataType colorMode = dataType::Individual;
  enum class Quality { Low, Medium, High, Extreme };
  Quality quality = Quality::High;
  QString cameraModel;
  bool singleCamera = false;
  bool singleCameraPerFolder = false;
  QString cameraParams;
  bool extraction = false;
  bool matching = false;
  bool sparse = false;
  bool dense = false;
  enum class mesher { Poisson, Delaunay };
  mesher meshType = mesher::Poisson;
  int numThreads = -1;
  bool useGPU = true;
  int gpuIndex = -1;
};