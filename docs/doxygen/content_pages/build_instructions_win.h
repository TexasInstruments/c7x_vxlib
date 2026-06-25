// Copyright (C) 2026 Texas Instruments Incorporated
//
// SPDX-License-Identifier: Apache-2.0

#if defined(__C7100__)
/**

 \page build_instructions_win Windows Build Instructions for VXLIB

 \par Environment Setup

  - Run the executables on EVM using CCS (Code composer studio)

  - Setup needed for the compiler for CGT7x
    - Download [CGT7x Compiler Installer](https://www.ti.com/tool/C7000-CGT) and install
  - Setup needed for MSVC compiler and CMake
        - Through the Visual Studio Installer, install Visual Studio Build Tools 2022 > Desktop development with C++
  - Install Ninja
        - Download the Ninja for Windows from the [Ninja Release Page](https://github.com/ninja-build/ninja/releases)
  - Edit the environment variables for the account
        - Add user variable CGT7X_ROOT with path to the compiler directory
            - Ex: \code C:/Users/<user>/Documents/ti-cgt-c7000_4.0.0.STS \endcode
        - Edit system variable PATH to include path to the "bin" directory in the compiler directory
            - Ex: \code C:\\Users\\<user>\\Documents\\ti-cgt-c7000_4.0.0.STS\\bin \endcode
        - Edit system variable PATH to include path to the Ninja directory
            - Ex: \code C:\Users\<user>\Documents\ninja \endcode

 \par Build

  - VXLIB utilizes CMake to build, ensure that system has CMake v3.16.0 or higher
  - CMake commands can be run within the Developer PowerShell for VS 2022 at the top level "vxlib" directory
  - Build options:
    - SOC=AM62A/j721e/j721s2/j784s4
    - DEVICE=C7504/C7100/C7120
    - TARGET_PLATFORM=PC/""
    - KERNEL_NAME
    - BUILD_TEST=1 OR BUILD_EXAMPLE=1 OR AUTO_TEST=1
    - VXLIB_DEBUGPRINT=1/0
    - VXLIB_TESTPRINT
    - ALL_TEST_CASES=1 OR TEST_CASE=TestCaseID
    - CMAKE_EXPORT_COMPILE_COMMANDS=TRUE
    - CMAKE_BUILD_TYPE=Release/Debug
    - AUTO_TEST=1/0 (builds all test cases and libraries)
  - Example CMake commands
    - To build VXLIB_add for target on J721E and run performance test cases:
      - \code cmake -B build -DTARGET_PLATFORM="" -DBUILD_TEST="1" -DKERNEL_NAME="VXLIB_add" -DSOC="j721e" `
-DDEVICE="C7100" -DVXLIB_DEBUGPRINT="0" -DALL_TEST_CASES="1" -DCMAKE_EXPORT_COMPILE_COMMANDS="TRUE" `
-DCMAKE_BUILD_TYPE="Release" \endcode
    - To build VXLIB_absDiff for host emulation on J721E and run example code
      - \code cmake -B build -DTARGET_PLATFORM="PC" -DBUILD_EXAMPLE="1" -DKERNEL_NAME="VXLIB_absDiff" `
-DSOC="j721e" -DDEVICE="C7100" -DVXLIB_DEBUGPRINT="0" -DCMAKE_EXPORT_COMPILE_COMMANDS="TRUE" `
-DCMAKE_BUILD_TYPE="Release" \endcode
    - To build VXLIB_addWeight for host emulation on J721E and run test case 2 with debug print statements
        - \code cmake -B build -DTARGET_PLATFORM="PC" -DBUILD_TEST="1" -DKERNEL_NAME="VXLIB_addWeight" -DSOC="j721e" `
-DDEVICE="C7100" -DVXLIB_DEBUGPRINT="1" -DTEST_CASE="2" -DCMAKE_EXPORT_COMPILE_COMMANDS="TRUE" `
-DCMAKE_BUILD_TYPE="Release" \endcode
    -  To build all tests cases and libraries for release for J721E for target
        - \code cmake -B build -DTARGET_PLATFORM="" -DAUTO_TEST="1" -DSOC="j721e" -DDEVICE="C7100" `
-DALL_TEST_CASES="1" -DCMAKE_BUILD_TYPE="Release" -DVXLIB_DEBUGPRINT="0" \endcode
    - Then run:
      - \code cmake --build build --config Release \endcode OR \code cmake --build build --config Debug \endcode
 - VXLIB can also be built using the Visual Studio Code's build configuration feature
    - Install the latest version of CMake Tools from the Visual Studio Code marketplace
    - Rename vscode/ to .vscode/
    - In the settings.json, change build parameters as needed
    - "Build" and "Run" buttons can be used to build for target/host emulation and host emulation respectively
 - Note: If changing build configuration options significantly (e.g. changing between target and host emulation builds),
delete build folder before rebuilding

 \par Run

  - To run VXLIB kernels on a PC:
    - \code bin/Release/test_VXLIB_<kernel_name>_<device>_x86_64.exe \endcode OR \code
bin/Debug/test_VXLIB_<kernel_name>_<device>_x86_64.exe \endcode
      - Ex: \code bin/Release/test_VXLIB_and_C7100_x86_64.exe \endcode
  - To run VXLIB kernels for target
    - To reproduce numbers given in the datasheet, run the .out program on the EVM in No Boot Mode

*/

