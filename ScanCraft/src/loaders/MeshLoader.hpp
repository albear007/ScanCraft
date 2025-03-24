#pragma once
#include <QString>
#include <QVector>
#include <vtkAlgorithm.h>
#include <vtkPolyData.h>
#include <vtkSmartPointer.h>

class MeshLoader {
public:
  MeshLoader() = default;
  MeshLoader(const MeshLoader &) = delete;
  MeshLoader(MeshLoader &&) noexcept = delete;
  MeshLoader &operator=(const MeshLoader &) = delete;
  MeshLoader &operator=(MeshLoader &&) noexcept = delete;
  virtual ~MeshLoader() = default;

  virtual vtkAlgorithmOutput *load(const QStringList &files) = 0;
};