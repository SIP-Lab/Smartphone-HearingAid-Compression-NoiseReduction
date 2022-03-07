/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 * File: VAD_internal_types.h
 *
 * MATLAB Coder version            : 5.3
 * C/C++ source code generated on  : 20-Oct-2021 00:32:25
 */

#ifndef VAD_INTERNAL_TYPES_H
#define VAD_INTERNAL_TYPES_H

/* Include Files */
#include "VAD_types.h"
#include "rtwtypes.h"

/* Type Definitions */
#ifndef typedef_c_audio_internal_SpeechNoiseEst
#define typedef_c_audio_internal_SpeechNoiseEst
typedef struct {
  int isInitialized;
  boolean_T isSetupComplete;
  double FFTLength;
  double pP[129];
  double pAlpha_c[129];
  double pSigmaN_sq[129];
  double pPbar[129];
  double pPsq_bar[129];
  double pActmin[129];
  double pActmin_sub[129];
  double pSubwc;
  double pUidx;
  double pActminbuffer[1032];
  double pLmin_flag[129];
  double pPmin_u[129];
  boolean_T pIsInitialized;
} c_audio_internal_SpeechNoiseEst;
#endif /* typedef_c_audio_internal_SpeechNoiseEst */

#ifndef typedef_audio_internal_SohnVAD
#define typedef_audio_internal_SohnVAD
typedef struct {
  boolean_T matlabCodegenIsDeleted;
  int isInitialized;
  boolean_T isSetupComplete;
  boolean_T TunablePropsChanged;
  double SilenceToSpeechProbability;
  double SpeechToSilenceProbability;
  double pXi_prev[129];
  double pGamma_log;
  double pSilenceToSpeechProbability;
  double pSpeechToSilenceProbability;
  c_audio_internal_SpeechNoiseEst pSNE;
} audio_internal_SohnVAD;
#endif /* typedef_audio_internal_SohnVAD */

#endif
/*
 * File trailer for VAD_internal_types.h
 *
 * [EOF]
 */
