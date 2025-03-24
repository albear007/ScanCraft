#include "JPGLoader.hpp"

vtkAlgorithmOutput *JPGLoader::load(const QStringList &files) {
  if (files.isEmpty()) {
    qWarning("JPGLoader::load - Empty file list provided.");
    return nullptr;
  }
}