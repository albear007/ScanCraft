#include "PhotogrammetryPipeline.hpp"

PhotogrammetryPipeline::PhotogrammetryPipeline(QObject *parent)
    : QObject(parent) {
  // Initialize the pipeline here if needed
}

QString &PhotogrammetryPipeline::getWorkspacePath() { return workspacePath; }

void PhotogrammetryPipeline::processImages() {
  // Implement the image processing logic here
  // This is where you would call the COLMAP commands
  // and handle the image processing pipeline.
}
void PhotogrammetryPipeline::setWorkspacePath(const QString &workspacePath) {
  this->workspacePath = workspacePath;
  // Implement the logic to set the workspace here
  // This could involve setting up directories, file paths, etc.
}