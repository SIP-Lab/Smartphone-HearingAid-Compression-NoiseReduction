/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 * File: SPL_internal_types.h
 *
 * MATLAB Coder version            : 5.3
 * C/C++ source code generated on  : 20-Oct-2021 00:44:28
 */

#ifndef SPL_INTERNAL_TYPES_H
#define SPL_INTERNAL_TYPES_H

/* Include Files */
#include "SPL_types.h"
#include "rtwtypes.h"

/* Type Definitions */
#ifndef typedef_dsp_SOSFilter_0
#define typedef_dsp_SOSFilter_0
typedef struct {
  int S0_isInitialized;
  double W0_FILT_STATES[6];
  int W1_PreviousNumChannels;
  double P0_ICRTP;
} dsp_SOSFilter_0;
#endif /* typedef_dsp_SOSFilter_0 */

#ifndef typedef_dspcodegen_SOSFilter
#define typedef_dspcodegen_SOSFilter
typedef struct {
  boolean_T matlabCodegenIsDeleted;
  int isInitialized;
  boolean_T isSetupComplete;
  dsp_SOSFilter_0 cSFunObject;
} dspcodegen_SOSFilter;
#endif /* typedef_dspcodegen_SOSFilter */

#ifndef typedef_dsp_SOSFilter_1
#define typedef_dsp_SOSFilter_1
typedef struct {
  int S0_isInitialized;
  double W0_FILT_STATES[2];
  int W1_PreviousNumChannels;
  double P0_ICRTP;
} dsp_SOSFilter_1;
#endif /* typedef_dsp_SOSFilter_1 */

#ifndef typedef_b_dspcodegen_SOSFilter
#define typedef_b_dspcodegen_SOSFilter
typedef struct {
  boolean_T matlabCodegenIsDeleted;
  int isInitialized;
  boolean_T isSetupComplete;
  dsp_SOSFilter_1 cSFunObject;
} b_dspcodegen_SOSFilter;
#endif /* typedef_b_dspcodegen_SOSFilter */

#ifndef typedef_audio_internal_StatCircBuffer
#define typedef_audio_internal_StatCircBuffer
typedef struct {
  int isInitialized;
  boolean_T isSetupComplete;
  double pMem[96000];
  unsigned int pMemPtr;
} audio_internal_StatCircBuffer;
#endif /* typedef_audio_internal_StatCircBuffer */

#ifndef typedef_cell_wrap_3
#define typedef_cell_wrap_3
typedef struct {
  unsigned int f1[8];
} cell_wrap_3;
#endif /* typedef_cell_wrap_3 */

#ifndef typedef_weightingFilter
#define typedef_weightingFilter
typedef struct {
  boolean_T matlabCodegenIsDeleted;
  int isInitialized;
  boolean_T isSetupComplete;
  boolean_T TunablePropsChanged;
  cell_wrap_3 inputVarSize[1];
  double pSampleRateDialog;
  dspcodegen_SOSFilter pFilter;
  double pNumMatrix[9];
  double pDenMatrix[9];
  double pScaleValues[4];
  double pNumChannels;
} weightingFilter;
#endif /* typedef_weightingFilter */

#ifndef typedef_splMeter
#define typedef_splMeter
typedef struct {
  boolean_T matlabCodegenIsDeleted;
  boolean_T tunablePropertyChanged[2];
  int isInitialized;
  boolean_T isSetupComplete;
  boolean_T TunablePropsChanged;
  cell_wrap_3 inputVarSize[1];
  char TimeWeighting[4];
  double PressureReference;
  weightingFilter pWeightingFilt;
  b_dspcodegen_SOSFilter pTimeWeightingFilt;
  audio_internal_StatCircBuffer pMovIN;
  audio_internal_StatCircBuffer pMovLT;
  double pCount;
  double pLeqHold;
  double pLpeakHold;
  double pLmaxHold;
  double pTimeWeightingFiltNum[3];
  double pTimeWeightingFiltDen[3];
} splMeter;
#endif /* typedef_splMeter */

#endif
/*
 * File trailer for SPL_internal_types.h
 *
 * [EOF]
 */
