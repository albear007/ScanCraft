#include "PipelineController.hpp"
#include <QFormLayout>
#include <QScrollBar>
#include <QVBoxLayout>
#include <qdebug.h>
#include <qstringliteral.h>

PipelineController::PipelineController(QWidget *parent)
    : QDockWidget("Pipeline Controller", parent),
      randomSeedField(new QSpinBox(this)),
      logToStdErrCheck(new QCheckBox("Log to StdErr", this)),
      logLevelField(new QSpinBox(this)), projectPathField(new QLineEdit(this)),
      workspacePathField(new QLineEdit(this)),
      imagePathField(new QLineEdit(this)), maskPathField(new QLineEdit(this)),
      vocabTreePathField(new QLineEdit(this)),
      dataTypeMenu(new QComboBox(this)), qualityMenu(new QComboBox(this)),
      cameraModelField(new QLineEdit(this)),
      singleCameraCheck(new QCheckBox("Single Camera", this)),
      singleCameraPerFolderCheck(
          new QCheckBox("Single Camera Per Folder", this)),
      cameraParamsField(new QLineEdit(this)),
      extractionCheck(new QCheckBox("Extraction", this)),
      matchingCheck(new QCheckBox("Matching", this)),
      sparseCheck(new QCheckBox("Sparse", this)),
      denseCheck(new QCheckBox("Dense", this)), mesherMenu(new QComboBox(this)),
      numThreadsField(new QSpinBox(this)),
      useGPUCheck(new QCheckBox("Use GPU", this)),
      gpuIndexField(new QSpinBox(this)),
      runButton(new QPushButton("Run", this)) {

  // Set initial values (same as before, omitted for brevity)
  randomSeedField->setMaximum(999999);
  randomSeedField->setValue(reconOpts.randomSeed);
  logToStdErrCheck->setChecked(reconOpts.logToStderr);
  logLevelField->setValue(reconOpts.logLevel);
  projectPathField->setText(reconOpts.projectPath);
  workspacePathField->setText(reconOpts.workspacePath);
  imagePathField->setText(reconOpts.imagePath);
  maskPathField->setText(reconOpts.maskPath);
  vocabTreePathField->setText(reconOpts.vocabTreePath);
  dataTypeMenu->addItems({"Individual", "Video", "Internet"});
  dataTypeMenu->setCurrentIndex(static_cast<int>(reconOpts.type));
  qualityMenu->addItems({"Low", "Medium", "High", "Extreme"});
  qualityMenu->setCurrentIndex(static_cast<int>(reconOpts.quality));
  cameraModelField->setText(reconOpts.cameraModel);
  singleCameraCheck->setChecked(reconOpts.singleCamera);
  singleCameraPerFolderCheck->setChecked(reconOpts.singleCameraPerFolder);
  cameraParamsField->setText(reconOpts.cameraParams);
  extractionCheck->setChecked(reconOpts.extraction);
  matchingCheck->setChecked(reconOpts.matching);
  sparseCheck->setChecked(reconOpts.sparse);
  denseCheck->setChecked(reconOpts.dense);
  mesherMenu->addItems({"Poisson", "Delaunay"});
  mesherMenu->setCurrentIndex(static_cast<int>(reconOpts.meshType));
  numThreadsField->setRange(-1, 256);
  numThreadsField->setValue(reconOpts.numThreads);
  useGPUCheck->setChecked(reconOpts.useGPU);
  gpuIndexField->setRange(-1, 15);
  gpuIndexField->setValue(reconOpts.gpuIndex);

  // Connections with logging
  connect(randomSeedField, QOverload<int>::of(&QSpinBox::valueChanged), this,
          [this](int val) {
            reconOpts.randomSeed = val;
            logChange("Random Seed", val);
          });
  connect(logToStdErrCheck, &QCheckBox::checkStateChanged, this,
          [this](int val) {
            bool state = (val == Qt::Checked);
            reconOpts.logToStderr = state;
            logChange("Log to StdErr", state);
          });
  connect(logLevelField, QOverload<int>::of(&QSpinBox::valueChanged), this,
          [this](int val) {
            reconOpts.logLevel = val;
            logChange("Log Level", val);
          });
  connect(projectPathField, &QLineEdit::textChanged, this,
          [this](const QString &text) {
            reconOpts.projectPath = text;
            logChange("Project Path", text);
          });
  connect(workspacePathField, &QLineEdit::textChanged, this,
          [this](const QString &text) {
            reconOpts.workspacePath = text;
            logChange("Workspace Path", text);
          });
  connect(imagePathField, &QLineEdit::textChanged, this,
          [this](const QString &text) {
            reconOpts.imagePath = text;
            logChange("Image Path", text);
          });
  connect(maskPathField, &QLineEdit::textChanged, this,
          [this](const QString &text) {
            reconOpts.maskPath = text;
            logChange("Mask Path", text);
          });
  connect(vocabTreePathField, &QLineEdit::textChanged, this,
          [this](const QString &text) {
            reconOpts.vocabTreePath = text;
            logChange("Vocab Tree Path", text);
          });
  connect(dataTypeMenu, QOverload<int>::of(&QComboBox::currentIndexChanged),
          this, [this](int index) {
            reconOpts.type =
                static_cast<ReconstructionOptions::dataType>(index);
            logChange("Data Type", dataTypeMenu->itemText(index));
          });
  connect(qualityMenu, QOverload<int>::of(&QComboBox::currentIndexChanged),
          this, [this](int index) {
            reconOpts.quality =
                static_cast<ReconstructionOptions::Quality>(index);
            logChange("Quality", qualityMenu->itemText(index));
          });
  connect(cameraModelField, &QLineEdit::textChanged, this,
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
  connect(cameraParamsField, &QLineEdit::textChanged, this,
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
  connect(mesherMenu, QOverload<int>::of(&QComboBox::currentIndexChanged), this,
          [this](int index) {
            reconOpts.meshType =
                static_cast<ReconstructionOptions::mesher>(index);
            logChange("Mesher", mesherMenu->itemText(index));
          });
  connect(numThreadsField, QOverload<int>::of(&QSpinBox::valueChanged), this,
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
  connect(gpuIndexField, QOverload<int>::of(&QSpinBox::valueChanged), this,
          [this](int val) {
            reconOpts.gpuIndex = val;
            logChange("GPU Index", val);
          });
  connect(runButton, &QPushButton::clicked, this,
          &PipelineController::onRunButtonClicked);

  auto *form = new QFormLayout;
  form->addRow("Random Seed", randomSeedField);
  form->addRow(logToStdErrCheck);
  form->addRow("Log Level", logLevelField);
  form->addRow("Project Path", projectPathField);
  form->addRow("Workspace Path", workspacePathField);
  form->addRow("Image Path", imagePathField);
  form->addRow("Mask Path", maskPathField);
  form->addRow("Vocab Tree Path", vocabTreePathField);
  form->addRow("Data Type", dataTypeMenu);
  form->addRow("Quality", qualityMenu);
  form->addRow("Camera Model", cameraModelField);
  form->addRow(singleCameraCheck);
  form->addRow(singleCameraPerFolderCheck);
  form->addRow("Camera Params", cameraParamsField);
  form->addRow(extractionCheck);
  form->addRow(matchingCheck);
  form->addRow(sparseCheck);
  form->addRow(denseCheck);
  form->addRow("Mesher", mesherMenu);
  form->addRow("Num Threads", numThreadsField);
  form->addRow(useGPUCheck);
  form->addRow("GPU Index", gpuIndexField);

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
  emit logMessage(label + " set to: " + value);
}

void PipelineController::logChange(const QString &label, int value) {
  logChange(label, QString::number(value));
}

void PipelineController::logChange(const QString &label, bool value) {
  logChange(label, value ? QStringLiteral("true") : QStringLiteral("false"));
}

void PipelineController::setWorkspacePath(const QString &workspacePath) {
  workspacePathField->setText(workspacePath);
}