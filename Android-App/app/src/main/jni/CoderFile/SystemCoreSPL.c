/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 * File: SystemCore.c
 *
 * MATLAB Coder version            : 5.3
 * C/C++ source code generated on  : 20-Oct-2021 00:44:28
 */

/* Include Files */
#include "SystemCoreSPL.h"
#include "SPL_internal_types.h"
#include "rt_nonfinite.h"
#include "weightingFilter.h"
#include <string.h>

/* Function Definitions */
/*
 * Arguments    : weightingFilter *obj
 * Return Type  : void
 */
void SystemCore_setup(weightingFilter *obj)
{
  dspcodegen_SOSFilter *b_obj;
  obj->isSetupComplete = false;
  obj->isInitialized = 1;
  obj->pNumChannels = 1.0;
  weightingFilter_designFilter(obj);
  b_obj = &obj->pFilter;
  obj->pFilter.isInitialized = 0;
  obj->pFilter.isInitialized = 0;
  /* System object Constructor function: dsp.SOSFilter */
  b_obj->cSFunObject.P0_ICRTP = 0.0;
  obj->pFilter.matlabCodegenIsDeleted = false;
  obj->pFilter.isSetupComplete = false;
  obj->pFilter.isInitialized = 1;
  obj->pFilter.isSetupComplete = true;
  obj->isSetupComplete = true;
  obj->TunablePropsChanged = false;
}

/*
 * Arguments    : audio_internal_StatCircBuffer *obj
 *                const double varargin_1_data[]
 *                int varargin_1_size
 * Return Type  : void
 */
void SystemCore_step(audio_internal_StatCircBuffer *obj,
                     const double varargin_1_data[], int varargin_1_size)
{
  int tmp_data[256];
  unsigned int b_qY;
  int i;
  int i1;
  int loop_ub;
  unsigned int q0;
  unsigned int qY;
  if (obj->isInitialized != 1) {
    obj->isSetupComplete = false;
    obj->isInitialized = 1;
    obj->pMemPtr = 0U;
    obj->isSetupComplete = true;
    memset(&obj->pMem[0], 0, 96000U * sizeof(double));
    obj->pMemPtr = 0U;
  }
  qY = 96000U - obj->pMemPtr;
  if (qY > 96000U) {
    qY = 0U;
  }
  if ((unsigned int)varargin_1_size > qY) {
    if (1U > qY) {
      loop_ub = 0;
    } else {
      loop_ub = (int)qY;
    }
    q0 = obj->pMemPtr;
    b_qY = q0 + 1U;
    if (q0 + 1U < q0) {
      b_qY = MAX_uint32_T;
    }
    if (b_qY > 96000U) {
      i = 1;
    } else {
      i = (int)b_qY;
    }
    for (i1 = 0; i1 < loop_ub; i1++) {
      obj->pMem[(i + i1) - 1] = varargin_1_data[i1];
    }
    if (qY + 1U > (unsigned int)varargin_1_size) {
      i = 0;
      i1 = 0;
    } else {
      i = (int)qY;
      i1 = varargin_1_size;
    }
    loop_ub = i1 - i;
    for (i1 = 0; i1 < loop_ub; i1++) {
      obj->pMem[i1] = varargin_1_data[i + i1];
    }
    qY = varargin_1_size - qY;
    if (qY > (unsigned int)varargin_1_size) {
      qY = 0U;
    }
    obj->pMemPtr = qY;
  } else {
    q0 = obj->pMemPtr;
    loop_ub = varargin_1_size - 1;
    for (i = 0; i <= loop_ub; i++) {
      qY = (q0 + i) + 1U;
      if (qY < q0) {
        qY = MAX_uint32_T;
      }
      tmp_data[i] = (int)qY - 1;
    }
    for (i = 0; i < varargin_1_size; i++) {
      obj->pMem[tmp_data[i]] = varargin_1_data[i];
    }
    q0 = obj->pMemPtr;
    qY = q0 + varargin_1_size;
    if (qY < q0) {
      qY = MAX_uint32_T;
    }
    obj->pMemPtr = qY;
  }
}

/*
 * File trailer for SystemCore.c
 *
 * [EOF]
 */
