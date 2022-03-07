/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 * File: splMeter.c
 *
 * MATLAB Coder version            : 5.3
 * C/C++ source code generated on  : 20-Oct-2021 00:44:28
 */

/* Include Files */
#include "splMeter.h"
#include "SPL_internal_types.h"
#include "StatCircBuffer.h"
#include "SystemCoreSPL.h"
#include "rt_nonfinite.h"
#include <math.h>
#include <string.h>

/* Function Definitions */
/*
 * Arguments    : splMeter *obj
 *                double u[256]
 *                double LT[256]
 *                double Leq[256]
 *                double Lpeak[256]
 *                double Lmax[256]
 * Return Type  : void
 */
void splMeter_computeSPL(splMeter *obj, double u[256], double LT[256],
                         double Leq[256], double Lpeak[256], double Lmax[256])
{
  static double x[96000];
  b_dspcodegen_SOSFilter *b_obj;
  dsp_SOSFilter_1 *c_obj;
  double u_data[256];
  double LeqNew;
  double LpeakNew;
  double idx;
  double idxStart;
  double numAccum;
  double pr;
  double pr2;
  double stageOut;
  double varargin_3_idx_2;
  int hi;
  int ib;
  int k;
  int xblockoffset;
  pr = obj->PressureReference;
  pr2 = pr * pr;
  for (ib = 0; ib < 256; ib++) {
    pr = u[ib];
    pr *= pr;
    u[ib] = pr;
  }
  b_obj = &obj->pTimeWeightingFilt;
  LpeakNew = obj->pTimeWeightingFiltNum[0];
  idxStart = obj->pTimeWeightingFiltNum[1];
  LeqNew = obj->pTimeWeightingFiltNum[2];
  idx = obj->pTimeWeightingFiltDen[1];
  varargin_3_idx_2 = obj->pTimeWeightingFiltDen[2];
  if (obj->pTimeWeightingFilt.isInitialized != 1) {
    obj->pTimeWeightingFilt.isSetupComplete = false;
    obj->pTimeWeightingFilt.isInitialized = 1;
    obj->pTimeWeightingFilt.isSetupComplete = true;
    /* System object Initialization function: dsp.SOSFilter */
    b_obj->cSFunObject.W0_FILT_STATES[0] = b_obj->cSFunObject.P0_ICRTP;
    b_obj->cSFunObject.W0_FILT_STATES[1] = b_obj->cSFunObject.P0_ICRTP;
  }
  c_obj = &obj->pTimeWeightingFilt.cSFunObject;
  /* System object Outputs function: dsp.SOSFilter */
  for (xblockoffset = 0; xblockoffset < 256; xblockoffset++) {
    numAccum = c_obj->W0_FILT_STATES[0];
    pr = u[xblockoffset];
    stageOut = numAccum + LpeakNew * pr;
    numAccum = c_obj->W0_FILT_STATES[1];
    c_obj->W0_FILT_STATES[0] = (numAccum + idxStart * pr) - idx * stageOut;
    c_obj->W0_FILT_STATES[1] = LeqNew * pr - varargin_3_idx_2 * stageOut;
    LT[xblockoffset] = stageOut;
  }
  for (k = 0; k < 256; k++) {
    LT[k] = 10.0 * log10(LT[k] / pr2);
    Lmax[k] = 0.0;
    Lpeak[k] = 0.0;
    Leq[k] = 0.0;
  }
  pr = obj->pLmaxHold;
  LpeakNew = obj->pLpeakHold;
  LeqNew = obj->pLeqHold;
  idx = 96000.0 - obj->pCount;
  obj->pCount += 256.0;
  idxStart = 1.0;
  while (obj->pCount >= 96000.0) {
    if (idxStart > idx) {
      ib = 0;
      k = 0;
    } else {
      ib = (int)idxStart - 1;
      k = (int)idx;
    }
    xblockoffset = k - ib;
    for (k = 0; k < xblockoffset; k++) {
      u_data[k] = u[ib + k];
    }
    SystemCore_step(&obj->pMovIN, u_data, xblockoffset);
    if (idxStart > idx) {
      ib = 0;
      k = 0;
    } else {
      ib = (int)idxStart - 1;
      k = (int)idx;
    }
    xblockoffset = k - ib;
    for (k = 0; k < xblockoffset; k++) {
      u_data[k] = LT[ib + k];
    }
    SystemCore_step(&obj->pMovLT, u_data, xblockoffset);
    if (idxStart > idx - 1.0) {
      ib = 1;
    } else {
      ib = (int)idxStart;
    }
    hi = (int)(idx - idxStart);
    for (k = 0; k < hi; k++) {
      Leq[(ib + k) - 1] = LeqNew;
    }
    if (idxStart > idx - 1.0) {
      ib = 1;
      k = 1;
    } else {
      ib = (int)idxStart;
      k = (int)idxStart;
    }
    for (xblockoffset = 0; xblockoffset < hi; xblockoffset++) {
      Lpeak[(ib + xblockoffset) - 1] = LpeakNew;
    }
    for (ib = 0; ib < hi; ib++) {
      Lmax[(k + ib) - 1] = pr;
    }
    for (xblockoffset = 0; xblockoffset < 96000; xblockoffset++) {
      x[xblockoffset] = obj->pMovIN.pMem[xblockoffset];
    }
    LpeakNew = x[0];
    for (k = 0; k < 1023; k++) {
      LpeakNew += x[k + 1];
    }
    for (ib = 0; ib < 93; ib++) {
      xblockoffset = (ib + 1) << 10;
      pr = x[xblockoffset];
      if (ib + 2 == 94) {
        hi = 768;
      } else {
        hi = 1024;
      }
      for (k = 2; k <= hi; k++) {
        pr += x[(xblockoffset + k) - 1];
      }
      LpeakNew += pr;
    }
    LeqNew = 10.0 * log10(LpeakNew / 96000.0 / pr2);
    pr = StatCircBuffer_getMax(&obj->pMovIN) / pr2;
    pr = log10(pr);
    LpeakNew = 10.0 * pr;
    pr = StatCircBuffer_getMax(&obj->pMovLT);
    idxStart = idx;
    obj->pCount -= 96000.0;
    idx += 96000.0;
  }
  hi = 257 - (int)idxStart;
  for (ib = 0; ib < hi; ib++) {
    u_data[ib] = u[((int)idxStart + ib) - 1];
  }
  SystemCore_step(&obj->pMovIN, u_data, 257 - (int)idxStart);
  for (ib = 0; ib < hi; ib++) {
    u_data[ib] = LT[((int)idxStart + ib) - 1];
  }
  SystemCore_step(&obj->pMovLT, u_data, 257 - (int)idxStart);
  hi = (short)(257 - (int)idxStart);
  for (ib = 0; ib < hi; ib++) {
    xblockoffset = ((int)idxStart + ib) - 1;
    Lmax[xblockoffset] = pr;
    Lpeak[xblockoffset] = LpeakNew;
    Leq[xblockoffset] = LeqNew;
  }
  obj->pLmaxHold = pr;
  obj->pLpeakHold = LpeakNew;
  obj->pLeqHold = LeqNew;
}

/*
 * File trailer for splMeter.c
 *
 * [EOF]
 */
