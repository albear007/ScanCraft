#include "MeshDisplay.hpp"
#include <QVTKOpenGLNativeWidget.h>
#include <vtkActor.h>
#include <vtkGenericOpenGLRenderWindow.h>
#include <vtkInteractorStyleTrackballCamera.h>
#include <vtkNew.h>
#include <vtkPolyDataMapper.h>
#include <vtkProperty.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkRenderer.h>
#include <vtkSTLReader.h>

MeshDisplay::MeshDisplay(QWidget *parent) : QVTKOpenGLNativeWidget(parent) {

  renderWindow = vtkSmartPointer<vtkGenericOpenGLRenderWindow>::New();
  this->setRenderWindow(renderWindow.Get());
  renderer = vtkSmartPointer<vtkRenderer>::New();
  renderWindow->AddRenderer(renderer);
  actor = vtkSmartPointer<vtkActor>::New();
  mapper = vtkSmartPointer<vtkPolyDataMapper>::New();
  actor->SetMapper(mapper);
  actor->GetProperty()->SetEdgeVisibility(1);
  renderer->AddActor(actor);
}
void MeshDisplay::displaySTL(const QString &fileName) {
  vtkNew<vtkSTLReader> reader;
  reader->SetFileName(fileName.toStdString().c_str());
  reader->Update();
  mapper->SetInputConnection(reader->GetOutputPort());
  renderer->ResetCamera();
  renderWindow->Render();
}