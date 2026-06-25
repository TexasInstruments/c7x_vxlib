// Copyright (C) 2026 Texas Instruments Incorporated
//
// SPDX-License-Identifier: Apache-2.0

#if defined(__C7100__)

/**
 \page performance_summary Performance Summary

Performance data was obtained on the J721E EVM. EVM warm cycle obtained by
profiling the kernel's compute code execution after a cold run of the same code.
Please refer to the kernel's documentation for more information about the parameters
in the tables shown below.

<BR><HR>

\section VXLIB VXLIB kernels
This section contains tables that depict the expected performance numbers for the VXLIB kernels.

\subsection VXLIB_absDiff VXLIB_absDiff
\htmlinclude ./html/VXLIB_absDiff_C7100.html

\subsection VXLIB_accumulateImage VXLIB_accumulateImage
\htmlinclude ./html/VXLIB_accumulateImage_C7100.html

\subsection VXLIB_accumulateSquareImage VXLIB_accumulateSquareImage
\htmlinclude ./html/VXLIB_accumulateSquareImage_C7100.html

\subsection VXLIB_accumulateWeightImage VXLIB_accumulateWeightImage
\htmlinclude ./html/VXLIB_accumulateImageWeight_C7100.html

\subsection VXLIB_add VXLIB_add
\htmlinclude ./html/VXLIB_add_C7100.html

\subsection VXLIB_addSqaure VXLIB_addSquare
\htmlinclude ./html/VXLIB_addSquare_C7100.html

\subsection VXLIB_addWeight VXLIB_addWeight
\htmlinclude ./html/VXLIB_addWeight_C7100.html

\subsection VXLIB_and VXLIB_and
\htmlinclude ./html/VXLIB_and_C7100.html

\subsection VXLIB_box VXLIB_box
\htmlinclude ./html/VXLIB_box_C7100.html

\subsection VXLIB_convertDepth VXLIB_convertDepth
\htmlinclude ./html/VXLIB_convertDepth_C7100.html

\subsection VXLIB_multiply VXLIB_multiply
\htmlinclude ./html/VXLIB_multiply_C7100.html

\subsection VXLIB_xor VXLIB_xor
\htmlinclude ./html/VXLIB_xor_C7100.html

\subsection VXLIB_thresholdRange VXLIB_thresholdRange
\htmlinclude ./html/VXLIB_thresholdRange_C7100.html

\subsection VXLIB_subtract VXLIB_subtract
\htmlinclude ./html/VXLIB_subtract_C7100.html

\subsection VXLIB_or VXLIB_or
\htmlinclude ./html/VXLIB_or_C7100.html

\subsection VXLIB_not VXLIB_not
\htmlinclude ./html/VXLIB_not_C7100.html

\subsection VXLIB_normL1 VXLIB_normL1
\htmlinclude ./html/VXLIB_normL1_C7100.html

\subsection VXLIB_normL2 VXLIB_normL2
\htmlinclude ./html/VXLIB_normL2_C7100.html

\subsection VXLIB_minMaxLoc VXLIB_minMaxLoc
\htmlinclude ./html/VXLIB_minMaxLoc_C7100.html

\subsection VXLIB_median VXLIB_median
\htmlinclude ./html/VXLIB_median_C7100.html

\subsection VXLIB_convolve VXLIB_convolve
\htmlinclude ./html/VXLIB_convolve_C7100.html

\subsection VXLIB_dilate VXLIB_dilate
\htmlinclude ./html/VXLIB_dilate_C7100.html

\subsection VXLIB_meanStdDev VXLIB_meanStdDev
\htmlinclude ./html/VXLIB_meanStdDev_C7100.html

\subsection VXLIB_gaussian VXLIB_gaussian
\htmlinclude ./html/VXLIB_gaussian_C7100.html

\subsection VXLIB_halfScaleGaussian VXLIB_halfScaleGaussian
\htmlinclude ./html/VXLIB_halfScaleGaussian_C7100.html

\subsection VXLIB_magnitude VXLIB_magnitude
\htmlinclude ./html/VXLIB_magnitude_C7100.html

\subsection VXLIB_histogram VXLIB_histogram
\htmlinclude ./html/VXLIB_histogram_C7100.html

\subsection VXLIB_tableLookup VXLIB_tableLookup
\htmlinclude ./html/VXLIB_tableLookup_C7100.html

\subsection VXLIB_thresholdBinary VXLIB_thresholdBinary
\htmlinclude ./html/VXLIB_thresholdBinary_C7100.html

<BR>

*/

