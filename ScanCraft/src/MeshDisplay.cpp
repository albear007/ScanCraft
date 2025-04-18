#include "MeshDisplay.hpp"
#include <QVTKOpenGLNativeWidget.h>
#include <qassert.h>
#include <qnamespace.h>
#include <vtkActor.h>
#include <vtkAlgorithm.h>
#include <vtkGenericOpenGLRenderWindow.h>
#include <vtkNew.h>
#include <vtkPolyDataMapper.h>
#include <vtkProperty.h>
#include <vtkRenderer.h>

MeshDisplay::MeshDisplay(QWidget *parent) : QVTKOpenGLNativeWidget(parent) {

  renderWindow = vtkSmartPointer<vtkGenericOpenGLRenderWindow>::New();
  this->setRenderWindow(renderWindow.Get());
  renderer = vtkSmartPointer<vtkRenderer>::New();
  renderWindow->AddRenderer(renderer);
  actor = vtkSmartPointer<vtkActor>::New();
  mapper = vtkSmartPointer<vtkPolyDataMapper>::New();
  actor->SetMapper(mapper);
  actor->GetProperty()->SetEdgeVisibility(0);
  renderer->AddActor(actor);
}
void MeshDisplay::displayMesh(vtkAlgorithmOutput *mesh) {
  Q_ASSERT(mesh != nullptr);
  mapper->SetInputConnection(mesh);
  renderer->ResetCamera();
  renderWindow->Render();

  logMessage("Mesh displayed successfully.");
}
