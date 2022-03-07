/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 * File: casyi.c
 *
 * MATLAB Coder version            : 5.3
 * C/C++ source code generated on  : 20-Oct-2021 00:32:25
 */

/* Include Files */
#include "casyi.h"
#include "VAD_data.h"
#include "VAD_rtwutil.h"
#include "cospiAndSinpi.h"
#include "rt_nonfinite.h"
#include "rt_nonfinite.h"
#include <math.h>

/* Function Definitions */
/*
 * Arguments    : const creal_T z
 *                double fnu
 *                creal_T *y
 * Return Type  : int
 */
int casyi(const creal_T z, double fnu, creal_T *y)
{
  double aa;
  double absxi;
  double absxr;
  double aez;
  double ak;
  double ak1_im;
  double ak1_re;
  double b_re;
  double bb;
  double bk;
  double cs1_im;
  double cs1_re;
  double cs2_im;
  double cs2_re;
  double dk_im;
  double dk_re;
  double ez_im;
  double ez_re;
  double im;
  double p1_re;
  double re;
  double sgn;
  double sqk;
  double tmp_im;
  double tmp_re;
  int i;
  int nz;
  boolean_T errflag;
  boolean_T exitg1;
  nz = 0;
  if (z.im == 0.0) {
    ak1_re = 0.15915494309189535 / z.re;
    ak1_im = 0.0;
  } else if (z.re == 0.0) {
    ak1_re = 0.0;
    ak1_im = -(0.15915494309189535 / z.im);
  } else {
    ak1_im = fabs(z.re);
    absxi = fabs(z.im);
    if (ak1_im > absxi) {
      absxi = z.im / z.re;
      absxr = z.re + absxi * z.im;
      ak1_re = (absxi * 0.0 + 0.15915494309189535) / absxr;
      ak1_im = (0.0 - absxi * 0.15915494309189535) / absxr;
    } else if (absxi == ak1_im) {
      if (z.re > 0.0) {
        absxi = 0.5;
      } else {
        absxi = -0.5;
      }
      if (z.im > 0.0) {
        absxr = 0.5;
      } else {
        absxr = -0.5;
      }
      ak1_re = (0.15915494309189535 * absxi + 0.0 * absxr) / ak1_im;
      ak1_im = (0.0 * absxi - 0.15915494309189535 * absxr) / ak1_im;
    } else {
      absxi = z.re / z.im;
      absxr = z.im + absxi * z.re;
      ak1_re = absxi * 0.15915494309189535 / absxr;
      ak1_im = (absxi * 0.0 - 0.15915494309189535) / absxr;
    }
  }
  if (ak1_im == 0.0) {
    if (ak1_re < 0.0) {
      absxi = 0.0;
      ak1_re = sqrt(-ak1_re);
    } else {
      absxi = sqrt(ak1_re);
      ak1_re = 0.0;
    }
  } else if (ak1_re == 0.0) {
    if (ak1_im < 0.0) {
      absxi = sqrt(-ak1_im / 2.0);
      ak1_re = -absxi;
    } else {
      absxi = sqrt(ak1_im / 2.0);
      ak1_re = absxi;
    }
  } else if (rtIsNaN(ak1_re)) {
    absxi = ak1_re;
  } else if (rtIsNaN(ak1_im)) {
    absxi = ak1_im;
    ak1_re = ak1_im;
  } else if (rtIsInf(ak1_im)) {
    absxi = fabs(ak1_im);
    ak1_re = ak1_im;
  } else if (rtIsInf(ak1_re)) {
    if (ak1_re < 0.0) {
      absxi = 0.0;
      ak1_re = ak1_im * -ak1_re;
    } else {
      absxi = ak1_re;
      ak1_re = 0.0;
    }
  } else {
    absxr = fabs(ak1_re);
    absxi = fabs(ak1_im);
    if ((absxr > 4.4942328371557893E+307) ||
        (absxi > 4.4942328371557893E+307)) {
      absxr *= 0.5;
      absxi = rt_hypotd_snf(absxr, absxi * 0.5);
      if (absxi > absxr) {
        absxi = sqrt(absxi) * sqrt(absxr / absxi + 1.0);
      } else {
        absxi = sqrt(absxi) * 1.4142135623730951;
      }
    } else {
      absxi = sqrt((rt_hypotd_snf(absxr, absxi) + absxr) * 0.5);
    }
    if (ak1_re > 0.0) {
      ak1_re = 0.5 * (ak1_im / absxi);
    } else {
      if (ak1_im < 0.0) {
        ak1_re = -absxi;
      } else {
        ak1_re = absxi;
      }
      absxi = 0.5 * (ak1_im / ak1_re);
    }
  }
  if (fabs(z.re) > 700.92179369444591) {
    nz = -1;
    y->re = rtNaN;
    y->im = 0.0;
  } else {
    absxr = fnu + fnu;
    if (z.im == 0.0) {
      tmp_re = exp(z.re);
      tmp_im = 0.0;
    } else if (rtIsInf(z.im) && rtIsInf(z.re) && (z.re < 0.0)) {
      tmp_re = 0.0;
      tmp_im = 0.0;
    } else {
      ak1_im = exp(z.re / 2.0);
      tmp_re = ak1_im * (ak1_im * cos(z.im));
      tmp_im = ak1_im * (ak1_im * sin(z.im));
    }
    re = absxi * tmp_re - ak1_re * tmp_im;
    im = absxi * tmp_im + ak1_re * tmp_re;
    absxi = 0.0;
    if (absxr > 4.7170688552396617E-153) {
      absxi = absxr * absxr;
    }
    ez_re = 8.0 * z.re;
    ez_im = 8.0 * z.im;
    aez = 8.0 * rt_hypotd_snf(z.re, z.im);
    if (z.im != 0.0) {
      cospiAndSinpi(fnu - (double)(int)fnu, &bk, &p1_re);
      if (z.im < 0.0) {
        bk = -bk;
      }
      if ((int)fnu != 0) {
        bk = -bk;
      } else {
        p1_re = -p1_re;
      }
    } else {
      p1_re = 0.0;
      bk = 0.0;
    }
    sqk = absxi - 1.0;
    ak1_re = 2.2204460492503131E-16 / aez * fabs(absxi - 1.0);
    sgn = 1.0;
    cs1_re = 1.0;
    cs1_im = 0.0;
    cs2_re = 1.0;
    cs2_im = 0.0;
    tmp_re = 1.0;
    tmp_im = 0.0;
    ak = 0.0;
    aa = 1.0;
    bb = aez;
    dk_re = ez_re;
    dk_im = ez_im;
    errflag = true;
    i = 0;
    exitg1 = false;
    while ((!exitg1) && (i < 45)) {
      tmp_re *= sqk;
      tmp_im *= sqk;
      if (dk_im == 0.0) {
        if (tmp_im == 0.0) {
          b_re = tmp_re / dk_re;
          tmp_im = 0.0;
        } else if (tmp_re == 0.0) {
          b_re = 0.0;
          tmp_im /= dk_re;
        } else {
          b_re = tmp_re / dk_re;
          tmp_im /= dk_re;
        }
      } else if (dk_re == 0.0) {
        if (tmp_re == 0.0) {
          b_re = tmp_im / dk_im;
          tmp_im = 0.0;
        } else if (tmp_im == 0.0) {
          b_re = 0.0;
          tmp_im = -(tmp_re / dk_im);
        } else {
          b_re = tmp_im / dk_im;
          tmp_im = -(tmp_re / dk_im);
        }
      } else {
        ak1_im = fabs(dk_re);
        absxi = fabs(dk_im);
        if (ak1_im > absxi) {
          absxi = dk_im / dk_re;
          absxr = dk_re + absxi * dk_im;
          b_re = (tmp_re + absxi * tmp_im) / absxr;
          tmp_im = (tmp_im - absxi * tmp_re) / absxr;
        } else if (absxi == ak1_im) {
          if (dk_re > 0.0) {
            absxi = 0.5;
          } else {
            absxi = -0.5;
          }
          if (dk_im > 0.0) {
            absxr = 0.5;
          } else {
            absxr = -0.5;
          }
          b_re = (tmp_re * absxi + tmp_im * absxr) / ak1_im;
          tmp_im = (tmp_im * absxi - tmp_re * absxr) / ak1_im;
        } else {
          absxi = dk_re / dk_im;
          absxr = dk_im + absxi * dk_re;
          b_re = (absxi * tmp_re + tmp_im) / absxr;
          tmp_im = (absxi * tmp_im - tmp_re) / absxr;
        }
      }
      tmp_re = b_re;
      cs2_re += b_re;
      cs2_im += tmp_im;
      sgn = -sgn;
      cs1_re += b_re * sgn;
      cs1_im += tmp_im * sgn;
      dk_re += ez_re;
      dk_im += ez_im;
      aa = aa * fabs(sqk) / bb;
      bb += aez;
      ak += 8.0;
      sqk -= ak;
      if (aa <= ak1_re) {
        errflag = false;
        exitg1 = true;
      } else {
        i++;
      }
    }
    if (errflag) {
      nz = -2;
    } else {
      if (z.re + z.re < 700.92179369444591) {
        tmp_re = -2.0 * z.re;
        tmp_im = -2.0 * z.im;
        if (tmp_im == 0.0) {
          tmp_re = exp(tmp_re);
          tmp_im = 0.0;
        } else if (rtIsInf(tmp_im) && rtIsInf(tmp_re) && (tmp_re < 0.0)) {
          tmp_re = 0.0;
          tmp_im = 0.0;
        } else {
          ak1_im = exp(tmp_re / 2.0);
          tmp_re = ak1_im * (ak1_im * cos(tmp_im));
          tmp_im = ak1_im * (ak1_im * sin(tmp_im));
        }
        b_re = tmp_re * cs2_re - tmp_im * cs2_im;
        absxi = tmp_re * cs2_im + tmp_im * cs2_re;
        cs1_re += b_re * p1_re - absxi * bk;
        cs1_im += b_re * bk + absxi * p1_re;
      }
      y->re = cs1_re * re - cs1_im * im;
      y->im = cs1_re * im + cs1_im * re;
    }
  }
  return nz;
}

/*
 * File trailer for casyi.c
 *
 * [EOF]
 */
