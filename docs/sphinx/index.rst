:icon: material/home

VXLIB — C7\ :sup:`™` Image Processing Library
===============================================

VXLIB is TI's optimized image-processing library for the **C7™** DSP architecture.
It provides a suite of kernels targeting the C7™ vector and streaming engines (SE/SA),
enabling high-throughput image processing operations such as filtering, convolution,
morphology, and pixel arithmetic on TI SoCs such as AM62D and AM275.

Each kernel ships in two variants selected at init time via the
``VXLIB_FUNCTION_OPT`` / ``VXLIB_FUNCTION_NATC`` enum in the kernel's ``InitArgs``:

- ``_cn`` — C-native reference (``NATC``): portable, functionally correct, used for validation
- ``_ci`` — C7™ intrinsic-optimized (``OPT``): hardware-optimized, targets SE/SA streaming engines

.. grid:: 1 2 2 3
   :gutter: 3
   :class-container: ti-home-grid

   .. grid-item-card:: :si-icon:`material/rocket-launch` Getting Started
      :link: getting_started
      :link-type: doc

      Build, run, and generate test data — from PC host emulation to on-target EVM.

   .. grid-item-card:: :si-icon:`material/book-open-variant` API Reference
      :link: api/index
      :link-type: doc

      Every kernel, grouped by category, with signatures, parameters, and usage notes.

   .. grid-item-card:: :si-icon:`material/chart-line` Performance
      :link: perf/index
      :link-type: doc

      Measured kernel cycle counts on C7504 (AM62D) and C7524 (AM275).

   .. grid-item-card:: :si-icon:`material/file-tree` Repository Layout
      :link: repository_layout
      :link-type: doc

      A guided tour of the source tree — kernels, tests, and build files.

   .. grid-item-card:: :si-icon:`material/scale-balance` License
      :link: license
      :link-type: doc

      VXLIB is distributed under the Apache License 2.0.

.. toctree::
   :hidden:
   :maxdepth: 2

   getting_started
   repository_layout
   api/index
   perf/index
   license
