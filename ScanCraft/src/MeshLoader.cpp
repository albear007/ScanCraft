#include "MeshLoader.hpp"
#include <QFile>
#include <vtkAlgorithm.h>
#include <vtkSTLReader.h>
#include <vtkSmartPointer.h>

vtkAlgorithmOutput *MeshLoader::loadSTL(const QString &file) {
  if (file.isEmpty()) {
    qWarning("STLLoader::load - Empty file list provided.");
    return nullptr;
  }

  reader = vtkSmartPointer<vtkSTLReader>::New();
  reader->SetFileName(file.toStdString().c_str());
  reader->Update();
  return reader->GetOutputPort();
}