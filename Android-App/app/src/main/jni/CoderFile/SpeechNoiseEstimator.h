/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 * File: SpeechNoiseEstimator.h
 *
 * MATLAB Coder version            : 5.3
 * C/C++ source code generated on  : 20-Oct-2021 00:32:25
 */

#ifndef SPEECHNOISEESTIMATOR_H
#define SPEECHNOISEESTIMATOR_H

/* Include Files */
#include "VAD_internal_types.h"
#include "rtwtypes.h"
#include <stddef.h>
#include <stdlib.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Function Declarations */
void SpeechNoiseEstimator_stepImpl(c_audio_internal_SpeechNoiseEst *obj,
                                   const double Ysq[129], double noiseVar[129]);

void c_SpeechNoiseEstimator_initiali(c_audio_internal_SpeechNoiseEst *obj);

#ifdef __cplusplus
}
#endif

#endif
/*
 * File trailer for SpeechNoiseEstimator.h
 *
 * [EOF]
 */
