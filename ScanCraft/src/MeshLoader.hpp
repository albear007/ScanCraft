#pragma once
#include <QString>
#include <vtkAlgorithm.h>
#include <vtkPLYReader.h>
#include <vtkSTLReader.h>
#include <vtkSmartPointer.h>
class MeshLoader {
public:
  MeshLoader() = default;
  MeshLoader(const MeshLoader &) = delete;
  MeshLoader(MeshLoader &&) noexcept = delete;
  MeshLoader &operator=(const MeshLoader &) = delete;
  MeshLoader &operator=(MeshLoader &&) noexcept = delete;
  ~MeshLoader() = default;
  vtkAlgorithmOutput *loadSTL(const QString &file);
  vtkAlgorithmOutput *loadPLY(const QString &file);

private:
  vtkSmartPointer<vtkSTLReader> STLreader;
  vtkSmartPointer<vtkPLYReader> PLYreader;
};