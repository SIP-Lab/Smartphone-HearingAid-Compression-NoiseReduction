/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 * File: SPL.h
 *
 * MATLAB Coder version            : 5.3
 * C/C++ source code generated on  : 20-Oct-2021 00:44:28
 */

#ifndef SPL_H
#define SPL_H

/* Include Files */
#include "rtwtypes.h"
#include <stddef.h>
#include <stdlib.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Function Declarations */
extern double SPL(const double frame[256]);

void SPL_free(void);

void SPL_init(void);

#ifdef __cplusplus
}
#endif

#endif
/*
 * File trailer for SPL.h
 *
 * [EOF]
 */
