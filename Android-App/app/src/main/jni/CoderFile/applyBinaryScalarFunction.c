/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 * File: applyBinaryScalarFunction.c
 *
 * MATLAB Coder version            : 5.2
 * C/C++ source code generated on  : 18-Oct-2021 12:18:21
 */

/* Include Files */
#include "applyBinaryScalarFunction.h"
#include "cbesi.h"
#include "rt_nonfinite.h"
#include "rt_nonfinite.h"

/* Function Definitions */
/*
 * Arguments    : const double y[129]
 *                creal_T z1[129]
 * Return Type  : void
 */
void b_flatIter(const double y[129], creal_T z1[129])
{
  creal_T w;
  creal_T zd;
  double d;
  int a__1;
  int ierr;
  int k;
#pragma omp parallel for num_threads(omp_get_max_threads()) private(           \
    zd, w, a__1, ierr, d)

  for (k = 0; k < 129; k++) {
    zd.re = y[k];
    zd.im = 0.0;
    if (rtIsNaN(zd.re)) {
      w.re = rtNaN;
      w.im = 0.0;
    } else {
      cbesi(zd, 1.0, &w, &a__1, &ierr);
      if (ierr == 5) {
        w.re = rtNaN;
        w.im = 0.0;
      } else if (ierr == 2) {
        w.re = rtInf;
        w.im = 0.0;
      }
      if (zd.re > 0.0) {
        d = w.re;
        w.re = d;
        w.im = 0.0;
      }
    }
    z1[k] = w;
  }
}

/*
 * Arguments    : const double y[129]
 *                creal_T z1[129]
 * Return Type  : void
 */
void flatIter(const double y[129], creal_T z1[129])
{
  creal_T w;
  creal_T zd;
  double d;
  int a__1;
  int ierr;
  int k;
#pragma omp parallel for num_threads(omp_get_max_threads()) private(           \
    zd, w, a__1, ierr, d)

  for (k = 0; k < 129; k++) {
    zd.re = y[k];
    zd.im = 0.0;
    if (rtIsNaN(zd.re)) {
      w.re = rtNaN;
      w.im = 0.0;
    } else {
      cbesi(zd, 0.0, &w, &a__1, &ierr);
      if (ierr == 5) {
        w.re = rtNaN;
        w.im = 0.0;
      } else if (ierr == 2) {
        w.re = rtInf;
        w.im = 0.0;
      }
      if (zd.re > 0.0) {
        d = w.re;
        w.re = d;
        w.im = 0.0;
      }
    }
    z1[k] = w;
  }
}

/*
 * File trailer for applyBinaryScalarFunction.c
 *
 * [EOF]
 */
