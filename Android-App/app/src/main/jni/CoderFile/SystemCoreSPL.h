/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 * File: SystemCore.h
 *
 * MATLAB Coder version            : 5.3
 * C/C++ source code generated on  : 20-Oct-2021 00:44:28
 */

#ifndef SYSTEMCORE_H
#define SYSTEMCORE_H

/* Include Files */
#include "SPL_internal_types.h"
#include "rtwtypes.h"
#include <stddef.h>
#include <stdlib.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Function Declarations */
void SystemCore_setup(weightingFilter *obj);

void SystemCore_step(audio_internal_StatCircBuffer *obj,
                     const double varargin_1_data[], int varargin_1_size);

#ifdef __cplusplus
}
#endif

#endif
/*
 * File trailer for SystemCore.h
 *
 * [EOF]
 */
