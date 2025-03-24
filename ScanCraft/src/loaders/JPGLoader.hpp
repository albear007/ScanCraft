#pragma once

#include "loaders/MeshLoader.hpp"
class JPGLoader : public MeshLoader {
public:
  JPGLoader() = default;
  JPGLoader(const JPGLoader &) = delete;
  JPGLoader(JPGLoader &&) noexcept = delete;
  JPGLoader &operator=(const JPGLoader &) = delete;
  JPGLoader &operator=(JPGLoader &&) noexcept = delete;
  ~JPGLoader() override = default;

  vtkAlgorithmOutput *load(const QStringList &files) override;
};