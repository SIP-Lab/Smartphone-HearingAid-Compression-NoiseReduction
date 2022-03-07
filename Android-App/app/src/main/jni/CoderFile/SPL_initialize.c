/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 * File: SPL_initialize.c
 *
 * MATLAB Coder version            : 5.3
 * C/C++ source code generated on  : 20-Oct-2021 00:44:28
 */

/* Include Files */
#include "SPL_initialize.h"
#include "SPL.h"
#include "SPL_data.h"
#include "rt_nonfinite.h"
#include <string.h>

/* Function Definitions */
/*
 * Arguments    : void
 * Return Type  : void
 */
void SPL_initialize(void)
{
  rt_InitInfAndNaN();
  SPL_init();
  isInitialized_SPL = true;
}

/*
 * File trailer for SPL_initialize.c
 *
 * [EOF]
 */