#elif defined(__C7120__)
/**

 \page build_instructions_win Windows Build Instructions for VXLIB

  \par Environment Setup

  - Run the executables on EVM using CCS (Code composer studio)

  - Setup needed for the compiler for CGT7x
    - Download [CGT7x Compiler Installer](https://www.ti.com/tool/C7000-CGT) and install
  - Setup needed for MSVC compiler and CMake
        - Through the Visual Studio Installer, install Visual Studio Build Tools 2022 > Desktop development with C++
  - Install Ninja
        - Download the Ninja for Windows from the [Ninja Release Page](https://github.com/ninja-build/ninja/releases)
  - Edit the environment variables for the account
        - Add user variable CGT7X_ROOT with path to the compiler directory
            - Ex: \code C:/Users/<user>/Documents/ti-cgt-c7000_4.0.0.STS \endcode
        - Edit system variable PATH to include path to the "bin" directory in the compiler directory
            - Ex: \code C:\\Users\\<user>\\Documents\\ti-cgt-c7000_4.0.0.STS\\bin \endcode
        - Edit system variable PATH to include path to the Ninja directory
            - Ex: \code C:\Users\<user>\Documents\ninja \endcode

 \par Build

  - VXLIB utilizes CMake to build, ensure that system has CMake v3.16.0 or higher
  - CMake commands can be run within the Developer PowerShell for VS 2022 at the top level "vxlib" directory
  - Build options:
    - SOC=AM62A/j721e/j721s2/j784s4
    - DEVICE=C7504/C7100/C7120
    - TARGET_PLATFORM=PC/""
    - KERNEL_NAME
    - BUILD_TEST=1 OR BUILD_EXAMPLE=1 OR AUTO_TEST=1
    - VXLIB_DEBUGPRINT=1/0
    - VXLIB_TESTPRINT
    - ALL_TEST_CASES=1 OR TEST_CASE=TestCaseID
    - CMAKE_EXPORT_COMPILE_COMMANDS=TRUE
    - CMAKE_BUILD_TYPE=Release/Debug
    - AUTO_TEST=1/0 (builds all test cases and libraries)
  - Example CMake commands
    - To build VXLIB_add for target on J721S2 and run performance test cases:
      - \code cmake -B build -DTARGET_PLATFORM="" -DBUILD_TEST="1" -DKERNEL_NAME="VXLIB_add" -DSOC="j721s2" `
-DDEVICE="C7120" -DVXLIB_DEBUGPRINT="0" -DALL_TEST_CASES="1" -DCMAKE_EXPORT_COMPILE_COMMANDS="TRUE" `
-DCMAKE_BUILD_TYPE="Release" \endcode
    - To build VXLIB_absDiff for host emulation on J721S2 and run example code
      - \code cmake -B build -DTARGET_PLATFORM="PC" -DBUILD_EXAMPLE="1" -DKERNEL_NAME="VXLIB_absDiff" `
-DSOC="j721s2" -DDEVICE="C7120" -DVXLIB_DEBUGPRINT="0" -DCMAKE_EXPORT_COMPILE_COMMANDS="TRUE" `
-DCMAKE_BUILD_TYPE="Release" \endcode
    - To build VXLIB_addWeight for host emulation on J721S2 and run test case 2 with debug print statements
        - \code cmake -B build -DTARGET_PLATFORM="PC" -DBUILD_TEST="1" -DKERNEL_NAME="VXLIB_exp" -DSOC="j721s2" `
-DDEVICE="C7120" -DVXLIB_DEBUGPRINT="1" -DTEST_CASE="2" -DCMAKE_EXPORT_COMPILE_COMMANDS="TRUE" `
-DCMAKE_BUILD_TYPE="Release" \endcode
    -  To build all tests cases and libraries for release for J721S2 for target
        - \code cmake -B build -DTARGET_PLATFORM="" -DAUTO_TEST="1" -DSOC="j721s2" -DDEVICE="C7120" `
-DALL_TEST_CASES="1" -DCMAKE_BUILD_TYPE="Release" -DVXLIB_DEBUGPRINT="0" \endcode
    - Then run:
      - \code cmake --build build --config Release \endcode OR \code cmake --build build --config Debug \endcode
      - To build for J784S4, replace the SOC option in the above examples to "j784s4"
 - VXLIB can also be built using the Visual Studio Code's build configuration feature
    - Install the latest version of CMake Tools from the Visual Studio Code marketplace
    - Rename vscode/ to .vscode/
    - In the settings.json, change build parameters as needed
    - "Build" and "Run" buttons can be used to build for target/host emulation and host emulation respectively
 - Note: If changing build configuration options significantly (e.g. changing between target and host emulation builds),
delete build folder before rebuilding
 \par Run

  - To run VXLIB kernels on a PC:
    - \code bin/Release/test_VXLIB_<kernel_name>_<device>_x86_64.exe \endcode OR \code
bin/Debug/test_VXLIB_<kernel_name>_<device>_x86_64.exe \endcode
      - Ex: \code bin/Release/test_VXLIB_and_C7120_x86_64.exe \endcode
  - To run VXLIB kernels for target
    - To reproduce numbers given in the datasheet, run the .out program on the EVM in No Boot Mode

*/

