set(EXE_NAME ScanCraft)
set(CMAKE_AUTOMOC ON)

find_package(fmt CONFIG REQUIRED)
find_package(Qt6 CONFIG REQUIRED COMPONENTS Widgets Gui)


qt_add_executable(${EXE_NAME}
  src/main.cpp
  src/MainWindow.cpp
  src/MainWindow.hpp
)

set_target_properties(${EXE_NAME} PROPERTIES
    CXX_STANDARD 20
    CXX_EXTENSIONS OFF
)


target_link_libraries(${EXE_NAME} PRIVATE
  fmt::fmt
  Qt::Widgets
  Qt::Gui
)
target_include_directories(${EXE_NAME} PRIVATE
  src
)