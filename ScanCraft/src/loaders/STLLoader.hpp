#pragma once
#include "MeshLoader.hpp"
#include <vtkSTLReader.h>
#include <vtkSmartPointer.h>
class STLLoader : public MeshLoader {
public:
  STLLoader() = default;
  STLLoader(const STLLoader &) = delete;
  STLLoader(STLLoader &&) noexcept = delete;
  STLLoader &operator=(const STLLoader &) = delete;
  STLLoader &operator=(STLLoader &&) noexcept = delete;
  ~STLLoader() override = default;
  vtkAlgorithmOutput *load(const QStringList &files) override;

private:
  vtkSmartPointer<vtkSTLReader> reader;
};