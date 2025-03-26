#pragma once
#include <QString>
#include <colmap/controllers/automatic_reconstruction.h>
#include <colmap/scene/reconstruction_manager.h>
#include <memory>
#include <vtkAlgorithmOutput.h>
#include <vtkPLYReader.h>
#include <vtkSmartPointer.h>

class PhotogrammetryPipeline {
public:
  PhotogrammetryPipeline() = default;
  PhotogrammetryPipeline(const PhotogrammetryPipeline &) = delete;
  PhotogrammetryPipeline(PhotogrammetryPipeline &&) noexcept = delete;
  PhotogrammetryPipeline &operator=(const PhotogrammetryPipeline &) = delete;
  PhotogrammetryPipeline &
  operator=(PhotogrammetryPipeline &&) noexcept = delete;
  ~PhotogrammetryPipeline() = default;

  vtkAlgorithmOutput *createMesh(const QString &workspace);

private:
  colmap::AutomaticReconstructionController::Options options;

  std::unique_ptr<colmap::AutomaticReconstructionController> controller;
  std::unique_ptr<colmap::ReconstructionManager> manager;
  vtkSmartPointer<vtkPLYReader> reader;
};