#include "MeshLoader.hpp"
#include <QWidget>
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
  emit logMessage("STL file loaded successfully.");
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
  logMessage("PLY file loaded successfully.");

  return PLYreader->GetOutputPort();
}