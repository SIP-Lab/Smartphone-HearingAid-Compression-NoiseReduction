/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 * File: StatCircBuffer.c
 *
 * MATLAB Coder version            : 5.3
 * C/C++ source code generated on  : 20-Oct-2021 00:44:28
 */

/* Include Files */
#include "StatCircBuffer.h"
#include "SPL_emxutil.h"
#include "SPL_internal_types.h"
#include "SPL_types.h"
#include "rt_nonfinite.h"
#include "rt_nonfinite.h"
#include <string.h>

/* Function Definitions */
/*
 * Arguments    : const audio_internal_StatCircBuffer *obj
 * Return Type  : double
 */
double StatCircBuffer_getMax(const audio_internal_StatCircBuffer *obj)
{
  emxArray_real_T *x;
  double d;
  double ymax;
  double *x_data;
  int idx;
  int k;
  boolean_T exitg1;
  emxInit_real_T(&x);
  idx = x->size[0];
  x->size[0] = 96000;
  emxEnsureCapacity_real_T(x, idx);
  x_data = x->data;
  for (idx = 0; idx < 96000; idx++) {
    x_data[idx] = obj->pMem[idx];
  }
  if (!rtIsNaN(x_data[0])) {
    idx = 1;
  } else {
    idx = 0;
    k = 2;
    exitg1 = false;
    while ((!exitg1) && (k < 96001)) {
      if (!rtIsNaN(x_data[k - 1])) {
        idx = k;
        exitg1 = true;
      } else {
        k++;
      }
    }
  }
  emxFree_real_T(&x);
  if (idx == 0) {
    ymax = obj->pMem[0];
  } else {
    ymax = obj->pMem[idx - 1];
    idx++;
    for (k = idx; k < 96001; k++) {
      d = obj->pMem[k - 1];
      if (ymax < d) {
        ymax = d;
      }
    }
  }
  return ymax;
}

/*
 * File trailer for StatCircBuffer.c
 *
 * [EOF]
 */