#else defined(__C7504__)
/**

 \page build_instructions_win Windows Build Instructions for VXLIB

  \par Environment Setup

  - Run the executables on EVM using CCS (Code composer studio)

  - Setup needed for the compiler for CGT7x
    - Download [CGT7x Compiler Installer](https://www.ti.com/tool/C7000-CGT) and install
  - Setup needed for MSVC compiler and CMake
        - Through the Visual Studio Installer, install Visual Studio Build Tools 2022 > Desktop development with C++
  - Install Ninja
        - Download the Ninja for Windows from the [Ninja Release Page](https://github.com/ninja-build/ninja/releases)
  - Edit the environment variables for the account
        - Add user variable CGT7X_ROOT with path to the compiler directory
            - Ex: \code C:/Users/<user>/Documents/ti-cgt-c7000_4.0.0.STS \endcode
        - Edit system variable PATH to include path to the "bin" directory in the compiler directory
            - Ex: \code C:\\Users\\<user>\\Documents\\ti-cgt-c7000_4.0.0.STS\\bin \endcode
        - Edit system variable PATH to include path to the Ninja directory
            - Ex: \code C:\Users\<user>\Documents\ninja \endcode

 \par Build

  - VXLIB utilizes CMake to build, ensure that system has CMake v3.16.0 or higher
  - CMake commands can be run within the Developer PowerShell for VS 2022 at the top level "vxlib" directory
  - Build options:
    - SOC=AM62A/j721e/j721s2/j784s4
    - DEVICE=C7504/C7100/C7120
    - TARGET_PLATFORM=PC/""
    - KERNEL_NAME
    - BUILD_TEST=1 OR BUILD_EXAMPLE=1 OR AUTO_TEST=1
    - VXLIB_DEBUGPRINT=1/0
    - VXLIB_TESTPRINT
    - ALL_TEST_CASES=1 OR TEST_CASE=TestCaseID
    - CMAKE_EXPORT_COMPILE_COMMANDS=TRUE
    - CMAKE_BUILD_TYPE=Release/Debug
    - AUTO_TEST=1/0 (builds all test cases and libraries)
  - Example CMake commands
    - To build VXLIB_add for target on AM62A and run performance test cases:
      - \code cmake -B build -DTARGET_PLATFORM="" -DBUILD_TEST="1" -DKERNEL_NAME="VXLIB_add" -DSOC="AM62A" `
-DDEVICE="C7504" -DVXLIB_DEBUGPRINT="0" -DALL_TEST_CASES="1" -DCMAKE_EXPORT_COMPILE_COMMANDS="TRUE" `
-DCMAKE_BUILD_TYPE="Release" \endcode
    - To build VXLIB_absDiff for host emulation on AM62A and run example code
      - \code cmake -B build -DTARGET_PLATFORM="PC" -DBUILD_EXAMPLE="1" -DKERNEL_NAME="VXLIB_absDiff" `
-DSOC="AM62A" -DDEVICE="C7504" -DVXLIB_DEBUGPRINT="0" -DCMAKE_EXPORT_COMPILE_COMMANDS="TRUE" `
-DCMAKE_BUILD_TYPE="Release" \endcode
    - To build VXLIB_addWeight for host emulation on AM62A and run test case 2 with debug print statements
        - \code cmake -B build -DTARGET_PLATFORM="PC" -DBUILD_TEST="1" -DKERNEL_NAME="VXLIB_addWeight" -DSOC="AM62A" `
-DDEVICE="C7504" -DVXLIB_DEBUGPRINT="1" -DTEST_CASE="2" -DCMAKE_EXPORT_COMPILE_COMMANDS="TRUE" `
-DCMAKE_BUILD_TYPE="Release" \endcode
    -  To build all tests cases and libraries for release for AM62A for target
        - \code cmake -B build -DTARGET_PLATFORM="" -DAUTO_TEST="1" -DSOC="AM62A" -DDEVICE="C7504" `
-DALL_TEST_CASES="1" -DCMAKE_BUILD_TYPE="Release" -DVXLIB_DEBUGPRINT="0" \endcode
    - Then run:
        - \code cmake --build build --config Release \endcode OR \code cmake --build build --config Debug \endcode
 - VXLIB can also be built using the Visual Studio Code's build configuration feature
    - Install the latest version of CMake Tools from the Visual Studio Code marketplace
    - Rename vscode/ to .vscode/
    - In the settings.json, change build parameters as needed
    - "Build" and "Run" buttons can be used to build for target/host emulation and host emulation respectively
 - Note: If changing build configuration options significantly (e.g. changing between target and host emulation builds),
delete build folder before rebuilding

 \par Run

  - To run VXLIB kernels on a PC:
    - \code bin/Release/test_VXLIB_<kernel_name>_<device>_x86_64.exe \endcode OR \code
bin/Debug/test_VXLIB_<kernel_name>_<device>_x86_64.exe \endcode
      - Ex: \code bin/Release/test_VXLIB_and_C7504_x86_64.exe \endcode
  - To run VXLIB kernels for target
    - To reproduce numbers given in the datasheet, run the .out program on the EVM in No Boot Mode

*/

#endif