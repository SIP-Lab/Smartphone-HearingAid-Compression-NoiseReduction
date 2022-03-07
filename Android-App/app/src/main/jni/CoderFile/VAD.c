/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 * File: VAD.c
 *
 * MATLAB Coder version            : 5.3
 * C/C++ source code generated on  : 20-Oct-2021 00:32:25
 */

/* Include Files */
#include "VAD.h"
#include "FFTImplementationCallback.h"
#include "SpeechNoiseEstimator.h"
#include "SystemCore.h"
#include "VAD_data.h"
#include "VAD_initialize.h"
#include "VAD_internal_types.h"
#include "cbesi.h"
#include "rt_nonfinite.h"
#include "rt_nonfinite.h"
#include <math.h>
#include <string.h>

/* Type Definitions */
#ifndef typedef_voiceActivityDetector
#define typedef_voiceActivityDetector
typedef struct {
  boolean_T matlabCodegenIsDeleted;
  int isInitialized;
  boolean_T isSetupComplete;
  boolean_T TunablePropsChanged;
  double SilenceToSpeechProbability;
  double SpeechToSilenceProbability;
  audio_internal_SohnVAD pVAD;
} voiceActivityDetector;
#endif /* typedef_voiceActivityDetector */

/* Variable Definitions */
static voiceActivityDetector VADin;

static boolean_T VADin_not_empty;

/* Function Definitions */
/*
 * Arguments    : const double frame[256]
 * Return Type  : double
 */