#elif defined(__C7120__)

/**
 \page performance_summary Performance Summary

Performance data was obtained on the J721S2 EVM. EVM warm cycle obtained by
profiling the kernel's compute code execution after a cold run of the same code.
Please refer to the kernel's documentation for more information about the parameters
in the tables shown below.

\section VXLIB VXLIB kernels
This section contains tables that depict the expected performance numbers for the VXLIB kernels.

\subsection VXLIB_absDiff VXLIB_absDiff
\htmlinclude ./html/VXLIB_absDiff_C7120.html

\subsection VXLIB_accumulateImage VXLIB_accumulateImage
\htmlinclude ./html/VXLIB_accumulateImage_C7120.html

\subsection VXLIB_accumulateSquareImage VXLIB_accumulateSquareImage
\htmlinclude ./html/VXLIB_accumulateSquareImage_C7120.html

\subsection VXLIB_accumulateWeightImage VXLIB_accumulateWeightImage
\htmlinclude ./html/VXLIB_accumulateWeightImage_C7120.html

\subsection VXLIB_add VXLIB_add
\htmlinclude ./html/VXLIB_add_C7120.html

\subsection VXLIB_addSqaure VXLIB_addSquare
\htmlinclude ./html/VXLIB_addSquare_C7120.html

\subsection VXLIB_addWeight VXLIB_addWeight
\htmlinclude ./html/VXLIB_addWeight_C7120.html

\subsection VXLIB_and VXLIB_and
\htmlinclude ./html/VXLIB_and_C7120.html

\subsection VXLIB_box VXLIB_box
\htmlinclude ./html/VXLIB_box_C7120.html

\subsection VXLIB_convertDepth VXLIB_convertDepth
\htmlinclude ./html/VXLIB_convertDepth_C7120.html

\subsection VXLIB_multiply VXLIB_multiply
\htmlinclude ./html/VXLIB_multiply_C7120.html

\subsection VXLIB_minMaxLoc VXLIB_minMaxLoc
\htmlinclude ./html/VXLIB_minMaxLoc_C7120.html

\subsection VXLIB_xor VXLIB_xor
\htmlinclude ./html/VXLIB_xor_C7120.html

\subsection VXLIB_thresholdBinary VXLIB_thresholdBinary
\htmlinclude ./html/VXLIB_thresholdBinary_C7120.html

\subsection VXLIB_tableLookup VXLIB_tableLookup
\htmlinclude ./html/VXLIB_tableLookup_C7120.html

\subsection VXLIB_subtract VXLIB_subtract
\htmlinclude ./html/VXLIB_subtract_C7120.html

\subsection VXLIB_or VXLIB_or
\htmlinclude ./html/VXLIB_or_C7120.html

\subsection VXLIB_not VXLIB_not
\htmlinclude ./html/VXLIB_not_C7120.html

\subsection VXLIB_normL1 VXLIB_normL1
\htmlinclude ./html/VXLIB_normL1_C7120.html

\subsection VXLIB_normL2 VXLIB_normL2
\htmlinclude ./html/VXLIB_normL2_C7120.html

\subsection VXLIB_thresholdRange VXLIB_thresholdRange
\htmlinclude ./html/VXLIB_thresholdRange_C7120.html

\subsection VXLIB_median VXLIB_median
\htmlinclude ./html/VXLIB_median_C7120.html

\subsection VXLIB_convolve VXLIB_convolve
\htmlinclude ./html/VXLIB_convolve_C7120.html

\subsection VXLIB_dilate VXLIB_dilate
\htmlinclude ./html/VXLIB_dilate_C7120.html

\subsection VXLIB_meanStdDev VXLIB_meanStdDev
\htmlinclude ./html/VXLIB_meanStdDev_C7120.html

\subsection VXLIB_gaussian VXLIB_gaussian
\htmlinclude ./html/VXLIB_gaussian_C7120.html

\subsection VXLIB_halfScaleGaussian VXLIB_halfScaleGaussian
\htmlinclude ./html/VXLIB_halfScaleGaussian_C7120.html

\subsection VXLIB_magnitude VXLIB_magnitude
\htmlinclude ./html/VXLIB_magnitude_C7120.html

\subsection VXLIB_histogram VXLIB_histogram
\htmlinclude ./html/VXLIB_histogram_C7120.html

*/
#elif defined(__C7504__)
/**
 \page performance_summary Performance Summary

Performance data was obtained on the AM62A EVM. EVM warm cycle obtained by
profiling the kernel's compute code execution after a cold run of the same code.
Please refer to the kernel's documentation for more information about the parameters
in the tables shown below.

\section VXLIB VXLIB kernels
This section contains tables that depict the expected performance numbers for the VXLIB kernels.

\subsection VXLIB_absDiff VXLIB_absDiff
\htmlinclude ./html/VXLIB_absDiff_C7504.html

\subsection VXLIB_accumulateImage VXLIB_accumulateImage
\htmlinclude ./html/VXLIB_accumulateImage_C7504.html

\subsection VXLIB_accumulateSquareImage VXLIB_accumulateSquareImage
\htmlinclude ./html/VXLIB_accumulateSquareImage_C7504.html

\subsection VXLIB_accumulateWeightImage VXLIB_accumulateWeightImage
\htmlinclude ./html/VXLIB_accumulateImageWeight_C7504.html

\subsection VXLIB_add VXLIB_add
\htmlinclude ./html/VXLIB_add_C7504.html

\subsection VXLIB_addSqaure VXLIB_addSquare
\htmlinclude ./html/VXLIB_addSquare_C7504.html

\subsection VXLIB_addWeight VXLIB_addWeight
\htmlinclude ./html/VXLIB_addWeight_C7504.html

\subsection VXLIB_and VXLIB_and
\htmlinclude ./html/VXLIB_and_C7504.html

\subsection VXLIB_box VXLIB_box
\htmlinclude ./html/VXLIB_box_C7504.html

\subsection VXLIB_convertDepth VXLIB_convertDepth
\htmlinclude ./html/VXLIB_convertDepth_C7504.html

\subsection VXLIB_multiply VXLIB_multiply
\htmlinclude ./html/VXLIB_multiply_C7504.html

\subsection VXLIB_xor VXLIB_xor
\htmlinclude ./html/VXLIB_xor_C7504.html

\subsection VXLIB_thresholdBinary VXLIB_thresholdBinary
\htmlinclude ./html/VXLIB_thresholdBinary_C7504.html

\subsection VXLIB_tableLookup VXLIB_tableLookup
\htmlinclude ./html/VXLIB_tableLookup_C7504.html

\subsection VXLIB_subtract VXLIB_subtract
\htmlinclude ./html/VXLIB_subtract_C7504.html

\subsection VXLIB_or VXLIB_or
\htmlinclude ./html/VXLIB_or_C7504.html

\subsection VXLIB_not VXLIB_not
\htmlinclude ./html/VXLIB_not_C7504.html

\subsection VXLIB_normL1 VXLIB_normL1
\htmlinclude ./html/VXLIB_normL1_C7504.html

\subsection VXLIB_normL2 VXLIB_normL2
\htmlinclude ./html/VXLIB_normL2_C7504.html

\subsection VXLIB_minMaxLoc VXLIB_minMaxLoc
\htmlinclude ./html/VXLIB_minMaxLoc_C7504.html

\subsection VXLIB_thresholdRange VXLIB_thresholdRange
\htmlinclude ./html/VXLIB_thresholdRange_C7504.html

\subsection VXLIB_median VXLIB_median
\htmlinclude ./html/VXLIB_median_C7504.html

\subsection VXLIB_convolve VXLIB_convolve
\htmlinclude ./html/VXLIB_convolve_C7504.html

\subsection VXLIB_dilate VXLIB_dilate
\htmlinclude ./html/VXLIB_dilate_C7504.html

\subsection VXLIB_meanStdDev VXLIB_meanStdDev
\htmlinclude ./html/VXLIB_meanStdDev_C7504.html

\subsection VXLIB_gaussian VXLIB_gaussian
\htmlinclude ./html/VXLIB_gaussian_C7504.html

\subsection VXLIB_halfScaleGaussian VXLIB_halfScaleGaussian
\htmlinclude ./html/VXLIB_halfScaleGaussian_C7504.html

\subsection VXLIB_magnitude VXLIB_magnitude
\htmlinclude ./html/VXLIB_magnitude_C7504.html

\subsection VXLIB_histogram VXLIB_histogram
\htmlinclude ./html/VXLIB_histogram_C7504.html

*/

