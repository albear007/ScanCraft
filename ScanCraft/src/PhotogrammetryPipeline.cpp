#include "PhotogrammetryPipeline.hpp"
#include "MeshLoader.hpp"
#include <colmap/controllers/automatic_reconstruction.h>
#include <colmap/mvs/meshing.h>
#include <colmap/scene/reconstruction_io.h>
#include <limits>
#include <vtkNew.h>

std::string PhotogrammetryPipeline::createMesh(const QString &workspace) {
  if (workspace.isEmpty()) {
    qWarning("JPGLoader::load - Empty file list provided.");
    return nullptr;
  }
  // Set up the reconstruction options for now, pass in and maintain state of
  // options later as struct; also get rid of magic numbers
  options.workspace_path = workspace.toStdString();
  options.image_path = workspace.toStdString();
  options.num_threads = 2;
  options.quality = colmap::AutomaticReconstructionController::Quality::EXTREME;
  options.use_gpu = false;
  options.data_type =
      colmap::AutomaticReconstructionController::DataType::INDIVIDUAL;

  manager = std::make_unique<colmap::ReconstructionManager>();
  controller = std::make_unique<colmap::AutomaticReconstructionController>(
      options, std::shared_ptr<colmap::ReconstructionManager>(
                   manager.get(), [](colmap::ReconstructionManager *) {}));

  controller->Start();
  controller->Wait();

  colmap::mvs::DelaunayMeshingOptions meshOptions;

  // Set the meshing options, pass in and maintain state of options later as
  // struct
  meshOptions.max_proj_dist = 50;
  meshOptions.max_depth_dist = 0.001; // Default: 0.05
  meshOptions.visibility_sigma =
      std::numeric_limits<double>::min();      // Default: 3.0
  meshOptions.distance_sigma_factor = 3;       // Default: 1.0
  meshOptions.quality_regularization = 0;      // Default: 1.0
  meshOptions.max_side_length_factor = 25;     // Default: 25.0
  meshOptions.max_side_length_percentile = 95; // Default: 95.0

  std::string sparsePath = options.workspace_path + "/sparse/0";
  std::string meshOutput = sparsePath + "out.ply";

  colmap::mvs::SparseDelaunayMeshing(meshOptions, sparsePath, meshOutput);
  return meshOutput;
}