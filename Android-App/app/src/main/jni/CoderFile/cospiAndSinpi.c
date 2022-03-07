/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 * File: cospiAndSinpi.c
 *
 * MATLAB Coder version            : 5.3
 * C/C++ source code generated on  : 20-Oct-2021 00:32:25
 */

/* Include Files */
#include "cospiAndSinpi.h"
#include "rt_nonfinite.h"
#include <math.h>

/* Function Definitions */
/*
 * Arguments    : double x
 *                double *c
 *                double *s
 * Return Type  : void
 */
void cospiAndSinpi(double x, double *c, double *s)
{
  double r;
  boolean_T negateSinpi;
  if (x < 0.0) {
    x = -x;
    negateSinpi = true;
  } else {
    negateSinpi = false;
  }
  if (x < 0.25) {
    *c = cos(x * 3.1415926535897931);
    *s = sin(x * 3.1415926535897931);
  } else {
    r = x - 2.0 * floor(x / 2.0);
    if (r < 0.25) {
      r *= 3.1415926535897931;
      *c = cos(r);
      *s = sin(r);
    } else if (r < 0.75) {
      r = 0.5 - r;
      r *= 3.1415926535897931;
      *c = sin(r);
      *s = cos(r);
    } else if (r < 1.25) {
      r = 1.0 - r;
      r *= 3.1415926535897931;
      *c = -cos(r);
      *s = sin(r);
    } else if (r < 1.75) {
      r -= 1.5;
      r *= 3.1415926535897931;
      *c = sin(r);
      *s = -cos(r);
    } else {
      r -= 2.0;
      r *= 3.1415926535897931;
      *c = cos(r);
      *s = sin(r);
    }
  }
  if (negateSinpi) {
    *s = -*s;
  }
}

/*
 * File trailer for cospiAndSinpi.c
 *
 * [EOF]
 */
