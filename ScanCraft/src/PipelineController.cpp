#include "PipelineController.hpp"
#include <QFormLayout>
#include <QVBoxLayout>
#include <qspinbox.h>

PipelineController::PipelineController(QWidget *parent)
    : QWidget(parent), randomSeedBox(new QSpinBox(this)),
      logToStderrCheck(new QCheckBox("Log to Stderr", this)),
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
  // Set initial values
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

  // Connections to update struct
  connect(randomSeedBox, QOverload<int>::of(&QSpinBox::valueChanged), this,
          [this](int val) { reconOpts.randomSeed = val; });
  connect(logToStderrCheck, &QCheckBox::toggled, this,
          [this](bool val) { reconOpts.logToStderr = val; });
  connect(logLevelBox, QOverload<int>::of(&QSpinBox::valueChanged), this,
          [this](int val) { reconOpts.logLevel = val; });
  connect(projectPathEdit, &QLineEdit::textChanged, this,
          [this](const QString &text) { reconOpts.projectPath = text; });
  connect(workspacePathEdit, &QLineEdit::textChanged, this,
          [this](const QString &text) { reconOpts.workspacePath = text; });
  connect(imagePathEdit, &QLineEdit::textChanged, this,
          [this](const QString &text) { reconOpts.imagePath = text; });
  connect(maskPathEdit, &QLineEdit::textChanged, this,
          [this](const QString &text) { reconOpts.maskPath = text; });
  connect(vocabTreePathEdit, &QLineEdit::textChanged, this,
          [this](const QString &text) { reconOpts.vocabTreePath = text; });
  connect(dataTypeBox, QOverload<int>::of(&QComboBox::currentIndexChanged),
          this, [this](int index) {
            reconOpts.colorMode =
                static_cast<ReconstructionOptions::dataType>(index);
          });
  connect(qualityBox, QOverload<int>::of(&QComboBox::currentIndexChanged), this,
          [this](int index) {
            reconOpts.quality =
                static_cast<ReconstructionOptions::Quality>(index);
          });
  connect(cameraModelEdit, &QLineEdit::textChanged, this,
          [this](const QString &text) { reconOpts.cameraModel = text; });
  connect(singleCameraCheck, &QCheckBox::toggled, this,
          [this](bool val) { reconOpts.singleCamera = val; });
  connect(singleCameraPerFolderCheck, &QCheckBox::toggled, this,
          [this](bool val) { reconOpts.singleCameraPerFolder = val; });
  connect(cameraParamsEdit, &QLineEdit::textChanged, this,
          [this](const QString &text) { reconOpts.cameraParams = text; });
  connect(extractionCheck, &QCheckBox::toggled, this,
          [this](bool val) { reconOpts.extraction = val; });
  connect(matchingCheck, &QCheckBox::toggled, this,
          [this](bool val) { reconOpts.matching = val; });
  connect(sparseCheck, &QCheckBox::toggled, this,
          [this](bool val) { reconOpts.sparse = val; });
  connect(denseCheck, &QCheckBox::toggled, this,
          [this](bool val) { reconOpts.dense = val; });
  connect(mesherBox, QOverload<int>::of(&QComboBox::currentIndexChanged), this,
          [this](int index) {
            reconOpts.meshType =
                static_cast<ReconstructionOptions::mesher>(index);
          });
  connect(numThreadsBox, QOverload<int>::of(&QSpinBox::valueChanged), this,
          [this](int val) { reconOpts.numThreads = val; });
  connect(useGPUCheck, &QCheckBox::toggled, this,
          [this](bool val) { reconOpts.useGPU = val; });
  connect(gpuIndexBox, QOverload<int>::of(&QSpinBox::valueChanged), this,
          [this](int val) { reconOpts.gpuIndex = val; });
  connect(runButton, &QPushButton::clicked, this,
          &PipelineController::onRunButtonClicked);

  // Layout
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

  auto *mainLayout = new QVBoxLayout(this);
  mainLayout->addLayout(form);
  mainLayout->addWidget(runButton);
  setLayout(mainLayout);
}

PipelineController::~PipelineController() = default;

void PipelineController::onRunButtonClicked() { emit runReconstruction(); }

ReconstructionOptions PipelineController::getOptions() const {
  return reconOpts;
}