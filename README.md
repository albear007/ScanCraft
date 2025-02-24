Here’s your corrected README.md with proper spacing and formatting:

# ScanCraft 🖥️📡

### Advanced GUI for Controlling Motors and Processing Images on Raspberry Pi

![ScanCraft Logo](resources/images/logo.png)

## 🚀 Overview

ScanCraft is a Qt-based GUI application designed to interface with a Raspberry Pi, allowing users to:

- Control motors 🏎️ for precise movement.
- Capture images 📸 from connected cameras.
- Process and analyze images using advanced algorithms.
- Provide an interactive and intuitive UI for seamless operation.

The project integrates **Qt6, FFTW3, QCustomPlot, and OpenCV** to deliver a powerful, user-friendly imaging tool.

## 📌 Features

✅ **GUI-Based Control Panel** - User-friendly interface to control motors and capture images.  
✅ **Real-time Image Processing** - Live feed and processing powered by FFT & custom algorithms.  
✅ **Integration with Raspberry Pi** - Supports hardware interfacing through GPIO and serial communication.  
✅ **Graph Plotting** - Uses **QCustomPlot** for data visualization.  
✅ **Modular Architecture** - Easy to extend and customize.

## 🏗️ Project Structure

ScanCraft/
│── build/ # Build directory (not included in repo)
│── resources/ # Icons, images, and stylesheets
│── src/ # Source files
│ │── gui/ # GUI components
│ │ │── MainWindow.hpp # Main application window header
│ │ │── MainWindow.cpp # Main application window implementation
│ │ │── Canvas.hpp # Image display and processing UI
│ │ └── Canvas.cpp # Implementation of image processing UI
│ │── Motor/ # Motor control classes
│ │── DAQ/ # Data acquisition classes
│ │── Processing/ # Image processing functions
│ │── main.cpp # Application entry point
│── CMakeLists.txt # CMake build configuration
│── README.md # This file
│── LICENSE # License information

## ⚙️ Installation & Build Instructions

### 1️⃣ Prerequisites

- **OS:** macOS (Apple Silicon), Linux, Windows
- **Qt6 Framework**
- **FFTW3 (Fast Fourier Transform)**
- **OpenCV** (for image processing)
- **CMake & Ninja** (build system)
- **VCPKG** (for dependency management)

### 2️⃣ Clone the Repository

```sh
git clone --recursive https://github.com/albear007/ScanCraft.git
cd ScanCraft

3️⃣ Install Dependencies

macOS (ARM64)

brew install cmake ninja qt6 fftw opencv

Ubuntu (Linux)

sudo apt update && sudo apt install -y cmake ninja-build qt6-base-dev libfftw3-dev libopencv-dev

Windows (Using vcpkg)

vcpkg install qt6 fftw3 opencv

4️⃣ Build the Project

mkdir -p build && cd build
cmake .. -G Ninja
ninja

🛠️ Usage

To run ScanCraft after building:

./build/ScanCraft

On Windows:

.\build\ScanCraft.exe

🔗 Configuration

Modify config.json to set custom motor speeds, image capture settings, and processing parameters.

Example:

{
  "motor_speed": 100,
  "image_resolution": "1280x720",
  "fft_enabled": true
}

🚀 Contributing

We welcome contributions! To get started:
	1.	Fork the repository 🍴
	2.	Create a new branch (git checkout -b feature-xyz)
	3.	Commit your changes (git commit -m "Add new feature")
	4.	Push to your branch (git push origin feature-xyz)
	5.	Open a Pull Request 🚀

📝 License

This project is licensed under the MIT License.

📞 Contact

📧 Email: albert.t@example.com
🐦 Twitter: @albear007
🔗 GitHub: albear007

📌 Notes
	•	If running on Raspberry Pi, additional GPIO libraries may be needed.
	•	Ensure camera permissions are set correctly before capturing images.

🌟 If you find this project useful, give it a ⭐ on GitHub! 🌟

### **🔹 Fixes & Improvements:**
✅ **Proper spacing between sections**
✅ **Code blocks properly formatted**
✅ **Better readability and alignment**

🚀 **Now you can copy-paste it directly into `README.md`!** 🚀
```
