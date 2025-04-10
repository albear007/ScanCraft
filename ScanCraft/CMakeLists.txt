set(EXE_NAME ScanCraft)


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

if (WIN32)
    add_compile_definitions(_USE_MATH_DEFINES)

    # On Windows, call windeployqt create a deployable folder
    # https://doc.qt.io/qt-6/windows-deployment.html
    set_target_properties(${EXE_NAME} PROPERTIES
        WIN32_EXECUTABLE ON
    )

    # Determine the path to windeployqt
    set(WINDEPLOYQT_PATH "${Qt6_DIR}/../../tools/Qt6/bin")
    set(WINDEPLOYQT_EXE "${WINDEPLOYQT_PATH}/windeployqt.exe")
    set(WINDEPLOYQT_DEBUG_EXE "${WINDEPLOYQT_PATH}/windeployqt.debug.bat")

    # Add post build command to call windeployqt
    add_custom_command(TARGET ${EXE_NAME} POST_BUILD
        COMMAND "$<IF:$<CONFIG:Debug>,${WINDEPLOYQT_DEBUG_EXE},${WINDEPLOYQT_EXE}>"
        --verbose 1
        "$<TARGET_FILE:${EXE_NAME}>"
    )
    endif()