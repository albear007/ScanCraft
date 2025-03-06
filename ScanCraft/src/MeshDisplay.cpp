#include "MeshDisplay.hpp"
#include <QVTKOpenGLNativeWidget.h>
#include <vtkGenericOpenGLRenderWindow.h>
#include <vtkNew.h>
#include <vtkRenderWindow.h>
#include <vtkRenderer.h>

MeshDisplay::MeshDisplay(QWidget *parent) : QVTKOpenGLNativeWidget(parent) {
  vtkNew<vtkGenericOpenGLRenderWindow> renderWindow;
  this->setRenderWindow(renderWindow);
}