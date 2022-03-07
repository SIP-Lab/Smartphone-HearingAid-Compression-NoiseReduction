/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 * File: weightingFilter.c
 *
 * MATLAB Coder version            : 5.3
 * C/C++ source code generated on  : 20-Oct-2021 00:44:28
 */

/* Include Files */
#include "weightingFilter.h"
#include "SPL_internal_types.h"
#include "rt_nonfinite.h"
#include "sort.h"
#include "rt_nonfinite.h"
#include <math.h>
#include <string.h>

/* Function Definitions */
/*
 * Arguments    : weightingFilter *obj
 * Return Type  : void
 */
void weightingFilter_designFilter(weightingFilter *obj)
{
  static const double p[6] = {-129.42731529303637, -129.42731529303637,
                              -676.40154875894643, -4636.1251222587643,
                              -76618.525086959533, -76618.525086959533};
  double sos[18];
  double new_z[6];
  double pd_tmp[6];
  double remaining_z[6];
  double varargin_1[6];
  double x[6];
  double den[3];
  double zb[3];
  double d;
  double remaining_z_tmp;
  double twoFs;
  double y;
  int iidx[6];
  int i;
  int idx;
  int j;
  int k;
  int m;
  boolean_T exitg1;
  twoFs = 2.0 * obj->pSampleRateDialog;
  remaining_z_tmp = (0.0 / twoFs + 1.0) / (1.0 - 0.0 / twoFs);
  remaining_z[0] = remaining_z_tmp;
  remaining_z[1] = remaining_z_tmp;
  remaining_z[2] = remaining_z_tmp;
  remaining_z[3] = remaining_z_tmp;
  remaining_z[4] = -1.0;
  remaining_z[5] = -1.0;
  for (i = 0; i < 6; i++) {
    d = p[i];
    remaining_z_tmp = d / twoFs;
    remaining_z_tmp = (remaining_z_tmp + 1.0) / (1.0 - remaining_z_tmp);
    pd_tmp[i] = remaining_z_tmp;
    x[i] = twoFs - d;
  }
  y = x[0];
  for (k = 0; k < 5; k++) {
    y *= x[k + 1];
  }
  for (k = 0; k < 6; k++) {
    d = pd_tmp[k];
    remaining_z_tmp = d;
    if (d < 0.0) {
      remaining_z_tmp = -1.0;
    } else if (d > 0.0) {
      remaining_z_tmp = 1.0;
    } else if (d == 0.0) {
      remaining_z_tmp = 0.0;
    }
    x[k] = fabs(d - remaining_z_tmp);
  }
  sort(x, iidx);
  for (i = 0; i < 6; i++) {
    x[i] = iidx[i];
    for (k = 0; k < 6; k++) {
      varargin_1[k] = fabs(remaining_z[k] - pd_tmp[(int)x[i] - 1]);
    }
    if (!rtIsNaN(varargin_1[0])) {
      idx = 1;
    } else {
      idx = 0;
      k = 2;
      exitg1 = false;
      while ((!exitg1) && (k < 7)) {
        if (!rtIsNaN(varargin_1[k - 1])) {
          idx = k;
          exitg1 = true;
        } else {
          k++;
        }
      }
    }
    if (idx == 0) {
      idx = 1;
    } else {
      remaining_z_tmp = varargin_1[idx - 1];
      j = idx + 1;
      for (k = j; k < 7; k++) {
        d = varargin_1[k - 1];
        if (remaining_z_tmp > d) {
          remaining_z_tmp = d;
          idx = k;
        }
      }
    }
    new_z[i] = remaining_z[idx - 1];
    remaining_z[idx - 1] = rtInf;
  }
  memset(&sos[0], 0, 18U * sizeof(double));
  obj->pScaleValues[0] =
      7.3863929841439228E+9 * (twoFs * twoFs * twoFs * twoFs) / y;
  for (m = 0; m < 3; m++) {
    idx = (m << 1) + 1;
    den[0] = 1.0;
    zb[0] = 1.0;
    for (j = 0; j < 2; j++) {
      i = (j + idx) - 1;
      den[j + 1] = -pd_tmp[iidx[i] - 1] * den[j];
      remaining_z_tmp = new_z[i];
      zb[j + 1] = -remaining_z_tmp * zb[j];
      for (k = j + 1; k >= 2; k--) {
        den[1] -= pd_tmp[iidx[i] - 1];
        zb[1] -= remaining_z_tmp;
      }
    }
    j = 3 - (int)ceil((double)idx / 2.0);
    sos[j] = 1.0;
    sos[j + 9] = 1.0;
    sos[j + 3] = zb[1];
    sos[j + 12] = den[1];
    sos[j + 6] = zb[2];
    sos[j + 15] = den[2];
    obj->pScaleValues[m + 1] = 1.0;
  }
  for (j = 0; j < 3; j++) {
    obj->pNumMatrix[3 * j] = sos[3 * j];
    idx = 3 * (j + 3);
    obj->pDenMatrix[3 * j] = sos[idx];
    i = 3 * j + 1;
    obj->pNumMatrix[i] = sos[i];
    obj->pDenMatrix[i] = sos[idx + 1];
    i = 3 * j + 2;
    obj->pNumMatrix[i] = sos[i];
    obj->pDenMatrix[i] = sos[idx + 2];
  }
}

/*
 * File trailer for weightingFilter.c
 *
 * [EOF]
 */
