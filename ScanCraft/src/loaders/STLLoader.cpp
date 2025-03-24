#include "STLLoader.hpp"
#include <QFile>
#include <vtkAlgorithm.h>
#include <vtkSTLReader.h>
#include <vtkSmartPointer.h>

vtkAlgorithmOutput *STLLoader::load(const QStringList &files) {
  if (files.isEmpty()) {
    qWarning("STLLoader::load - Empty file list provided.");
    return nullptr;
  }

  reader = vtkSmartPointer<vtkSTLReader>::New();
  reader->SetFileName(files.first().toStdString().c_str());
  reader->Update();
  return reader->GetOutputPort();
}