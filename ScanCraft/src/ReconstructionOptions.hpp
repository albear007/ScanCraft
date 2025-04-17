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
  QString toString() const {
    return QString("randomSeed = %1\n"
                   "logToStderr = %2\n"
                   "logLevel = %3\n"
                   "projectPath = %4\n"
                   "workspacePath = %5\n"
                   "imagePath = %6\n"
                   "maskPath = %7\n"
                   "vocabTreePath = %8\n"
                   "dataType = %9\n"
                   "quality = %10\n"
                   "cameraModel = %11\n"
                   "singleCamera = %12\n"
                   "singleCameraPerFolder = %13\n"
                   "cameraParams = %14\n"
                   "extraction = %15\n"
                   "matching = %16\n"
                   "sparse = %17\n"
                   "dense = %18\n"
                   "mesher = %19\n"
                   "numThreads = %20\n"
                   "useGPU = %21\n"
                   "gpuIndex = %22\n")
        .arg(randomSeed)
        .arg(logToStderr)
        .arg(logLevel)
        .arg(projectPath)
        .arg(workspacePath)
        .arg(imagePath)
        .arg(maskPath)
        .arg(vocabTreePath)
        .arg(static_cast<int>(colorMode))
        .arg(static_cast<int>(quality))
        .arg(cameraModel)
        .arg(singleCamera)
        .arg(singleCameraPerFolder)
        .arg(cameraParams)
        .arg(extraction)
        .arg(matching)
        .arg(sparse)
        .arg(dense)
        .arg(static_cast<int>(meshType))
        .arg(numThreads)
        .arg(useGPU)
        .arg(gpuIndex);
  }
};