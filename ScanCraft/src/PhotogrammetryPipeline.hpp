#pragma once
#include <QObject>

class PhotogrammetryPipeline : public QObject {
  Q_OBJECT
public:
  explicit PhotogrammetryPipeline(QObject *parent = nullptr);
  PhotogrammetryPipeline(const PhotogrammetryPipeline &) = delete;
  PhotogrammetryPipeline(PhotogrammetryPipeline &&) noexcept = delete;
  PhotogrammetryPipeline &operator=(const PhotogrammetryPipeline &) = delete;
  PhotogrammetryPipeline &
  operator=(PhotogrammetryPipeline &&) noexcept = delete;
  ~PhotogrammetryPipeline() = default;

  [[nodiscard]] QString &getWorkspacePath();

signals:
public slots:
  void processImages();
  void setWorkspacePath(const QString &workspacePath);

private:
  QString workspacePath;
};