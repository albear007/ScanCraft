#pragma once
#include <QVTKOpenGLNativeWidget.h>
#include <QWidget>
#include <qtmetamacros.h>
#include <vtkActor.h>
#include <vtkAlgorithm.h>
#include <vtkInteractorStyle.h>
#include <vtkPolyData.h>
#include <vtkPolyDataMapper.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkSmartPointer.h>

class MeshDisplay : public QVTKOpenGLNativeWidget {
  Q_OBJECT
public:
  explicit MeshDisplay(QWidget *parent = nullptr);

signals:
  void logMessage(const QString &message);

public slots:
  // void displayMesh(vtkAlgorithmOutput *mesh);
  void displayMesh(vtkAlgorithmOutput *mesh);

private:
  vtkSmartPointer<vtkGenericOpenGLRenderWindow> renderWindow;
  vtkSmartPointer<vtkRenderer> renderer;
  vtkSmartPointer<vtkActor> actor;
  vtkSmartPointer<vtkPolyDataMapper> mapper;
};
