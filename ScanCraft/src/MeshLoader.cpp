#include "MeshLoader.hpp"
#include <vtkAlgorithmOutput.h>
#include <vtkSTLReader.h>
#include <vtkSmartPointer.h>

MeshLoader::MeshLoader(QObject *parent) : QObject(parent) {}

vtkAlgorithmOutput *MeshLoader::loadSTL(const QString &file) {
  if (file.isEmpty()) {
    qWarning("STLLoader::load - Empty file list provided.");
    return nullptr;
  }

  STLreader = vtkSmartPointer<vtkSTLReader>::New();
  STLreader->SetFileName(file.toStdString().c_str());
  STLreader->Update();
  return STLreader->GetOutputPort();
}
vtkAlgorithmOutput *MeshLoader::loadPLY(const QString &file) {
  if (file.isEmpty()) {
    qWarning("JPGLoader::load - Empty file list provided.");
    return nullptr;
  }

  PLYreader = vtkSmartPointer<vtkPLYReader>::New();
  PLYreader->SetFileName(file.toStdString().c_str());
  PLYreader->Update();
  return PLYreader->GetOutputPort();
}