/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 * File: SPL.c
 *
 * MATLAB Coder version            : 5.3
 * C/C++ source code generated on  : 20-Oct-2021 00:44:28
 */

/* Include Files */
#include "SPL.h"
#include "SPL_data.h"
#include "SPL_initialize.h"
#include "SPL_internal_types.h"
#include "SystemCoreSPL.h"
#include "rt_nonfinite.h"
#include "splMeter.h"
#include "weightingFilter.h"
#include <math.h>
#include <string.h>

/* Variable Definitions */
static splMeter SPLin;

static boolean_T SPLin_not_empty;

/* Function Definitions */
/*
 * Arguments    : const double frame[256]
 * Return Type  : double
 */
double SPL(const double frame[256])
{
  static const char b[4] = {'F', 'a', 's', 't'};
  b_dspcodegen_SOSFilter *c_obj;
  dsp_SOSFilter_0 *b_obj;
  weightingFilter *obj;
  double u[256];
  double varargin_1[256];
  double varargout_2[256];
  double varargout_3[256];
  double varargout_4[256];
  double varargin_2[9];
  double varargin_3[9];
  double alpha;
  double d;
  double d1;
  double d10;
  double d11;
  double d12;
  double d13;
  double d14;
  double d2;
  double d3;
  double d4;
  double d5;
  double d6;
  double d7;
  double d8;
  double d9;
  double numAccum;
  double stageIn;
  double stageOut;
  double varargin_4_idx_1;
  double varargin_4_idx_2;
  double varargin_4_idx_3;
  int ret;
  boolean_T flag;
  if (!isInitialized_SPL) {
    SPL_initialize();
  }
  if (!SPLin_not_empty) {
    SPLin.PressureReference = 2.0E-5;
    SPLin.isInitialized = 0;
    SPLin.tunablePropertyChanged[0] = false;
    SPLin.tunablePropertyChanged[1] = false;
    flag = (SPLin.isInitialized == 1);
    if (flag) {
      SPLin.TunablePropsChanged = true;
      SPLin.tunablePropertyChanged[0] = true;
    }
    SPLin.TimeWeighting[0] = 'F';
    SPLin.TimeWeighting[1] = 'a';
    SPLin.TimeWeighting[2] = 's';
    SPLin.TimeWeighting[3] = 't';
    SPLin.matlabCodegenIsDeleted = false;
    SPLin_not_empty = true;
  }
  if (SPLin.isInitialized != 1) {
    SPLin.isSetupComplete = false;
    SPLin.isInitialized = 1;
    SPLin.pWeightingFilt.pNumChannels = -1.0;
    SPLin.pWeightingFilt.isInitialized = 0;
    SPLin.pWeightingFilt.isInitialized = 0;
    flag = (SPLin.pWeightingFilt.isInitialized == 1);
    if (flag) {
      SPLin.pWeightingFilt.TunablePropsChanged = true;
    }
    SPLin.pWeightingFilt.pSampleRateDialog = 48000.0;
    SPLin.pWeightingFilt.matlabCodegenIsDeleted = false;
    SystemCore_setup(&SPLin.pWeightingFilt);
    SPLin.pMovIN.isInitialized = 0;
    SPLin.pMovIN.isInitialized = 0;
    SPLin.pMovLT.isInitialized = 0;
    SPLin.pMovLT.isInitialized = 0;
    SPLin.pMovIN.isSetupComplete = false;
    SPLin.pMovIN.isInitialized = 1;
    memset(&SPLin.pMovIN.pMem[0], 0, 96000U * sizeof(double));
    SPLin.pMovIN.pMemPtr = 0U;
    SPLin.pMovIN.isSetupComplete = true;
    SPLin.pMovLT.isSetupComplete = false;
    SPLin.pMovLT.isInitialized = 1;
    memset(&SPLin.pMovLT.pMem[0], 0, 96000U * sizeof(double));
    SPLin.pMovLT.pMemPtr = 0U;
    SPLin.pMovLT.isSetupComplete = true;
    ret = memcmp(&SPLin.TimeWeighting[0], &b[0], 4);
    if (ret == 0) {
      alpha = 0.125;
    } else {
      alpha = 1.0;
    }
    alpha = exp(-1.0 / (48000.0 * alpha));
    c_obj = &SPLin.pTimeWeightingFilt;
    SPLin.pTimeWeightingFilt.isInitialized = 0;
    SPLin.pTimeWeightingFilt.isInitialized = 0;
    /* System object Constructor function: dsp.SOSFilter */
    c_obj->cSFunObject.P0_ICRTP = 0.0;
    SPLin.pTimeWeightingFilt.matlabCodegenIsDeleted = false;
    SPLin.pTimeWeightingFilt.isSetupComplete = false;
    SPLin.pTimeWeightingFilt.isInitialized = 1;
    SPLin.pTimeWeightingFilt.isSetupComplete = true;
    SPLin.pTimeWeightingFiltNum[0] = 1.0 - alpha;
    SPLin.pTimeWeightingFiltNum[1] = 0.0;
    SPLin.pTimeWeightingFiltNum[2] = 0.0;
    SPLin.pTimeWeightingFiltDen[0] = 1.0;
    SPLin.pTimeWeightingFiltDen[1] = -alpha;
    SPLin.pTimeWeightingFiltDen[2] = 0.0;
    SPLin.pLeqHold = 0.0;
    SPLin.pLpeakHold = 0.0;
    SPLin.pLmaxHold = 0.0;
    SPLin.isSetupComplete = true;
    SPLin.TunablePropsChanged = false;
    if (SPLin.pMovIN.isInitialized == 1) {
      memset(&SPLin.pMovIN.pMem[0], 0, 96000U * sizeof(double));
      SPLin.pMovIN.pMemPtr = 0U;
    }
    if (SPLin.pMovLT.isInitialized == 1) {
      memset(&SPLin.pMovLT.pMem[0], 0, 96000U * sizeof(double));
      SPLin.pMovLT.pMemPtr = 0U;
    }
    if (SPLin.pTimeWeightingFilt.isInitialized == 1) {
      /* System object Initialization function: dsp.SOSFilter */
      SPLin.pTimeWeightingFilt.cSFunObject.W0_FILT_STATES[0] =
          SPLin.pTimeWeightingFilt.cSFunObject.P0_ICRTP;
      SPLin.pTimeWeightingFilt.cSFunObject.W0_FILT_STATES[1] =
          SPLin.pTimeWeightingFilt.cSFunObject.P0_ICRTP;
    }
    if (SPLin.pWeightingFilt.isInitialized == 1) {
      if (SPLin.pWeightingFilt.pFilter.isInitialized == 1) {
        /* System object Initialization function: dsp.SOSFilter */
        for (ret = 0; ret < 6; ret++) {
          SPLin.pWeightingFilt.pFilter.cSFunObject.W0_FILT_STATES[ret] =
              SPLin.pWeightingFilt.pFilter.cSFunObject.P0_ICRTP;
        }
      }
      weightingFilter_designFilter(&SPLin.pWeightingFilt);
    }
    SPLin.pCount = 0.0;
    SPLin.pLeqHold = rtMinusInf;
    SPLin.pLpeakHold = rtMinusInf;
    SPLin.pLmaxHold = rtMinusInf;
  }
  if (SPLin.TunablePropsChanged) {
    SPLin.TunablePropsChanged = false;
    flag = SPLin.tunablePropertyChanged[0];
    if (flag) {
      ret = memcmp(&SPLin.TimeWeighting[0], &b[0], 4);
      if (ret == 0) {
        alpha = 0.125;
      } else {
        alpha = 1.0;
      }
      alpha = exp(-1.0 / (48000.0 * alpha));
      SPLin.pTimeWeightingFiltNum[0] = 1.0 - alpha;
      SPLin.pTimeWeightingFiltNum[1] = 0.0;
      SPLin.pTimeWeightingFiltNum[2] = 0.0;
      SPLin.pTimeWeightingFiltDen[0] = 1.0;
      SPLin.pTimeWeightingFiltDen[1] = -alpha;
      SPLin.pTimeWeightingFiltDen[2] = 0.0;
    }
    SPLin.tunablePropertyChanged[0] = false;
    SPLin.tunablePropertyChanged[1] = false;
  }
  memcpy(&u[0], &frame[0], 256U * sizeof(double));
  obj = &SPLin.pWeightingFilt;
  if (SPLin.pWeightingFilt.isInitialized != 1) {
    SystemCore_setup(&SPLin.pWeightingFilt);
    if (obj->pFilter.isInitialized == 1) {
      /* System object Initialization function: dsp.SOSFilter */
      for (ret = 0; ret < 6; ret++) {
        SPLin.pWeightingFilt.pFilter.cSFunObject.W0_FILT_STATES[ret] =
            SPLin.pWeightingFilt.pFilter.cSFunObject.P0_ICRTP;
      }
    }
    weightingFilter_designFilter(&SPLin.pWeightingFilt);
  }
  if (SPLin.pWeightingFilt.TunablePropsChanged) {
    SPLin.pWeightingFilt.TunablePropsChanged = false;
    weightingFilter_designFilter(&SPLin.pWeightingFilt);
  }
  memcpy(&varargin_2[0], &SPLin.pWeightingFilt.pNumMatrix[0],
         9U * sizeof(double));
  memcpy(&varargin_3[0], &SPLin.pWeightingFilt.pDenMatrix[0],
         9U * sizeof(double));
  alpha = SPLin.pWeightingFilt.pScaleValues[0];
  varargin_4_idx_1 = SPLin.pWeightingFilt.pScaleValues[1];
  varargin_4_idx_2 = SPLin.pWeightingFilt.pScaleValues[2];
  varargin_4_idx_3 = SPLin.pWeightingFilt.pScaleValues[3];
  if (obj->pFilter.isInitialized != 1) {
    obj->pFilter.isSetupComplete = false;
    obj->pFilter.isInitialized = 1;
    obj->pFilter.isSetupComplete = true;
    /* System object Initialization function: dsp.SOSFilter */
    for (ret = 0; ret < 6; ret++) {
      SPLin.pWeightingFilt.pFilter.cSFunObject.W0_FILT_STATES[ret] =
          SPLin.pWeightingFilt.pFilter.cSFunObject.P0_ICRTP;
    }
  }
  memcpy(&varargin_1[0], &u[0], 256U * sizeof(double));
  b_obj = &obj->pFilter.cSFunObject;
  /* System object Outputs function: dsp.SOSFilter */
  d = varargin_2[0];
  d1 = varargin_2[3];
  d2 = varargin_2[6];
  d3 = varargin_2[1];
  d4 = varargin_2[4];
  d5 = varargin_2[7];
  d6 = varargin_2[2];
  d7 = varargin_2[5];
  d8 = varargin_2[8];
  d9 = varargin_3[3];
  d10 = varargin_3[6];
  d11 = varargin_3[4];
  d12 = varargin_3[7];
  d13 = varargin_3[5];
  d14 = varargin_3[8];
  for (ret = 0; ret < 256; ret++) {
    stageIn = alpha * varargin_1[ret];
    numAccum = b_obj->W0_FILT_STATES[0];
    stageOut = numAccum + d * stageIn;
    numAccum = b_obj->W0_FILT_STATES[1];
    b_obj->W0_FILT_STATES[0] = (numAccum + d1 * stageIn) - d9 * stageOut;
    b_obj->W0_FILT_STATES[1] = d2 * stageIn - d10 * stageOut;
    stageIn = varargin_4_idx_1 * stageOut;
    numAccum = b_obj->W0_FILT_STATES[2];
    stageOut = numAccum + d3 * stageIn;
    numAccum = b_obj->W0_FILT_STATES[3];
    b_obj->W0_FILT_STATES[2] = (numAccum + d4 * stageIn) - d11 * stageOut;
    b_obj->W0_FILT_STATES[3] = d5 * stageIn - d12 * stageOut;
    stageIn = varargin_4_idx_2 * stageOut;
    numAccum = b_obj->W0_FILT_STATES[4];
    stageOut = numAccum + d6 * stageIn;
    numAccum = b_obj->W0_FILT_STATES[5];
    b_obj->W0_FILT_STATES[4] = (numAccum + d7 * stageIn) - d13 * stageOut;
    b_obj->W0_FILT_STATES[5] = d8 * stageIn - d14 * stageOut;
    u[ret] = varargin_4_idx_3 * stageOut;
  }
  splMeter_computeSPL(&SPLin, u, varargin_1, varargout_2, varargout_3,
                      varargout_4);
  alpha = varargin_1[0];
  for (ret = 0; ret < 255; ret++) {
    alpha += varargin_1[ret + 1];
  }
  return alpha / 256.0;
}