#elif defined(__C7524__)
/**
 \page performance_summary Performance Summary

Performance data was obtained on the J722S EVM. EVM warm cycle obtained by
profiling the kernel's compute code execution after a cold run of the same code.
Please refer to the kernel's documentation for more information about the parameters
in the tables shown below.

\section VXLIB VXLIB kernels
This section contains tables that depict the expected performance numbers for the VXLIB kernels.

\subsection VXLIB_absDiff VXLIB_absDiff
\htmlinclude ./html/VXLIB_absDiff_C7524.html

\subsection VXLIB_accumulateImage VXLIB_accumulateImage
\htmlinclude ./html/VXLIB_accumulateImage_C7524.html

\subsection VXLIB_accumulateSquareImage VXLIB_accumulateSquareImage
\htmlinclude ./html/VXLIB_accumulateSquareImage_C7524.html

\subsection VXLIB_accumulateWeightImage VXLIB_accumulateWeightImage
\htmlinclude ./html/VXLIB_accumulateImageWeight_C7524.html

\subsection VXLIB_add VXLIB_add
\htmlinclude ./html/VXLIB_add_C7524.html

\subsection VXLIB_addSqaure VXLIB_addSquare
\htmlinclude ./html/VXLIB_addSquare_C7524.html

\subsection VXLIB_addWeight VXLIB_addWeight
\htmlinclude ./html/VXLIB_addWeight_C7524.html

\subsection VXLIB_and VXLIB_and
\htmlinclude ./html/VXLIB_and_C7524.html

\subsection VXLIB_box VXLIB_box
\htmlinclude ./html/VXLIB_box_C7524.html

\subsection VXLIB_convertDepth VXLIB_convertDepth
\htmlinclude ./html/VXLIB_convertDepth_C7524.html

\subsection VXLIB_multiply VXLIB_multiply
\htmlinclude ./html/VXLIB_multiply_C7524.html

\subsection VXLIB_xor VXLIB_xor
\htmlinclude ./html/VXLIB_xor_C7524.html

\subsection VXLIB_thresholdBinary VXLIB_thresholdBinary
\htmlinclude ./html/VXLIB_thresholdBinary_C7524.html

\subsection VXLIB_subtract VXLIB_subtract
\htmlinclude ./html/VXLIB_subtract_C7524.html

\subsection VXLIB_or VXLIB_or
\htmlinclude ./html/VXLIB_or_C7524.html

\subsection VXLIB_not VXLIB_not
\htmlinclude ./html/VXLIB_not_C7524.html

\subsection VXLIB_normL1 VXLIB_normL1
\htmlinclude ./html/VXLIB_normL1_C7524.html

\subsection VXLIB_normL2 VXLIB_normL2
\htmlinclude ./html/VXLIB_normL2_C7524.html

\subsection VXLIB_minMaxLoc VXLIB_minMaxLoc
\htmlinclude ./html/VXLIB_minMaxLoc_C7524.html

\subsection VXLIB_thresholdRange VXLIB_thresholdRange
\htmlinclude ./html/VXLIB_thresholdRange_C7524.html

\subsection VXLIB_median VXLIB_median
\htmlinclude ./html/VXLIB_median_C7524.html

\subsection VXLIB_convolve VXLIB_convolve
\htmlinclude ./html/VXLIB_convolve_C7524.html

\subsection VXLIB_dilate VXLIB_dilate
\htmlinclude ./html/VXLIB_dilate_C7524.html

\subsection VXLIB_meanStdDev VXLIB_meanStdDev
\htmlinclude ./html/VXLIB_meanStdDev_C7524.html

\subsection VXLIB_gaussian VXLIB_gaussian
\htmlinclude ./html/VXLIB_gaussian_C7524.html

\subsection VXLIB_halfScaleGaussian VXLIB_halfScaleGaussian
\htmlinclude ./html/VXLIB_halfScaleGaussian_C7524.html

\subsection VXLIB_magnitude VXLIB_magnitude
\htmlinclude ./html/VXLIB_magnitude_C7524.html

*/
#endif
// clang-format on
