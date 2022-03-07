/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 * File: splMeter.h
 *
 * MATLAB Coder version            : 5.3
 * C/C++ source code generated on  : 20-Oct-2021 00:44:28
 */

#ifndef SPLMETER_H
#define SPLMETER_H

/* Include Files */
#include "SPL_internal_types.h"
#include "rtwtypes.h"
#include <stddef.h>
#include <stdlib.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Function Declarations */
void splMeter_computeSPL(splMeter *obj, double u[256], double LT[256],
                         double Leq[256], double Lpeak[256], double Lmax[256]);

#ifdef __cplusplus
}
#endif

#endif
/*
 * File trailer for splMeter.h
 *
 * [EOF]
 */
