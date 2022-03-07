/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 * File: SPL_terminate.c
 *
 * MATLAB Coder version            : 5.3
 * C/C++ source code generated on  : 20-Oct-2021 00:44:28
 */

/* Include Files */
#include "SPL_terminate.h"
#include "SPL.h"
#include "SPL_data.h"
#include "rt_nonfinite.h"
#include <string.h>

/* Function Definitions */
/*
 * Arguments    : void
 * Return Type  : void
 */
void SPL_terminate(void)
{
  SPL_free();
  isInitialized_SPL = false;
}

/*
 * File trailer for SPL_terminate.c
 *
 * [EOF]
 */
