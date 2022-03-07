/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 * File: VAD_terminate.c
 *
 * MATLAB Coder version            : 5.3
 * C/C++ source code generated on  : 20-Oct-2021 00:32:25
 */

/* Include Files */
#include "VAD_terminate.h"
#include "VAD.h"
#include "VAD_data.h"
#include "rt_nonfinite.h"

/* Function Definitions */
/*
 * Arguments    : void
 * Return Type  : void
 */
void VAD_terminate(void)
{
  VAD_free();
  isInitialized_VAD = false;
}

/*
 * File trailer for VAD_terminate.c
 *
 * [EOF]
 */
