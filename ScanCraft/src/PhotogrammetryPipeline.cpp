#include "PhotogrammetryPipeline.hpp"
#include <colmap/controllers/automatic_reconstruction.h>
#include <colmap/mvs/meshing.h>
#include <colmap/scene/reconstruction_io.h>

#include <vtkNew.h>
#include <vtkPLYReader.h>

vtkAlgorithmOutput *
PhotogrammetryPipeline::createMesh(const QString &workspace) {
  if (workspace.isEmpty()) {
    qWarning("JPGLoader::load - Empty file list provided.");
    return nullptr;
  }
  options.workspace_path = workspace.toStdString();
  options.image_path = workspace.toStdString();
  options.use_gpu = false;
  options.dense = false;

  manager = std::make_unique<colmap::ReconstructionManager>();

  controller = std::make_unique<colmap::AutomaticReconstructionController>(
      options, std::shared_ptr<colmap::ReconstructionManager>(
                   manager.get(), [](colmap::ReconstructionManager *) {}));

  controller->Start();
  controller->Wait();

  colmap::mvs::PoissonMeshingOptions meshOptions;
  std::string sparsePath = options.workspace_path + "/sparse/0";
  std::string meshOutput = sparsePath + "/meshed-poisson.ply";
  std::string meshOutput1 = sparsePath + "/meshed-poisson12.ply";

  colmap::Reconstruction reconstruction;
  reconstruction.ReadBinary(sparsePath);

  colmap::ExportPLY(reconstruction, meshOutput);
  colmap::mvs::SparseDelaunayMeshing(meshOptions, meshOutput, meshOutput1);

  reader = vtkSmartPointer<vtkPLYReader>::New();
  reader->SetFileName(meshOutput.c_str());
  reader->Update();

  return reader->GetOutputPort();
}