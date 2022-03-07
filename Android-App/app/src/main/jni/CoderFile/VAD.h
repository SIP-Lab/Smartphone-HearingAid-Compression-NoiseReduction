/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 * File: VAD.h
 *
 * MATLAB Coder version            : 5.3
 * C/C++ source code generated on  : 20-Oct-2021 00:32:25
 */

#ifndef VAD_H
#define VAD_H

/* Include Files */
#include "rtwtypes.h"
#include <stddef.h>
#include <stdlib.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Function Declarations */
extern double VAD(const double frame[256]);

void VAD_free(void);

void VAD_init(void);

#ifdef __cplusplus
}
#endif

#endif
/*
 * File trailer for VAD.h
 *
 * [EOF]
 */
