#pragma once
#include <QVTKOpenGLNativeWidget.h>
#include <QWidget>
#include <qtmetamacros.h>

class MeshDisplay : public QVTKOpenGLNativeWidget {
  Q_OBJECT
public:
  explicit MeshDisplay(QWidget *parent = nullptr);

private:
};
