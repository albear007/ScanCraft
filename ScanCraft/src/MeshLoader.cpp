#include "MeshLoader.hpp"
#include "MainWindow.hpp"
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
  if (auto *mw = qobject_cast<MainWindow *>(this->parent())) {
    emit mw->logMessage("STL file loaded successfully.");
  }
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
  if (auto *mw = qobject_cast<MainWindow *>(this->parent())) {
    emit mw->logMessage("PLY file loaded successfully.");
  }
  return PLYreader->GetOutputPort();
}