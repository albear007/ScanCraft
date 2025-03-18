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

  vtkNew<vtkGenericOpenGLRenderWindow> renderWindow;

  this->setRenderWindow(renderWindow.Get());

  vtkNew<vtkSTLReader> reader;

  reader->SetFileName("/Users/albert.t/Downloads/yuh/code/projects/ScanCraft/"
                      "ScanCraft/src/Cube_3d_printing_sample.stl");
  reader->Update();

  vtkNew<vtkPolyDataMapper> mapper;
  mapper->SetInputConnection(reader->GetOutputPort());

  vtkNew<vtkActor> actor;
  actor->SetMapper(mapper);
  actor->GetProperty()->SetEdgeVisibility(1);

  vtkNew<vtkRenderer> renderer;
  renderer->AddActor(actor);

  renderWindow->AddRenderer(renderer);
}