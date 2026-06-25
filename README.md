<div align="center">

<picture>
  <source media="(prefers-color-scheme: dark)" srcset="https://www.ti.com/content/dam/ticom/images/identities/ti-brand/ti-logo-hz-1c-white.svg" width="300">
  <img alt="Texas Instruments Logo" src="https://www.ti.com/content/dam/ticom/images/identities/ti-brand/ti-hz-2c-pos-rgb.svg" width="300">
</picture>

# VXLIB — C7<sup>™</sup> Image Processing Library

[Summary](#summary) | [Features](#features) | [Operators](#operators) | [Supported Devices](#supported-devices) | [Setup Instructions](#setup-instructions) | [Build Instructions](#build-instructions) | [Related Repos](#related-repos) | [Licensing](#licensing) | [Contributions](#contributions) | [Developer Resources](#developer-resources)

</div>

## Summary

VXLIB is TI's optimized image-processing library for the **C7<sup>™</sup>** DSP architecture. It provides a suite of kernels targeting the C7<sup>™</sup> vector and streaming engines (SE/SA), enabling high-throughput image processing operations such as filtering, convolution, morphology, and pixel arithmetic on TI SoCs such as AM62D and AM275.

Each kernel ships in two variants selected at init time via the
`VXLIB_FUNCTION_OPT` / `VXLIB_FUNCTION_NATC` enum in the kernel's `InitArgs`:

| Suffix | Description |
|--------|-------------|
| `_cn` | C-native reference (`NATC`) — portable, functionally correct, used for validation |
| `_ci` | C7<sup>™</sup> intrinsic (`OPT`) — hardware-optimized, targets SE/SA streaming engines |

Each kernel has a corresponding test driver (`_d.c`). Some kernels additionally include a Python
reference implementation under `test/VXLIB_idat_gen/VXLIB_<kernel>/` for test vector generation.


## Features

- **30+ kernels** spanning pixel arithmetic, filtering, morphology, feature detection, and image conversion
- **C7<sup>™</sup> streaming engine optimized** — leverages SE/SA hardware for peak throughput across all kernels
- **Portable reference implementations** — `_cn` variants enable host-side validation and porting
- **CMake-based build** with presets for PC simulation and on-target deployment
- **Multi-type support** — `uint8_t`, `int16_t`, `uint16_t`, `int32_t`, `float`


## Operators

### Pixel Arithmetic
| Kernel | Description |
|--------|-------------|
| `VXLIB_add` | Element-wise addition of two images |
| `VXLIB_subtract` | Element-wise subtraction of two images |
| `VXLIB_multiply` | Element-wise multiplication of two images |
| `VXLIB_absDiff` | Absolute difference between two images |
| `VXLIB_addSquare` | Add the square of a pixel value to an accumulator |
| `VXLIB_addWeight` | Weighted addition of two images |

### Bitwise Operations
| Kernel | Description |
|--------|-------------|
| `VXLIB_and` | Bitwise AND of two images |
| `VXLIB_or` | Bitwise OR of two images |
| `VXLIB_xor` | Bitwise XOR of two images |
| `VXLIB_not` | Bitwise NOT of an image |

### Filtering
| Kernel | Description |
|--------|-------------|
| `VXLIB_box` | Box (averaging) filter |
| `VXLIB_gaussian` | Gaussian filter |
| `VXLIB_median` | Median filter |
| `VXLIB_convolve` | User-defined convolution kernel |
| `VXLIB_halfScaleGaussian` | Half-scale Gaussian pyramid step |

### Morphology
| Kernel | Description |
|--------|-------------|
| `VXLIB_dilate` | Morphological dilation |

### Feature Detection & Analysis
| Kernel | Description |
|--------|-------------|
| `VXLIB_magnitude` | Gradient magnitude from Sobel x/y components |
| `VXLIB_histogram` | Compute image histogram |
| `VXLIB_meanStdDev` | Mean and standard deviation of pixel values |
| `VXLIB_minMaxLoc` | Minimum and maximum pixel value and location |
| `VXLIB_normL1` | L1 norm of an image or vector |
| `VXLIB_normL2` | L2 norm of an image or vector |

### Accumulation
| Kernel | Description |
|--------|-------------|
| `VXLIB_accumulateImage` | Accumulate an image into a running sum |
| `VXLIB_accumulateSquareImage` | Accumulate the square of an image |
| `VXLIB_accumulateWeightImage` | Weighted accumulation of an image |

### Conversion & Lookup
| Kernel | Description |
|--------|-------------|
| `VXLIB_convertDepth` | Convert pixel depth (e.g., U8 to S16) |
| `VXLIB_tableLookup` | Apply a lookup table transformation |
| `VXLIB_thresholdBinary` | Binary threshold (pixels above/below threshold → 0 or 255) |
| `VXLIB_thresholdRange` | Range threshold (pixels inside/outside range → 0 or 255) |


## Supported Devices

| Device | C7<sup>™</sup> Core |
|--------|----------|
| AM62D | C7504 |
| AM275 | C7524 |


## Setup Instructions

### Prerequisites

- **Linux** host (Ubuntu 20.04 or later recommended)
- **CMake** ≥ 3.21
- **TI C7000 Code Generation Tools** (`ti-cgt-c7000`) — install to `~/ti/`

  Download from [TI CGT C7000](https://www.ti.com/tool/C7000-CGT).
  Default expected path: `~/ti/ti-cgt-c7000_5.0.0.LTS/`

  Or set the environment variable before building:
  ```bash
  export CGT7X_ROOT=/path/to/ti-cgt-c7000_<version>
  ```


## Build Instructions

VXLIB uses **CMake presets** to manage build configurations.

### Available Presets

| Preset | SoC | Platform |
|--------|-----|----------|
| `release-autotest-am62d-pc` | AM62D | PC simulation + tests |
| `release-autotest-am62d-target` | AM62D | On-device + tests |
| `release-autotest-am275-pc` | AM275 | PC simulation + tests |
| `release-autotest-am275-target` | AM275 | On-device + tests |
| `release-buildlib-am62d-pc` | AM62D | PC (library only) |
| `release-buildlib-am62d-target` | AM62D | On-device (library only) |
| `release-buildlib-am275-pc` | AM275 | PC (library only) |
| `release-buildlib-am275-target` | AM275 | On-device (library only) |

### Quick Start — PC simulation (AM62D)

```bash
# Configure
cmake -S . -B build --preset=release-autotest-am62d-pc

# Build
cmake --build build -- -j$(nproc)

# Build test binaries (ctest not supported; run binaries directly on target)
cmake --build build -- -j$(nproc)
```

### On-Target Build (AM62D)

```bash
cmake -S . -B build --preset=release-autotest-am62d-target
cmake --build build -- -j$(nproc)
```

### Library-Only Build

```bash
cmake -S . -B build --preset=release-buildlib-am62d-pc
cmake --build build -- -j$(nproc)
```


## Related Repos

- [MCU+ SDK](https://github.com/TexasInstruments/mcupsdk-core) — SoC drivers and middleware for AM2x/AM6x devices


## Licensing

This repository is licensed under the **Apache License, Version 2.0**.
See [LICENSE](LICENSE) for the full text.

All source files carry an SPDX `Apache-2.0` identifier.


## Contributions

This repository is not currently accepting community contributions.

Bug reports and feature requests are welcome via [TI E2E Community Forums](https://e2e.ti.com).


---

## Developer Resources

[TI E2E™ design support forums](https://e2e.ti.com)
