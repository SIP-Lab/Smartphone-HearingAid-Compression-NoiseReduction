/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 * File: SystemCore.c
 *
 * MATLAB Coder version            : 5.3
 * C/C++ source code generated on  : 20-Oct-2021 00:32:25
 */

/* Include Files */
#include "SystemCore.h"
#include "SpeechNoiseEstimator.h"
#include "VAD_internal_types.h"
#include "rt_nonfinite.h"

/* Function Definitions */
/*
 * Arguments    : audio_internal_SohnVAD *obj
 * Return Type  : void
 */
void SystemCore_Setup(audio_internal_SohnVAD *obj)
{
  int i;
  obj->isSetupComplete = false;
  obj->isInitialized = 1;
  obj->pSNE.isInitialized = 0;
  obj->pSNE.isInitialized = 0;
  obj->pSNE.FFTLength = 256.0;
  obj->pSNE.isSetupComplete = false;
  obj->pSNE.isInitialized = 1;
  c_SpeechNoiseEstimator_initiali(&obj->pSNE);
  obj->pSNE.isSetupComplete = true;
  for (i = 0; i < 129; i++) {
    obj->pXi_prev[i] = 1.0;
  }
  obj->pGamma_log = 0.0;
  obj->pSilenceToSpeechProbability = obj->SilenceToSpeechProbability;
  obj->pSpeechToSilenceProbability = obj->SpeechToSilenceProbability;
  obj->isSetupComplete = true;
  obj->TunablePropsChanged = false;
}

/*
 * File trailer for SystemCore.c
 *
 * [EOF]
 */