double VAD(const double frame[256])
{
  static const double dv1[256] = {0.0,
                                  0.00015059065189787502,
                                  0.0006022718974137975,
                                  0.0013547716606548965,
                                  0.0024076366639015356,
                                  0.0037602327006450165,
                                  0.0054117450176094928,
                                  0.0073611788055293892,
                                  0.0096073597983847847,
                                  0.012148934980735715,
                                  0.014984373402728013,
                                  0.01811196710228008,
                                  0.021529832133895588,
                                  0.025235909703481663,
                                  0.029227967408489597,
                                  0.033503600582630522,
                                  0.038060233744356631,
                                  0.042895122148234655,
                                  0.048005353438278331,
                                  0.053387849402242338,
                                  0.059039367825822475,
                                  0.06495650444564427,
                                  0.071135694999863941,
                                  0.077573217375146442,
                                  0.084265193848727382,
                                  0.091207593424208144,
                                  0.098396234259677529,
                                  0.10582678618669683,
                                  0.1134947733186315,
                                  0.12139557674675772,
                                  0.12952443732252039,
                                  0.1378764585242665,
                                  0.14644660940672621,
                                  0.15522972763146653,
                                  0.16422052257649078,
                                  0.17341357852311157,
                                  0.18280335791817726,
                                  0.19238420470968659,
                                  0.20215034775378327,
                                  0.21209590429107733,
                                  0.22221488349019886,
                                  0.23250119005645137,
                                  0.24294862790338917,
                                  0.25355090388510793,
                                  0.2643016315870011,
                                  0.2751943351726967,
                                  0.2862224532848589,
                                  0.29737934299750507,
                                  0.30865828381745508,
                                  0.32005248173250589,
                                  0.33155507330389,
                                  0.34315912980055419,
                                  0.35485766137276886,
                                  0.36664362126255079,
                                  0.378509910048368,
                                  0.39044937992156514,
                                  0.40245483899193585,
                                  0.41451905561984931,
                                  0.42663476277231915,
                                  0.43879466240039189,
                                  0.45099142983521961,
                                  0.46321771820016627,
                                  0.47546616283629095,
                                  0.48772938573854385,
                                  0.49999999999999994,
                                  0.512270614261456,
                                  0.524533837163709,
                                  0.53678228179983367,
                                  0.54900857016478033,
                                  0.56120533759960811,
                                  0.57336523722768085,
                                  0.58548094438015064,
                                  0.5975451610080641,
                                  0.60955062007843486,
                                  0.62149008995163191,
                                  0.63335637873744921,
                                  0.645142338627231,
                                  0.6568408701994457,
                                  0.66844492669611,
                                  0.67994751826749411,
                                  0.69134171618254481,
                                  0.70262065700249487,
                                  0.71377754671514093,
                                  0.72480566482730335,
                                  0.73569836841299885,
                                  0.746449096114892,
                                  0.75705137209661078,
                                  0.76749880994354847,
                                  0.777785116509801,
                                  0.78790409570892272,
                                  0.79784965224621662,
                                  0.80761579529031335,
                                  0.81719664208182263,
                                  0.82658642147688832,
                                  0.83577947742350922,
                                  0.84477027236853353,
                                  0.85355339059327373,
                                  0.86212354147573333,
                                  0.87047556267747939,
                                  0.87860442325324239,
                                  0.88650522668136844,
                                  0.89417321381330317,
                                  0.90160376574032242,
                                  0.90879240657579174,
                                  0.91573480615127267,
                                  0.92242678262485356,
                                  0.928864305000136,
                                  0.93504349555435562,
                                  0.94096063217417747,
                                  0.94661215059775761,
                                  0.95199464656172172,
                                  0.95710487785176535,
                                  0.96193976625564337,
                                  0.96649639941736942,
                                  0.97077203259151035,
                                  0.97476409029651834,
                                  0.97847016786610441,
                                  0.98188803289772,
                                  0.985015626597272,
                                  0.98785106501926423,
                                  0.99039264020161522,
                                  0.99263882119447056,
                                  0.99458825498239056,
                                  0.996239767299355,
                                  0.99759236333609835,
                                  0.9986452283393451,
                                  0.9993977281025862,
                                  0.99984940934810207,
                                  1.0,
                                  0.99984940934810207,
                                  0.9993977281025862,
                                  0.9986452283393451,
                                  0.99759236333609835,
                                  0.996239767299355,
                                  0.99458825498239056,
                                  0.99263882119447056,
                                  0.99039264020161522,
                                  0.98785106501926423,
                                  0.985015626597272,
                                  0.98188803289772,
                                  0.97847016786610441,
                                  0.97476409029651834,
                                  0.97077203259151035,
                                  0.96649639941736942,
                                  0.96193976625564337,
                                  0.95710487785176535,
                                  0.95199464656172172,
                                  0.94661215059775761,
                                  0.94096063217417747,
                                  0.93504349555435562,
                                  0.928864305000136,
                                  0.92242678262485356,
                                  0.91573480615127267,
                                  0.90879240657579174,
                                  0.90160376574032242,
                                  0.89417321381330317,
                                  0.88650522668136844,
                                  0.87860442325324239,
                                  0.87047556267747939,
                                  0.86212354147573333,
                                  0.85355339059327373,
                                  0.84477027236853353,
                                  0.83577947742350922,
                                  0.82658642147688832,
                                  0.81719664208182263,
                                  0.80761579529031335,
                                  0.79784965224621662,
                                  0.78790409570892272,
                                  0.777785116509801,
                                  0.76749880994354847,
                                  0.75705137209661078,
                                  0.746449096114892,
                                  0.73569836841299885,
                                  0.72480566482730335,
                                  0.71377754671514093,
                                  0.70262065700249487,
                                  0.69134171618254481,
                                  0.67994751826749411,
                                  0.66844492669611,
                                  0.6568408701994457,
                                  0.645142338627231,
                                  0.63335637873744921,
                                  0.62149008995163191,
                                  0.60955062007843486,
                                  0.5975451610080641,
                                  0.58548094438015064,
                                  0.57336523722768085,
                                  0.56120533759960811,
                                  0.54900857016478033,
                                  0.53678228179983367,
                                  0.524533837163709,
                                  0.512270614261456,
                                  0.49999999999999994,
                                  0.48772938573854385,
                                  0.47546616283629095,
                                  0.46321771820016627,
                                  0.45099142983521961,
                                  0.43879466240039189,
                                  0.42663476277231915,
                                  0.41451905561984931,
                                  0.40245483899193585,
                                  0.39044937992156514,
                                  0.378509910048368,
                                  0.36664362126255079,
                                  0.35485766137276886,
                                  0.34315912980055419,
                                  0.33155507330389,
                                  0.32005248173250589,
                                  0.30865828381745508,
                                  0.29737934299750507,
                                  0.2862224532848589,
                                  0.2751943351726967,
                                  0.2643016315870011,
                                  0.25355090388510793,
                                  0.24294862790338917,
                                  0.23250119005645137,
                                  0.22221488349019886,
                                  0.21209590429107733,
                                  0.20215034775378327,
                                  0.19238420470968659,
                                  0.18280335791817726,
                                  0.17341357852311157,
                                  0.16422052257649078,
                                  0.15522972763146653,
                                  0.14644660940672621,
                                  0.1378764585242665,
                                  0.12952443732252039,
                                  0.12139557674675772,
                                  0.1134947733186315,
                                  0.10582678618669683,
                                  0.098396234259677529,
                                  0.091207593424208144,
                                  0.084265193848727382,
                                  0.077573217375146442,
                                  0.071135694999863941,
                                  0.06495650444564427,
                                  0.059039367825822475,
                                  0.053387849402242338,
                                  0.048005353438278331,
                                  0.042895122148234655,
                                  0.038060233744356631,
                                  0.033503600582630522,
                                  0.029227967408489597,
                                  0.025235909703481663,
                                  0.021529832133895588,
                                  0.01811196710228008,
                                  0.014984373402728013,
                                  0.012148934980735715,
                                  0.0096073597983847847,
                                  0.0073611788055293892,
                                  0.0054117450176094928,
                                  0.0037602327006450165,
                                  0.0024076366639015356,
                                  0.0013547716606548965,
                                  0.0006022718974137975,
                                  0.00015059065189787502};
  audio_internal_SohnVAD *obj;
  creal_T X[256];
  creal_T b_w[129];
  creal_T w;
  creal_T zd;
  double dv[256];
  double G[129];
  double Ysq[129];
  double b_gamma[129];
  double lambda_d[129];
  double xi_prev[129];
  double Gamma_log;
  double Lambda;
  double a01;
  double a10;
  double d;
  double p;
  double varargin_4;
  int i;
  int ierr;
  int k;
  boolean_T flag;
  if (!isInitialized_VAD) {
    VAD_initialize();
  }
  if (!VADin_not_empty) {
    VADin.SilenceToSpeechProbability = 0.2;
    VADin.SpeechToSilenceProbability = 0.1;
    VADin.isInitialized = 0;
    VADin.matlabCodegenIsDeleted = false;
    VADin_not_empty = true;
  }
  if (VADin.isInitialized != 1) {
    VADin.isSetupComplete = false;
    VADin.isInitialized = 1;
    Lambda = VADin.SilenceToSpeechProbability;
    varargin_4 = VADin.SpeechToSilenceProbability;
    VADin.pVAD.isInitialized = 0;
    VADin.pVAD.isInitialized = 0;
    flag = (VADin.pVAD.isInitialized == 1);
    if (flag) {
      VADin.pVAD.TunablePropsChanged = true;
    }
    VADin.pVAD.SilenceToSpeechProbability = Lambda;
    flag = (VADin.pVAD.isInitialized == 1);
    if (flag) {
      VADin.pVAD.TunablePropsChanged = true;
    }
    VADin.pVAD.SpeechToSilenceProbability = varargin_4;
    VADin.pVAD.matlabCodegenIsDeleted = false;
    SystemCore_Setup(&VADin.pVAD);
    VADin.isSetupComplete = true;
    VADin.TunablePropsChanged = false;
    obj = &VADin.pVAD;
    if (VADin.pVAD.isInitialized == 1) {
      if (obj->pSNE.isInitialized == 1) {
        c_SpeechNoiseEstimator_initiali(&obj->pSNE);
      }
      for (i = 0; i < 129; i++) {
        VADin.pVAD.pXi_prev[i] = 1.0;
      }
      VADin.pVAD.pGamma_log = 0.0;
    }
  }
  if (VADin.TunablePropsChanged) {
    VADin.TunablePropsChanged = false;
    flag = (VADin.pVAD.isInitialized == 1);
    if (flag) {
      VADin.pVAD.TunablePropsChanged = true;
    }
    VADin.pVAD.SilenceToSpeechProbability = VADin.SilenceToSpeechProbability;
    flag = (VADin.pVAD.isInitialized == 1);
    if (flag) {
      VADin.pVAD.TunablePropsChanged = true;
    }
    VADin.pVAD.SpeechToSilenceProbability = VADin.SpeechToSilenceProbability;
  }
  for (i = 0; i < 256; i++) {
    dv[i] = dv1[i] * frame[i];
  }
  c_FFTImplementationCallback_doH(dv, X);
  obj = &VADin.pVAD;
  if (VADin.pVAD.isInitialized != 1) {
    SystemCore_Setup(&VADin.pVAD);
    if (obj->pSNE.isInitialized == 1) {
      c_SpeechNoiseEstimator_initiali(&obj->pSNE);
    }
    for (i = 0; i < 129; i++) {
      VADin.pVAD.pXi_prev[i] = 1.0;
    }
    VADin.pVAD.pGamma_log = 0.0;
  }
  if (VADin.pVAD.TunablePropsChanged) {
    VADin.pVAD.TunablePropsChanged = false;
    VADin.pVAD.pSilenceToSpeechProbability =
        VADin.pVAD.SilenceToSpeechProbability;
    VADin.pVAD.pSpeechToSilenceProbability =
        VADin.pVAD.SpeechToSilenceProbability;
  }
  memcpy(&xi_prev[0], &VADin.pVAD.pXi_prev[0], 129U * sizeof(double));
  a01 = VADin.pVAD.pSilenceToSpeechProbability;
  a10 = VADin.pVAD.pSpeechToSilenceProbability;
  Gamma_log = VADin.pVAD.pGamma_log;
  for (i = 0; i < 129; i++) {
    varargin_4 = X[i].re;
    Lambda = X[i].im;
    Ysq[i] = varargin_4 * varargin_4 - Lambda * -Lambda;
  }
  if (obj->pSNE.isInitialized != 1) {
    obj->pSNE.isSetupComplete = false;
    obj->pSNE.isInitialized = 1;
    c_SpeechNoiseEstimator_initiali(&obj->pSNE);
    obj->pSNE.isSetupComplete = true;
    c_SpeechNoiseEstimator_initiali(&obj->pSNE);
  }
  SpeechNoiseEstimator_stepImpl(&obj->pSNE, Ysq, lambda_d);
  for (k = 0; k < 129; k++) {
    varargin_4 = Ysq[k] / lambda_d[k];
    if (!(varargin_4 <= 50.0)) {
      varargin_4 = 50.0;
    }
    if (!(varargin_4 >= 0.0001)) {
      varargin_4 = 0.0001;
    }
    b_gamma[k] = varargin_4;
    if (0.0 >= varargin_4 - 1.0) {
      Lambda = 0.0;
    } else {
      Lambda = varargin_4 - 1.0;
    }
    Ysq[k] = Lambda;
    Lambda = 0.9 * xi_prev[k] + 0.099999999999999978 * Lambda;
    d = Lambda + 1.0;
    Lambda = varargin_4 * Lambda / (Lambda + 1.0);
    xi_prev[k] = Lambda;
    d = log(d);
    d = Lambda - d;
    lambda_d[k] = d;
  }
  Lambda = lambda_d[0];
  for (k = 0; k < 128; k++) {
    Lambda += lambda_d[k + 1];
  }
  varargin_4 = exp(Gamma_log);
  Gamma_log = (log(a01 + (1.0 - a10) * varargin_4) -
               log((1.0 - a01) + a10 * varargin_4)) +
              (Lambda - 0.5 * (lambda_d[0] + lambda_d[128])) / 128.0;
  Lambda = exp(log(a10 / a01) + Gamma_log);
  p = Lambda / (Lambda + 1.0);
  zd.im = 0.0;
  for (k = 0; k < 129; k++) {
    Lambda = xi_prev[k];
    d = Lambda / 2.0;
    lambda_d[k] = d;
    G[k] = sqrt(Lambda);
    Ysq[k] = exp(-d);
    zd.re = d;
    if (rtIsNaN(d)) {
      w.re = rtNaN;
      w.im = 0.0;
    } else {
      cbesi(zd, 0.0, &w, &i, &ierr);
      if (ierr == 5) {
        w.re = rtNaN;
        w.im = 0.0;
      } else if (ierr == 2) {
        w.re = rtInf;
        w.im = 0.0;
      }
      if (d > 0.0) {
        Lambda = w.re;
        w.re = Lambda;
        w.im = 0.0;
      }
    }
    b_w[k] = w;
  }
  zd.im = 0.0;
  for (k = 0; k < 129; k++) {
    zd.re = lambda_d[k];
    if (rtIsNaN(zd.re)) {
      w.re = rtNaN;
    } else {
      cbesi(zd, 1.0, &w, &i, &ierr);
      if (ierr == 5) {
        w.re = rtNaN;
      } else if (ierr == 2) {
        w.re = rtInf;
      }
      if (zd.re > 0.0) {
        Lambda = w.re;
        w.re = Lambda;
      }
    }
    Lambda = xi_prev[k];
    Lambda = 0.88622692545275794 * G[k] / b_gamma[k] * Ysq[k] *
             ((Lambda + 1.0) * b_w[k].re + Lambda * w.re);
    G[k] = Lambda;
    lambda_d[k] = Lambda * Lambda;
  }
  for (i = 0; i < 129; i++) {
    VADin.pVAD.pXi_prev[i] = b_gamma[i] * lambda_d[i];
  }
  VADin.pVAD.pGamma_log = Gamma_log;
  return p;
}

