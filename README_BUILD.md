# Building Adaptive LED Matrix High Beam Project

This document provides instructions for building the project using CMake, similar to the CMSIS-DSP examples structure.

## Prerequisites

### Required Tools
- **CMake** (version 3.10 or higher)
- **C++ Compiler** supporting C++11:
  - GCC 5.0+ (Linux)
  - Clang 3.4+ (macOS/Linux)
  - MSVC 2015+ (Windows)
  - MinGW-w64 (Windows)

### Platform Support
- Linux (Ubuntu, Debian, Fedora, etc.)
- macOS (10.12+)
- Windows (7, 8, 10, 11)

## Quick Start

### Linux/macOS

```bash
# Navigate to project directory
cd adaptive-led-matrix-highbeam_orgs

# Create build directory
mkdir build && cd build

# Configure with CMake
cmake ..

# Build the project
cmake --build .

# Run examples
./bin/led_pattern_simulator
./bin/vehicle_position_calc
./bin/serial_comm_test
```

### Windows (Command Prompt)

```cmd
rem Navigate to project directory
cd adaptive-led-matrix-highbeam_orgs

rem Create build directory
mkdir build
cd build

rem Configure with CMake
cmake ..

rem Build the project
cmake --build . --config Release

rem Run examples
bin\Release\led_pattern_simulator.exe
bin\Release\vehicle_position_calc.exe
bin\Release\serial_comm_test.exe
```

### Windows (PowerShell)

```powershell
# Navigate to project directory
cd adaptive-led-matrix-highbeam_orgs

# Create build directory
New-Item -ItemType Directory -Path build
cd build

# Configure with CMake
cmake ..

# Build the project
cmake --build . --config Release

# Run examples
.\bin\Release\led_pattern_simulator.exe
.\bin\Release\vehicle_position_calc.exe
.\bin\Release\serial_comm_test.exe
```

## Build Options

### CMake Configuration Options

```bash
# Build with specific build type
cmake -DCMAKE_BUILD_TYPE=Release ..
# Options: Debug, Release, RelWithDebInfo, MinSizeRel

# Specify compiler
cmake -DCMAKE_C_COMPILER=gcc -DCMAKE_CXX_COMPILER=g++ ..

# Disable examples
cmake -DBUILD_EXAMPLES=OFF ..

# Install to custom directory
cmake -DCMAKE_INSTALL_PREFIX=/path/to/install ..
```

## Project Structure

```
adaptive-led-matrix-highbeam_orgs/
├── CMakeLists.txt              # Root CMake configuration
├── README.md                   # Main project README
├── README_BUILD.md             # This file
├── .gitignore                  # Git ignore file
├── include/                    # Public headers
│   └── led_matrix.h           # LED matrix control API
├── examples/                   # Example applications
│   ├── CMakeLists.txt         # Examples CMake configuration
│   ├── led_pattern_simulator.cpp
│   ├── vehicle_position_calc.cpp
│   └── serial_comm_test.cpp
├── LEDController/             # Arduino LED controller code
│   └── LEDController.ino
└── Python/                    # Python vehicle detection
    ├── vehicleDetect.py
    ├── label_map.pbtxt
    └── inference_graph/
```

## Examples Description

### 1. LED Pattern Simulator
**File:** `examples/led_pattern_simulator.cpp`

Demonstrates the LED matrix patterns for different vehicle detection scenarios.

**Features:**
- Simulates all single vehicle positions (0-8)
- Shows dual vehicle detection patterns
- Displays safety mode (multiple vehicles)
- Visual ASCII representation of LED states

**Usage:**
```bash
./bin/led_pattern_simulator
```

### 2. Vehicle Position Calculator
**File:** `examples/vehicle_position_calc.cpp`

Tests the position calculation algorithm that converts camera frame coordinates to LED column positions.

**Features:**
- Pre-defined test cases for common resolutions (640p, 720p, 1080p)
- Visual column division display
- Interactive mode for custom testing
- Detailed position mapping

**Usage:**
```bash
./bin/vehicle_position_calc

# Interactive mode example:
# Frame width X-coord: 640 320
# Vehicle at X=320 in 640px frame -> Position 4
```

### 3. Serial Communication Test
**File:** `examples/serial_comm_test.cpp`

