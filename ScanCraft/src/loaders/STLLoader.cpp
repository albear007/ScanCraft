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
  if (files.size() > 1) {
    qWarning("STLLoader::load - Multiple files provided, only the first will "
             "be loaded.");
  }

  reader = vtkSmartPointer<vtkSTLReader>::New();
  reader->SetFileName(files.first().toStdString().c_str());
  reader->Update();
  return reader->GetOutputPort();
}