/*
 * Arguments    : void
 * Return Type  : void
 */
void VAD_free(void)
{
  audio_internal_SohnVAD *obj;
  if (!VADin.matlabCodegenIsDeleted) {
    VADin.matlabCodegenIsDeleted = true;
    if (VADin.isInitialized == 1) {
      VADin.isInitialized = 2;
      if (VADin.isSetupComplete) {
        obj = &VADin.pVAD;
        if (VADin.pVAD.isInitialized == 1) {
          VADin.pVAD.isInitialized = 2;
          if (VADin.pVAD.isSetupComplete && (obj->pSNE.isInitialized == 1)) {
            obj->pSNE.isInitialized = 2;
          }
        }
      }
    }
  }
  obj = &VADin.pVAD;
  if (!obj->matlabCodegenIsDeleted) {
    obj->matlabCodegenIsDeleted = true;
    if (obj->isInitialized == 1) {
      obj->isInitialized = 2;
      if (obj->isSetupComplete && (obj->pSNE.isInitialized == 1)) {
        obj->pSNE.isInitialized = 2;
      }
    }
  }
}

/*
 * Arguments    : void
 * Return Type  : void
 */
void VAD_init(void)
{
  VADin_not_empty = false;
  VADin.pVAD.matlabCodegenIsDeleted = true;
  VADin.matlabCodegenIsDeleted = true;
}

/*
 * File trailer for VAD.c
 *
 * [EOF]
 */
