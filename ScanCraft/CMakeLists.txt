set(EXE_NAME ScanCraft)

set(CMAKE_FIND_USE_SYSTEM_PACKAGE_REGISTRY OFF)
set(CMAKE_FIND_USE_SYSTEM_PREFIX_PATH OFF)

find_package(Qt6 CONFIG REQUIRED COMPONENTS Widgets Gui)
find_package(VTK REQUIRED COMPONENTS CommonCore GUISupportQt IOGeometry IOPLY)
find_package(colmap REQUIRED)
qt_standard_project_setup()
set(CMAKE_AUTOMOC ON)



qt_add_executable(${EXE_NAME}
  src/main.cpp
  src/MainWindow.cpp
  src/MainWindow.hpp
  src/MeshDisplay.hpp
  src/MeshDisplay.cpp
  src/MeshLoader.hpp
  src/MeshLoader.cpp
  src/PhotogrammetryPipeline.cpp
  src/PhotogrammetryPipeline.hpp
)



set_target_properties(${EXE_NAME} PROPERTIES
    CXX_STANDARD 20
    CXX_EXTENSIONS OFF
)


target_link_libraries(${EXE_NAME} PRIVATE
  Qt::Widgets
  Qt::Gui
  VTK::CommonCore
  VTK::GUISupportQt
  VTK::IOGeometry
  VTK::IOPLY
  colmap::colmap
)
target_include_directories(${EXE_NAME} PRIVATE
  src
  
)