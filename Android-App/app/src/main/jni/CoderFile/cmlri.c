/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 * File: cmlri.c
 *
 * MATLAB Coder version            : 5.3
 * C/C++ source code generated on  : 20-Oct-2021 00:32:25
 */

/* Include Files */
#include "cmlri.h"
#include "VAD_data.h"
#include "VAD_rtwutil.h"
#include "gammaln.h"
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
int cmlri(const creal_T z, double fnu, creal_T *y)
{
  double ack;
  double ak;
  double az;
  double ck_im;
  double ck_re;
  double fixfnu;
  double flooraz;
  double fnf;
  double p1_im;
  double p1_re;
  double p2_im;
  double p2_re;
  double pt_im;
  double pt_re;
  double rho2;
  double rz_im;
  double rz_re;
  double s;
  double s_im;
  double tst;
  int i;
  int icounter;
  int itime;
  int kcounter;
  int nz;
  boolean_T earlyExit;
  boolean_T exitg1;
  boolean_T guard1 = false;
  nz = 0;
  az = rt_hypotd_snf(z.re, z.im);
  flooraz = floor(az);
  if (fnu < 0.0) {
    fixfnu = ceil(fnu);
  } else {
    fixfnu = floor(fnu);
  }
  if (z.im == 0.0) {
    ck_re = (flooraz + 1.0) / z.re;
    ck_im = 0.0;
    rz_re = 2.0 / z.re;
    rz_im = 0.0;
  } else if (z.re == 0.0) {
    ck_re = 0.0;
    ck_im = -((flooraz + 1.0) / z.im);
    rz_re = 0.0;
    rz_im = -(2.0 / z.im);
  } else {
    ack = fabs(z.re);
    rho2 = fabs(z.im);
    if (ack > rho2) {
      s = z.im / z.re;
      tst = z.re + s * z.im;
      ck_re = ((flooraz + 1.0) + s * 0.0) / tst;
      ck_im = (0.0 - s * (flooraz + 1.0)) / tst;
      s = z.im / z.re;
      tst = z.re + s * z.im;
      rz_re = (s * 0.0 + 2.0) / tst;
      rz_im = (0.0 - s * 2.0) / tst;
    } else {
      if (rho2 == ack) {
        if (z.re > 0.0) {
          s = 0.5;
        } else {
          s = -0.5;
        }
        if (z.im > 0.0) {
          tst = 0.5;
        } else {
          tst = -0.5;
        }
        ck_re = ((flooraz + 1.0) * s + 0.0 * tst) / ack;
        ck_im = (0.0 * s - (flooraz + 1.0) * tst) / ack;
      } else {
        s = z.re / z.im;
        tst = z.im + s * z.re;
        ck_re = s * (flooraz + 1.0) / tst;
        ck_im = (s * 0.0 - (flooraz + 1.0)) / tst;
      }
      if (rho2 == ack) {
        if (z.re > 0.0) {
          s = 0.5;
        } else {
          s = -0.5;
        }
        if (z.im > 0.0) {
          tst = 0.5;
        } else {
          tst = -0.5;
        }
        rz_re = (2.0 * s + 0.0 * tst) / ack;
        rz_im = (0.0 * s - 2.0 * tst) / ack;
      } else {
        s = z.re / z.im;
        tst = z.im + s * z.re;
        rz_re = s * 2.0 / tst;
        rz_im = (s * 0.0 - 2.0) / tst;
      }
    }
  }
  p1_re = 0.0;
  p1_im = 0.0;
  p2_re = 1.0;
  p2_im = 0.0;
  ack = ((flooraz + 1.0) + 1.0) / az;
  ack += sqrt(ack * ack - 1.0);
  rho2 = ack * ack;
  tst = (rho2 + rho2) / ((rho2 - 1.0) * (ack - 1.0)) / 2.2204460492503131E-16;
  ak = flooraz + 1.0;
  earlyExit = true;
  icounter = 1;
  i = 0;
  exitg1 = false;
  while ((!exitg1) && (i < 80)) {
    icounter++;
    pt_re = p2_re;
    pt_im = p2_im;
    ack = ck_re * p2_re - ck_im * p2_im;
    rho2 = ck_re * p2_im + ck_im * p2_re;
    p2_re = p1_re - ack;
    p2_im = p1_im - rho2;
    p1_re = pt_re;
    p1_im = pt_im;
    ck_re += rz_re;
    ck_im += rz_im;
    if (rt_hypotd_snf(p2_re, p2_im) > tst * ak * ak) {
      earlyExit = false;
      exitg1 = true;
    } else {
      ak++;
      i++;
    }
  }
  if (earlyExit) {
    nz = -2;
  } else {
    kcounter = 1;
    guard1 = false;
    if ((int)fixfnu >= (int)flooraz) {
      p1_re = 0.0;
      p1_im = 0.0;
      p2_re = 1.0;
      p2_im = 0.0;
      if (z.im == 0.0) {
        ck_re = ((double)(int)fixfnu + 1.0) / z.re;
        ck_im = 0.0;
      } else if (z.re == 0.0) {
        if ((double)(int)fixfnu + 1.0 == 0.0) {
          ck_re = 0.0 / z.im;
          ck_im = 0.0;
        } else {
          ck_re = 0.0;
          ck_im = -(((double)(int)fixfnu + 1.0) / z.im);
        }
      } else {
        ack = fabs(z.re);
        rho2 = fabs(z.im);
        if (ack > rho2) {
          s = z.im / z.re;
          tst = z.re + s * z.im;
          ck_re = (((double)(int)fixfnu + 1.0) + s * 0.0) / tst;
          ck_im = (0.0 - s * ((double)(int)fixfnu + 1.0)) / tst;
        } else if (rho2 == ack) {
          if (z.re > 0.0) {
            s = 0.5;
          } else {
            s = -0.5;
          }
          if (z.im > 0.0) {
            tst = 0.5;
          } else {
            tst = -0.5;
          }
          ck_re = (((double)(int)fixfnu + 1.0) * s + 0.0 * tst) / ack;
          ck_im = (0.0 * s - ((double)(int)fixfnu + 1.0) * tst) / ack;
        } else {
          s = z.re / z.im;
          tst = z.im + s * z.re;
          ck_re = s * ((double)(int)fixfnu + 1.0) / tst;
          ck_im = (s * 0.0 - ((double)(int)fixfnu + 1.0)) / tst;
        }
      }
      tst = sqrt(((double)(int)fixfnu + 1.0) / az / 2.2204460492503131E-16);
      itime = 1;
      earlyExit = true;
      i = 0;
      exitg1 = false;
      while ((!exitg1) && (i < 80)) {
        kcounter++;
        pt_re = p2_re;
        pt_im = p2_im;
        ack = ck_re * p2_re - ck_im * p2_im;
        rho2 = ck_re * p2_im + ck_im * p2_re;
        p2_re = p1_re - ack;
        p2_im = p1_im - rho2;
        p1_re = pt_re;
        p1_im = pt_im;
        ck_re += rz_re;
        ck_im += rz_im;
        rho2 = rt_hypotd_snf(p2_re, p2_im);
        if (rho2 >= tst * ak * ak) {
          if (itime == 2) {
            earlyExit = false;
            exitg1 = true;
          } else {
            ack = rt_hypotd_snf(ck_re, ck_im);
            s = ack + sqrt(ack * ack - 1.0);
            ack = rho2 / rt_hypotd_snf(pt_re, pt_im);
            if ((s <= ack) || rtIsNaN(ack)) {
              ack = s;
            }
            tst *= sqrt(ack / (ack * ack - 1.0));
            itime = 2;
            i++;
          }
        } else {
          i++;
        }
      }
      if (earlyExit) {
        nz = -2;
      } else {
        guard1 = true;
      }
    } else {
      guard1 = true;
    }
    if (guard1) {
      itime = icounter + (int)flooraz;
      icounter = kcounter + (int)fixfnu;
      if (itime >= icounter) {
        icounter = itime;
      }
      az = icounter;
      p1_re = 0.0;
      p1_im = 0.0;
      p2_re = 1.0020841800044864E-289;
      p2_im = 0.0;
      fnf = fnu - fixfnu;
      ak = fnf + fnf;
      s = ((double)icounter + ak) + 1.0;
      gammaln(&s);
      ack = (double)icounter + 1.0;
      gammaln(&ack);
      rho2 = ak + 1.0;
      gammaln(&rho2);
      tst = exp((s - ack) - rho2);
      flooraz = 0.0;
      s_im = 0.0;
      icounter -= (int)fixfnu;
      for (i = 0; i < icounter; i++) {
        pt_re = p2_re;
        pt_im = p2_im;
        rho2 = az + fnf;
        s = rho2 * rz_re;
        rho2 *= rz_im;
        ack = s * p2_re - rho2 * p2_im;
        rho2 = s * p2_im + rho2 * p2_re;
        p2_re = p1_re + ack;
        p2_im = p1_im + rho2;
        p1_re = pt_re;
        p1_im = pt_im;
        ack = tst * (1.0 - ak / (az + ak));
        flooraz += (ack + tst) * pt_re;
        s_im += (ack + tst) * pt_im;
        tst = ack;
        az--;
      }
      y->re = p2_re;
      y->im = p2_im;
      if ((int)fixfnu > 0) {
        pt_re = p2_re;
        pt_im = p2_im;
        s = (az + fnf) * rz_re;
        rho2 = (az + fnf) * rz_im;
        ack = s * p2_re - rho2 * p2_im;
        rho2 = s * p2_im + rho2 * p2_re;
        p2_re = p1_re + ack;
        p2_im = p1_im + rho2;
        rho2 = tst * (1.0 - ak / (az + ak)) + tst;
        flooraz += rho2 * pt_re;
        s_im += rho2 * pt_im;
      }
      if (rz_im == 0.0) {
        if (rz_re < 0.0) {
          ck_re = log(fabs(rz_re));
          ck_im = 3.1415926535897931;
        } else {
          ck_re = log(rz_re);
          ck_im = 0.0;
        }
      } else if ((fabs(rz_re) > 8.9884656743115785E+307) ||
                 (fabs(rz_im) > 8.9884656743115785E+307)) {
        ck_re =
            log(rt_hypotd_snf(rz_re / 2.0, rz_im / 2.0)) + 0.69314718055994529;
        ck_im = rt_atan2d_snf(rz_im, rz_re);
      } else {
        ck_re = log(rt_hypotd_snf(rz_re, rz_im));
        ck_im = rt_atan2d_snf(rz_im, rz_re);
      }
      rho2 = -fnf * ck_re - -0.0 * ck_im;
      ack = -fnf * ck_im + -0.0 * ck_re;
      s = fnf + 1.0;
      gammaln(&s);
      ck_re = (rho2 + z.re) - s;
      ck_im = ack + z.im;
      p2_re += flooraz;
      p2_im += s_im;
      p1_re = 1.0 / rt_hypotd_snf(p2_re, p2_im);
      if (ck_im == 0.0) {
        ck_re = exp(ck_re);
        ck_im = 0.0;
      } else if (rtIsInf(ck_im) && rtIsInf(ck_re) && (ck_re < 0.0)) {
        ck_re = 0.0;
        ck_im = 0.0;
      } else {
        rho2 = exp(ck_re / 2.0);
        ck_re = rho2 * (rho2 * cos(ck_im));
        ck_im = rho2 * (rho2 * sin(ck_im));
      }
      ack = ck_re * p1_re - ck_im * 0.0;
      ck_im = ck_re * 0.0 + ck_im * p1_re;
      rho2 = p2_re * p1_re + p2_im * 0.0;
      p2_im = p2_re * 0.0 - p2_im * p1_re;
      ck_re = ack * rho2 - ck_im * p2_im;
      ck_im = ack * p2_im + ck_im * rho2;
      ack = y->re * ck_im + y->im * ck_re;
      y->re = y->re * ck_re - y->im * ck_im;
      y->im = ack;
    }
  }
  return nz;
}

/*
 * File trailer for cmlri.c
 *
 * [EOF]
 */
