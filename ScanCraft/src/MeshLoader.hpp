#pragma once
#include <QString>
#include <qobject.h>
#include <vtkAlgorithm.h>
#include <vtkPLYReader.h>
#include <vtkSTLReader.h>
#include <vtkSmartPointer.h>
class MeshLoader : public QObject {
  Q_OBJECT
public:
  explicit MeshLoader(QObject *parent = nullptr);
  MeshLoader(const MeshLoader &) = delete;
  MeshLoader(MeshLoader &&) noexcept = delete;
  MeshLoader &operator=(const MeshLoader &) = delete;
  MeshLoader &operator=(MeshLoader &&) noexcept = delete;
  ~MeshLoader() = default;
  vtkAlgorithmOutput *loadSTL(const QString &file);
  vtkAlgorithmOutput *loadPLY(const QString &file);
signals:
  void logMessage(const QString &message);
public slots:
private:
  vtkSmartPointer<vtkSTLReader> STLreader;
  vtkSmartPointer<vtkPLYReader> PLYreader;
};