Demonstrates and validates the serial communication protocol between the Python detection system and Arduino controller.

**Features:**
- Complete protocol specification
- Command generation for single and dual vehicles
- Command decoder and validator
- Interactive command testing
- Multiple output formats (ASCII, Hex, Decimal)

**Usage:**
```bash
./bin/serial_comm_test

# Interactive mode example:
# Command: xy5
# (Decodes and explains the command)
```

## Advanced Build Scenarios

### Out-of-Source Build (Recommended)

```bash
# Create a separate build directory
mkdir ../adaptive-led-build
cd ../adaptive-led-build
cmake ../adaptive-led-matrix-highbeam_orgs
cmake --build .
```

### Multi-Configuration Build (Windows/MSVC)

```bash
mkdir build && cd build
cmake ..
cmake --build . --config Debug
cmake --build . --config Release
```

### Parallel Build

```bash
# Linux/macOS
cmake --build . -j$(nproc)

# Windows
cmake --build . --parallel
```

### Clean Build

```bash
# Remove build directory and rebuild
cd ..
rm -rf build
mkdir build && cd build
cmake ..
cmake --build .
```

## Installation

Install the built examples and headers to a system or custom directory:

```bash
# Configure with install prefix
cmake -DCMAKE_INSTALL_PREFIX=/usr/local ..

# Build
cmake --build .

# Install (may require sudo on Linux/macOS)
cmake --build . --target install
```

Installed files:
- Executables: `<prefix>/bin/`
- Documentation: `<prefix>/share/doc/adaptive-led-highbeam/`

## Troubleshooting

### CMake Not Found
```bash
# Ubuntu/Debian
sudo apt-get install cmake

# macOS (Homebrew)
brew install cmake

# Windows: Download from https://cmake.org/download/
```

### Compiler Not Found
```bash
# Ubuntu/Debian
sudo apt-get install build-essential

# macOS
xcode-select --install

# Windows: Install Visual Studio or MinGW-w64
```

### Build Errors

1. **Clean the build directory:**
   ```bash
   rm -rf build/*
   ```

2. **Verify CMake version:**
   ```bash
   cmake --version  # Should be 3.10 or higher
   ```

3. **Check compiler compatibility:**
   ```bash
   g++ --version    # GCC 5.0+
   clang++ --version  # Clang 3.4+
   ```

## Testing the Examples

### Test Workflow

1. **LED Pattern Simulator**
   - Verifies LED matrix control logic
   - Checks pattern generation for all scenarios
   - Visual confirmation of patterns

2. **Vehicle Position Calculator**
   - Validates coordinate-to-position mapping
   - Tests edge cases and boundary conditions
   - Confirms algorithm accuracy across resolutions

3. **Serial Communication Test**
   - Validates protocol implementation
   - Tests command encoding/decoding
   - Ensures compatibility with Arduino code

## Integration with Hardware

The example code provides the core algorithms used in the actual hardware system:

1. **Arduino Integration**: The logic in `led_pattern_simulator.cpp` mirrors the Arduino `LEDController.ino` functions
2. **Python Integration**: The position calculation in `vehicle_position_calc.cpp` matches the Python `vehicleDetect.py` logic
3. **Protocol**: The serial commands in `serial_comm_test.cpp` are identical to those used in the real system

## Development Workflow

For developers working on the project:

```bash
# 1. Create a feature branch
git checkout -b feature/my-feature

# 2. Build and test frequently
mkdir build && cd build
cmake ..
cmake --build .

# 3. Run all examples to verify changes
./bin/led_pattern_simulator
./bin/vehicle_position_calc
./bin/serial_comm_test

# 4. Commit and push
git add .
git commit -m "Add feature"
git push origin feature/my-feature
```

## Similar Projects and References

This build system is inspired by:
- **CMSIS-DSP Examples**: ARM's signal processing library examples
  - Repository: https://github.com/ARM-software/CMSIS-DSP/tree/main/Examples
  - Similar CMake-based build structure
  - Modular example organization

## License

See the main README.md for license information.

## Additional Resources

- Main Project README: [README.md](README.md)
- Arduino Code: [LEDController/LEDController.ino](LEDController/LEDController.ino)
- Python Detection: [Python/vehicleDetect.py](Python/vehicleDetect.py)
- CMake Documentation: https://cmake.org/documentation/
