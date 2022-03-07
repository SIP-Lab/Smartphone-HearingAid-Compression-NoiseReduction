/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 * File: SpeechNoiseEstimator.c
 *
 * MATLAB Coder version            : 5.3
 * C/C++ source code generated on  : 20-Oct-2021 00:32:25
 */

/* Include Files */
#include "SpeechNoiseEstimator.h"
#include "VAD_internal_types.h"
#include "rt_nonfinite.h"
#include "rt_nonfinite.h"
#include <float.h>
#include <math.h>
#include <string.h>

/* Function Declarations */
static double rt_remd_snf(double u0, double u1);

/* Function Definitions */
/*
 * Arguments    : double u0
 *                double u1
 * Return Type  : double
 */
static double rt_remd_snf(double u0, double u1)
{
  double b_u1;
  double y;
  if (rtIsNaN(u0) || rtIsNaN(u1) || rtIsInf(u0)) {
    y = rtNaN;
  } else if (rtIsInf(u1)) {
    y = u0;
  } else {
    if (u1 < 0.0) {
      b_u1 = ceil(u1);
    } else {
      b_u1 = floor(u1);
    }
    if ((u1 != 0.0) && (u1 != b_u1)) {
      b_u1 = fabs(u0 / u1);
      if (!(fabs(b_u1 - floor(b_u1 + 0.5)) > DBL_EPSILON * b_u1)) {
        y = 0.0 * u0;
      } else {
        y = fmod(u0, u1);
      }
    } else {
      y = fmod(u0, u1);
    }
  }
  return y;
}

/*
 * Arguments    : c_audio_internal_SpeechNoiseEst *obj
 *                const double Ysq[129]
 *                double noiseVar[129]
 * Return Type  : void
 */
