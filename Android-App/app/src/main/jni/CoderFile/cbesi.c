/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 * File: cbesi.c
 *
 * MATLAB Coder version            : 5.3
 * C/C++ source code generated on  : 20-Oct-2021 00:32:25
 */

/* Include Files */
#include "cbesi.h"
#include "VAD_rtwutil.h"
#include "casyi.h"
#include "cmlri.h"
#include "cospiAndSinpi.h"
#include "gammaln.h"
#include "rt_nonfinite.h"
#include "rt_nonfinite.h"
#include <math.h>

/* Function Definitions */
/*
 * Arguments    : const creal_T z
 *                double fnu
 *                creal_T *cy
 *                int *nz
 *                int *ierr
 * Return Type  : void
 */
void cbesi(const creal_T z, double fnu, creal_T *cy, int *nz, int *ierr)
{
  creal_T zn;
  double AZ;
  double acz;
  double ak;
  double ascle;
  double az_tmp;
  double b_atol;
  double coef_im;
  double coef_re;
  double crsc_re;
  double csgn_im;
  double csgn_re;
  double cz_im;
  double cz_re;
  double hz_im;
  double hz_re;
  double re;
  double rs;
  double s;
  double s1_im;
  double s1_re;
  int nw;
  boolean_T guard1 = false;
  boolean_T guard2 = false;
  boolean_T iflag;
  *ierr = 0;
  AZ = rt_hypotd_snf(z.re, z.im);
  if (AZ > 1.0737418235E+9) {
    *ierr = 4;
  } else if (AZ > 32767.999992370605) {
    *ierr = 3;
  }
  zn = z;
  csgn_re = 1.0;
  csgn_im = 0.0;
  if (z.re < 0.0) {
    zn.re = -z.re;
    zn.im = -z.im;
    cospiAndSinpi(0.0, &csgn_re, &csgn_im);
    if ((int)fnu == 1) {
      csgn_re = -csgn_re;
      csgn_im = -csgn_im;
    }
  }
  cy->re = 0.0;
  cy->im = 0.0;
  az_tmp = rt_hypotd_snf(zn.re, zn.im);
  guard1 = false;
  if ((az_tmp <= 2.0) || (az_tmp * az_tmp * 0.25 <= fnu + 1.0)) {
    nw = 0;
    if (az_tmp == 0.0) {
      if (fnu == 0.0) {
        cy->re = 1.0;
        cy->im = 0.0;
      }
    } else {
      crsc_re = 1.0;
      iflag = false;
      if (az_tmp < 2.2250738585072014E-305) {
        nw = 1;
        if (fnu == 0.0) {
          nw = 0;
          cy->re = 1.0;
          cy->im = 0.0;
        }
      } else {
        hz_re = 0.5 * zn.re;
        hz_im = 0.5 * zn.im;
        if (az_tmp > 4.7170688552396617E-153) {
          cz_re = hz_re * hz_re - hz_im * hz_im;
          AZ = hz_re * hz_im;
          cz_im = AZ + AZ;
          acz = rt_hypotd_snf(cz_re, cz_im);
        } else {
          cz_re = 0.0;
          cz_im = 0.0;
          acz = 0.0;
        }
        if (hz_im == 0.0) {
          if (hz_re < 0.0) {
            hz_re = log(fabs(hz_re));
            hz_im = 3.1415926535897931;
          } else {
            hz_re = log(hz_re);
            hz_im = 0.0;
          }
        } else if ((fabs(hz_re) > 8.9884656743115785E+307) ||
                   (fabs(hz_im) > 8.9884656743115785E+307)) {
          AZ = hz_re;
          hz_re = log(rt_hypotd_snf(hz_re / 2.0, hz_im / 2.0)) +
                  0.69314718055994529;
          hz_im = rt_atan2d_snf(hz_im, AZ);
        } else {
          AZ = hz_re;
          hz_re = log(rt_hypotd_snf(hz_re, hz_im));
          hz_im = rt_atan2d_snf(hz_im, AZ);
        }
        AZ = ((fnu + 1.0) - 1.0) + 1.0;
        gammaln(&AZ);
        hz_re = hz_re * ((fnu + 1.0) - 1.0) - AZ;
        hz_im *= (fnu + 1.0) - 1.0;
        if (hz_re > -700.92179369444591) {
          ascle = 0.0;
          if (hz_re <= -664.87164553371019) {
            iflag = true;
            crsc_re = 2.2204460492503131E-16;
            ascle = 1.0020841800044864E-289;
          }
          AZ = exp(hz_re);
          if (iflag) {
            AZ /= 2.2204460492503131E-16;
          }
          coef_re = AZ * cos(hz_im);
          coef_im = AZ * sin(hz_im);
          b_atol = 2.2204460492503131E-16 * acz / (((fnu + 1.0) - 1.0) + 1.0);
          s1_re = 1.0;
          s1_im = 0.0;
          if (!(acz < 2.2204460492503131E-16 * (fnu + 1.0))) {
            hz_re = 1.0;
            hz_im = 0.0;
            ak = (fnu + 1.0) + 2.0;
            s = fnu + 1.0;
            AZ = 2.0;
            do {
              rs = 1.0 / s;
              re = hz_re * cz_re - hz_im * cz_im;
              hz_im = hz_re * cz_im + hz_im * cz_re;
              hz_re = rs * re;
              hz_im *= rs;
              s1_re += hz_re;
              s1_im += hz_im;
              s += ak;
              ak += 2.0;
              AZ = AZ * acz * rs;
            } while (!!(AZ > b_atol));
          }
          hz_re = s1_re * coef_re - s1_im * coef_im;
          hz_im = s1_re * coef_im + s1_im * coef_re;
          guard2 = false;
          if (iflag) {
            AZ = fabs(hz_re);
            coef_re = fabs(hz_im);
            if (AZ > coef_re) {
              coef_im = coef_re;
              coef_re = AZ;
            } else {
              coef_im = AZ;
            }
            if ((!(coef_im <= ascle)) ||
                (!(coef_re < coef_im / 2.2204460492503131E-16))) {
              guard2 = true;
            }
          } else {
            guard2 = true;
          }
          if (guard2) {
            cy->re = hz_re * crsc_re - hz_im * 0.0;
            cy->im = hz_re * 0.0 + hz_im * crsc_re;
          }
        } else {
          nw = 1;
          if (acz > (fnu + 1.0) - 1.0) {
            nw = -1;
          }
        }
      }
    }
    if (nw < 0) {
      *nz = 1;
    } else {
      *nz = nw;
    }
    if ((1 - *nz != 0) && (nw < 0)) {
      guard1 = true;
    }
  } else {
    guard1 = true;
  }
  if (guard1) {
    if (az_tmp < 21.784271729432426) {
      nw = cmlri(zn, fnu, cy);
      if (nw < 0) {
        if (nw == -2) {
          *nz = -2;
        } else {
          *nz = -1;
        }
      } else {
        *nz = 0;
      }
    } else {
      nw = casyi(zn, fnu, cy);
      if (nw < 0) {
        if (nw == -2) {
          *nz = -2;
        } else {
          *nz = -1;
        }
      } else {
        *nz = 0;
      }
    }
  }
  if (*nz < 0) {
    if (*nz == -2) {
      *nz = 0;
      *ierr = 5;
    } else {
      *nz = 0;
      *ierr = 2;
    }
  } else if ((!(z.re >= 0.0)) && (*nz != 1)) {
    AZ = fabs(cy->re);
    coef_re = fabs(cy->im);
    if ((AZ >= coef_re) || rtIsNaN(coef_re)) {
      coef_re = AZ;
    }
    if (coef_re <= 1.0020841800044864E-289) {
      cy->re *= 4.503599627370496E+15;
      cy->im *= 4.503599627370496E+15;
      AZ = 2.2204460492503131E-16;
    } else {
      AZ = 1.0;
    }
    re = cy->re * csgn_re - cy->im * csgn_im;
    hz_im = cy->re * csgn_im + cy->im * csgn_re;
    cy->re = AZ * re;
    cy->im = AZ * hz_im;
  }
}

/*
 * File trailer for cbesi.c
 *
 * [EOF]
 */