/*
 * Arguments    : void
 * Return Type  : void
 */
void SPL_free(void)
{
  b_dspcodegen_SOSFilter *obj;
  dspcodegen_SOSFilter *c_obj;
  weightingFilter *b_obj;
  if (!SPLin.matlabCodegenIsDeleted) {
    SPLin.matlabCodegenIsDeleted = true;
    if (SPLin.isInitialized == 1) {
      SPLin.isInitialized = 2;
      if (SPLin.isSetupComplete) {
        if (SPLin.pMovLT.isInitialized == 1) {
          SPLin.pMovLT.isInitialized = 2;
        }
        if (SPLin.pMovIN.isInitialized == 1) {
          SPLin.pMovIN.isInitialized = 2;
        }
        if (SPLin.pTimeWeightingFilt.isInitialized == 1) {
          SPLin.pTimeWeightingFilt.isInitialized = 2;
        }
        b_obj = &SPLin.pWeightingFilt;
        if (SPLin.pWeightingFilt.isInitialized == 1) {
          SPLin.pWeightingFilt.isInitialized = 2;
          if (SPLin.pWeightingFilt.isSetupComplete) {
            if (b_obj->pFilter.isInitialized == 1) {
              b_obj->pFilter.isInitialized = 2;
            }
            SPLin.pWeightingFilt.pNumChannels = -1.0;
          }
        }
      }
    }
  }
  obj = &SPLin.pTimeWeightingFilt;
  if (!obj->matlabCodegenIsDeleted) {
    obj->matlabCodegenIsDeleted = true;
    if (obj->isInitialized == 1) {
      obj->isInitialized = 2;
    }
  }
  b_obj = &SPLin.pWeightingFilt;
  if (!b_obj->matlabCodegenIsDeleted) {
    b_obj->matlabCodegenIsDeleted = true;
    if (b_obj->isInitialized == 1) {
      b_obj->isInitialized = 2;
      if (b_obj->isSetupComplete) {
        if (b_obj->pFilter.isInitialized == 1) {
          b_obj->pFilter.isInitialized = 2;
        }
        b_obj->pNumChannels = -1.0;
      }
    }
  }
  c_obj = &SPLin.pWeightingFilt.pFilter;
  if (!c_obj->matlabCodegenIsDeleted) {
    c_obj->matlabCodegenIsDeleted = true;
    if (c_obj->isInitialized == 1) {
      c_obj->isInitialized = 2;
    }
  }
}

/*
 * Arguments    : void
 * Return Type  : void
 */
void SPL_init(void)
{
  SPLin_not_empty = false;
  SPLin.pWeightingFilt.pFilter.matlabCodegenIsDeleted = true;
  SPLin.pWeightingFilt.matlabCodegenIsDeleted = true;
  SPLin.pTimeWeightingFilt.matlabCodegenIsDeleted = true;
  SPLin.matlabCodegenIsDeleted = true;
}

/*
 * File trailer for SPL.c
 *
 * [EOF]
 */