void SpeechNoiseEstimator_stepImpl(c_audio_internal_SpeechNoiseEst *obj,
                                   const double Ysq[129], double noiseVar[129])
{
  double e_tmp_data[1032];
  double PBc[129];
  double Qeq_inv[129];
  double alpha_hat[129];
  double Qinv_bar;
  double Uidx;
  double b_y;
  double d;
  double out;
  double subwc;
  double y;
  int b_trueCount;
  int i;
  int k;
  int trueCount;
  int xOffset;
  short c_tmp_data[1032];
  unsigned char b_tmp_data[129];
  unsigned char d_tmp_data[129];
  unsigned char tmp_data[129];
  boolean_T bv[1032];
  boolean_T a[129];
  boolean_T bv1[129];
  boolean_T k_mod[129];
  boolean_T b;
  boolean_T oddLengthFFT;
  oddLengthFFT = (rt_remd_snf(obj->FFTLength, 2.0) != 0.0);
  if (obj->pIsInitialized) {
    memcpy(&noiseVar[0], &obj->pSigmaN_sq[0], 129U * sizeof(double));
  } else {
    for (k = 0; k < 129; k++) {
      d = Ysq[k];
      obj->pP[k] = d;
      obj->pPbar[k] = d;
      obj->pPsq_bar[k] = d * d;
      obj->pPmin_u[k] = d;
      noiseVar[k] = d;
    }
    obj->pIsInitialized = true;
  }
  subwc = obj->pSubwc;
  Uidx = obj->pUidx;
  if (oddLengthFFT) {
    y = obj->pP[0];
    b_y = Ysq[0];
    for (k = 0; k < 128; k++) {
      y += obj->pP[k + 1];
      b_y += Ysq[k + 1];
    }
    out = 2.0 * y - obj->pP[0];
    y = 2.0 * b_y - Ysq[0];
  } else {
    y = obj->pP[0];
    b_y = Ysq[0];
    for (k = 0; k < 128; k++) {
      y += obj->pP[k + 1];
      b_y += Ysq[k + 1];
    }
    out = (2.0 * y - obj->pP[0]) - obj->pP[128];
    y = (2.0 * b_y - Ysq[0]) - Ysq[128];
  }
  y = out / y - 1.0;
  b_y = 1.0 / (y * y + 1.0);
  if (!(b_y >= 0.7)) {
    b_y = 0.7;
  }
  for (k = 0; k < 129; k++) {
    obj->pAlpha_c[k] = 0.7 * obj->pAlpha_c[k] + 0.3 * b_y;
    d = noiseVar[k];
    y = obj->pP[k] / d - 1.0;
    y = 0.96 * obj->pAlpha_c[k] / (y * y + 1.0);
    if (!(y >= 0.3)) {
      y = 0.3;
    }
    obj->pP[k] = y * obj->pP[k] + (1.0 - y) * Ysq[k];
    out = y * y;
    if (0.8 <= out) {
      y = 0.8;
    } else {
      y = out;
    }
    obj->pPbar[k] = y * obj->pPbar[k] + (1.0 - y) * obj->pP[k];
    obj->pPsq_bar[k] =
        y * obj->pPsq_bar[k] + (1.0 - y) * (obj->pP[k] * obj->pP[k]);
    y = (obj->pPsq_bar[k] - obj->pPbar[k] * obj->pPbar[k]) / (2.0 * (d * d));
    if (!(y <= 0.5)) {
      y = 0.5;
    }
    Qeq_inv[k] = y;
  }
  if (oddLengthFFT) {
    y = Qeq_inv[0];
    for (k = 0; k < 128; k++) {
      y += Qeq_inv[k + 1];
    }
    y = (y - 0.5 * Qeq_inv[0]) / 128.5;
  } else {
    y = Qeq_inv[0];
    for (k = 0; k < 128; k++) {
      y += Qeq_inv[k + 1];
    }
    y = (y - 0.5 * (Qeq_inv[0] + Qeq_inv[128])) / 128.0;
  }
  if ((0.0 >= y) || rtIsNaN(y)) {
    Qinv_bar = 0.0;
  } else {
    Qinv_bar = y;
  }
  y = 2.12 * sqrt(Qinv_bar) + 1.0;
  trueCount = 0;
  xOffset = 0;
  for (i = 0; i < 129; i++) {
    d = 1.0 / Qeq_inv[i];
    Qeq_inv[i] = d;
    d = 158.0 / ((d - 1.73) / 0.135) + 1.0;
    alpha_hat[i] = d;
    out = obj->pP[i] * y;
    PBc[i] = out;
    b_y = out * d;
    k_mod[i] = (b_y < obj->pActmin[i]);
    if (b_y < obj->pActmin[i]) {
      trueCount++;
    }
    if (out * d < obj->pActmin[i]) {
      tmp_data[xOffset] = (unsigned char)(i + 1);
      xOffset++;
    }
  }
  for (k = 0; k < trueCount; k++) {
    xOffset = tmp_data[k] - 1;
    obj->pActmin[xOffset] = PBc[xOffset] * alpha_hat[xOffset];
  }
  trueCount = 0;
  xOffset = 0;
  for (i = 0; i < 129; i++) {
    if (k_mod[i]) {
      trueCount++;
      b_tmp_data[xOffset] = (unsigned char)(i + 1);
      xOffset++;
    }
  }
  for (k = 0; k < trueCount; k++) {
    xOffset = b_tmp_data[k] - 1;
    obj->pActmin_sub[xOffset] =
        PBc[xOffset] * (18.0 / ((Qeq_inv[xOffset] - 1.22) / 0.39) + 1.0);
  }
  if (subwc == 10.0) {
    for (i = 0; i < 129; i++) {
      if (k_mod[i]) {
        obj->pLmin_flag[i] = 0.0;
      }
      obj->pActminbuffer[i + 129 * ((int)Uidx - 1)] = obj->pActmin[i];
    }
    Uidx = rt_remd_snf(Uidx, 8.0) + 1.0;
    memcpy(&obj->pPmin_u[0], &obj->pActminbuffer[0], 129U * sizeof(double));
    for (i = 0; i < 7; i++) {
      xOffset = (i + 1) * 129;
      for (k = 0; k < 129; k++) {
        y = obj->pActminbuffer[xOffset + k];
        if (rtIsNaN(y)) {
          oddLengthFFT = false;
        } else if (rtIsNaN(obj->pPmin_u[k])) {
          oddLengthFFT = true;
        } else {
          oddLengthFFT = (obj->pPmin_u[k] > y);
        }
        if (oddLengthFFT) {
          obj->pPmin_u[k] = y;
        }
      }
    }
    if (Qinv_bar < 0.03) {
      y = 8.0;
    } else if (Qinv_bar < 0.05) {
      y = 4.0;
    } else if (Qinv_bar < 0.06) {
      y = 2.0;
    } else {
      y = 1.2;
    }
    for (i = 0; i < 129; i++) {
      oddLengthFFT = ((obj->pLmin_flag[i] != 0.0) &&
                      (obj->pActmin_sub[i] < y * obj->pPmin_u[i]));
      k_mod[i] = oddLengthFFT;
      b = (obj->pActmin_sub[i] > obj->pPmin_u[i]);
      bv1[i] = b;
      if (oddLengthFFT && b) {
        obj->pPmin_u[i] = obj->pActmin_sub[i];
      }
      a[i] = (oddLengthFFT && b);
    }
    for (i = 0; i < 8; i++) {
      xOffset = i * 129;
      memcpy(&bv[xOffset], &a[0], 129U * sizeof(boolean_T));
    }
    trueCount = 0;
    xOffset = 0;
    for (i = 0; i < 1032; i++) {
      if (bv[i]) {
        trueCount++;
        c_tmp_data[xOffset] = (short)(i + 1);
        xOffset++;
      }
    }
    b_trueCount = 0;
    xOffset = 0;
    for (i = 0; i < 129; i++) {
      if (k_mod[i] && bv1[i]) {
        b_trueCount++;
        d_tmp_data[xOffset] = (unsigned char)(i + 1);
        xOffset++;
      }
    }
    for (i = 0; i < 8; i++) {
      xOffset = i * b_trueCount;
      for (k = 0; k < b_trueCount; k++) {
        e_tmp_data[xOffset + k] = obj->pActmin_sub[d_tmp_data[k] - 1];
      }
    }
    for (k = 0; k < trueCount; k++) {
      obj->pActminbuffer[c_tmp_data[k] - 1] = e_tmp_data[k];
    }
    subwc = 1.0;
    for (i = 0; i < 129; i++) {
      obj->pLmin_flag[i] = 0.0;
      obj->pActmin[i] = rtInf;
    }
  } else {
    if (subwc > 1.0) {
      for (k = 0; k < 129; k++) {
        if (k_mod[k]) {
          obj->pLmin_flag[k] = 1.0;
        }
        if ((obj->pActmin_sub[k] <= obj->pPmin_u[k]) ||
            rtIsNaN(obj->pPmin_u[k])) {
          d = obj->pActmin_sub[k];
        } else {
          d = obj->pPmin_u[k];
        }
        noiseVar[k] = d;
        obj->pPmin_u[k] = d;
      }
    }
    subwc++;
  }
  memcpy(&obj->pSigmaN_sq[0], &noiseVar[0], 129U * sizeof(double));
  obj->pSubwc = subwc;
  obj->pUidx = Uidx;
}

/*
 * Arguments    : c_audio_internal_SpeechNoiseEst *obj
 * Return Type  : void
 */
void c_SpeechNoiseEstimator_initiali(c_audio_internal_SpeechNoiseEst *obj)
{
  int i;
  obj->pIsInitialized = false;
  for (i = 0; i < 129; i++) {
    obj->pP[i] = 0.0;
    obj->pPbar[i] = obj->pP[i];
    obj->pPsq_bar[i] = obj->pP[i];
    obj->pPmin_u[i] = obj->pP[i];
    obj->pSigmaN_sq[i] = obj->pP[i];
    obj->pAlpha_c[i] = 1.0;
    obj->pActmin[i] = rtInf;
    obj->pActmin_sub[i] = obj->pActmin[i];
  }
  obj->pSubwc = 10.0;
  obj->pUidx = 1.0;
  for (i = 0; i < 1032; i++) {
    obj->pActminbuffer[i] = rtInf;
  }
  memset(&obj->pLmin_flag[0], 0, 129U * sizeof(double));
}

/*
 * File trailer for SpeechNoiseEstimator.c
 *
 * [EOF]
 */
