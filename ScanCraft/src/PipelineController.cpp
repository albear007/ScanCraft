#include "PipelineController.hpp"
#include "MainWindow.hpp"
#include <QFormLayout>
#include <QScrollBar>
#include <QVBoxLayout>
#include <qdebug.h>
#include <qstringliteral.h>

PipelineController::PipelineController(QWidget *parent)
    : QDockWidget("Pipeline Controller", parent),
      randomSeedBox(new QSpinBox(this)),
      logToStderrCheck(new QCheckBox("Log to StdErr", this)),
      logLevelBox(new QSpinBox(this)), projectPathEdit(new QLineEdit(this)),
      workspacePathEdit(new QLineEdit(this)),
      imagePathEdit(new QLineEdit(this)), maskPathEdit(new QLineEdit(this)),
      vocabTreePathEdit(new QLineEdit(this)), dataTypeBox(new QComboBox(this)),
      qualityBox(new QComboBox(this)), cameraModelEdit(new QLineEdit(this)),
      singleCameraCheck(new QCheckBox("Single Camera", this)),
      singleCameraPerFolderCheck(
          new QCheckBox("Single Camera Per Folder", this)),
      cameraParamsEdit(new QLineEdit(this)),
      extractionCheck(new QCheckBox("Extraction", this)),
      matchingCheck(new QCheckBox("Matching", this)),
      sparseCheck(new QCheckBox("Sparse", this)),
      denseCheck(new QCheckBox("Dense", this)), mesherBox(new QComboBox(this)),
      numThreadsBox(new QSpinBox(this)),
      useGPUCheck(new QCheckBox("Use GPU", this)),
      gpuIndexBox(new QSpinBox(this)), runButton(new QPushButton("Run", this)) {

  // Set initial values (same as before, omitted for brevity)
  randomSeedBox->setMaximum(999999);
  randomSeedBox->setValue(reconOpts.randomSeed);
  logToStderrCheck->setChecked(reconOpts.logToStderr);
  logLevelBox->setValue(reconOpts.logLevel);
  projectPathEdit->setText(reconOpts.projectPath);
  workspacePathEdit->setText(reconOpts.workspacePath);
  imagePathEdit->setText(reconOpts.imagePath);
  maskPathEdit->setText(reconOpts.maskPath);
  vocabTreePathEdit->setText(reconOpts.vocabTreePath);
  dataTypeBox->addItems({"Individual", "Video", "Internet"});
  dataTypeBox->setCurrentIndex(static_cast<int>(reconOpts.colorMode));
  qualityBox->addItems({"Low", "Medium", "High", "Extreme"});
  qualityBox->setCurrentIndex(static_cast<int>(reconOpts.quality));
  cameraModelEdit->setText(reconOpts.cameraModel);
  singleCameraCheck->setChecked(reconOpts.singleCamera);
  singleCameraPerFolderCheck->setChecked(reconOpts.singleCameraPerFolder);
  cameraParamsEdit->setText(reconOpts.cameraParams);
  extractionCheck->setChecked(reconOpts.extraction);
  matchingCheck->setChecked(reconOpts.matching);
  sparseCheck->setChecked(reconOpts.sparse);
  denseCheck->setChecked(reconOpts.dense);
  mesherBox->addItems({"Poisson", "Delaunay"});
  mesherBox->setCurrentIndex(static_cast<int>(reconOpts.meshType));
  numThreadsBox->setRange(-1, 256);
  numThreadsBox->setValue(reconOpts.numThreads);
  useGPUCheck->setChecked(reconOpts.useGPU);
  gpuIndexBox->setRange(-1, 15);
  gpuIndexBox->setValue(reconOpts.gpuIndex);

  // Connections with logging
  connect(randomSeedBox, QOverload<int>::of(&QSpinBox::valueChanged), this,
          [this](int val) {
            reconOpts.randomSeed = val;
            logChange("Random Seed", val);
          });
  connect(logToStderrCheck, &QCheckBox::checkStateChanged, this,
          [this](int val) {
            bool state = (val == Qt::Checked);
            reconOpts.logToStderr = state;
            logChange("Log to StdErr", state);
          });
  connect(logLevelBox, QOverload<int>::of(&QSpinBox::valueChanged), this,
          [this](int val) {
            reconOpts.logLevel = val;
            logChange("Log Level", val);
          });
  connect(projectPathEdit, &QLineEdit::textChanged, this,
          [this](const QString &text) {
            reconOpts.projectPath = text;
            logChange("Project Path", text);
          });
  connect(workspacePathEdit, &QLineEdit::textChanged, this,
          [this](const QString &text) {
            reconOpts.workspacePath = text;
            logChange("Workspace Path", text);
          });
  connect(imagePathEdit, &QLineEdit::textChanged, this,
          [this](const QString &text) {
            reconOpts.imagePath = text;
            logChange("Image Path", text);
          });
  connect(maskPathEdit, &QLineEdit::textChanged, this,
          [this](const QString &text) {
            reconOpts.maskPath = text;
            logChange("Mask Path", text);
          });
  connect(vocabTreePathEdit, &QLineEdit::textChanged, this,
          [this](const QString &text) {
            reconOpts.vocabTreePath = text;
            logChange("Vocab Tree Path", text);
          });
  connect(dataTypeBox, QOverload<int>::of(&QComboBox::currentIndexChanged),
          this, [this](int index) {
            reconOpts.colorMode =
                static_cast<ReconstructionOptions::dataType>(index);
            logChange("Data Type", dataTypeBox->itemText(index));
          });
  connect(qualityBox, QOverload<int>::of(&QComboBox::currentIndexChanged), this,
          [this](int index) {
            reconOpts.quality =
                static_cast<ReconstructionOptions::Quality>(index);
            logChange("Quality", qualityBox->itemText(index));
          });
  connect(cameraModelEdit, &QLineEdit::textChanged, this,
          [this](const QString &text) {
            reconOpts.cameraModel = text;
            logChange("Camera Model", text);
          });
  connect(singleCameraCheck, &QCheckBox::checkStateChanged, this,
          [this](int val) {
            bool state = (val == Qt::Checked);
            reconOpts.singleCamera = state;
            logChange("Single Camera", state);
          });
  connect(singleCameraPerFolderCheck, &QCheckBox::checkStateChanged, this,
          [this](int val) {
            bool state = (val == Qt::Checked);
            reconOpts.singleCameraPerFolder = state;
            logChange("Single Camera Per Folder", state);
          });
  connect(cameraParamsEdit, &QLineEdit::textChanged, this,
          [this](const QString &text) {
            reconOpts.cameraParams = text;
            logChange("Camera Params", text);
          });
  connect(extractionCheck, &QCheckBox::checkStateChanged, this,
          [this](int val) {
            bool state = (val == Qt::Checked);
            reconOpts.extraction = state;
            logChange("Extraction", state);
          });
  connect(matchingCheck, &QCheckBox::checkStateChanged, this, [this](int val) {
    bool state = (val == Qt::Checked);
    reconOpts.matching = state;
    logChange("Matching", state);
  });
  connect(sparseCheck, &QCheckBox::checkStateChanged, this, [this](int val) {
    bool state = (val == Qt::Checked);
    reconOpts.sparse = state;
    logChange("Sparse", state);
  });
  connect(denseCheck, &QCheckBox::checkStateChanged, this, [this](int val) {
    bool state = (val == Qt::Checked);
    reconOpts.dense = state;
    logChange("Dense", state);
  });
  connect(mesherBox, QOverload<int>::of(&QComboBox::currentIndexChanged), this,
          [this](int index) {
            reconOpts.meshType =
                static_cast<ReconstructionOptions::mesher>(index);
            logChange("Mesher", mesherBox->itemText(index));
          });
  connect(numThreadsBox, QOverload<int>::of(&QSpinBox::valueChanged), this,
          [this](int val) {
            reconOpts.numThreads = val;
            logChange("Num Threads", val);
          });
  connect(useGPUCheck, &QCheckBox::checkStateChanged, this, [this](int val) {
    bool state = (val == Qt::Checked);
    reconOpts.useGPU = state;
    qDebug() << "Use GPU:" << state;
    logChange("Use GPU", state);
  });
  connect(gpuIndexBox, QOverload<int>::of(&QSpinBox::valueChanged), this,
          [this](int val) {
            reconOpts.gpuIndex = val;
            logChange("GPU Index", val);
          });
  connect(runButton, &QPushButton::clicked, this,
          &PipelineController::onRunButtonClicked);

  auto *form = new QFormLayout;
  form->addRow("Random Seed", randomSeedBox);
  form->addRow(logToStderrCheck);
  form->addRow("Log Level", logLevelBox);
  form->addRow("Project Path", projectPathEdit);
  form->addRow("Workspace Path", workspacePathEdit);
  form->addRow("Image Path", imagePathEdit);
  form->addRow("Mask Path", maskPathEdit);
  form->addRow("Vocab Tree Path", vocabTreePathEdit);
  form->addRow("Data Type", dataTypeBox);
  form->addRow("Quality", qualityBox);
  form->addRow("Camera Model", cameraModelEdit);
  form->addRow(singleCameraCheck);
  form->addRow(singleCameraPerFolderCheck);
  form->addRow("Camera Params", cameraParamsEdit);
  form->addRow(extractionCheck);
  form->addRow(matchingCheck);
  form->addRow(sparseCheck);
  form->addRow(denseCheck);
  form->addRow("Mesher", mesherBox);
  form->addRow("Num Threads", numThreadsBox);
  form->addRow(useGPUCheck);
  form->addRow("GPU Index", gpuIndexBox);

  auto *container = new QWidget(this);
  auto *mainLayout = new QVBoxLayout(container);
  mainLayout->addLayout(form);
  mainLayout->addWidget(runButton);
  container->setLayout(mainLayout);
  setWidget(container);
}

PipelineController::~PipelineController() = default;

void PipelineController::onRunButtonClicked() { emit runReconstruction(); }

ReconstructionOptions PipelineController::getOptions() const {
  return reconOpts;
}

void PipelineController::logChange(const QString &label, const QString &value) {
  if (auto *mainWin = qobject_cast<MainWindow *>(this->window())) {
    emit mainWin->logMessage(label + " set to: " + value);
  }
}

void PipelineController::logChange(const QString &label, int value) {
  logChange(label, QString::number(value));
}

void PipelineController::logChange(const QString &label, bool value) {
  logChange(label, value ? QStringLiteral("true") : QStringLiteral("false"));
}