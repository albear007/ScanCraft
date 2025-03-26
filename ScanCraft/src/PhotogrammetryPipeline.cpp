#include "PhotogrammetryPipeline.hpp"
#include <colmap/controllers/automatic_reconstruction.h>
#include <colmap/mvs/meshing.h>
#include <colmap/scene/reconstruction_io.h>

#include <limits>
#include <vtkNew.h>
#include <vtkPLYReader.h>

vtkAlgorithmOutput *
PhotogrammetryPipeline::createMesh(const QString &workspace) {
  if (workspace.isEmpty()) {
    qWarning("JPGLoader::load - Empty file list provided.");
    return nullptr;
  }
  options.workspace_path = "/Users/albert.t/Downloads/test";
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

  // Reduce projection distance threshold → tighter spatial merging of nearby
  // points
  meshOptions.max_proj_dist = 50; // Default: 20.0

  // Stricter depth agreement between points and cells
  meshOptions.max_depth_dist = 0.001; // Default: 0.05

  // Lower visibility sigma to reduce reliance on uncertain (single-view) points
  meshOptions.visibility_sigma =
      std::numeric_limits<double>::min(); // Default: 3.0

  // Increase smoothness constraint
  meshOptions.distance_sigma_factor = 3;  // Default: 1.0
  meshOptions.quality_regularization = 0; // Default: 1.0

  // Stronger filtering of bad triangles (too long edges)
  meshOptions.max_side_length_factor = 20;     // Default: 25.0
  meshOptions.max_side_length_percentile = 70; // Default: 95.0
  std::string sparsePath = options.workspace_path + "/sparse/0";
  std::string meshOutput = sparsePath + "/meshed-poisson.ply";
  std::string meshOutput1 = sparsePath + "/meshed-poisson12.ply";

  colmap::Reconstruction reconstruction;
  reconstruction.ReadBinary(sparsePath);

  colmap::ExportPLY(reconstruction, meshOutput);
  colmap::mvs::SparseDelaunayMeshing(meshOptions, sparsePath, meshOutput1);

  reader = vtkSmartPointer<vtkPLYReader>::New();
  reader->SetFileName(meshOutput1.c_str());
  reader->Update();

  return reader->GetOutputPort();
}