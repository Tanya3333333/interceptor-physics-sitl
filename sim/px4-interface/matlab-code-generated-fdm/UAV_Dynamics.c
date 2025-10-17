/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: UAV_Dynamics.c
 *
 * Code generated for Simulink model 'UAV_Dynamics'.
 *
 * Model version                  : 4.5
 * Simulink Coder version         : 23.2 (R2023b) 01-Aug-2023
 * C/C++ source code generated on : Fri Oct 10 10:35:15 2025
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: Intel->x86-64 (Windows64)
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#include "UAV_Dynamics.h"
#include "rtwtypes.h"
#include <math.h>
#include <emmintrin.h>
#include <string.h>
#include <stddef.h>
#include <float.h>
#define NumBitsPerChar                 8U

/* Private macros used by the generated code to access rtModel */
#ifndef rtmSetFirstInitCond
#define rtmSetFirstInitCond(rtm, val)  ((rtm)->Timing.firstInitCondFlag = (val))
#endif

#ifndef rtmIsFirstInitCond
#define rtmIsFirstInitCond(rtm)        ((rtm)->Timing.firstInitCondFlag)
#endif

#ifndef rtmIsMajorTimeStep
#define rtmIsMajorTimeStep(rtm)        (((rtm)->Timing.simTimeStep) == MAJOR_TIME_STEP)
#endif

#ifndef rtmIsMinorTimeStep
#define rtmIsMinorTimeStep(rtm)        (((rtm)->Timing.simTimeStep) == MINOR_TIME_STEP)
#endif

#ifndef rtmSetTPtr
#define rtmSetTPtr(rtm, val)           ((rtm)->Timing.t = (val))
#endif

/* Invariant block signals (default storage) */
const ConstB_UAV_Dynamics_T UAV_Dynamics_ConstB = {
  { 0.0, 0.0, 0.0 },                   /* '<S20>/1//2' */

  { 0.0, 0.0, 0.0 },                   /* '<S20>/sincos' */

  { 1.0, 1.0, 1.0 },                   /* '<S20>/sincos' */
  1.0,                                 /* '<S20>/q0' */
  0.0,                                 /* '<S20>/q1' */
  0.0,                                 /* '<S20>/q2' */
  0.0,                                 /* '<S20>/q3' */

  { 0.005, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.005, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.009, 0.0, 0.0, 0.0 },            /* '<S12>/Vector Concatenate' */

  { 0.005, 0.0, 0.0, 0.0, 0.005, 0.0, 0.0, 0.0, 0.009 },/* '<S11>/Selector' */

  { 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0 },/* '<S11>/Selector1' */

  { 0.005, 0.0, 0.0, 0.0, 0.005, 0.0, 0.0, 0.0, 0.009 }/* '<S11>/Selector2' */
};

/* Constant parameters (default storage) */
const ConstP_UAV_Dynamics_T UAV_Dynamics_ConstP = {
  /* Expression: [21.5 1.16 43.1]
   * Referenced by: '<S3>/IMU1'
   */
  { 21.5, 1.16, 43.1 },

  /* Pooled Parameter (Mixed Expressions)
   * Referenced by:
   *   '<S3>/IMU1'
   *   '<S7>/p,q,r '
   *   '<S7>/ub,vb,wb'
   *   '<S10>/Initial Euler Angles'
   *   '<S50>/Constant'
   *   '<S56>/Constant'
   */
  { 0.0, 0.0, 0.0 },

  /* Pooled Parameter (Expression: fractalcoef().Denominator)
   * Referenced by: '<S3>/IMU1'
   */
  { 1.0, -0.5 }
};

/* Block signals (default storage) */
B_UAV_Dynamics_T UAV_Dynamics_B;

/* Continuous states */
X_UAV_Dynamics_T UAV_Dynamics_X;

/* Disabled State Vector */
XDis_UAV_Dynamics_T UAV_Dynamics_XDis;

/* Block states (default storage) */
DW_UAV_Dynamics_T UAV_Dynamics_DW;

/* External inputs (root inport signals with default storage) */
ExtU_UAV_Dynamics_T UAV_Dynamics_U;

/* External outputs (root outports fed by signals with default storage) */
ExtY_UAV_Dynamics_T UAV_Dynamics_Y;

/* Real-time model */
static RT_MODEL_UAV_Dynamics_T UAV_Dynamics_M_;
RT_MODEL_UAV_Dynamics_T *const UAV_Dynamics_M = &UAV_Dynamics_M_;
extern real_T rt_atan2d_snf(real_T u0, real_T u1);
extern real_T rt_roundd_snf(real_T u);
extern void rt_mrdivide_U1d1x3_U2d_9vOrDY9Z(const real_T u0[3], const real_T u1
  [9], real_T y[3]);
extern real_T rt_remd_snf(real_T u0, real_T u1);
extern real_T rt_hypotd_snf(real_T u0, real_T u1);
extern real_T rt_powd_snf(real_T u0, real_T u1);
extern real_T rt_urand_Upu32_Yd_f_pw_snf(uint32_T *u);
extern real_T rt_nrand_Upu32_Yd_f_pw_snf(uint32_T *u);

/* private model entry point functions */
extern void UAV_Dynamics_derivatives(void);

/* Forward declaration for local functions */
static boolean_T UAV_Dynamics_isequal_p(const real_T varargin_1[3], const real_T
  varargin_2[3]);
static void imuSensor_set_MagneticFieldNED(fusion_simulink_imuSensor_UAV_T *obj,
  const real_T val[3]);
static boolean_T UAV_Dynamics_isequal(const real_T varargin_1[2], const real_T
  varargin_2[2]);
static void UAV_D_imuSensor_makeAccelParams(const
  fusion_simulink_imuSensor_UAV_T *obj, real_T *ap_MeasurementRange, real_T
  *ap_Resolution, real_T ap_ConstantBias[3], real_T ap_AxesMisalignment[9],
  real_T ap_NoiseDensity[3], real_T ap_BiasInstability[3], real_T ap_RandomWalk
  [3], real_T *ap_BiasInstabilityCoefficients_, real_T
  ap_BiasInstabilityCoefficient_0[2], char_T ap_NoiseType_Value[12], real_T
  ap_TemperatureBias[3], real_T ap_TemperatureScaleFactor[3]);
static void UAV_Dy_imuSensor_makeGyroParams(const
  fusion_simulink_imuSensor_UAV_T *obj, real_T *gp_MeasurementRange, real_T
  *gp_Resolution, real_T gp_ConstantBias[3], real_T gp_AxesMisalignment[9],
  real_T gp_NoiseDensity[3], real_T gp_BiasInstability[3], real_T gp_RandomWalk
  [3], real_T *gp_BiasInstabilityCoefficients_, real_T
  gp_BiasInstabilityCoefficient_0[2], char_T gp_NoiseType_Value[12], real_T
  gp_TemperatureBias[3], real_T gp_TemperatureScaleFactor[3], real_T
  gp_AccelerationBias[3]);
static void UAV_Dyn_imuSensor_makeMagParams(const
  fusion_simulink_imuSensor_UAV_T *obj, real_T *mp_MeasurementRange, real_T
  *mp_Resolution, real_T mp_ConstantBias[3], real_T mp_AxesMisalignment[9],
  real_T mp_NoiseDensity[3], real_T mp_BiasInstability[3], real_T mp_RandomWalk
  [3], real_T *mp_BiasInstabilityCoefficients_, real_T
  mp_BiasInstabilityCoefficient_0[2], char_T mp_NoiseType_Value[12], real_T
  mp_TemperatureBias[3], real_T mp_TemperatureScaleFactor[3]);
static void IMUSensorParameters_updateSyste(real_T obj_MeasurementRange, real_T
  obj_Resolution, const real_T obj_ConstantBias[3], const real_T
  obj_AxesMisalignment[9], const real_T obj_NoiseDensity[3], const real_T
  obj_BiasInstability[3], const real_T obj_RandomWalk[3], real_T
  obj_BiasInstabilityCoefficients, const real_T obj_BiasInstabilityCoefficien_0
  [2], const char_T obj_NoiseType_Value[12], const real_T obj_TemperatureBias[3],
  const real_T obj_TemperatureScaleFactor[3], g_fusion_internal_Acceleromet_T
  *sobj);
static void IMUSensorParameters_updateSys_p(real_T obj_MeasurementRange, real_T
  obj_Resolution, const real_T obj_ConstantBias[3], const real_T
  obj_AxesMisalignment[9], const real_T obj_NoiseDensity[3], const real_T
  obj_BiasInstability[3], const real_T obj_RandomWalk[3], real_T
  obj_BiasInstabilityCoefficients, const real_T obj_BiasInstabilityCoefficien_0
  [2], const char_T obj_NoiseType_Value[12], const real_T obj_TemperatureBias[3],
  const real_T obj_TemperatureScaleFactor[3], const real_T obj_AccelerationBias
  [3], h_fusion_internal_GyroscopeSi_T *sobj);
static void IMUSensorParameters_updateSy_ph(real_T obj_MeasurementRange, real_T
  obj_Resolution, const real_T obj_ConstantBias[3], const real_T
  obj_AxesMisalignment[9], const real_T obj_NoiseDensity[3], const real_T
  obj_BiasInstability[3], const real_T obj_RandomWalk[3], real_T
  obj_BiasInstabilityCoefficients, const real_T obj_BiasInstabilityCoefficien_0
  [2], const char_T obj_NoiseType_Value[12], const real_T obj_TemperatureBias[3],
  const real_T obj_TemperatureScaleFactor[3], i_fusion_internal_Magnetomete_T
  *sobj);
static boolean_T UAV_Dynamics_vectorAny(const boolean_T x_data[], const int32_T
  x_size[2]);
static void UAV_Dyn_genrand_uint32_vector_p(uint32_T mt[625], uint32_T u[2]);
static real_T UAV_Dynamics_genrandu_p(uint32_T mt[625]);
static void UAV_Dynamics_filter(real_T b, real_T a[2], const real_T x[3], const
  real_T zi[3], real_T y[3], real_T zf[3]);
static void UAV_Dynamics_SystemCore_step_p(g_fusion_internal_Acceleromet_T *obj,
  const real_T varargin_1[3], const real_T varargin_2[9], const real_T
  varargin_3[9], real_T varargout_1[3]);
static void UAV_Dynamics_SystemCore_step_ph(h_fusion_internal_GyroscopeSi_T *obj,
  const real_T varargin_1[3], const real_T varargin_2[3], const real_T
  varargin_3[9], const real_T varargin_4[9], real_T varargout_1[3]);
static void UAV_Dynamics_imuSensor_stepImpl(fusion_simulink_imuSensor_UAV_T *obj,
  const real_T la[3], const real_T av[3], const real_T o[4], real_T a[3], real_T
  g[3], real_T m[3]);
static void UAV_Dynamics_SystemCore_step(fusion_simulink_imuSensor_UAV_T *obj,
  const real_T varargin_1[3], const real_T varargin_2[3], const real_T
  varargin_3[4], real_T varargout_1[3], real_T varargout_2[3], real_T
  varargout_3[3]);
static void mt19937ar_genrand_uint32_vector(c_coder_internal_mt19937ar_UA_T *obj,
  uint32_T u[2]);
static boolean_T UAV_Dynamics_is_valid_state(const uint32_T mt[625]);
static real_T UAV_Dynamics_mt19937ar_genrandu(c_coder_internal_mt19937ar_UA_T
  *obj);
static real_T UAV_Dynamics_RandStream_rand_p(b_coder_internal_RandStream_U_T *s);
static real_T UA_RandStream_inversionGenrandn(b_coder_internal_RandStream_U_T *s);
static void UAV_Dynamics_RandStream_rand(b_coder_internal_RandStream_U_T *s,
  real_T u[2]);
static real_T UAV_Dy_RandStream_polarGenrandn(b_coder_internal_RandStream_U_T
  *rs);
static real_T UAV_RandStream_zigguratGenrandn(b_coder_internal_RandStream_U_T *s);
static real_T UAV_Dynami_mt19937ar_mtziggurat(c_coder_internal_mt19937ar_UA_T
  *obj);
static void GPSSensorBase_stepRandomStream(fusion_internal_simulink_gpsS_T *obj,
  real_T noise[3]);
static real_T UAV_Dynamics_cosd(real_T x);
static real_T UAV_Dynamics_sind(real_T x);
static void UAV_Dynamics_SystemCore_setup_p(fusion_simulink_imuSensor_UAV_T *obj);
static void UAV_Dyn_IMUSensorBase_resetImpl(fusion_simulink_imuSensor_UAV_T *obj);
static void UAV_Dynamics_SystemCore_setup(fusion_internal_simulink_gpsS_T *obj);
static void UAV_Dyn_GPSSensorBase_resetImpl(fusion_internal_simulink_gpsS_T *obj);
static real_T rtGetInf(void);
static real32_T rtGetInfF(void);
static real_T rtGetMinusInf(void);
static real32_T rtGetMinusInfF(void);
static real_T rtGetNaN(void);
static real32_T rtGetNaNF(void);

/*===========*
 * Constants *
 *===========*/
#define RT_PI                          3.14159265358979323846
#define RT_PIF                         3.1415927F
#define RT_LN_10                       2.30258509299404568402
#define RT_LN_10F                      2.3025851F
#define RT_LOG10E                      0.43429448190325182765
#define RT_LOG10EF                     0.43429449F
#define RT_E                           2.7182818284590452354
#define RT_EF                          2.7182817F

/*
 * UNUSED_PARAMETER(x)
 *   Used to specify that a function parameter (argument) is required but not
 *   accessed by the function body.
 */
#ifndef UNUSED_PARAMETER
#if defined(__LCC__)
#define UNUSED_PARAMETER(x)                                      /* do nothing */
#else

/*
 * This is the semi-ANSI standard way of indicating that an
 * unused function parameter is required.
 */
#define UNUSED_PARAMETER(x)            (void) (x)
#endif
#endif

#define NOT_USING_NONFINITE_LITERALS   1

extern real_T rtInf;
extern real_T rtMinusInf;
extern real_T rtNaN;
extern real32_T rtInfF;
extern real32_T rtMinusInfF;
extern real32_T rtNaNF;
static void rt_InitInfAndNaN(size_t realSize);
static boolean_T rtIsInf(real_T value);
static boolean_T rtIsInfF(real32_T value);
static boolean_T rtIsNaN(real_T value);
static boolean_T rtIsNaNF(real32_T value);
typedef struct {
  struct {
    uint32_T wordH;
    uint32_T wordL;
  } words;
} BigEndianIEEEDouble;

typedef struct {
  struct {
    uint32_T wordL;
    uint32_T wordH;
  } words;
} LittleEndianIEEEDouble;

typedef struct {
  union {
    real32_T wordLreal;
    uint32_T wordLuint;
  } wordL;
} IEEESingle;

real_T rtInf;
real_T rtMinusInf;
real_T rtNaN;
real32_T rtInfF;
real32_T rtMinusInfF;
real32_T rtNaNF;

/*
 * Initialize rtInf needed by the generated code.
 * Inf is initialized as non-signaling. Assumes IEEE.
 */
static real_T rtGetInf(void)
{
  size_t bitsPerReal = sizeof(real_T) * (NumBitsPerChar);
  real_T inf = 0.0;
  if (bitsPerReal == 32U) {
    inf = rtGetInfF();
  } else {
    union {
      LittleEndianIEEEDouble bitVal;
      real_T fltVal;
    } tmpVal;

    tmpVal.bitVal.words.wordH = 0x7FF00000U;
    tmpVal.bitVal.words.wordL = 0x00000000U;
    inf = tmpVal.fltVal;
  }

  return inf;
}

/*
 * Initialize rtInfF needed by the generated code.
 * Inf is initialized as non-signaling. Assumes IEEE.
 */
static real32_T rtGetInfF(void)
{
  IEEESingle infF;
  infF.wordL.wordLuint = 0x7F800000U;
  return infF.wordL.wordLreal;
}

/*
 * Initialize rtMinusInf needed by the generated code.
 * Inf is initialized as non-signaling. Assumes IEEE.
 */
static real_T rtGetMinusInf(void)
{
  size_t bitsPerReal = sizeof(real_T) * (NumBitsPerChar);
  real_T minf = 0.0;
  if (bitsPerReal == 32U) {
    minf = rtGetMinusInfF();
  } else {
    union {
      LittleEndianIEEEDouble bitVal;
      real_T fltVal;
    } tmpVal;

    tmpVal.bitVal.words.wordH = 0xFFF00000U;
    tmpVal.bitVal.words.wordL = 0x00000000U;
    minf = tmpVal.fltVal;
  }

  return minf;
}

/*
 * Initialize rtMinusInfF needed by the generated code.
 * Inf is initialized as non-signaling. Assumes IEEE.
 */
static real32_T rtGetMinusInfF(void)
{
  IEEESingle minfF;
  minfF.wordL.wordLuint = 0xFF800000U;
  return minfF.wordL.wordLreal;
}

/*
 * Initialize rtNaN needed by the generated code.
 * NaN is initialized as non-signaling. Assumes IEEE.
 */
static real_T rtGetNaN(void)
{
  size_t bitsPerReal = sizeof(real_T) * (NumBitsPerChar);
  real_T nan = 0.0;
  if (bitsPerReal == 32U) {
    nan = rtGetNaNF();
  } else {
    union {
      LittleEndianIEEEDouble bitVal;
      real_T fltVal;
    } tmpVal;

    tmpVal.bitVal.words.wordH = 0xFFF80000U;
    tmpVal.bitVal.words.wordL = 0x00000000U;
    nan = tmpVal.fltVal;
  }

  return nan;
}

/*
 * Initialize rtNaNF needed by the generated code.
 * NaN is initialized as non-signaling. Assumes IEEE.
 */
static real32_T rtGetNaNF(void)
{
  IEEESingle nanF = { { 0.0F } };

  nanF.wordL.wordLuint = 0xFFC00000U;
  return nanF.wordL.wordLreal;
}

/*
 * Initialize the rtInf, rtMinusInf, and rtNaN needed by the
 * generated code. NaN is initialized as non-signaling. Assumes IEEE.
 */
static void rt_InitInfAndNaN(size_t realSize)
{
  (void) (realSize);
  rtNaN = rtGetNaN();
  rtNaNF = rtGetNaNF();
  rtInf = rtGetInf();
  rtInfF = rtGetInfF();
  rtMinusInf = rtGetMinusInf();
  rtMinusInfF = rtGetMinusInfF();
}

/* Test if value is infinite */
static boolean_T rtIsInf(real_T value)
{
  return (boolean_T)((value==rtInf || value==rtMinusInf) ? 1U : 0U);
}

/* Test if single-precision value is infinite */
static boolean_T rtIsInfF(real32_T value)
{
  return (boolean_T)(((value)==rtInfF || (value)==rtMinusInfF) ? 1U : 0U);
}

/* Test if value is not a number */
static boolean_T rtIsNaN(real_T value)
{
  boolean_T result = (boolean_T) 0;
  size_t bitsPerReal = sizeof(real_T) * (NumBitsPerChar);
  if (bitsPerReal == 32U) {
    result = rtIsNaNF((real32_T)value);
  } else {
    union {
      LittleEndianIEEEDouble bitVal;
      real_T fltVal;
    } tmpVal;

    tmpVal.fltVal = value;
    result = (boolean_T)((tmpVal.bitVal.words.wordH & 0x7FF00000) == 0x7FF00000 &&
                         ( (tmpVal.bitVal.words.wordH & 0x000FFFFF) != 0 ||
                          (tmpVal.bitVal.words.wordL != 0) ));
  }

  return result;
}

/* Test if single-precision value is not a number */
static boolean_T rtIsNaNF(real32_T value)
{
  IEEESingle tmp;
  tmp.wordL.wordLreal = value;
  return (boolean_T)( (tmp.wordL.wordLuint & 0x7F800000) == 0x7F800000 &&
                     (tmp.wordL.wordLuint & 0x007FFFFF) != 0 );
}

/*
 * This function updates continuous states using the ODE4 fixed-step
 * solver algorithm
 */
static void rt_ertODEUpdateContinuousStates(RTWSolverInfo *si )
{
  time_T t = rtsiGetT(si);
  time_T tnew = rtsiGetSolverStopTime(si);
  time_T h = rtsiGetStepSize(si);
  real_T *x = rtsiGetContStates(si);
  ODE4_IntgData *id = (ODE4_IntgData *)rtsiGetSolverData(si);
  real_T *y = id->y;
  real_T *f0 = id->f[0];
  real_T *f1 = id->f[1];
  real_T *f2 = id->f[2];
  real_T *f3 = id->f[3];
  real_T temp;
  int_T i;
  int_T nXc = 21;
  rtsiSetSimTimeStep(si,MINOR_TIME_STEP);

  /* Save the state values at time t in y, we'll use x as ynew. */
  (void) memcpy(y, x,
                (uint_T)nXc*sizeof(real_T));

  /* Assumes that rtsiSetT and ModelOutputs are up-to-date */
  /* f0 = f(t,y) */
  rtsiSetdX(si, f0);
  UAV_Dynamics_derivatives();

  /* f1 = f(t + (h/2), y + (h/2)*f0) */
  temp = 0.5 * h;
  for (i = 0; i < nXc; i++) {
    x[i] = y[i] + (temp*f0[i]);
  }

  rtsiSetT(si, t + temp);
  rtsiSetdX(si, f1);
  UAV_Dynamics_step();
  UAV_Dynamics_derivatives();

  /* f2 = f(t + (h/2), y + (h/2)*f1) */
  for (i = 0; i < nXc; i++) {
    x[i] = y[i] + (temp*f1[i]);
  }

  rtsiSetdX(si, f2);
  UAV_Dynamics_step();
  UAV_Dynamics_derivatives();

  /* f3 = f(t + h, y + h*f2) */
  for (i = 0; i < nXc; i++) {
    x[i] = y[i] + (h*f2[i]);
  }

  rtsiSetT(si, tnew);
  rtsiSetdX(si, f3);
  UAV_Dynamics_step();
  UAV_Dynamics_derivatives();

  /* tnew = t + h
     ynew = y + (h/6)*(f0 + 2*f1 + 2*f2 + 2*f3) */
  temp = h / 6.0;
  for (i = 0; i < nXc; i++) {
    x[i] = y[i] + temp*(f0[i] + 2.0*f1[i] + 2.0*f2[i] + f3[i]);
  }

  rtsiSetSimTimeStep(si,MAJOR_TIME_STEP);
}

real_T rt_atan2d_snf(real_T u0, real_T u1)
{
  real_T y;
  if (rtIsNaN(u0) || rtIsNaN(u1)) {
    y = (rtNaN);
  } else if (rtIsInf(u0) && rtIsInf(u1)) {
    int32_T tmp;
    int32_T tmp_0;
    if (u0 > 0.0) {
      tmp = 1;
    } else {
      tmp = -1;
    }

    if (u1 > 0.0) {
      tmp_0 = 1;
    } else {
      tmp_0 = -1;
    }

    y = atan2(tmp, tmp_0);
  } else if (u1 == 0.0) {
    if (u0 > 0.0) {
      y = RT_PI / 2.0;
    } else if (u0 < 0.0) {
      y = -(RT_PI / 2.0);
    } else {
      y = 0.0;
    }
  } else {
    y = atan2(u0, u1);
  }

  return y;
}

static boolean_T UAV_Dynamics_isequal_p(const real_T varargin_1[3], const real_T
  varargin_2[3])
{
  int32_T b_k;
  boolean_T exitg1;
  boolean_T p;
  boolean_T p_0;
  p = false;
  p_0 = true;
  b_k = 0;
  exitg1 = false;
  while ((!exitg1) && (b_k < 3)) {
    if (!(varargin_1[b_k] == varargin_2[b_k])) {
      p_0 = false;
      exitg1 = true;
    } else {
      b_k++;
    }
  }

  if (p_0) {
    p = true;
  }

  return p;
}

static void imuSensor_set_MagneticFieldNED(fusion_simulink_imuSensor_UAV_T *obj,
  const real_T val[3])
{
  /* Start for MATLABSystem: '<S3>/IMU1' */
  if (obj->isInitialized == 1) {
    obj->TunablePropsChanged = true;
    obj->tunablePropertyChanged[2] = true;
  }

  obj->MagneticField[0] = val[0];
  obj->MagneticField[1] = val[1];
  obj->MagneticField[2] = val[2];

  /* End of Start for MATLABSystem: '<S3>/IMU1' */
}

static boolean_T UAV_Dynamics_isequal(const real_T varargin_1[2], const real_T
  varargin_2[2])
{
  int32_T b_k;
  boolean_T exitg1;
  boolean_T p;
  boolean_T p_0;
  p = false;
  p_0 = true;
  b_k = 0;
  exitg1 = false;
  while ((!exitg1) && (b_k < 2)) {
    if (!(varargin_1[b_k] == varargin_2[b_k])) {
      p_0 = false;
      exitg1 = true;
    } else {
      b_k++;
    }
  }

  if (p_0) {
    p = true;
  }

  return p;
}

static void UAV_D_imuSensor_makeAccelParams(const
  fusion_simulink_imuSensor_UAV_T *obj, real_T *ap_MeasurementRange, real_T
  *ap_Resolution, real_T ap_ConstantBias[3], real_T ap_AxesMisalignment[9],
  real_T ap_NoiseDensity[3], real_T ap_BiasInstability[3], real_T ap_RandomWalk
  [3], real_T *ap_BiasInstabilityCoefficients_, real_T
  ap_BiasInstabilityCoefficient_0[2], char_T ap_NoiseType_Value[12], real_T
  ap_TemperatureBias[3], real_T ap_TemperatureScaleFactor[3])
{
  real_T c[9];
  int32_T k;
  int8_T onesMask[9];
  static const char_T tmp_1[12] = { 'd', 'o', 'u', 'b', 'l', 'e', '-', 's', 'i',
    'd', 'e', 'd' };

  *ap_MeasurementRange = obj->AccelParamsMeasurementRange;
  *ap_Resolution = obj->AccelParamsResolution;
  ap_ConstantBias[0] = obj->AccelParamsConstantBias[0];
  ap_ConstantBias[1] = obj->AccelParamsConstantBias[1];
  ap_ConstantBias[2] = obj->AccelParamsConstantBias[2];
  memset(&ap_AxesMisalignment[0], 0, 9U * sizeof(real_T));
  ap_AxesMisalignment[0] = 1.0;
  ap_AxesMisalignment[4] = 1.0;
  ap_AxesMisalignment[8] = 1.0;
  for (k = 0; k < 9; k++) {
    onesMask[k] = (int8_T)(1 - (int32_T)ap_AxesMisalignment[k]);
  }

  for (k = 0; k < 3; k++) {
    real_T obj_0;
    int32_T c_tmp;

    /* Start for MATLABSystem: '<S3>/IMU1' */
    obj_0 = obj->AccelParamsAxesMisalignment[k];
    c[3 * k] = (real_T)onesMask[3 * k] * obj_0;
    c_tmp = 3 * k + 1;
    c[c_tmp] = (real_T)onesMask[c_tmp] * obj_0;
    c_tmp = 3 * k + 2;
    c[c_tmp] = (real_T)onesMask[c_tmp] * obj_0;
  }

  for (k = 0; k <= 6; k += 2) {
    __m128d tmp;
    __m128d tmp_0;

    /* Start for MATLABSystem: '<S3>/IMU1' */
    tmp = _mm_loadu_pd(&ap_AxesMisalignment[k]);
    tmp_0 = _mm_loadu_pd(&c[k]);
    _mm_storeu_pd(&ap_AxesMisalignment[k], _mm_add_pd(_mm_mul_pd(_mm_set1_pd
      (100.0), tmp), tmp_0));
  }

  for (k = 8; k < 9; k++) {
    /* Start for MATLABSystem: '<S3>/IMU1' */
    ap_AxesMisalignment[k] = 100.0 * ap_AxesMisalignment[k] + c[k];
  }

  ap_NoiseDensity[0] = obj->AccelParamsNoiseDensity;
  ap_BiasInstability[0] = obj->AccelParamsBiasInstability[0];
  ap_RandomWalk[0] = obj->AccelParamsRandomWalk[0];
  ap_NoiseDensity[1] = obj->AccelParamsNoiseDensity;
  ap_BiasInstability[1] = obj->AccelParamsBiasInstability[1];
  ap_RandomWalk[1] = obj->AccelParamsRandomWalk[1];
  ap_NoiseDensity[2] = obj->AccelParamsNoiseDensity;
  ap_BiasInstability[2] = obj->AccelParamsBiasInstability[2];
  ap_RandomWalk[2] = obj->AccelParamsRandomWalk[2];
  for (k = 0; k < 12; k++) {
    ap_NoiseType_Value[k] = tmp_1[k];
  }

  ap_TemperatureBias[0] = obj->AccelParamsTemperatureBias[0];
  ap_TemperatureScaleFactor[0] = obj->AccelParamsTemperatureScaleFactor[0];
  ap_TemperatureBias[1] = obj->AccelParamsTemperatureBias[1];
  ap_TemperatureScaleFactor[1] = obj->AccelParamsTemperatureScaleFactor[1];
  ap_TemperatureBias[2] = obj->AccelParamsTemperatureBias[2];
  ap_TemperatureScaleFactor[2] = obj->AccelParamsTemperatureScaleFactor[2];
  *ap_BiasInstabilityCoefficients_ = obj->AccelParamsBiasInstabilityNumerator;
  ap_BiasInstabilityCoefficient_0[0] =
    obj->AccelParamsBiasInstabilityDenominator[0];
  ap_BiasInstabilityCoefficient_0[1] =
    obj->AccelParamsBiasInstabilityDenominator[1];
}

static void UAV_Dy_imuSensor_makeGyroParams(const
  fusion_simulink_imuSensor_UAV_T *obj, real_T *gp_MeasurementRange, real_T
  *gp_Resolution, real_T gp_ConstantBias[3], real_T gp_AxesMisalignment[9],
  real_T gp_NoiseDensity[3], real_T gp_BiasInstability[3], real_T gp_RandomWalk
  [3], real_T *gp_BiasInstabilityCoefficients_, real_T
  gp_BiasInstabilityCoefficient_0[2], char_T gp_NoiseType_Value[12], real_T
  gp_TemperatureBias[3], real_T gp_TemperatureScaleFactor[3], real_T
  gp_AccelerationBias[3])
{
  real_T c[9];
  int32_T k;
  int8_T onesMask[9];
  static const char_T tmp_1[12] = { 'd', 'o', 'u', 'b', 'l', 'e', '-', 's', 'i',
    'd', 'e', 'd' };

  *gp_MeasurementRange = obj->GyroParamsMeasurementRange;
  *gp_Resolution = obj->GyroParamsResolution;
  gp_ConstantBias[0] = obj->GyroParamsConstantBias[0];
  gp_ConstantBias[1] = obj->GyroParamsConstantBias[1];
  gp_ConstantBias[2] = obj->GyroParamsConstantBias[2];
  memset(&gp_AxesMisalignment[0], 0, 9U * sizeof(real_T));
  gp_AxesMisalignment[0] = 1.0;
  gp_AxesMisalignment[4] = 1.0;
  gp_AxesMisalignment[8] = 1.0;
  for (k = 0; k < 9; k++) {
    onesMask[k] = (int8_T)(1 - (int32_T)gp_AxesMisalignment[k]);
  }

  for (k = 0; k < 3; k++) {
    real_T obj_0;
    int32_T c_tmp;

    /* Start for MATLABSystem: '<S3>/IMU1' */
    obj_0 = obj->GyroParamsAxesMisalignment[k];
    c[3 * k] = (real_T)onesMask[3 * k] * obj_0;
    c_tmp = 3 * k + 1;
    c[c_tmp] = (real_T)onesMask[c_tmp] * obj_0;
    c_tmp = 3 * k + 2;
    c[c_tmp] = (real_T)onesMask[c_tmp] * obj_0;
  }

  for (k = 0; k <= 6; k += 2) {
    __m128d tmp;
    __m128d tmp_0;

    /* Start for MATLABSystem: '<S3>/IMU1' */
    tmp = _mm_loadu_pd(&gp_AxesMisalignment[k]);
    tmp_0 = _mm_loadu_pd(&c[k]);
    _mm_storeu_pd(&gp_AxesMisalignment[k], _mm_add_pd(_mm_mul_pd(_mm_set1_pd
      (100.0), tmp), tmp_0));
  }

  for (k = 8; k < 9; k++) {
    /* Start for MATLABSystem: '<S3>/IMU1' */
    gp_AxesMisalignment[k] = 100.0 * gp_AxesMisalignment[k] + c[k];
  }

  gp_NoiseDensity[0] = obj->GyroParamsNoiseDensity;
  gp_BiasInstability[0] = obj->GyroParamsBiasInstability[0];
  gp_RandomWalk[0] = obj->GyroParamsRandomWalk[0];
  gp_NoiseDensity[1] = obj->GyroParamsNoiseDensity;
  gp_BiasInstability[1] = obj->GyroParamsBiasInstability[1];
  gp_RandomWalk[1] = obj->GyroParamsRandomWalk[1];
  gp_NoiseDensity[2] = obj->GyroParamsNoiseDensity;
  gp_BiasInstability[2] = obj->GyroParamsBiasInstability[2];
  gp_RandomWalk[2] = obj->GyroParamsRandomWalk[2];
  for (k = 0; k < 12; k++) {
    gp_NoiseType_Value[k] = tmp_1[k];
  }

  gp_TemperatureBias[0] = obj->GyroParamsTemperatureBias[0];
  gp_TemperatureScaleFactor[0] = obj->GyroParamsTemperatureScaleFactor[0];
  gp_AccelerationBias[0] = obj->GyroParamsAccelerationBias;
  gp_TemperatureBias[1] = obj->GyroParamsTemperatureBias[1];
  gp_TemperatureScaleFactor[1] = obj->GyroParamsTemperatureScaleFactor[1];
  gp_AccelerationBias[1] = obj->GyroParamsAccelerationBias;
  gp_TemperatureBias[2] = obj->GyroParamsTemperatureBias[2];
  gp_TemperatureScaleFactor[2] = obj->GyroParamsTemperatureScaleFactor[2];
  gp_AccelerationBias[2] = obj->GyroParamsAccelerationBias;
  *gp_BiasInstabilityCoefficients_ = obj->GyroParamsBiasInstabilityNumerator;
  gp_BiasInstabilityCoefficient_0[0] = obj->
    GyroParamsBiasInstabilityDenominator[0];
  gp_BiasInstabilityCoefficient_0[1] = obj->
    GyroParamsBiasInstabilityDenominator[1];
}

static void UAV_Dyn_imuSensor_makeMagParams(const
  fusion_simulink_imuSensor_UAV_T *obj, real_T *mp_MeasurementRange, real_T
  *mp_Resolution, real_T mp_ConstantBias[3], real_T mp_AxesMisalignment[9],
  real_T mp_NoiseDensity[3], real_T mp_BiasInstability[3], real_T mp_RandomWalk
  [3], real_T *mp_BiasInstabilityCoefficients_, real_T
  mp_BiasInstabilityCoefficient_0[2], char_T mp_NoiseType_Value[12], real_T
  mp_TemperatureBias[3], real_T mp_TemperatureScaleFactor[3])
{
  real_T c[9];
  int32_T k;
  int8_T onesMask[9];
  static const char_T tmp_1[12] = { 'd', 'o', 'u', 'b', 'l', 'e', '-', 's', 'i',
    'd', 'e', 'd' };

  *mp_MeasurementRange = obj->MagParamsMeasurementRange;
  *mp_Resolution = obj->MagParamsResolution;
  mp_ConstantBias[0] = obj->MagParamsConstantBias[0];
  mp_ConstantBias[1] = obj->MagParamsConstantBias[1];
  mp_ConstantBias[2] = obj->MagParamsConstantBias[2];
  memset(&mp_AxesMisalignment[0], 0, 9U * sizeof(real_T));
  mp_AxesMisalignment[0] = 1.0;
  mp_AxesMisalignment[4] = 1.0;
  mp_AxesMisalignment[8] = 1.0;
  for (k = 0; k < 9; k++) {
    onesMask[k] = (int8_T)(1 - (int32_T)mp_AxesMisalignment[k]);
  }

  for (k = 0; k < 3; k++) {
    real_T obj_0;
    int32_T c_tmp;

    /* Start for MATLABSystem: '<S3>/IMU1' */
    obj_0 = obj->MagParamsAxesMisalignment[k];
    c[3 * k] = (real_T)onesMask[3 * k] * obj_0;
    c_tmp = 3 * k + 1;
    c[c_tmp] = (real_T)onesMask[c_tmp] * obj_0;
    c_tmp = 3 * k + 2;
    c[c_tmp] = (real_T)onesMask[c_tmp] * obj_0;
  }

  for (k = 0; k <= 6; k += 2) {
    __m128d tmp;
    __m128d tmp_0;

    /* Start for MATLABSystem: '<S3>/IMU1' */
    tmp = _mm_loadu_pd(&mp_AxesMisalignment[k]);
    tmp_0 = _mm_loadu_pd(&c[k]);
    _mm_storeu_pd(&mp_AxesMisalignment[k], _mm_add_pd(_mm_mul_pd(_mm_set1_pd
      (100.0), tmp), tmp_0));
  }

  for (k = 8; k < 9; k++) {
    /* Start for MATLABSystem: '<S3>/IMU1' */
    mp_AxesMisalignment[k] = 100.0 * mp_AxesMisalignment[k] + c[k];
  }

  mp_NoiseDensity[0] = obj->MagParamsNoiseDensity;
  mp_BiasInstability[0] = obj->MagParamsBiasInstability[0];
  mp_RandomWalk[0] = obj->MagParamsRandomWalk[0];
  mp_NoiseDensity[1] = obj->MagParamsNoiseDensity;
  mp_BiasInstability[1] = obj->MagParamsBiasInstability[1];
  mp_RandomWalk[1] = obj->MagParamsRandomWalk[1];
  mp_NoiseDensity[2] = obj->MagParamsNoiseDensity;
  mp_BiasInstability[2] = obj->MagParamsBiasInstability[2];
  mp_RandomWalk[2] = obj->MagParamsRandomWalk[2];
  for (k = 0; k < 12; k++) {
    mp_NoiseType_Value[k] = tmp_1[k];
  }

  mp_TemperatureBias[0] = obj->MagParamsTemperatureBias[0];
  mp_TemperatureScaleFactor[0] = obj->MagParamsTemperatureScaleFactor[0];
  mp_TemperatureBias[1] = obj->MagParamsTemperatureBias[1];
  mp_TemperatureScaleFactor[1] = obj->MagParamsTemperatureScaleFactor[1];
  mp_TemperatureBias[2] = obj->MagParamsTemperatureBias[2];
  mp_TemperatureScaleFactor[2] = obj->MagParamsTemperatureScaleFactor[2];
  *mp_BiasInstabilityCoefficients_ = obj->MagParamsBiasInstabilityNumerator;
  mp_BiasInstabilityCoefficient_0[0] = obj->MagParamsBiasInstabilityDenominator
    [0];
  mp_BiasInstabilityCoefficient_0[1] = obj->MagParamsBiasInstabilityDenominator
    [1];
}

static void IMUSensorParameters_updateSyste(real_T obj_MeasurementRange, real_T
  obj_Resolution, const real_T obj_ConstantBias[3], const real_T
  obj_AxesMisalignment[9], const real_T obj_NoiseDensity[3], const real_T
  obj_BiasInstability[3], const real_T obj_RandomWalk[3], real_T
  obj_BiasInstabilityCoefficients, const real_T obj_BiasInstabilityCoefficien_0
  [2], const char_T obj_NoiseType_Value[12], const real_T obj_TemperatureBias[3],
  const real_T obj_TemperatureScaleFactor[3], g_fusion_internal_Acceleromet_T
  *sobj)
{
  int32_T i;

  /* Start for MATLABSystem: '<S3>/IMU1' */
  if (sobj->isInitialized == 1) {
    sobj->TunablePropsChanged = true;
    sobj->tunablePropertyChanged[0] = true;
  }

  sobj->MeasurementRange = obj_MeasurementRange;

  /* Start for MATLABSystem: '<S3>/IMU1' */
  if (sobj->isInitialized == 1) {
    sobj->TunablePropsChanged = true;
    sobj->tunablePropertyChanged[1] = true;
  }

  sobj->Resolution = obj_Resolution;

  /* Start for MATLABSystem: '<S3>/IMU1' */
  if (sobj->isInitialized == 1) {
    sobj->TunablePropsChanged = true;
    sobj->tunablePropertyChanged[2] = true;
  }

  sobj->ConstantBias[0] = obj_ConstantBias[0];
  sobj->ConstantBias[1] = obj_ConstantBias[1];
  sobj->ConstantBias[2] = obj_ConstantBias[2];

  /* Start for MATLABSystem: '<S3>/IMU1' */
  if (sobj->isInitialized == 1) {
    sobj->TunablePropsChanged = true;
    sobj->tunablePropertyChanged[3] = true;
  }

  memcpy(&sobj->AxesMisalignment[0], &obj_AxesMisalignment[0], 9U * sizeof
         (real_T));

  /* Start for MATLABSystem: '<S3>/IMU1' */
  if (sobj->isInitialized == 1) {
    sobj->TunablePropsChanged = true;
    sobj->tunablePropertyChanged[4] = true;
  }

  sobj->NoiseDensity[0] = obj_NoiseDensity[0];
  sobj->NoiseDensity[1] = obj_NoiseDensity[1];
  sobj->NoiseDensity[2] = obj_NoiseDensity[2];

  /* Start for MATLABSystem: '<S3>/IMU1' */
  if (sobj->isInitialized == 1) {
    sobj->TunablePropsChanged = true;
    sobj->tunablePropertyChanged[5] = true;
  }

  sobj->BiasInstability[0] = obj_BiasInstability[0];
  sobj->BiasInstability[1] = obj_BiasInstability[1];
  sobj->BiasInstability[2] = obj_BiasInstability[2];

  /* Start for MATLABSystem: '<S3>/IMU1' */
  if (sobj->isInitialized == 1) {
    sobj->TunablePropsChanged = true;
    sobj->tunablePropertyChanged[6] = true;
  }

  sobj->RandomWalk[0] = obj_RandomWalk[0];
  sobj->RandomWalk[1] = obj_RandomWalk[1];
  sobj->RandomWalk[2] = obj_RandomWalk[2];

  /* Start for MATLABSystem: '<S3>/IMU1' */
  if (sobj->isInitialized == 1) {
    sobj->TunablePropsChanged = true;
    sobj->tunablePropertyChanged[7] = true;
  }

  sobj->BiasInstabilityCoefficients.Numerator = obj_BiasInstabilityCoefficients;
  sobj->BiasInstabilityCoefficients.Denominator[0] =
    obj_BiasInstabilityCoefficien_0[0];
  sobj->BiasInstabilityCoefficients.Denominator[1] =
    obj_BiasInstabilityCoefficien_0[1];
  if (sobj->isInitialized == 1) {
    sobj->TunablePropsChanged = true;
    sobj->tunablePropertyChanged[8] = true;
  }

  for (i = 0; i < 12; i++) {
    sobj->NoiseType.Value[i] = obj_NoiseType_Value[i];
  }

  /* Start for MATLABSystem: '<S3>/IMU1' */
  if (sobj->isInitialized == 1) {
    sobj->TunablePropsChanged = true;
    sobj->tunablePropertyChanged[9] = true;
  }

  sobj->TemperatureBias[0] = obj_TemperatureBias[0];
  sobj->TemperatureBias[1] = obj_TemperatureBias[1];
  sobj->TemperatureBias[2] = obj_TemperatureBias[2];

  /* Start for MATLABSystem: '<S3>/IMU1' */
  if (sobj->isInitialized == 1) {
    sobj->TunablePropsChanged = true;
    sobj->tunablePropertyChanged[10] = true;
  }

  sobj->TemperatureScaleFactor[0] = obj_TemperatureScaleFactor[0];
  sobj->TemperatureScaleFactor[1] = obj_TemperatureScaleFactor[1];
  sobj->TemperatureScaleFactor[2] = obj_TemperatureScaleFactor[2];
}

static void IMUSensorParameters_updateSys_p(real_T obj_MeasurementRange, real_T
  obj_Resolution, const real_T obj_ConstantBias[3], const real_T
  obj_AxesMisalignment[9], const real_T obj_NoiseDensity[3], const real_T
  obj_BiasInstability[3], const real_T obj_RandomWalk[3], real_T
  obj_BiasInstabilityCoefficients, const real_T obj_BiasInstabilityCoefficien_0
  [2], const char_T obj_NoiseType_Value[12], const real_T obj_TemperatureBias[3],
  const real_T obj_TemperatureScaleFactor[3], const real_T obj_AccelerationBias
  [3], h_fusion_internal_GyroscopeSi_T *sobj)
{
  int32_T i;

  /* Start for MATLABSystem: '<S3>/IMU1' */
  if (sobj->isInitialized == 1) {
    sobj->TunablePropsChanged = true;
    sobj->tunablePropertyChanged[0] = true;
  }

  sobj->AccelerationBias[0] = obj_AccelerationBias[0];
  sobj->AccelerationBias[1] = obj_AccelerationBias[1];
  sobj->AccelerationBias[2] = obj_AccelerationBias[2];
  if (sobj->isInitialized == 1) {
    sobj->TunablePropsChanged = true;
    sobj->tunablePropertyChanged[1] = true;
  }

  sobj->MeasurementRange = obj_MeasurementRange;

  /* Start for MATLABSystem: '<S3>/IMU1' */
  if (sobj->isInitialized == 1) {
    sobj->TunablePropsChanged = true;
    sobj->tunablePropertyChanged[2] = true;
  }

  sobj->Resolution = obj_Resolution;

  /* Start for MATLABSystem: '<S3>/IMU1' */
  if (sobj->isInitialized == 1) {
    sobj->TunablePropsChanged = true;
    sobj->tunablePropertyChanged[3] = true;
  }

  sobj->ConstantBias[0] = obj_ConstantBias[0];
  sobj->ConstantBias[1] = obj_ConstantBias[1];
  sobj->ConstantBias[2] = obj_ConstantBias[2];

  /* Start for MATLABSystem: '<S3>/IMU1' */
  if (sobj->isInitialized == 1) {
    sobj->TunablePropsChanged = true;
    sobj->tunablePropertyChanged[4] = true;
  }

  memcpy(&sobj->AxesMisalignment[0], &obj_AxesMisalignment[0], 9U * sizeof
         (real_T));

  /* Start for MATLABSystem: '<S3>/IMU1' */
  if (sobj->isInitialized == 1) {
    sobj->TunablePropsChanged = true;
    sobj->tunablePropertyChanged[5] = true;
  }

  sobj->NoiseDensity[0] = obj_NoiseDensity[0];
  sobj->NoiseDensity[1] = obj_NoiseDensity[1];
  sobj->NoiseDensity[2] = obj_NoiseDensity[2];

  /* Start for MATLABSystem: '<S3>/IMU1' */
  if (sobj->isInitialized == 1) {
    sobj->TunablePropsChanged = true;
    sobj->tunablePropertyChanged[6] = true;
  }

  sobj->BiasInstability[0] = obj_BiasInstability[0];
  sobj->BiasInstability[1] = obj_BiasInstability[1];
  sobj->BiasInstability[2] = obj_BiasInstability[2];

  /* Start for MATLABSystem: '<S3>/IMU1' */
  if (sobj->isInitialized == 1) {
    sobj->TunablePropsChanged = true;
    sobj->tunablePropertyChanged[7] = true;
  }

  sobj->RandomWalk[0] = obj_RandomWalk[0];
  sobj->RandomWalk[1] = obj_RandomWalk[1];
  sobj->RandomWalk[2] = obj_RandomWalk[2];

  /* Start for MATLABSystem: '<S3>/IMU1' */
  if (sobj->isInitialized == 1) {
    sobj->TunablePropsChanged = true;
    sobj->tunablePropertyChanged[8] = true;
  }

  sobj->BiasInstabilityCoefficients.Numerator = obj_BiasInstabilityCoefficients;
  sobj->BiasInstabilityCoefficients.Denominator[0] =
    obj_BiasInstabilityCoefficien_0[0];
  sobj->BiasInstabilityCoefficients.Denominator[1] =
    obj_BiasInstabilityCoefficien_0[1];
  if (sobj->isInitialized == 1) {
    sobj->TunablePropsChanged = true;
    sobj->tunablePropertyChanged[9] = true;
  }

  for (i = 0; i < 12; i++) {
    sobj->NoiseType.Value[i] = obj_NoiseType_Value[i];
  }

  /* Start for MATLABSystem: '<S3>/IMU1' */
  if (sobj->isInitialized == 1) {
    sobj->TunablePropsChanged = true;
    sobj->tunablePropertyChanged[10] = true;
  }

  sobj->TemperatureBias[0] = obj_TemperatureBias[0];
  sobj->TemperatureBias[1] = obj_TemperatureBias[1];
  sobj->TemperatureBias[2] = obj_TemperatureBias[2];

  /* Start for MATLABSystem: '<S3>/IMU1' */
  if (sobj->isInitialized == 1) {
    sobj->TunablePropsChanged = true;
    sobj->tunablePropertyChanged[11] = true;
  }

  sobj->TemperatureScaleFactor[0] = obj_TemperatureScaleFactor[0];
  sobj->TemperatureScaleFactor[1] = obj_TemperatureScaleFactor[1];
  sobj->TemperatureScaleFactor[2] = obj_TemperatureScaleFactor[2];
}

static void IMUSensorParameters_updateSy_ph(real_T obj_MeasurementRange, real_T
  obj_Resolution, const real_T obj_ConstantBias[3], const real_T
  obj_AxesMisalignment[9], const real_T obj_NoiseDensity[3], const real_T
  obj_BiasInstability[3], const real_T obj_RandomWalk[3], real_T
  obj_BiasInstabilityCoefficients, const real_T obj_BiasInstabilityCoefficien_0
  [2], const char_T obj_NoiseType_Value[12], const real_T obj_TemperatureBias[3],
  const real_T obj_TemperatureScaleFactor[3], i_fusion_internal_Magnetomete_T
  *sobj)
{
  int32_T i;

  /* Start for MATLABSystem: '<S3>/IMU1' */
  if (sobj->isInitialized == 1) {
    sobj->TunablePropsChanged = true;
    sobj->tunablePropertyChanged[0] = true;
  }

  sobj->MeasurementRange = obj_MeasurementRange;

  /* Start for MATLABSystem: '<S3>/IMU1' */
  if (sobj->isInitialized == 1) {
    sobj->TunablePropsChanged = true;
    sobj->tunablePropertyChanged[1] = true;
  }

  sobj->Resolution = obj_Resolution;

  /* Start for MATLABSystem: '<S3>/IMU1' */
  if (sobj->isInitialized == 1) {
    sobj->TunablePropsChanged = true;
    sobj->tunablePropertyChanged[2] = true;
  }

  sobj->ConstantBias[0] = obj_ConstantBias[0];
  sobj->ConstantBias[1] = obj_ConstantBias[1];
  sobj->ConstantBias[2] = obj_ConstantBias[2];

  /* Start for MATLABSystem: '<S3>/IMU1' */
  if (sobj->isInitialized == 1) {
    sobj->TunablePropsChanged = true;
    sobj->tunablePropertyChanged[3] = true;
  }

  memcpy(&sobj->AxesMisalignment[0], &obj_AxesMisalignment[0], 9U * sizeof
         (real_T));

  /* Start for MATLABSystem: '<S3>/IMU1' */
  if (sobj->isInitialized == 1) {
    sobj->TunablePropsChanged = true;
    sobj->tunablePropertyChanged[4] = true;
  }

  sobj->NoiseDensity[0] = obj_NoiseDensity[0];
  sobj->NoiseDensity[1] = obj_NoiseDensity[1];
  sobj->NoiseDensity[2] = obj_NoiseDensity[2];

  /* Start for MATLABSystem: '<S3>/IMU1' */
  if (sobj->isInitialized == 1) {
    sobj->TunablePropsChanged = true;
    sobj->tunablePropertyChanged[5] = true;
  }

  sobj->BiasInstability[0] = obj_BiasInstability[0];
  sobj->BiasInstability[1] = obj_BiasInstability[1];
  sobj->BiasInstability[2] = obj_BiasInstability[2];

  /* Start for MATLABSystem: '<S3>/IMU1' */
  if (sobj->isInitialized == 1) {
    sobj->TunablePropsChanged = true;
    sobj->tunablePropertyChanged[6] = true;
  }

  sobj->RandomWalk[0] = obj_RandomWalk[0];
  sobj->RandomWalk[1] = obj_RandomWalk[1];
  sobj->RandomWalk[2] = obj_RandomWalk[2];

  /* Start for MATLABSystem: '<S3>/IMU1' */
  if (sobj->isInitialized == 1) {
    sobj->TunablePropsChanged = true;
    sobj->tunablePropertyChanged[7] = true;
  }

  sobj->BiasInstabilityCoefficients.Numerator = obj_BiasInstabilityCoefficients;
  sobj->BiasInstabilityCoefficients.Denominator[0] =
    obj_BiasInstabilityCoefficien_0[0];
  sobj->BiasInstabilityCoefficients.Denominator[1] =
    obj_BiasInstabilityCoefficien_0[1];
  if (sobj->isInitialized == 1) {
    sobj->TunablePropsChanged = true;
    sobj->tunablePropertyChanged[8] = true;
  }

  for (i = 0; i < 12; i++) {
    sobj->NoiseType.Value[i] = obj_NoiseType_Value[i];
  }

  /* Start for MATLABSystem: '<S3>/IMU1' */
  if (sobj->isInitialized == 1) {
    sobj->TunablePropsChanged = true;
    sobj->tunablePropertyChanged[9] = true;
  }

  sobj->TemperatureBias[0] = obj_TemperatureBias[0];
  sobj->TemperatureBias[1] = obj_TemperatureBias[1];
  sobj->TemperatureBias[2] = obj_TemperatureBias[2];

  /* Start for MATLABSystem: '<S3>/IMU1' */
  if (sobj->isInitialized == 1) {
    sobj->TunablePropsChanged = true;
    sobj->tunablePropertyChanged[10] = true;
  }

  sobj->TemperatureScaleFactor[0] = obj_TemperatureScaleFactor[0];
  sobj->TemperatureScaleFactor[1] = obj_TemperatureScaleFactor[1];
  sobj->TemperatureScaleFactor[2] = obj_TemperatureScaleFactor[2];
}

static boolean_T UAV_Dynamics_vectorAny(const boolean_T x_data[], const int32_T
  x_size[2])
{
  int32_T b_k;
  boolean_T exitg1;
  boolean_T y;
  y = false;
  b_k = 0;
  exitg1 = false;
  while ((!exitg1) && (b_k <= x_size[1] - 1)) {
    if (x_data[b_k]) {
      y = true;
      exitg1 = true;
    } else {
      b_k++;
    }
  }

  return y;
}

static void UAV_Dyn_genrand_uint32_vector_p(uint32_T mt[625], uint32_T u[2])
{
  int32_T b_j;
  int32_T b_kk;
  for (b_j = 0; b_j < 2; b_j++) {
    uint32_T mti;
    uint32_T y;
    mti = mt[624] + 1U;
    if (mt[624] + 1U >= 625U) {
      for (b_kk = 0; b_kk < 227; b_kk++) {
        /* Start for MATLABSystem: '<S3>/IMU1' */
        y = (mt[b_kk + 1] & 2147483647U) | (mt[b_kk] & 2147483648U);
        if ((y & 1U) == 0U) {
          mti = y >> 1U;
        } else {
          mti = y >> 1U ^ 2567483615U;
        }

        mt[b_kk] = mt[b_kk + 397] ^ mti;
      }

      for (b_kk = 0; b_kk < 396; b_kk++) {
        /* Start for MATLABSystem: '<S3>/IMU1' */
        y = (mt[b_kk + 227] & 2147483648U) | (mt[b_kk + 228] & 2147483647U);
        if ((y & 1U) == 0U) {
          mti = y >> 1U;
        } else {
          mti = y >> 1U ^ 2567483615U;
        }

        mt[b_kk + 227] = mt[b_kk] ^ mti;
      }

      y = (mt[623] & 2147483648U) | (mt[0] & 2147483647U);

      /* Start for MATLABSystem: '<S3>/IMU1' */
      if ((y & 1U) == 0U) {
        mti = y >> 1U;
      } else {
        mti = y >> 1U ^ 2567483615U;
      }

      mt[623] = mt[396] ^ mti;
      mti = 1U;
    }

    y = mt[(int32_T)mti - 1];
    mt[624] = mti;
    y ^= y >> 11U;
    y ^= y << 7U & 2636928640U;
    y ^= y << 15U & 4022730752U;

    /* Start for MATLABSystem: '<S3>/IMU1' */
    u[b_j] = y >> 18U ^ y;
  }
}

static real_T UAV_Dynamics_genrandu_p(uint32_T mt[625])
{
  real_T r;
  int32_T exitg1;
  int32_T k;
  uint32_T b_u[2];
  uint32_T r_0;
  boolean_T b_isvalid;
  boolean_T exitg2;

  /* ========================= COPYRIGHT NOTICE ============================ */
  /*  This is a uniform (0,1) pseudorandom number generator based on:        */
  /*                                                                         */
  /*  A C-program for MT19937, with initialization improved 2002/1/26.       */
  /*  Coded by Takuji Nishimura and Makoto Matsumoto.                        */
  /*                                                                         */
  /*  Copyright (C) 1997 - 2002, Makoto Matsumoto and Takuji Nishimura,      */
  /*  All rights reserved.                                                   */
  /*                                                                         */
  /*  Redistribution and use in source and binary forms, with or without     */
  /*  modification, are permitted provided that the following conditions     */
  /*  are met:                                                               */
  /*                                                                         */
  /*    1. Redistributions of source code must retain the above copyright    */
  /*       notice, this list of conditions and the following disclaimer.     */
  /*                                                                         */
  /*    2. Redistributions in binary form must reproduce the above copyright */
  /*       notice, this list of conditions and the following disclaimer      */
  /*       in the documentation and/or other materials provided with the     */
  /*       distribution.                                                     */
  /*                                                                         */
  /*    3. The names of its contributors may not be used to endorse or       */
  /*       promote products derived from this software without specific      */
  /*       prior written permission.                                         */
  /*                                                                         */
  /*  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS    */
  /*  "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT      */
  /*  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR  */
  /*  A PARTICULAR PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL THE COPYRIGHT  */
  /*  OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,  */
  /*  SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT       */
  /*  LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,  */
  /*  DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY  */
  /*  THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT    */
  /*  (INCLUDING  NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE */
  /*  OF THIS  SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.  */
  /*                                                                         */
  /* =============================   END   ================================= */
  do {
    exitg1 = 0;
    UAV_Dyn_genrand_uint32_vector_p(mt, b_u);
    r = ((real_T)(b_u[0] >> 5U) * 6.7108864E+7 + (real_T)(b_u[1] >> 6U)) *
      1.1102230246251565E-16;
    if (r == 0.0) {
      if ((mt[624] >= 1U) && (mt[624] < 625U)) {
        b_isvalid = true;
      } else {
        b_isvalid = false;
      }

      if (b_isvalid) {
        b_isvalid = false;
        k = 0;
        exitg2 = false;
        while ((!exitg2) && (k + 1 < 625)) {
          if (mt[k] == 0U) {
            k++;
          } else {
            b_isvalid = true;
            exitg2 = true;
          }
        }
      }

      if (!b_isvalid) {
        r_0 = 87254U;
        mt[0] = 87254U;
        for (k = 0; k < 623; k++) {
          r_0 = ((r_0 >> 30U ^ r_0) * 1812433253U + (uint32_T)k) + 1U;
          mt[k + 1] = r_0;
        }

        mt[624] = 624U;
      }
    } else {
      exitg1 = 1;
    }
  } while (exitg1 == 0);

  return r;
}

static void UAV_Dynamics_filter(real_T b, real_T a[2], const real_T x[3], const
  real_T zi[3], real_T y[3], real_T zf[3])
{
  /* Start for MATLABSystem: '<S3>/IMU1' */
  if ((!rtIsInf(a[0])) && (!rtIsNaN(a[0])) && (!(a[0] == 0.0)) && (a[0] != 1.0))
  {
    b /= a[0];
    a[1] /= a[0];
  }

  y[0] = x[0] * b + zi[0];
  zf[0] = -y[0] * a[1];
  y[1] = x[1] * b + zi[1];
  zf[1] = -y[1] * a[1];
  y[2] = x[2] * b + zi[2];
  zf[2] = -y[2] * a[1];

  /* End of Start for MATLABSystem: '<S3>/IMU1' */
}

real_T rt_roundd_snf(real_T u)
{
  real_T y;
  if (fabs(u) < 4.503599627370496E+15) {
    if (u >= 0.5) {
      y = floor(u + 0.5);
    } else if (u > -0.5) {
      y = u * 0.0;
    } else {
      y = ceil(u - 0.5);
    }
  } else {
    y = u;
  }

  return y;
}

static void UAV_Dynamics_SystemCore_step_p(g_fusion_internal_Acceleromet_T *obj,
  const real_T varargin_1[3], const real_T varargin_2[9], const real_T
  varargin_3[9], real_T varargout_1[3])
{
  real_T B[3];
  real_T c[3];
  real_T y[3];
  real_T b_x;
  real_T b_x_0;
  real_T b_x_1;
  int32_T ret;
  int8_T b_data[3];
  static const char_T b[12] = { 'd', 'o', 'u', 'b', 'l', 'e', '-', 's', 'i', 'd',
    'e', 'd' };

  __m128d tmp;
  __m128d tmp_0;
  __m128d tmp_1;
  __m128d tmp_2;
  real_T obj_0[3];
  real_T obj_1[2];
  real_T x_idx_5;
  int32_T tmp_size_idx_1;
  int32_T trueCount;
  int8_T tmp_data[3];
  if (obj->isInitialized != 1) {
    /* Start for MATLABSystem: '<S3>/IMU1' */
    obj->isInitialized = 1;
    for (ret = 0; ret <= 6; ret += 2) {
      /* Start for MATLABSystem: '<S3>/IMU1' */
      tmp_2 = _mm_loadu_pd(&obj->AxesMisalignment[ret]);
      _mm_storeu_pd(&obj->pGain[ret], _mm_div_pd(tmp_2, _mm_set1_pd(100.0)));
    }

    for (ret = 8; ret < 9; ret++) {
      /* Start for MATLABSystem: '<S3>/IMU1' */
      obj->pGain[ret] = obj->AxesMisalignment[ret] / 100.0;
    }

    /* Start for MATLABSystem: '<S3>/IMU1' */
    ret = memcmp(&obj->NoiseType.Value[0], &b[0], 12);
    if (ret == 0) {
      obj->pBandwidth = 50.0;
    } else {
      obj->pBandwidth = 100.0;
    }

    obj->pBiasInstFilterNum = obj->BiasInstabilityCoefficients.Numerator;
    obj->pBiasInstFilterDen[0] = obj->BiasInstabilityCoefficients.Denominator[0];
    obj->pBiasInstFilterDen[1] = obj->BiasInstabilityCoefficients.Denominator[1];
    obj->pCorrelationTime = 0.02;
    b_x = sqrt(2.0 / (100.0 * obj->pCorrelationTime));
    b_x_0 = sqrt(obj->pBandwidth);
    b_x_1 = sqrt(obj->pBandwidth);
    obj->TunablePropsChanged = false;
    obj->pStdDevBiasInst[0] = b_x * obj->BiasInstability[0];
    obj->pStdDevWhiteNoise[0] = b_x_0 * obj->NoiseDensity[0];
    obj->pStdDevRandWalk[0] = obj->RandomWalk[0] / b_x_1;
    obj->pBiasInstFilterStates[0] = 0.0;
    obj->pRandWalkFilterStates[0] = 0.0;
    obj->pStdDevBiasInst[1] = b_x * obj->BiasInstability[1];
    obj->pStdDevWhiteNoise[1] = b_x_0 * obj->NoiseDensity[1];
    obj->pStdDevRandWalk[1] = obj->RandomWalk[1] / b_x_1;
    obj->pBiasInstFilterStates[1] = 0.0;
    obj->pRandWalkFilterStates[1] = 0.0;
    obj->pStdDevBiasInst[2] = b_x * obj->BiasInstability[2];
    obj->pStdDevWhiteNoise[2] = b_x_0 * obj->NoiseDensity[2];
    obj->pStdDevRandWalk[2] = obj->RandomWalk[2] / b_x_1;
    obj->pBiasInstFilterStates[2] = 0.0;
    obj->pRandWalkFilterStates[2] = 0.0;
  }

  /* Start for MATLABSystem: '<S3>/IMU1' */
  if (obj->TunablePropsChanged) {
    obj->TunablePropsChanged = false;
    if (obj->tunablePropertyChanged[3]) {
      for (ret = 0; ret <= 6; ret += 2) {
        tmp_2 = _mm_loadu_pd(&obj->AxesMisalignment[ret]);
        _mm_storeu_pd(&obj->pGain[ret], _mm_div_pd(tmp_2, _mm_set1_pd(100.0)));
      }

      for (ret = 8; ret < 9; ret++) {
        obj->pGain[ret] = obj->AxesMisalignment[ret] / 100.0;
      }
    }

    if (obj->tunablePropertyChanged[4] || obj->tunablePropertyChanged[8]) {
      ret = memcmp(&obj->NoiseType.Value[0], &b[0], 12);
      if (ret == 0) {
        obj->pBandwidth = 50.0;
      } else {
        obj->pBandwidth = 100.0;
      }

      b_x = sqrt(obj->pBandwidth);
      obj->pStdDevWhiteNoise[0] = b_x * obj->NoiseDensity[0];
      obj->pStdDevWhiteNoise[1] = b_x * obj->NoiseDensity[1];
      obj->pStdDevWhiteNoise[2] = b_x * obj->NoiseDensity[2];
    }

    if (obj->tunablePropertyChanged[5]) {
      b_x = sqrt(2.0 / (100.0 * obj->pCorrelationTime));
      obj->pStdDevBiasInst[0] = b_x * obj->BiasInstability[0];
      obj->pStdDevBiasInst[1] = b_x * obj->BiasInstability[1];
      obj->pStdDevBiasInst[2] = b_x * obj->BiasInstability[2];
    }

    if (obj->tunablePropertyChanged[6] || obj->tunablePropertyChanged[8]) {
      ret = memcmp(&obj->NoiseType.Value[0], &b[0], 12);
      if (ret == 0) {
        obj->pBandwidth = 50.0;
      } else {
        obj->pBandwidth = 100.0;
      }

      b_x = sqrt(obj->pBandwidth);
      obj->pStdDevRandWalk[0] = obj->RandomWalk[0] / b_x;
      obj->pStdDevRandWalk[1] = obj->RandomWalk[1] / b_x;
      obj->pStdDevRandWalk[2] = obj->RandomWalk[2] / b_x;
    }

    if (obj->tunablePropertyChanged[7]) {
      obj->pBiasInstFilterNum = obj->BiasInstabilityCoefficients.Numerator;
      obj->pBiasInstFilterDen[0] = obj->BiasInstabilityCoefficients.Denominator
        [0];
      obj->pBiasInstFilterDen[1] = obj->BiasInstabilityCoefficients.Denominator
        [1];
    }

    for (ret = 0; ret < 12; ret++) {
      obj->tunablePropertyChanged[ret] = false;
    }
  }

  b_x = -varargin_1[0];
  b_x_0 = -varargin_1[1];
  b_x_1 = -varargin_1[2] + 9.81;
  for (ret = 0; ret <= 0; ret += 2) {
    /* Start for MATLABSystem: '<S3>/IMU1' */
    tmp_2 = _mm_loadu_pd(&varargin_2[ret + 3]);
    tmp_0 = _mm_loadu_pd(&varargin_2[ret]);
    tmp_1 = _mm_loadu_pd(&varargin_2[ret + 6]);
    _mm_storeu_pd(&B[ret], _mm_add_pd(_mm_add_pd(_mm_mul_pd(tmp_2, _mm_set1_pd
      (b_x_0)), _mm_mul_pd(tmp_0, _mm_set1_pd(b_x))), _mm_mul_pd(tmp_1,
      _mm_set1_pd(b_x_1))));
  }

  /* Start for MATLABSystem: '<S3>/IMU1' */
  for (ret = 2; ret < 3; ret++) {
    B[ret] = (varargin_2[ret + 3] * b_x_0 + varargin_2[ret] * b_x) +
      varargin_2[ret + 6] * b_x_1;
  }

  b_x = B[1];
  b_x_0 = B[0];
  b_x_1 = B[2];
  for (ret = 0; ret <= 0; ret += 2) {
    /* Start for MATLABSystem: '<S3>/IMU1' */
    tmp_2 = _mm_loadu_pd(&obj->pGain[ret + 3]);
    tmp_0 = _mm_loadu_pd(&obj->pGain[ret]);
    tmp_1 = _mm_loadu_pd(&obj->pGain[ret + 6]);
    tmp = _mm_loadu_pd(&obj->ConstantBias[ret]);
    _mm_storeu_pd(&B[ret], _mm_add_pd(_mm_add_pd(_mm_add_pd(_mm_mul_pd(tmp_2,
      _mm_set1_pd(b_x)), _mm_mul_pd(tmp_0, _mm_set1_pd(b_x_0))), _mm_mul_pd
      (tmp_1, _mm_set1_pd(b_x_1))), tmp));
    tmp_2 = _mm_loadu_pd(&varargin_3[ret]);
    tmp_0 = _mm_loadu_pd(&obj->pStdDevBiasInst[ret]);
    _mm_storeu_pd(&c[ret], _mm_mul_pd(tmp_2, tmp_0));
  }

  for (ret = 2; ret < 3; ret++) {
    /* Start for MATLABSystem: '<S3>/IMU1' */
    B[ret] = ((obj->pGain[ret + 3] * b_x + obj->pGain[ret] * b_x_0) + obj->
              pGain[ret + 6] * b_x_1) + obj->ConstantBias[ret];
    c[ret] = varargin_3[ret] * obj->pStdDevBiasInst[ret];
  }

  for (ret = 0; ret < 3; ret++) {
    /* Start for MATLABSystem: '<S3>/IMU1' */
    obj_0[ret] = obj->pBiasInstFilterStates[ret];
  }

  for (ret = 0; ret < 2; ret++) {
    /* Start for MATLABSystem: '<S3>/IMU1' */
    obj_1[ret] = obj->pBiasInstFilterDen[ret];
  }

  /* Start for MATLABSystem: '<S3>/IMU1' */
  UAV_Dynamics_filter(obj->pBiasInstFilterNum, obj_1, c, obj_0, y,
                      obj->pBiasInstFilterStates);
  b_x_0 = obj->pStdDevRandWalk[0] * varargin_3[6] + obj->pRandWalkFilterStates[0];
  b_x_1 = obj->pStdDevRandWalk[1] * varargin_3[7] + obj->pRandWalkFilterStates[1];
  x_idx_5 = obj->pStdDevRandWalk[2] * varargin_3[8] + obj->
    pRandWalkFilterStates[2];
  obj->pRandWalkFilterStates[0] = b_x_0;
  obj->pRandWalkFilterStates[1] = b_x_1;
  obj->pRandWalkFilterStates[2] = x_idx_5;
  b_x = (obj->Temperature - 25.0) * 0.01;
  varargout_1[0] = ((((obj->pStdDevWhiteNoise[0] * varargin_3[3] + y[0]) + b_x_0)
                     + (obj->Temperature - 25.0) * obj->TemperatureBias[0]) + B
                    [0]) * (b_x * obj->TemperatureScaleFactor[0] + 1.0);
  varargout_1[1] = ((((obj->pStdDevWhiteNoise[1] * varargin_3[4] + y[1]) + b_x_1)
                     + (obj->Temperature - 25.0) * obj->TemperatureBias[1]) + B
                    [1]) * (b_x * obj->TemperatureScaleFactor[1] + 1.0);
  varargout_1[2] = ((((obj->pStdDevWhiteNoise[2] * varargin_3[5] + y[2]) +
                      x_idx_5) + (obj->Temperature - 25.0) *
                     obj->TemperatureBias[2]) + B[2]) * (b_x *
    obj->TemperatureScaleFactor[2] + 1.0);
  if (!rtIsInf(obj->MeasurementRange)) {
    b_x = fabs(varargout_1[0]);
    y[0] = b_x;
    b_x_0 = fabs(varargout_1[1]);
    y[1] = b_x_0;
    b_x_1 = fabs(varargout_1[2]);
    y[2] = b_x_1;
    trueCount = 0;
    for (ret = 0; ret < 3; ret++) {
      if (y[ret] > obj->MeasurementRange) {
        b_data[trueCount] = (int8_T)ret;
        trueCount++;
      }
    }

    y[0] = b_x;
    y[1] = b_x_0;
    y[2] = b_x_1;
    trueCount = 0;
    for (ret = 0; ret < 3; ret++) {
      if (y[ret] > obj->MeasurementRange) {
        trueCount++;
      }
    }

    tmp_size_idx_1 = trueCount;
    trueCount = 0;
    for (ret = 0; ret < 3; ret++) {
      if (y[ret] > obj->MeasurementRange) {
        tmp_data[trueCount] = (int8_T)ret;
        trueCount++;
      }
    }

    for (ret = 0; ret < tmp_size_idx_1; ret++) {
      B[ret] = varargout_1[tmp_data[ret]];
    }

    trueCount = 0;
    for (ret = 0; ret < 3; ret++) {
      if (y[ret] > obj->MeasurementRange) {
        trueCount++;
      }
    }

    trueCount--;
    for (ret = 0; ret <= trueCount; ret++) {
      b_x = B[ret];
      if (rtIsNaN(b_x)) {
        B[ret] = (rtNaN);
      } else if (b_x < 0.0) {
        B[ret] = -1.0;
      } else {
        B[ret] = (b_x > 0.0);
      }
    }

    for (ret = 0; ret < tmp_size_idx_1; ret++) {
      varargout_1[b_data[ret]] = B[ret] * obj->MeasurementRange;
    }
  }

  if (obj->Resolution != 0.0) {
    varargout_1[0] /= obj->Resolution;
    varargout_1[1] /= obj->Resolution;
    varargout_1[2] /= obj->Resolution;
    varargout_1[0] = rt_roundd_snf(varargout_1[0]);
    varargout_1[1] = rt_roundd_snf(varargout_1[1]);
    varargout_1[2] = rt_roundd_snf(varargout_1[2]);
    varargout_1[0] *= obj->Resolution;
    varargout_1[1] *= obj->Resolution;
    varargout_1[2] *= obj->Resolution;
  }
}

static void UAV_Dynamics_SystemCore_step_ph(h_fusion_internal_GyroscopeSi_T *obj,
  const real_T varargin_1[3], const real_T varargin_2[3], const real_T
  varargin_3[9], const real_T varargin_4[9], real_T varargout_1[3])
{
  real_T B[3];
  real_T c[3];
  real_T b_x;
  real_T b_x_0;
  real_T b_x_1;
  int32_T ret;
  int8_T b_data[3];
  static const char_T b[12] = { 'd', 'o', 'u', 'b', 'l', 'e', '-', 's', 'i', 'd',
    'e', 'd' };

  __m128d tmp;
  __m128d tmp_0;
  __m128d tmp_1;
  __m128d tmp_2;
  real_T obj_0[3];
  real_T varargin_3_0[3];
  real_T obj_1[2];
  real_T x_idx_5;
  int32_T tmp_size_idx_1;
  int32_T trueCount;
  int8_T tmp_data[3];
  if (obj->isInitialized != 1) {
    /* Start for MATLABSystem: '<S3>/IMU1' */
    obj->isInitialized = 1;
    for (ret = 0; ret <= 6; ret += 2) {
      /* Start for MATLABSystem: '<S3>/IMU1' */
      tmp_2 = _mm_loadu_pd(&obj->AxesMisalignment[ret]);
      _mm_storeu_pd(&obj->pGain[ret], _mm_div_pd(tmp_2, _mm_set1_pd(100.0)));
    }

    for (ret = 8; ret < 9; ret++) {
      /* Start for MATLABSystem: '<S3>/IMU1' */
      obj->pGain[ret] = obj->AxesMisalignment[ret] / 100.0;
    }

    /* Start for MATLABSystem: '<S3>/IMU1' */
    ret = memcmp(&obj->NoiseType.Value[0], &b[0], 12);
    if (ret == 0) {
      obj->pBandwidth = 50.0;
    } else {
      obj->pBandwidth = 100.0;
    }

    obj->pBiasInstFilterNum = obj->BiasInstabilityCoefficients.Numerator;
    obj->pBiasInstFilterDen[0] = obj->BiasInstabilityCoefficients.Denominator[0];
    obj->pBiasInstFilterDen[1] = obj->BiasInstabilityCoefficients.Denominator[1];
    obj->pCorrelationTime = 0.02;
    b_x = sqrt(2.0 / (100.0 * obj->pCorrelationTime));
    b_x_0 = sqrt(obj->pBandwidth);
    b_x_1 = sqrt(obj->pBandwidth);
    obj->TunablePropsChanged = false;
    obj->pStdDevBiasInst[0] = b_x * obj->BiasInstability[0];
    obj->pStdDevWhiteNoise[0] = b_x_0 * obj->NoiseDensity[0];
    obj->pStdDevRandWalk[0] = obj->RandomWalk[0] / b_x_1;
    obj->pBiasInstFilterStates[0] = 0.0;
    obj->pRandWalkFilterStates[0] = 0.0;
    obj->pStdDevBiasInst[1] = b_x * obj->BiasInstability[1];
    obj->pStdDevWhiteNoise[1] = b_x_0 * obj->NoiseDensity[1];
    obj->pStdDevRandWalk[1] = obj->RandomWalk[1] / b_x_1;
    obj->pBiasInstFilterStates[1] = 0.0;
    obj->pRandWalkFilterStates[1] = 0.0;
    obj->pStdDevBiasInst[2] = b_x * obj->BiasInstability[2];
    obj->pStdDevWhiteNoise[2] = b_x_0 * obj->NoiseDensity[2];
    obj->pStdDevRandWalk[2] = obj->RandomWalk[2] / b_x_1;
    obj->pBiasInstFilterStates[2] = 0.0;
    obj->pRandWalkFilterStates[2] = 0.0;
  }

  /* Start for MATLABSystem: '<S3>/IMU1' */
  if (obj->TunablePropsChanged) {
    obj->TunablePropsChanged = false;
    if (obj->tunablePropertyChanged[4]) {
      for (ret = 0; ret <= 6; ret += 2) {
        tmp_2 = _mm_loadu_pd(&obj->AxesMisalignment[ret]);
        _mm_storeu_pd(&obj->pGain[ret], _mm_div_pd(tmp_2, _mm_set1_pd(100.0)));
      }

      for (ret = 8; ret < 9; ret++) {
        obj->pGain[ret] = obj->AxesMisalignment[ret] / 100.0;
      }
    }

    if (obj->tunablePropertyChanged[5] || obj->tunablePropertyChanged[9]) {
      ret = memcmp(&obj->NoiseType.Value[0], &b[0], 12);
      if (ret == 0) {
        obj->pBandwidth = 50.0;
      } else {
        obj->pBandwidth = 100.0;
      }

      b_x = sqrt(obj->pBandwidth);
      obj->pStdDevWhiteNoise[0] = b_x * obj->NoiseDensity[0];
      obj->pStdDevWhiteNoise[1] = b_x * obj->NoiseDensity[1];
      obj->pStdDevWhiteNoise[2] = b_x * obj->NoiseDensity[2];
    }

    if (obj->tunablePropertyChanged[6]) {
      b_x = sqrt(2.0 / (100.0 * obj->pCorrelationTime));
      obj->pStdDevBiasInst[0] = b_x * obj->BiasInstability[0];
      obj->pStdDevBiasInst[1] = b_x * obj->BiasInstability[1];
      obj->pStdDevBiasInst[2] = b_x * obj->BiasInstability[2];
    }

    if (obj->tunablePropertyChanged[7] || obj->tunablePropertyChanged[9]) {
      ret = memcmp(&obj->NoiseType.Value[0], &b[0], 12);
      if (ret == 0) {
        obj->pBandwidth = 50.0;
      } else {
        obj->pBandwidth = 100.0;
      }

      b_x = sqrt(obj->pBandwidth);
      obj->pStdDevRandWalk[0] = obj->RandomWalk[0] / b_x;
      obj->pStdDevRandWalk[1] = obj->RandomWalk[1] / b_x;
      obj->pStdDevRandWalk[2] = obj->RandomWalk[2] / b_x;
    }

    if (obj->tunablePropertyChanged[8]) {
      obj->pBiasInstFilterNum = obj->BiasInstabilityCoefficients.Numerator;
      obj->pBiasInstFilterDen[0] = obj->BiasInstabilityCoefficients.Denominator
        [0];
      obj->pBiasInstFilterDen[1] = obj->BiasInstabilityCoefficients.Denominator
        [1];
    }

    for (ret = 0; ret < 13; ret++) {
      obj->tunablePropertyChanged[ret] = false;
    }
  }

  b_x = varargin_1[1];
  b_x_0 = varargin_1[0];
  b_x_1 = varargin_1[2];
  for (ret = 0; ret <= 0; ret += 2) {
    /* Start for MATLABSystem: '<S3>/IMU1' */
    tmp_2 = _mm_loadu_pd(&varargin_2[ret]);
    _mm_storeu_pd(&obj->pAcceleration[ret], tmp_2);
    tmp_2 = _mm_loadu_pd(&varargin_3[ret + 3]);
    tmp_0 = _mm_loadu_pd(&varargin_3[ret]);
    tmp_1 = _mm_loadu_pd(&varargin_3[ret + 6]);
    _mm_storeu_pd(&varargin_3_0[ret], _mm_add_pd(_mm_add_pd(_mm_mul_pd(tmp_2,
      _mm_set1_pd(b_x)), _mm_mul_pd(tmp_0, _mm_set1_pd(b_x_0))), _mm_mul_pd
      (tmp_1, _mm_set1_pd(b_x_1))));
  }

  /* Start for MATLABSystem: '<S3>/IMU1' */
  for (ret = 2; ret < 3; ret++) {
    obj->pAcceleration[ret] = varargin_2[ret];
    varargin_3_0[ret] = (varargin_3[ret + 3] * b_x + varargin_3[ret] * b_x_0) +
      varargin_3[ret + 6] * b_x_1;
  }

  b_x = varargin_3_0[1];
  b_x_0 = varargin_3_0[0];
  b_x_1 = varargin_3_0[2];
  for (ret = 0; ret <= 0; ret += 2) {
    /* Start for MATLABSystem: '<S3>/IMU1' */
    tmp_2 = _mm_loadu_pd(&obj->pGain[ret + 3]);
    tmp_0 = _mm_loadu_pd(&obj->pGain[ret]);
    tmp_1 = _mm_loadu_pd(&obj->pGain[ret + 6]);
    tmp = _mm_loadu_pd(&obj->ConstantBias[ret]);
    _mm_storeu_pd(&B[ret], _mm_add_pd(_mm_add_pd(_mm_add_pd(_mm_mul_pd(tmp_2,
      _mm_set1_pd(b_x)), _mm_mul_pd(tmp_0, _mm_set1_pd(b_x_0))), _mm_mul_pd
      (tmp_1, _mm_set1_pd(b_x_1))), tmp));
    tmp_2 = _mm_loadu_pd(&varargin_4[ret]);
    tmp_0 = _mm_loadu_pd(&obj->pStdDevBiasInst[ret]);
    _mm_storeu_pd(&c[ret], _mm_mul_pd(tmp_2, tmp_0));
  }

  for (ret = 2; ret < 3; ret++) {
    /* Start for MATLABSystem: '<S3>/IMU1' */
    B[ret] = ((obj->pGain[ret + 3] * b_x + obj->pGain[ret] * b_x_0) + obj->
              pGain[ret + 6] * b_x_1) + obj->ConstantBias[ret];
    c[ret] = varargin_4[ret] * obj->pStdDevBiasInst[ret];
  }

  for (ret = 0; ret < 3; ret++) {
    /* Start for MATLABSystem: '<S3>/IMU1' */
    obj_0[ret] = obj->pBiasInstFilterStates[ret];
  }

  for (ret = 0; ret < 2; ret++) {
    /* Start for MATLABSystem: '<S3>/IMU1' */
    obj_1[ret] = obj->pBiasInstFilterDen[ret];
  }

  /* Start for MATLABSystem: '<S3>/IMU1' */
  UAV_Dynamics_filter(obj->pBiasInstFilterNum, obj_1, c, obj_0, varargin_3_0,
                      obj->pBiasInstFilterStates);
  b_x_0 = obj->pStdDevRandWalk[0] * varargin_4[6] + obj->pRandWalkFilterStates[0];
  b_x_1 = obj->pStdDevRandWalk[1] * varargin_4[7] + obj->pRandWalkFilterStates[1];
  x_idx_5 = obj->pStdDevRandWalk[2] * varargin_4[8] + obj->
    pRandWalkFilterStates[2];
  obj->pRandWalkFilterStates[0] = b_x_0;
  obj->pRandWalkFilterStates[1] = b_x_1;
  obj->pRandWalkFilterStates[2] = x_idx_5;
  b_x = (obj->Temperature - 25.0) * 0.01;
  varargout_1[0] = ((((obj->pStdDevWhiteNoise[0] * varargin_4[3] + varargin_3_0
                       [0]) + b_x_0) + ((obj->Temperature - 25.0) *
    obj->TemperatureBias[0] + obj->pAcceleration[0] * obj->AccelerationBias[0]))
                    + B[0]) * (b_x * obj->TemperatureScaleFactor[0] + 1.0);
  varargout_1[1] = ((((obj->pStdDevWhiteNoise[1] * varargin_4[4] + varargin_3_0
                       [1]) + b_x_1) + ((obj->Temperature - 25.0) *
    obj->TemperatureBias[1] + obj->pAcceleration[1] * obj->AccelerationBias[1]))
                    + B[1]) * (b_x * obj->TemperatureScaleFactor[1] + 1.0);
  varargout_1[2] = ((((obj->pStdDevWhiteNoise[2] * varargin_4[5] + varargin_3_0
                       [2]) + x_idx_5) + ((obj->Temperature - 25.0) *
    obj->TemperatureBias[2] + obj->pAcceleration[2] * obj->AccelerationBias[2]))
                    + B[2]) * (b_x * obj->TemperatureScaleFactor[2] + 1.0);
  if (!rtIsInf(obj->MeasurementRange)) {
    b_x = fabs(varargout_1[0]);
    varargin_3_0[0] = b_x;
    b_x_0 = fabs(varargout_1[1]);
    varargin_3_0[1] = b_x_0;
    b_x_1 = fabs(varargout_1[2]);
    varargin_3_0[2] = b_x_1;
    trueCount = 0;
    for (ret = 0; ret < 3; ret++) {
      if (varargin_3_0[ret] > obj->MeasurementRange) {
        b_data[trueCount] = (int8_T)ret;
        trueCount++;
      }
    }

    varargin_3_0[0] = b_x;
    varargin_3_0[1] = b_x_0;
    varargin_3_0[2] = b_x_1;
    trueCount = 0;
    for (ret = 0; ret < 3; ret++) {
      if (varargin_3_0[ret] > obj->MeasurementRange) {
        trueCount++;
      }
    }

    tmp_size_idx_1 = trueCount;
    trueCount = 0;
    for (ret = 0; ret < 3; ret++) {
      if (varargin_3_0[ret] > obj->MeasurementRange) {
        tmp_data[trueCount] = (int8_T)ret;
        trueCount++;
      }
    }

    for (ret = 0; ret < tmp_size_idx_1; ret++) {
      B[ret] = varargout_1[tmp_data[ret]];
    }

    trueCount = 0;
    for (ret = 0; ret < 3; ret++) {
      if (varargin_3_0[ret] > obj->MeasurementRange) {
        trueCount++;
      }
    }

    trueCount--;
    for (ret = 0; ret <= trueCount; ret++) {
      b_x = B[ret];
      if (rtIsNaN(b_x)) {
        B[ret] = (rtNaN);
      } else if (b_x < 0.0) {
        B[ret] = -1.0;
      } else {
        B[ret] = (b_x > 0.0);
      }
    }

    for (ret = 0; ret < tmp_size_idx_1; ret++) {
      varargout_1[b_data[ret]] = B[ret] * obj->MeasurementRange;
    }
  }

  if (obj->Resolution != 0.0) {
    varargout_1[0] /= obj->Resolution;
    varargout_1[1] /= obj->Resolution;
    varargout_1[2] /= obj->Resolution;
    varargout_1[0] = rt_roundd_snf(varargout_1[0]);
    varargout_1[1] = rt_roundd_snf(varargout_1[1]);
    varargout_1[2] = rt_roundd_snf(varargout_1[2]);
    varargout_1[0] *= obj->Resolution;
    varargout_1[1] *= obj->Resolution;
    varargout_1[2] *= obj->Resolution;
  }
}

static void UAV_Dynamics_imuSensor_stepImpl(fusion_simulink_imuSensor_UAV_T *obj,
  const real_T la[3], const real_T av[3], const real_T o[4], real_T a[3], real_T
  g[3], real_T m[3])
{
  i_fusion_internal_Magnetomete_T *obj_0;
  real_T allRandData[27];
  real_T a_1[9];
  real_T rmat[9];
  real_T a_0[3];
  real_T magneticfield[3];
  real_T temperatureDrift[3];
  real_T y[3];
  real_T aasq;
  real_T ab2;
  real_T ac2;
  real_T ad2;
  real_T bc2;
  real_T bd2;
  real_T cd2;
  real_T maximum;
  real_T n;
  real_T x;
  int32_T b_colIdx;
  uint32_T c_mt[625];
  uint32_T u32[2];
  char_T obj1_Value[12];
  int8_T b_data[3];
  boolean_T flag;
  static const char_T b[12] = { 'd', 'o', 'u', 'b', 'l', 'e', '-', 's', 'i', 'd',
    'e', 'd' };

  __m128d tmp;
  __m128d tmp_0;
  __m128d tmp_1;
  int32_T i;
  int8_T tmp_data[3];
  static const real_T tmp_2[257] = { 0.0, 0.215241895984875, 0.286174591792068,
    0.335737519214422, 0.375121332878378, 0.408389134611989, 0.43751840220787,
    0.46363433679088, 0.487443966139235, 0.50942332960209, 0.529909720661557,
    0.549151702327164, 0.567338257053817, 0.584616766106378, 0.601104617755991,
    0.61689699000775, 0.63207223638606, 0.646695714894993, 0.660822574244419,
    0.674499822837293, 0.687767892795788, 0.700661841106814, 0.713212285190975,
    0.725446140909999, 0.737387211434295, 0.749056662017815, 0.760473406430107,
    0.771654424224568, 0.782615023307232, 0.793369058840623, 0.80392911698997,
    0.814306670135215, 0.824512208752291, 0.834555354086381, 0.844444954909153,
    0.854189171008163, 0.863795545553308, 0.87327106808886, 0.882622229585165,
    0.891855070732941, 0.900975224461221, 0.909987953496718, 0.91889818364959,
    0.927710533401999, 0.936429340286575, 0.945058684468165, 0.953602409881086,
    0.96206414322304, 0.970447311064224, 0.978755155294224, 0.986990747099062,
    0.99515699963509, 1.00325667954467, 1.01129241744, 1.01926671746548,
    1.02718196603564, 1.03504043983344, 1.04284431314415, 1.05059566459093,
    1.05829648333067, 1.06594867476212, 1.07355406579244, 1.0811144097034,
    1.08863139065398, 1.09610662785202, 1.10354167942464, 1.11093804601357,
    1.11829717411934, 1.12562045921553, 1.13290924865253, 1.14016484436815,
    1.14738850542085, 1.15458145035993, 1.16174485944561, 1.16887987673083,
    1.17598761201545, 1.18306914268269, 1.19012551542669, 1.19715774787944,
    1.20416683014438, 1.2111537262437, 1.21811937548548, 1.22506469375653,
    1.23199057474614, 1.23889789110569, 1.24578749554863, 1.2526602218949,
    1.25951688606371, 1.26635828701823, 1.27318520766536, 1.27999841571382,
    1.28679866449324, 1.29358669373695, 1.30036323033084, 1.30712898903073,
    1.31388467315022, 1.32063097522106, 1.32736857762793, 1.33409815321936,
    1.3408203658964, 1.34753587118059, 1.35424531676263, 1.36094934303328,
    1.36764858359748, 1.37434366577317, 1.38103521107586, 1.38772383568998,
    1.39441015092814, 1.40109476367925, 1.4077782768464, 1.41446128977547,
    1.42114439867531, 1.42782819703026, 1.43451327600589, 1.44120022484872,
    1.44788963128058, 1.45458208188841, 1.46127816251028, 1.46797845861808,
    1.47468355569786, 1.48139403962819, 1.48811049705745, 1.49483351578049,
    1.50156368511546, 1.50830159628131, 1.51504784277671, 1.521803020761,
    1.52856772943771, 1.53534257144151, 1.542128153229, 1.54892508547417,
    1.55573398346918, 1.56255546753104, 1.56939016341512, 1.57623870273591,
    1.58310172339603, 1.58997987002419, 1.59687379442279, 1.60378415602609,
    1.61071162236983, 1.61765686957301, 1.62462058283303, 1.63160345693487,
    1.63860619677555, 1.64562951790478, 1.65267414708306, 1.65974082285818,
    1.66683029616166, 1.67394333092612, 1.68108070472517, 1.68824320943719,
    1.69543165193456, 1.70264685479992, 1.7098896570713, 1.71716091501782,
    1.72446150294804, 1.73179231405296, 1.73915426128591, 1.74654827828172,
    1.75397532031767, 1.76143636531891, 1.76893241491127, 1.77646449552452,
    1.78403365954944, 1.79164098655216, 1.79928758454972, 1.80697459135082,
    1.81470317596628, 1.82247454009388, 1.83028991968276, 1.83815058658281,
    1.84605785028518, 1.8540130597602, 1.86201760539967, 1.87007292107127,
    1.878180486293, 1.88634182853678, 1.8945585256707, 1.90283220855043,
    1.91116456377125, 1.91955733659319, 1.92801233405266, 1.93653142827569,
    1.94511656000868, 1.95376974238465, 1.96249306494436, 1.97128869793366,
    1.98015889690048, 1.98910600761744, 1.99813247135842, 2.00724083056053,
    2.0164337349062, 2.02571394786385, 2.03508435372962, 2.04454796521753,
    2.05410793165065, 2.06376754781173, 2.07353026351874, 2.0833996939983,
    2.09337963113879, 2.10347405571488, 2.11368715068665, 2.12402331568952,
    2.13448718284602, 2.14508363404789, 2.15581781987674, 2.16669518035431,
    2.17772146774029, 2.18890277162636, 2.20024554661128, 2.21175664288416,
    2.22344334009251, 2.23531338492992, 2.24737503294739, 2.25963709517379,
    2.27210899022838, 2.28480080272449, 2.29772334890286, 2.31088825060137,
    2.32430801887113, 2.33799614879653, 2.35196722737914, 2.36623705671729,
    2.38082279517208, 2.39574311978193, 2.41101841390112, 2.42667098493715,
    2.44272531820036, 2.4592083743347, 2.47614993967052, 2.49358304127105,
    2.51154444162669, 2.53007523215985, 2.54922155032478, 2.56903545268184,
    2.58957598670829, 2.61091051848882, 2.63311639363158, 2.65628303757674,
    2.68051464328574, 2.70593365612306, 2.73268535904401, 2.76094400527999,
    2.79092117400193, 2.82287739682644, 2.85713873087322, 2.89412105361341,
    2.93436686720889, 2.97860327988184, 3.02783779176959, 3.08352613200214,
    3.147889289518, 3.2245750520478, 3.32024473383983, 3.44927829856143,
    3.65415288536101, 3.91075795952492 };

  static const real_T tmp_3[257] = { 1.0, 0.977101701267673, 0.959879091800108,
    0.9451989534423, 0.932060075959231, 0.919991505039348, 0.908726440052131,
    0.898095921898344, 0.887984660755834, 0.878309655808918, 0.869008688036857,
    0.860033621196332, 0.851346258458678, 0.842915653112205, 0.834716292986884,
    0.826726833946222, 0.818929191603703, 0.811307874312656, 0.803849483170964,
    0.796542330422959, 0.789376143566025, 0.782341832654803, 0.775431304981187,
    0.768637315798486, 0.761953346836795, 0.755373506507096, 0.748892447219157,
    0.742505296340151, 0.736207598126863, 0.729995264561476, 0.72386453346863,
    0.717811932630722, 0.711834248878248, 0.705928501332754, 0.700091918136512,
    0.694321916126117, 0.688616083004672, 0.682972161644995, 0.677388036218774,
    0.671861719897082, 0.66639134390875, 0.660975147776663, 0.655611470579697,
    0.650298743110817, 0.645035480820822, 0.639820277453057, 0.634651799287624,
    0.629528779924837, 0.624450015547027, 0.619414360605834, 0.614420723888914,
    0.609468064925773, 0.604555390697468, 0.599681752619125, 0.594846243767987,
    0.590047996332826, 0.585286179263371, 0.580559996100791, 0.575868682972354,
    0.571211506735253, 0.566587763256165, 0.561996775814525, 0.557437893618766,
    0.552910490425833, 0.548413963255266, 0.543947731190026, 0.539511234256952,
    0.535103932380458, 0.530725304403662, 0.526374847171684, 0.522052074672322,
    0.517756517229756, 0.513487720747327, 0.509245245995748, 0.505028667943468,
    0.500837575126149, 0.49667156905249, 0.492530263643869, 0.488413284705458,
    0.484320269426683, 0.480250865909047, 0.476204732719506, 0.47218153846773,
    0.468180961405694, 0.464202689048174, 0.460246417812843, 0.456311852678716,
    0.452398706861849, 0.448506701507203, 0.444635565395739, 0.440785034665804,
    0.436954852547985, 0.433144769112652, 0.429354541029442, 0.425583931338022,
    0.421832709229496, 0.418100649837848, 0.414387534040891, 0.410693148270188,
    0.407017284329473, 0.403359739221114, 0.399720314980197, 0.396098818515832,
    0.392495061459315, 0.388908860018789, 0.385340034840077, 0.381788410873393,
    0.378253817245619, 0.374736087137891, 0.371235057668239, 0.367750569779032,
    0.364282468129004, 0.360830600989648, 0.357394820145781, 0.353974980800077,
    0.350570941481406, 0.347182563956794, 0.343809713146851, 0.340452257044522,
    0.337110066637006, 0.333783015830718, 0.330470981379163, 0.327173842813601,
    0.323891482376391, 0.320623784956905, 0.317370638029914, 0.314131931596337,
    0.310907558126286, 0.307697412504292, 0.30450139197665, 0.301319396100803,
    0.298151326696685, 0.294997087799962, 0.291856585617095, 0.288729728482183,
    0.285616426815502, 0.282516593083708, 0.279430141761638, 0.276356989295668,
    0.273297054068577, 0.270250256365875, 0.267216518343561, 0.264195763997261,
    0.261187919132721, 0.258192911337619, 0.255210669954662, 0.252241126055942,
    0.249284212418529, 0.246339863501264, 0.24340801542275, 0.240488605940501,
    0.237581574431238, 0.23468686187233, 0.231804410824339, 0.228934165414681,
    0.226076071322381, 0.223230075763918, 0.220396127480152, 0.217574176724331,
    0.214764175251174, 0.211966076307031, 0.209179834621125, 0.206405406397881,
    0.203642749310335, 0.200891822494657, 0.198152586545776, 0.195425003514135,
    0.192709036903589, 0.190004651670465, 0.187311814223801, 0.1846304924268,
    0.181960655599523, 0.179302274522848, 0.176655321443735, 0.174019770081839,
    0.171395595637506, 0.168782774801212, 0.166181285764482, 0.163591108232366,
    0.161012223437511, 0.158444614155925, 0.15588826472448, 0.153343161060263,
    0.150809290681846, 0.148286642732575, 0.145775208005994, 0.143274978973514,
    0.140785949814445, 0.138308116448551, 0.135841476571254, 0.133386029691669,
    0.130941777173644, 0.12850872228, 0.126086870220186, 0.123676228201597,
    0.12127680548479, 0.11888861344291, 0.116511665625611, 0.114145977827839,
    0.111791568163838, 0.109448457146812, 0.107116667774684, 0.104796225622487,
    0.102487158941935, 0.10018949876881, 0.0979032790388625, 0.095628536713009,
    0.093365311912691, 0.0911136480663738, 0.0888735920682759,
    0.0866451944505581, 0.0844285095703535, 0.082223595813203,
    0.0800305158146631, 0.0778493367020961, 0.0756801303589272,
    0.0735229737139814, 0.0713779490588905, 0.0692451443970068,
    0.0671246538277886, 0.065016577971243, 0.0629210244377582, 0.06083810834954,
    0.0587679529209339, 0.0567106901062031, 0.0546664613248891,
    0.0526354182767924, 0.0506177238609479, 0.0486135532158687,
    0.0466230949019305, 0.0446465522512946, 0.0426841449164746,
    0.0407361106559411, 0.0388027074045262, 0.0368842156885674,
    0.0349809414617162, 0.0330932194585786, 0.0312214171919203,
    0.0293659397581334, 0.0275272356696031, 0.0257058040085489,
    0.0239022033057959, 0.0221170627073089, 0.0203510962300445,
    0.0186051212757247, 0.0168800831525432, 0.0151770883079353,
    0.0134974506017399, 0.0118427578579079, 0.0102149714397015,
    0.00861658276939875, 0.00705087547137324, 0.00552240329925101,
    0.00403797259336304, 0.00260907274610216, 0.0012602859304986,
    0.000477467764609386 };

  real_T obj_1[2];
  int32_T exitg1;
  int32_T tmp_size_idx_1;
  boolean_T guard1;

  /* Start for MATLABSystem: '<S3>/IMU1' */
  n = sqrt(((o[0] * o[0] + o[1] * o[1]) + o[2] * o[2]) + o[3] * o[3]);
  aasq = o[0] / n;
  maximum = o[1] / n;
  x = o[2] / n;
  n = o[3] / n;
  ab2 = aasq * maximum * 2.0;
  ac2 = aasq * x * 2.0;
  ad2 = aasq * n * 2.0;
  bc2 = maximum * x * 2.0;
  bd2 = maximum * n * 2.0;
  cd2 = x * n * 2.0;

  /* Start for MATLABSystem: '<S3>/IMU1' */
  aasq = aasq * aasq * 2.0 - 1.0;
  rmat[0] = maximum * maximum * 2.0 + aasq;
  rmat[3] = bc2 + ad2;
  rmat[6] = bd2 - ac2;
  rmat[1] = bc2 - ad2;

  /* Start for MATLABSystem: '<S3>/IMU1' */
  rmat[4] = x * x * 2.0 + aasq;
  rmat[7] = cd2 + ab2;
  rmat[2] = bd2 + ac2;
  rmat[5] = cd2 - ab2;

  /* Start for MATLABSystem: '<S3>/IMU1' */
  rmat[8] = n * n * 2.0 + aasq;
  for (i = 0; i < 625; i++) {
    /* Start for MATLABSystem: '<S3>/IMU1' */
    c_mt[i] = obj->pStreamState[i];
  }

  for (b_colIdx = 0; b_colIdx < 27; b_colIdx++) {
    do {
      exitg1 = 0;
      UAV_Dyn_genrand_uint32_vector_p(c_mt, u32);
      i = (int32_T)((u32[1] >> 24U) + 1U);
      maximum = (((real_T)(u32[0] >> 3U) * 1.6777216E+7 + (real_T)((int32_T)u32
        [1] & 16777215)) * 2.2204460492503131E-16 - 1.0) * tmp_2[i];
      if (fabs(maximum) <= tmp_2[i - 1]) {
        exitg1 = 1;
      } else if (i < 256) {
        x = UAV_Dynamics_genrandu_p(c_mt);
        if ((tmp_3[i - 1] - tmp_3[i]) * x + tmp_3[i] < exp(-0.5 * maximum *
             maximum)) {
          exitg1 = 1;
        }
      } else {
        do {
          x = UAV_Dynamics_genrandu_p(c_mt);
          x = log(x) * 0.273661237329758;
          aasq = UAV_Dynamics_genrandu_p(c_mt);
        } while (!(-2.0 * log(aasq) > x * x));

        if (maximum < 0.0) {
          maximum = x - 3.65415288536101;
        } else {
          maximum = 3.65415288536101 - x;
        }

        exitg1 = 1;
      }
    } while (exitg1 == 0);

    /* Start for MATLABSystem: '<S3>/IMU1' */
    allRandData[b_colIdx] = maximum;
  }

  for (i = 0; i < 625; i++) {
    /* Start for MATLABSystem: '<S3>/IMU1' */
    obj->pStreamState[i] = c_mt[i];
  }

  /* Start for MATLABSystem: '<S3>/IMU1' */
  UAV_Dynamics_SystemCore_step_p(obj->pAccel, la, rmat, &allRandData[0], a);
  UAV_Dynamics_SystemCore_step_ph(obj->pGyro, av, la, rmat, &allRandData[9], g);
  a_0[0] = obj->MagneticField[0];
  a_0[1] = obj->MagneticField[1];
  a_0[2] = obj->MagneticField[2];
  obj_0 = obj->pMag;
  if (obj_0->isInitialized != 1) {
    /* Start for MATLABSystem: '<S3>/IMU1' */
    obj_0->isInitialized = 1;
    for (i = 0; i < 9; i++) {
      /* Start for MATLABSystem: '<S3>/IMU1' */
      obj_0->pGain[i] = obj_0->AxesMisalignment[i] / 100.0;
    }

    for (i = 0; i < 12; i++) {
      /* Start for MATLABSystem: '<S3>/IMU1' */
      obj1_Value[i] = obj_0->NoiseType.Value[i];
    }

    /* Start for MATLABSystem: '<S3>/IMU1' */
    i = memcmp(&obj1_Value[0], &b[0], 12);
    if (i == 0) {
      obj_0->pBandwidth = 50.0;
    } else {
      obj_0->pBandwidth = 100.0;
    }

    maximum = obj_0->BiasInstabilityCoefficients.Numerator;
    obj_0->pBiasInstFilterNum = maximum;
    maximum = obj_0->BiasInstabilityCoefficients.Denominator[0];
    obj_0->pBiasInstFilterDen[0] = maximum;
    maximum = obj_0->BiasInstabilityCoefficients.Denominator[1];
    obj_0->pBiasInstFilterDen[1] = maximum;
    obj_0->pCorrelationTime = 0.02;
    x = 2.0 / (100.0 * obj_0->pCorrelationTime);
    maximum = sqrt(x);
    x = obj_0->pBandwidth;
    aasq = sqrt(x);
    x = obj_0->pBandwidth;
    x = sqrt(x);
    obj_0->TunablePropsChanged = false;
    obj_0->pBiasInstFilterStates[0] = 0.0;
    obj_0->pStdDevBiasInst[0] = maximum * obj_0->BiasInstability[0];
    obj_0->pStdDevWhiteNoise[0] = aasq * obj_0->NoiseDensity[0];
    obj_0->pRandWalkFilterStates[0] = 0.0;
    obj_0->pStdDevRandWalk[0] = obj_0->RandomWalk[0] / x;
    obj_0->pBiasInstFilterStates[0] = 0.0;
    obj_0->pRandWalkFilterStates[0] = 0.0;
    obj_0->pBiasInstFilterStates[1] = 0.0;
    obj_0->pStdDevBiasInst[1] = maximum * obj_0->BiasInstability[1];
    obj_0->pStdDevWhiteNoise[1] = aasq * obj_0->NoiseDensity[1];
    obj_0->pRandWalkFilterStates[1] = 0.0;
    obj_0->pStdDevRandWalk[1] = obj_0->RandomWalk[1] / x;
    obj_0->pBiasInstFilterStates[1] = 0.0;
    obj_0->pRandWalkFilterStates[1] = 0.0;
    obj_0->pBiasInstFilterStates[2] = 0.0;
    obj_0->pStdDevBiasInst[2] = maximum * obj_0->BiasInstability[2];
    obj_0->pStdDevWhiteNoise[2] = aasq * obj_0->NoiseDensity[2];
    obj_0->pRandWalkFilterStates[2] = 0.0;
    obj_0->pStdDevRandWalk[2] = obj_0->RandomWalk[2] / x;
    obj_0->pBiasInstFilterStates[2] = 0.0;
    obj_0->pRandWalkFilterStates[2] = 0.0;
  }

  /* Start for MATLABSystem: '<S3>/IMU1' */
  if (obj_0->TunablePropsChanged) {
    obj_0->TunablePropsChanged = false;
    flag = obj_0->tunablePropertyChanged[3];
    if (flag) {
      for (i = 0; i < 9; i++) {
        obj_0->pGain[i] = obj_0->AxesMisalignment[i] / 100.0;
      }
    }

    flag = obj_0->tunablePropertyChanged[4];
    guard1 = false;
    if (flag) {
      guard1 = true;
    } else {
      flag = obj_0->tunablePropertyChanged[8];
      if (flag) {
        guard1 = true;
      }
    }

    if (guard1) {
      for (i = 0; i < 12; i++) {
        obj1_Value[i] = obj_0->NoiseType.Value[i];
      }

      i = memcmp(&obj1_Value[0], &b[0], 12);
      if (i == 0) {
        obj_0->pBandwidth = 50.0;
      } else {
        obj_0->pBandwidth = 100.0;
      }

      x = obj_0->pBandwidth;
      maximum = sqrt(x);
      obj_0->pStdDevWhiteNoise[0] = maximum * obj_0->NoiseDensity[0];
      obj_0->pStdDevWhiteNoise[1] = maximum * obj_0->NoiseDensity[1];
      obj_0->pStdDevWhiteNoise[2] = maximum * obj_0->NoiseDensity[2];
    }

    flag = obj_0->tunablePropertyChanged[5];
    if (flag) {
      x = 2.0 / (100.0 * obj_0->pCorrelationTime);
      maximum = sqrt(x);
      obj_0->pStdDevBiasInst[0] = maximum * obj_0->BiasInstability[0];
      obj_0->pStdDevBiasInst[1] = maximum * obj_0->BiasInstability[1];
      obj_0->pStdDevBiasInst[2] = maximum * obj_0->BiasInstability[2];
    }

    flag = obj_0->tunablePropertyChanged[6];
    guard1 = false;
    if (flag) {
      guard1 = true;
    } else {
      flag = obj_0->tunablePropertyChanged[8];
      if (flag) {
        guard1 = true;
      }
    }

    if (guard1) {
      for (i = 0; i < 12; i++) {
        obj1_Value[i] = obj_0->NoiseType.Value[i];
      }

      i = memcmp(&obj1_Value[0], &b[0], 12);
      if (i == 0) {
        obj_0->pBandwidth = 50.0;
      } else {
        obj_0->pBandwidth = 100.0;
      }

      x = obj_0->pBandwidth;
      maximum = sqrt(x);
      obj_0->pStdDevRandWalk[0] = obj_0->RandomWalk[0] / maximum;
      obj_0->pStdDevRandWalk[1] = obj_0->RandomWalk[1] / maximum;
      obj_0->pStdDevRandWalk[2] = obj_0->RandomWalk[2] / maximum;
    }

    flag = obj_0->tunablePropertyChanged[7];
    if (flag) {
      maximum = obj_0->BiasInstabilityCoefficients.Numerator;
      obj_0->pBiasInstFilterNum = maximum;
      maximum = obj_0->BiasInstabilityCoefficients.Denominator[0];
      obj_0->pBiasInstFilterDen[0] = maximum;
      maximum = obj_0->BiasInstabilityCoefficients.Denominator[1];
      obj_0->pBiasInstFilterDen[1] = maximum;
    }

    for (i = 0; i < 12; i++) {
      obj_0->tunablePropertyChanged[i] = false;
    }
  }

  for (i = 0; i < 9; i++) {
    /* Start for MATLABSystem: '<S3>/IMU1' */
    a_1[i] = obj_0->pGain[i];
  }

  /* Start for MATLABSystem: '<S3>/IMU1' */
  maximum = a_0[1];
  x = a_0[0];
  aasq = a_0[2];
  for (i = 0; i <= 0; i += 2) {
    /* Start for MATLABSystem: '<S3>/IMU1' */
    tmp = _mm_loadu_pd(&rmat[i + 3]);
    tmp_0 = _mm_loadu_pd(&rmat[i]);
    tmp_1 = _mm_loadu_pd(&rmat[i + 6]);
    _mm_storeu_pd(&magneticfield[i], _mm_add_pd(_mm_add_pd(_mm_mul_pd(tmp,
      _mm_set1_pd(maximum)), _mm_mul_pd(tmp_0, _mm_set1_pd(x))), _mm_mul_pd
      (tmp_1, _mm_set1_pd(aasq))));
  }

  /* Start for MATLABSystem: '<S3>/IMU1' */
  for (i = 2; i < 3; i++) {
    magneticfield[i] = (rmat[i + 3] * maximum + rmat[i] * x) + rmat[i + 6] *
      aasq;
  }

  x = magneticfield[1];
  aasq = magneticfield[0];
  n = magneticfield[2];
  for (i = 0; i < 3; i++) {
    /* Start for MATLABSystem: '<S3>/IMU1' */
    maximum = obj_0->ConstantBias[i];
    magneticfield[i] = ((a_1[i + 3] * x + a_1[i] * aasq) + a_1[i + 6] * n) +
      maximum;
    maximum = obj_0->pStdDevBiasInst[i];
    temperatureDrift[i] = allRandData[i + 18] * maximum;
  }

  for (i = 0; i < 2; i++) {
    /* Start for MATLABSystem: '<S3>/IMU1' */
    obj_1[i] = obj_0->pBiasInstFilterDen[i];
  }

  /* Start for MATLABSystem: '<S3>/IMU1' */
  UAV_Dynamics_filter(obj_0->pBiasInstFilterNum, obj_1, temperatureDrift,
                      obj_0->pBiasInstFilterStates, y, a_0);
  obj_0->pBiasInstFilterStates[0] = a_0[0];
  maximum = obj_0->pStdDevWhiteNoise[0];
  x = allRandData[21] * maximum;
  maximum = obj_0->pStdDevRandWalk[0];
  ad2 = obj_0->pRandWalkFilterStates[0];
  ab2 = allRandData[24] * maximum;
  obj_0->pBiasInstFilterStates[1] = a_0[1];
  maximum = obj_0->pStdDevWhiteNoise[1];
  aasq = allRandData[22] * maximum;
  maximum = obj_0->pStdDevRandWalk[1];
  bc2 = obj_0->pRandWalkFilterStates[1];
  ac2 = allRandData[25] * maximum;
  obj_0->pBiasInstFilterStates[2] = a_0[2];
  maximum = obj_0->pStdDevWhiteNoise[2];
  n = allRandData[23] * maximum;
  maximum = obj_0->pStdDevRandWalk[2];
  bd2 = obj_0->pRandWalkFilterStates[2];
  ab2 += ad2;
  ac2 += bc2;

  /* Start for MATLABSystem: '<S3>/IMU1' */
  ad2 = allRandData[26] * maximum + bd2;
  maximum = obj_0->Temperature - 25.0;
  obj_0->pRandWalkFilterStates[0] = ab2;
  a_0[0] = maximum * obj_0->TemperatureBias[0];
  obj_0->pRandWalkFilterStates[1] = ac2;
  a_0[1] = maximum * obj_0->TemperatureBias[1];
  obj_0->pRandWalkFilterStates[2] = ad2;
  a_0[2] = maximum * obj_0->TemperatureBias[2];
  temperatureDrift[0] = a_0[0];
  temperatureDrift[1] = a_0[1];
  temperatureDrift[2] = a_0[2];
  maximum = (obj_0->Temperature - 25.0) * 0.01;
  a_0[0] = maximum * obj_0->TemperatureScaleFactor[0] + 1.0;
  a_0[1] = maximum * obj_0->TemperatureScaleFactor[1] + 1.0;
  a_0[2] = maximum * obj_0->TemperatureScaleFactor[2] + 1.0;
  m[0] = ((((x + y[0]) + ab2) + temperatureDrift[0]) + magneticfield[0]) * a_0[0];
  m[1] = ((((aasq + y[1]) + ac2) + temperatureDrift[1]) + magneticfield[1]) *
    a_0[1];
  m[2] = ((((n + y[2]) + ad2) + temperatureDrift[2]) + magneticfield[2]) * a_0[2];
  x = obj_0->MeasurementRange;
  if (!rtIsInf(x)) {
    maximum = obj_0->MeasurementRange;
    x = fabs(m[0]);
    y[0] = x;
    aasq = fabs(m[1]);
    y[1] = aasq;
    n = fabs(m[2]);
    y[2] = n;
    b_colIdx = 0;
    for (i = 0; i < 3; i++) {
      if (y[i] > maximum) {
        b_data[b_colIdx] = (int8_T)i;
        b_colIdx++;
      }
    }

    y[0] = x;
    y[1] = aasq;
    y[2] = n;
    b_colIdx = 0;
    for (i = 0; i < 3; i++) {
      if (y[i] > maximum) {
        b_colIdx++;
      }
    }

    tmp_size_idx_1 = b_colIdx;
    b_colIdx = 0;
    for (i = 0; i < 3; i++) {
      if (y[i] > maximum) {
        tmp_data[b_colIdx] = (int8_T)i;
        b_colIdx++;
      }
    }

    for (i = 0; i < tmp_size_idx_1; i++) {
      a_0[i] = m[tmp_data[i]];
    }

    b_colIdx = 0;
    for (i = 0; i < 3; i++) {
      if (y[i] > maximum) {
        b_colIdx++;
      }
    }

    b_colIdx--;
    for (i = 0; i <= b_colIdx; i++) {
      x = a_0[i];
      if (rtIsNaN(x)) {
        a_0[i] = (rtNaN);
      } else if (x < 0.0) {
        a_0[i] = -1.0;
      } else {
        a_0[i] = (x > 0.0);
      }
    }

    for (i = 0; i < tmp_size_idx_1; i++) {
      m[b_data[i]] = a_0[i] * maximum;
    }
  }

  if (obj_0->Resolution != 0.0) {
    maximum = obj_0->Resolution;
    m[0] /= maximum;
    m[1] /= maximum;
    m[2] /= maximum;
    m[0] = rt_roundd_snf(m[0]);
    m[1] = rt_roundd_snf(m[1]);
    m[2] = rt_roundd_snf(m[2]);
    m[0] *= maximum;
    m[1] *= maximum;
    m[2] *= maximum;
  }
}

static void UAV_Dynamics_SystemCore_step(fusion_simulink_imuSensor_UAV_T *obj,
  const real_T varargin_1[3], const real_T varargin_2[3], const real_T
  varargin_3[4], real_T varargout_1[3], real_T varargout_2[3], real_T
  varargout_3[3])
{
  g_fusion_internal_Acceleromet_T *obj_0;
  h_fusion_internal_GyroscopeSi_T *obj_1;
  i_fusion_internal_Magnetomete_T *obj_2;
  real_T ap_AxesMisalignment[9];
  real_T gp_AxesMisalignment[9];
  real_T mp_AxesMisalignment[9];
  real_T ap_BiasInstability[3];
  real_T ap_ConstantBias[3];
  real_T ap_NoiseDensity[3];
  real_T ap_RandomWalk[3];
  real_T ap_TemperatureBias[3];
  real_T ap_TemperatureScaleFactor[3];
  real_T gp_AccelerationBias[3];
  real_T gp_BiasInstability[3];
  real_T gp_ConstantBias[3];
  real_T gp_NoiseDensity[3];
  real_T gp_RandomWalk[3];
  real_T gp_TemperatureBias[3];
  real_T gp_TemperatureScaleFactor[3];
  real_T mp_BiasInstability[3];
  real_T mp_ConstantBias[3];
  real_T mp_NoiseDensity[3];
  real_T mp_RandomWalk[3];
  real_T mp_TemperatureBias[3];
  real_T mp_TemperatureScaleFactor[3];
  real_T ap_BiasInstabilityCoefficient_0[2];
  real_T gp_BiasInstabilityCoefficient_0[2];
  real_T mp_BiasInstabilityCoefficient_0[2];
  real_T ap_BiasInstabilityCoefficients_;
  real_T ap_MeasurementRange;
  real_T ap_Resolution;
  real_T gp_BiasInstabilityCoefficients_;
  real_T gp_MeasurementRange;
  real_T gp_Resolution;
  real_T mp_BiasInstabilityCoefficients_;
  real_T mp_MeasurementRange;
  real_T mp_Resolution;
  int32_T i;
  char_T ap_NoiseType_Value[12];
  char_T gp_NoiseType_Value[12];
  char_T mp_NoiseType_Value[12];
  boolean_T flag_1[12];
  boolean_T flag_0[11];
  boolean_T flag;
  static const int32_T tmp[2] = { 1, 11 };

  static const int32_T tmp_0[2] = { 1, 12 };

  /* Start for MATLABSystem: '<S3>/IMU1' */
  if (obj->TunablePropsChanged) {
    obj->TunablePropsChanged = false;
    UAV_D_imuSensor_makeAccelParams(obj, &ap_MeasurementRange, &ap_Resolution,
      ap_ConstantBias, ap_AxesMisalignment, ap_NoiseDensity, ap_BiasInstability,
      ap_RandomWalk, &ap_BiasInstabilityCoefficients_,
      ap_BiasInstabilityCoefficient_0, ap_NoiseType_Value, ap_TemperatureBias,
      ap_TemperatureScaleFactor);
    UAV_Dy_imuSensor_makeGyroParams(obj, &gp_MeasurementRange, &gp_Resolution,
      gp_ConstantBias, gp_AxesMisalignment, gp_NoiseDensity, gp_BiasInstability,
      gp_RandomWalk, &gp_BiasInstabilityCoefficients_,
      gp_BiasInstabilityCoefficient_0, gp_NoiseType_Value, gp_TemperatureBias,
      gp_TemperatureScaleFactor, gp_AccelerationBias);
    UAV_Dyn_imuSensor_makeMagParams(obj, &mp_MeasurementRange, &mp_Resolution,
      mp_ConstantBias, mp_AxesMisalignment, mp_NoiseDensity, mp_BiasInstability,
      mp_RandomWalk, &mp_BiasInstabilityCoefficients_,
      mp_BiasInstabilityCoefficient_0, mp_NoiseType_Value, mp_TemperatureBias,
      mp_TemperatureScaleFactor);
    flag = obj->tunablePropertyChanged[37];
    if (flag) {
      obj_0 = obj->pAccel;
      flag = (obj_0->isInitialized == 1);
      if (flag) {
        obj_0->TunablePropsChanged = true;
        obj_0->tunablePropertyChanged[11] = true;
      }

      obj->pAccel->Temperature = obj->Temperature;
      IMUSensorParameters_updateSyste(ap_MeasurementRange, ap_Resolution,
        ap_ConstantBias, ap_AxesMisalignment, ap_NoiseDensity,
        ap_BiasInstability, ap_RandomWalk, ap_BiasInstabilityCoefficients_,
        ap_BiasInstabilityCoefficient_0, ap_NoiseType_Value, ap_TemperatureBias,
        ap_TemperatureScaleFactor, obj->pAccel);
      obj_1 = obj->pGyro;
      flag = (obj_1->isInitialized == 1);
      if (flag) {
        obj_1->TunablePropsChanged = true;
        obj_1->tunablePropertyChanged[12] = true;
      }

      obj->pGyro->Temperature = obj->Temperature;
      IMUSensorParameters_updateSys_p(gp_MeasurementRange, gp_Resolution,
        gp_ConstantBias, gp_AxesMisalignment, gp_NoiseDensity,
        gp_BiasInstability, gp_RandomWalk, gp_BiasInstabilityCoefficients_,
        gp_BiasInstabilityCoefficient_0, gp_NoiseType_Value, gp_TemperatureBias,
        gp_TemperatureScaleFactor, gp_AccelerationBias, obj->pGyro);
      obj_2 = obj->pMag;
      flag = (obj_2->isInitialized == 1);
      if (flag) {
        obj_2->TunablePropsChanged = true;
        obj_2->tunablePropertyChanged[11] = true;
      }

      obj->pMag->Temperature = obj->Temperature;
      IMUSensorParameters_updateSy_ph(mp_MeasurementRange, mp_Resolution,
        mp_ConstantBias, mp_AxesMisalignment, mp_NoiseDensity,
        mp_BiasInstability, mp_RandomWalk, mp_BiasInstabilityCoefficients_,
        mp_BiasInstabilityCoefficient_0, mp_NoiseType_Value, mp_TemperatureBias,
        mp_TemperatureScaleFactor, obj->pMag);
    }

    flag_0[0] = obj->tunablePropertyChanged[3];
    flag_0[1] = obj->tunablePropertyChanged[4];
    flag_0[2] = obj->tunablePropertyChanged[5];
    flag_0[3] = obj->tunablePropertyChanged[6];
    flag_0[4] = obj->tunablePropertyChanged[7];
    flag_0[5] = obj->tunablePropertyChanged[8];
    flag_0[6] = obj->tunablePropertyChanged[9];
    flag_0[7] = obj->tunablePropertyChanged[10];
    flag_0[8] = obj->tunablePropertyChanged[11];
    flag_0[9] = obj->tunablePropertyChanged[12];
    flag_0[10] = obj->tunablePropertyChanged[13];
    if (UAV_Dynamics_vectorAny(flag_0, tmp)) {
      IMUSensorParameters_updateSyste(ap_MeasurementRange, ap_Resolution,
        ap_ConstantBias, ap_AxesMisalignment, ap_NoiseDensity,
        ap_BiasInstability, ap_RandomWalk, ap_BiasInstabilityCoefficients_,
        ap_BiasInstabilityCoefficient_0, ap_NoiseType_Value, ap_TemperatureBias,
        ap_TemperatureScaleFactor, obj->pAccel);
    }

    flag_1[0] = obj->tunablePropertyChanged[14];
    flag_1[1] = obj->tunablePropertyChanged[15];
    flag_1[2] = obj->tunablePropertyChanged[16];
    flag_1[3] = obj->tunablePropertyChanged[17];
    flag_1[4] = obj->tunablePropertyChanged[18];
    flag_1[5] = obj->tunablePropertyChanged[19];
    flag_1[6] = obj->tunablePropertyChanged[20];
    flag_1[7] = obj->tunablePropertyChanged[21];
    flag_1[8] = obj->tunablePropertyChanged[22];
    flag_1[9] = obj->tunablePropertyChanged[23];
    flag_1[10] = obj->tunablePropertyChanged[24];
    flag_1[11] = obj->tunablePropertyChanged[25];
    if (UAV_Dynamics_vectorAny(flag_1, tmp_0)) {
      IMUSensorParameters_updateSys_p(gp_MeasurementRange, gp_Resolution,
        gp_ConstantBias, gp_AxesMisalignment, gp_NoiseDensity,
        gp_BiasInstability, gp_RandomWalk, gp_BiasInstabilityCoefficients_,
        gp_BiasInstabilityCoefficient_0, gp_NoiseType_Value, gp_TemperatureBias,
        gp_TemperatureScaleFactor, gp_AccelerationBias, obj->pGyro);
    }

    flag_0[0] = obj->tunablePropertyChanged[26];
    flag_0[1] = obj->tunablePropertyChanged[27];
    flag_0[2] = obj->tunablePropertyChanged[28];
    flag_0[3] = obj->tunablePropertyChanged[29];
    flag_0[4] = obj->tunablePropertyChanged[30];
    flag_0[5] = obj->tunablePropertyChanged[31];
    flag_0[6] = obj->tunablePropertyChanged[32];
    flag_0[7] = obj->tunablePropertyChanged[33];
    flag_0[8] = obj->tunablePropertyChanged[34];
    flag_0[9] = obj->tunablePropertyChanged[35];
    flag_0[10] = obj->tunablePropertyChanged[36];
    if (UAV_Dynamics_vectorAny(flag_0, tmp)) {
      IMUSensorParameters_updateSy_ph(mp_MeasurementRange, mp_Resolution,
        mp_ConstantBias, mp_AxesMisalignment, mp_NoiseDensity,
        mp_BiasInstability, mp_RandomWalk, mp_BiasInstabilityCoefficients_,
        mp_BiasInstabilityCoefficient_0, mp_NoiseType_Value, mp_TemperatureBias,
        mp_TemperatureScaleFactor, obj->pMag);
    }

    for (i = 0; i < 38; i++) {
      obj->tunablePropertyChanged[i] = false;
    }
  }

  /* End of Start for MATLABSystem: '<S3>/IMU1' */
  UAV_Dynamics_imuSensor_stepImpl(obj, varargin_1, varargin_2, varargin_3,
    varargout_1, varargout_2, varargout_3);
}

void rt_mrdivide_U1d1x3_U2d_9vOrDY9Z(const real_T u0[3], const real_T u1[9],
  real_T y[3])
{
  real_T A[9];
  real_T a21;
  real_T maxval;
  int32_T r1;
  int32_T r2;
  int32_T r3;
  memcpy(&A[0], &u1[0], 9U * sizeof(real_T));
  r1 = 0;
  r2 = 1;
  r3 = 2;
  maxval = fabs(u1[0]);
  a21 = fabs(u1[1]);
  if (a21 > maxval) {
    maxval = a21;
    r1 = 1;
    r2 = 0;
  }

  if (fabs(u1[2]) > maxval) {
    r1 = 2;
    r2 = 1;
    r3 = 0;
  }

  A[r2] = u1[r2] / u1[r1];
  A[r3] /= A[r1];
  A[r2 + 3] -= A[r1 + 3] * A[r2];
  A[r3 + 3] -= A[r1 + 3] * A[r3];
  A[r2 + 6] -= A[r1 + 6] * A[r2];
  A[r3 + 6] -= A[r1 + 6] * A[r3];
  if (fabs(A[r3 + 3]) > fabs(A[r2 + 3])) {
    int32_T rtemp;
    rtemp = r2 + 1;
    r2 = r3;
    r3 = rtemp - 1;
  }

  A[r3 + 3] /= A[r2 + 3];
  A[r3 + 6] -= A[r3 + 3] * A[r2 + 6];
  y[r1] = u0[0] / A[r1];
  y[r2] = u0[1] - A[r1 + 3] * y[r1];
  y[r3] = u0[2] - A[r1 + 6] * y[r1];
  y[r2] /= A[r2 + 3];
  y[r3] -= A[r2 + 6] * y[r2];
  y[r3] /= A[r3 + 6];
  y[r2] -= A[r3 + 3] * y[r3];
  y[r1] -= y[r3] * A[r3];
  y[r1] -= y[r2] * A[r2];
}

static void mt19937ar_genrand_uint32_vector(c_coder_internal_mt19937ar_UA_T *obj,
  uint32_T u[2])
{
  int32_T b_j;
  int32_T b_kk;
  for (b_j = 0; b_j < 2; b_j++) {
    uint32_T statei;
    uint32_T y;
    statei = obj->State[624] + 1U;
    if (obj->State[624] + 1U >= 625U) {
      for (b_kk = 0; b_kk < 227; b_kk++) {
        /* Start for MATLABSystem: '<S2>/GPS' */
        y = (obj->State[b_kk + 1] & 2147483647U) | (obj->State[b_kk] &
          2147483648U);
        if ((y & 1U) == 0U) {
          statei = y >> 1U;
        } else {
          statei = y >> 1U ^ 2567483615U;
        }

        obj->State[b_kk] = obj->State[b_kk + 397] ^ statei;
      }

      for (b_kk = 0; b_kk < 396; b_kk++) {
        /* Start for MATLABSystem: '<S2>/GPS' */
        y = (obj->State[b_kk + 227] & 2147483648U) | (obj->State[b_kk + 228] &
          2147483647U);
        if ((y & 1U) == 0U) {
          statei = y >> 1U;
        } else {
          statei = y >> 1U ^ 2567483615U;
        }

        obj->State[b_kk + 227] = obj->State[b_kk] ^ statei;
      }

      y = (obj->State[623] & 2147483648U) | (obj->State[0] & 2147483647U);

      /* Start for MATLABSystem: '<S2>/GPS' */
      if ((y & 1U) == 0U) {
        statei = y >> 1U;
      } else {
        statei = y >> 1U ^ 2567483615U;
      }

      obj->State[623] = obj->State[396] ^ statei;
      statei = 1U;
    }

    y = obj->State[(int32_T)statei - 1];
    obj->State[624] = statei;
    y ^= y >> 11U;
    y ^= y << 7U & 2636928640U;
    y ^= y << 15U & 4022730752U;

    /* Start for MATLABSystem: '<S2>/GPS' */
    u[b_j] = y >> 18U ^ y;
  }
}

static boolean_T UAV_Dynamics_is_valid_state(const uint32_T mt[625])
{
  boolean_T isvalid;
  if ((mt[624] >= 1U) && (mt[624] < 625U)) {
    isvalid = true;
  } else {
    isvalid = false;
  }

  if (isvalid) {
    int32_T k;
    boolean_T exitg1;
    isvalid = false;
    k = 0;
    exitg1 = false;
    while ((!exitg1) && (k + 1 < 625)) {
      if (mt[k] == 0U) {
        k++;
      } else {
        isvalid = true;
        exitg1 = true;
      }
    }
  }

  return isvalid;
}

static real_T UAV_Dynamics_mt19937ar_genrandu(c_coder_internal_mt19937ar_UA_T
  *obj)
{
  real_T r;
  int32_T b_statei;
  int32_T exitg1;
  uint32_T u[2];
  uint32_T r_0;

  /* ========================= COPYRIGHT NOTICE ============================ */
  /*  This is a uniform (0,1) pseudorandom number generator based on: */
  /*  */
  /*  A C-program for MT19937, with initialization improved 2002/1/26. */
  /*  Coded by Takuji Nishimura and Makoto Matsumoto. */
  /*  */
  /*  Copyright (C) 1997 - 2002, Makoto Matsumoto and Takuji Nishimura, */
  /*  All rights reserved. */
  /*  */
  /*  Redistribution and use in source and binary forms, with or without */
  /*  modification, are permitted provided that the following conditions */
  /*  are met: */
  /*  */
  /*    1. Redistributions of source code must retain the above copyright */
  /*       notice, this list of conditions and the following disclaimer. */
  /*  */
  /*    2. Redistributions in binary form must reproduce the above copyright */
  /*       notice, this list of conditions and the following disclaimer */
  /*       in the documentation and/or other materials provided with the */
  /*       distribution. */
  /*  */
  /*    3. The names of its contributors may not be used to endorse or */
  /*       promote products derived from this software without specific */
  /*       prior written permission. */
  /*  */
  /*  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS */
  /*  "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT */
  /*  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR */
  /*  A PARTICULAR PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL THE COPYRIGHT */
  /*  OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, */
  /*  SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT */
  /*  LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, */
  /*  DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY */
  /*  THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT */
  /*  (INCLUDING  NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE */
  /*  OF THIS  SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE. */
  /*  */
  /* =============================   END   ================================= */
  do {
    exitg1 = 0;
    mt19937ar_genrand_uint32_vector(obj, u);
    u[0] >>= 5U;
    u[1] >>= 6U;
    r = ((real_T)u[0] * 6.7108864E+7 + (real_T)u[1]) * 1.1102230246251565E-16;
    if (r == 0.0) {
      if (!UAV_Dynamics_is_valid_state(obj->State)) {
        obj->Seed = 5489U;
        r_0 = obj->Seed;
        obj->State[0] = obj->Seed;
        for (b_statei = 0; b_statei < 623; b_statei++) {
          r_0 = ((r_0 >> 30U ^ r_0) * 1812433253U + (uint32_T)b_statei) + 1U;
          obj->State[b_statei + 1] = r_0;
        }

        obj->State[624] = 624U;
      }
    } else {
      exitg1 = 1;
    }
  } while (exitg1 == 0);

  return r;
}

static real_T UAV_Dynamics_RandStream_rand_p(b_coder_internal_RandStream_U_T *s)
{
  c_coder_internal_mt19937ar_UA_T *obj;
  obj = s->Generator;
  return UAV_Dynamics_mt19937ar_genrandu(obj);
}

static real_T UA_RandStream_inversionGenrandn(b_coder_internal_RandStream_U_T *s)
{
  real_T r;
  real_T u;
  real_T z;
  u = UAV_Dynamics_RandStream_rand_p(s);

  /* Start for MATLABSystem: '<S2>/GPS' */
  if (fabs(u - 0.5) <= 0.425) {
    r = 0.180625 - (u - 0.5) * (u - 0.5);
    z = (((((((2509.0809287301227 * r + 33430.575583588128) * r +
              67265.7709270087) * r + 45921.95393154987) * r +
            13731.693765509461) * r + 1971.5909503065513) * r +
          133.14166789178438) * r + 3.3871328727963665) * (u - 0.5) /
      (((((((5226.4952788528544 * r + 28729.085735721943) * r +
            39307.895800092709) * r + 21213.794301586597) * r +
          5394.1960214247511) * r + 687.18700749205789) * r + 42.313330701600911)
       * r + 1.0);
  } else {
    if (u - 0.5 < 0.0) {
      r = sqrt(-log(u));
    } else {
      r = sqrt(-log(1.0 - u));
    }

    if (r <= 5.0) {
      z = ((((((((r - 1.6) * 0.00077454501427834139 + 0.022723844989269184) * (r
                 - 1.6) + 0.24178072517745061) * (r - 1.6) + 1.2704582524523684)
              * (r - 1.6) + 3.6478483247632045) * (r - 1.6) + 5.769497221460691)
            * (r - 1.6) + 4.6303378461565456) * (r - 1.6) + 1.4234371107496835) /
        ((((((((r - 1.6) * 1.0507500716444169E-9 + 0.00054759380849953455) * (r
               - 1.6) + 0.015198666563616457) * (r - 1.6) + 0.14810397642748008)
            * (r - 1.6) + 0.6897673349851) * (r - 1.6) + 1.6763848301838038) *
          (r - 1.6) + 2.053191626637759) * (r - 1.6) + 1.0);
    } else {
      z = ((((((((r - 5.0) * 2.0103343992922881E-7 + 2.7115555687434876E-5) * (r
                 - 5.0) + 0.0012426609473880784) * (r - 5.0) +
               0.026532189526576124) * (r - 5.0) + 0.29656057182850487) * (r -
              5.0) + 1.7848265399172913) * (r - 5.0) + 5.4637849111641144) * (r
            - 5.0) + 6.6579046435011033) / ((((((((r - 5.0) *
        2.0442631033899397E-15 + 1.4215117583164459E-7) * (r - 5.0) +
        1.8463183175100548E-5) * (r - 5.0) + 0.00078686913114561329) * (r - 5.0)
        + 0.014875361290850615) * (r - 5.0) + 0.13692988092273581) * (r - 5.0) +
        0.599832206555888) * (r - 5.0) + 1.0);
    }

    if (u - 0.5 < 0.0) {
      z = -z;
    }
  }

  /* End of Start for MATLABSystem: '<S2>/GPS' */
  return z;
}

static void UAV_Dynamics_RandStream_rand(b_coder_internal_RandStream_U_T *s,
  real_T u[2])
{
  c_coder_internal_mt19937ar_UA_T *obj;
  obj = s->Generator;

  /* Start for MATLABSystem: '<S2>/GPS' */
  u[0] = UAV_Dynamics_mt19937ar_genrandu(obj);
  u[1] = UAV_Dynamics_mt19937ar_genrandu(obj);
}

static real_T UAV_Dy_RandStream_polarGenrandn(b_coder_internal_RandStream_U_T
  *rs)
{
  real_T u[2];
  real_T r;
  real_T s;
  real_T t;
  real_T z;
  if (rs->HaveSavedPolarValue) {
    rs->HaveSavedPolarValue = false;
    z = rs->SavedPolarValue;
  } else {
    do {
      UAV_Dynamics_RandStream_rand(rs, u);
      r = 2.0 * u[0] - 1.0;
      s = 2.0 * u[1] - 1.0;
      t = r * r + s * s;
    } while (!(t <= 1.0));

    t = sqrt(-2.0 * log(t) / t);
    z = r * t;
    rs->HaveSavedPolarValue = true;
    rs->SavedPolarValue = s * t;
  }

  return z;
}

static real_T UAV_RandStream_zigguratGenrandn(b_coder_internal_RandStream_U_T *s)
{
  real_T u[2];
  real_T x;
  real_T z;
  uint32_T ik;
  static const real_T tmp[257] = { 0.0, 0.215241895984875, 0.286174591792068,
    0.335737519214422, 0.375121332878378, 0.408389134611989, 0.43751840220787,
    0.46363433679088, 0.487443966139235, 0.50942332960209, 0.529909720661557,
    0.549151702327164, 0.567338257053817, 0.584616766106378, 0.601104617755991,
    0.61689699000775, 0.63207223638606, 0.646695714894993, 0.660822574244419,
    0.674499822837293, 0.687767892795788, 0.700661841106814, 0.713212285190975,
    0.725446140909999, 0.737387211434295, 0.749056662017815, 0.760473406430107,
    0.771654424224568, 0.782615023307232, 0.793369058840623, 0.80392911698997,
    0.814306670135215, 0.824512208752291, 0.834555354086381, 0.844444954909153,
    0.854189171008163, 0.863795545553308, 0.87327106808886, 0.882622229585165,
    0.891855070732941, 0.900975224461221, 0.909987953496718, 0.91889818364959,
    0.927710533401999, 0.936429340286575, 0.945058684468165, 0.953602409881086,
    0.96206414322304, 0.970447311064224, 0.978755155294224, 0.986990747099062,
    0.99515699963509, 1.00325667954467, 1.01129241744, 1.01926671746548,
    1.02718196603564, 1.03504043983344, 1.04284431314415, 1.05059566459093,
    1.05829648333067, 1.06594867476212, 1.07355406579244, 1.0811144097034,
    1.08863139065398, 1.09610662785202, 1.10354167942464, 1.11093804601357,
    1.11829717411934, 1.12562045921553, 1.13290924865253, 1.14016484436815,
    1.14738850542085, 1.15458145035993, 1.16174485944561, 1.16887987673083,
    1.17598761201545, 1.18306914268269, 1.19012551542669, 1.19715774787944,
    1.20416683014438, 1.2111537262437, 1.21811937548548, 1.22506469375653,
    1.23199057474614, 1.23889789110569, 1.24578749554863, 1.2526602218949,
    1.25951688606371, 1.26635828701823, 1.27318520766536, 1.27999841571382,
    1.28679866449324, 1.29358669373695, 1.30036323033084, 1.30712898903073,
    1.31388467315022, 1.32063097522106, 1.32736857762793, 1.33409815321936,
    1.3408203658964, 1.34753587118059, 1.35424531676263, 1.36094934303328,
    1.36764858359748, 1.37434366577317, 1.38103521107586, 1.38772383568998,
    1.39441015092814, 1.40109476367925, 1.4077782768464, 1.41446128977547,
    1.42114439867531, 1.42782819703026, 1.43451327600589, 1.44120022484872,
    1.44788963128058, 1.45458208188841, 1.46127816251028, 1.46797845861808,
    1.47468355569786, 1.48139403962819, 1.48811049705745, 1.49483351578049,
    1.50156368511546, 1.50830159628131, 1.51504784277671, 1.521803020761,
    1.52856772943771, 1.53534257144151, 1.542128153229, 1.54892508547417,
    1.55573398346918, 1.56255546753104, 1.56939016341512, 1.57623870273591,
    1.58310172339603, 1.58997987002419, 1.59687379442279, 1.60378415602609,
    1.61071162236983, 1.61765686957301, 1.62462058283303, 1.63160345693487,
    1.63860619677555, 1.64562951790478, 1.65267414708306, 1.65974082285818,
    1.66683029616166, 1.67394333092612, 1.68108070472517, 1.68824320943719,
    1.69543165193456, 1.70264685479992, 1.7098896570713, 1.71716091501782,
    1.72446150294804, 1.73179231405296, 1.73915426128591, 1.74654827828172,
    1.75397532031767, 1.76143636531891, 1.76893241491127, 1.77646449552452,
    1.78403365954944, 1.79164098655216, 1.79928758454972, 1.80697459135082,
    1.81470317596628, 1.82247454009388, 1.83028991968276, 1.83815058658281,
    1.84605785028518, 1.8540130597602, 1.86201760539967, 1.87007292107127,
    1.878180486293, 1.88634182853678, 1.8945585256707, 1.90283220855043,
    1.91116456377125, 1.91955733659319, 1.92801233405266, 1.93653142827569,
    1.94511656000868, 1.95376974238465, 1.96249306494436, 1.97128869793366,
    1.98015889690048, 1.98910600761744, 1.99813247135842, 2.00724083056053,
    2.0164337349062, 2.02571394786385, 2.03508435372962, 2.04454796521753,
    2.05410793165065, 2.06376754781173, 2.07353026351874, 2.0833996939983,
    2.09337963113879, 2.10347405571488, 2.11368715068665, 2.12402331568952,
    2.13448718284602, 2.14508363404789, 2.15581781987674, 2.16669518035431,
    2.17772146774029, 2.18890277162636, 2.20024554661128, 2.21175664288416,
    2.22344334009251, 2.23531338492992, 2.24737503294739, 2.25963709517379,
    2.27210899022838, 2.28480080272449, 2.29772334890286, 2.31088825060137,
    2.32430801887113, 2.33799614879653, 2.35196722737914, 2.36623705671729,
    2.38082279517208, 2.39574311978193, 2.41101841390112, 2.42667098493715,
    2.44272531820036, 2.4592083743347, 2.47614993967052, 2.49358304127105,
    2.51154444162669, 2.53007523215985, 2.54922155032478, 2.56903545268184,
    2.58957598670829, 2.61091051848882, 2.63311639363158, 2.65628303757674,
    2.68051464328574, 2.70593365612306, 2.73268535904401, 2.76094400527999,
    2.79092117400193, 2.82287739682644, 2.85713873087322, 2.89412105361341,
    2.93436686720889, 2.97860327988184, 3.02783779176959, 3.08352613200214,
    3.147889289518, 3.2245750520478, 3.32024473383983, 3.44927829856143,
    3.65415288536101, 3.91075795952492 };

  static const real_T tmp_0[257] = { 1.0, 0.977101701267673, 0.959879091800108,
    0.9451989534423, 0.932060075959231, 0.919991505039348, 0.908726440052131,
    0.898095921898344, 0.887984660755834, 0.878309655808918, 0.869008688036857,
    0.860033621196332, 0.851346258458678, 0.842915653112205, 0.834716292986884,
    0.826726833946222, 0.818929191603703, 0.811307874312656, 0.803849483170964,
    0.796542330422959, 0.789376143566025, 0.782341832654803, 0.775431304981187,
    0.768637315798486, 0.761953346836795, 0.755373506507096, 0.748892447219157,
    0.742505296340151, 0.736207598126863, 0.729995264561476, 0.72386453346863,
    0.717811932630722, 0.711834248878248, 0.705928501332754, 0.700091918136512,
    0.694321916126117, 0.688616083004672, 0.682972161644995, 0.677388036218774,
    0.671861719897082, 0.66639134390875, 0.660975147776663, 0.655611470579697,
    0.650298743110817, 0.645035480820822, 0.639820277453057, 0.634651799287624,
    0.629528779924837, 0.624450015547027, 0.619414360605834, 0.614420723888914,
    0.609468064925773, 0.604555390697468, 0.599681752619125, 0.594846243767987,
    0.590047996332826, 0.585286179263371, 0.580559996100791, 0.575868682972354,
    0.571211506735253, 0.566587763256165, 0.561996775814525, 0.557437893618766,
    0.552910490425833, 0.548413963255266, 0.543947731190026, 0.539511234256952,
    0.535103932380458, 0.530725304403662, 0.526374847171684, 0.522052074672322,
    0.517756517229756, 0.513487720747327, 0.509245245995748, 0.505028667943468,
    0.500837575126149, 0.49667156905249, 0.492530263643869, 0.488413284705458,
    0.484320269426683, 0.480250865909047, 0.476204732719506, 0.47218153846773,
    0.468180961405694, 0.464202689048174, 0.460246417812843, 0.456311852678716,
    0.452398706861849, 0.448506701507203, 0.444635565395739, 0.440785034665804,
    0.436954852547985, 0.433144769112652, 0.429354541029442, 0.425583931338022,
    0.421832709229496, 0.418100649837848, 0.414387534040891, 0.410693148270188,
    0.407017284329473, 0.403359739221114, 0.399720314980197, 0.396098818515832,
    0.392495061459315, 0.388908860018789, 0.385340034840077, 0.381788410873393,
    0.378253817245619, 0.374736087137891, 0.371235057668239, 0.367750569779032,
    0.364282468129004, 0.360830600989648, 0.357394820145781, 0.353974980800077,
    0.350570941481406, 0.347182563956794, 0.343809713146851, 0.340452257044522,
    0.337110066637006, 0.333783015830718, 0.330470981379163, 0.327173842813601,
    0.323891482376391, 0.320623784956905, 0.317370638029914, 0.314131931596337,
    0.310907558126286, 0.307697412504292, 0.30450139197665, 0.301319396100803,
    0.298151326696685, 0.294997087799962, 0.291856585617095, 0.288729728482183,
    0.285616426815502, 0.282516593083708, 0.279430141761638, 0.276356989295668,
    0.273297054068577, 0.270250256365875, 0.267216518343561, 0.264195763997261,
    0.261187919132721, 0.258192911337619, 0.255210669954662, 0.252241126055942,
    0.249284212418529, 0.246339863501264, 0.24340801542275, 0.240488605940501,
    0.237581574431238, 0.23468686187233, 0.231804410824339, 0.228934165414681,
    0.226076071322381, 0.223230075763918, 0.220396127480152, 0.217574176724331,
    0.214764175251174, 0.211966076307031, 0.209179834621125, 0.206405406397881,
    0.203642749310335, 0.200891822494657, 0.198152586545776, 0.195425003514135,
    0.192709036903589, 0.190004651670465, 0.187311814223801, 0.1846304924268,
    0.181960655599523, 0.179302274522848, 0.176655321443735, 0.174019770081839,
    0.171395595637506, 0.168782774801212, 0.166181285764482, 0.163591108232366,
    0.161012223437511, 0.158444614155925, 0.15588826472448, 0.153343161060263,
    0.150809290681846, 0.148286642732575, 0.145775208005994, 0.143274978973514,
    0.140785949814445, 0.138308116448551, 0.135841476571254, 0.133386029691669,
    0.130941777173644, 0.12850872228, 0.126086870220186, 0.123676228201597,
    0.12127680548479, 0.11888861344291, 0.116511665625611, 0.114145977827839,
    0.111791568163838, 0.109448457146812, 0.107116667774684, 0.104796225622487,
    0.102487158941935, 0.10018949876881, 0.0979032790388625, 0.095628536713009,
    0.093365311912691, 0.0911136480663738, 0.0888735920682759,
    0.0866451944505581, 0.0844285095703535, 0.082223595813203,
    0.0800305158146631, 0.0778493367020961, 0.0756801303589272,
    0.0735229737139814, 0.0713779490588905, 0.0692451443970068,
    0.0671246538277886, 0.065016577971243, 0.0629210244377582, 0.06083810834954,
    0.0587679529209339, 0.0567106901062031, 0.0546664613248891,
    0.0526354182767924, 0.0506177238609479, 0.0486135532158687,
    0.0466230949019305, 0.0446465522512946, 0.0426841449164746,
    0.0407361106559411, 0.0388027074045262, 0.0368842156885674,
    0.0349809414617162, 0.0330932194585786, 0.0312214171919203,
    0.0293659397581334, 0.0275272356696031, 0.0257058040085489,
    0.0239022033057959, 0.0221170627073089, 0.0203510962300445,
    0.0186051212757247, 0.0168800831525432, 0.0151770883079353,
    0.0134974506017399, 0.0118427578579079, 0.0102149714397015,
    0.00861658276939875, 0.00705087547137324, 0.00552240329925101,
    0.00403797259336304, 0.00260907274610216, 0.0012602859304986,
    0.000477467764609386 };

  int32_T exitg1;
  do {
    exitg1 = 0;
    UAV_Dynamics_RandStream_rand(s, u);
    ik = (uint32_T)(256.0 * u[0]) + 1U;
    z = (2.0 * u[1] - 1.0) * tmp[(int32_T)ik];
    if (fabs(z) <= tmp[(int32_T)ik - 1]) {
      exitg1 = 1;
    } else if (ik < 256U) {
      u[0] = UAV_Dynamics_RandStream_rand_p(s);
      x = tmp_0[(int32_T)ik];
      if ((tmp_0[(int32_T)ik - 1] - x) * u[0] + x < exp(-0.5 * z * z)) {
        exitg1 = 1;
      }
    } else {
      do {
        UAV_Dynamics_RandStream_rand(s, u);
        x = log(u[0]) * 0.273661237329758;
      } while (!(x * x < -2.0 * log(u[1])));

      if (z < 0.0) {
        z = x - 3.65415288536101;
      } else {
        z = 3.65415288536101 - x;
      }

      exitg1 = 1;
    }
  } while (exitg1 == 0);

  return z;
}

static real_T UAV_Dynami_mt19937ar_mtziggurat(c_coder_internal_mt19937ar_UA_T
  *obj)
{
  real_T u;
  real_T x;
  real_T z;
  int32_T i;
  uint32_T u32[2];
  static const real_T tmp[257] = { 0.0, 0.215241895984875, 0.286174591792068,
    0.335737519214422, 0.375121332878378, 0.408389134611989, 0.43751840220787,
    0.46363433679088, 0.487443966139235, 0.50942332960209, 0.529909720661557,
    0.549151702327164, 0.567338257053817, 0.584616766106378, 0.601104617755991,
    0.61689699000775, 0.63207223638606, 0.646695714894993, 0.660822574244419,
    0.674499822837293, 0.687767892795788, 0.700661841106814, 0.713212285190975,
    0.725446140909999, 0.737387211434295, 0.749056662017815, 0.760473406430107,
    0.771654424224568, 0.782615023307232, 0.793369058840623, 0.80392911698997,
    0.814306670135215, 0.824512208752291, 0.834555354086381, 0.844444954909153,
    0.854189171008163, 0.863795545553308, 0.87327106808886, 0.882622229585165,
    0.891855070732941, 0.900975224461221, 0.909987953496718, 0.91889818364959,
    0.927710533401999, 0.936429340286575, 0.945058684468165, 0.953602409881086,
    0.96206414322304, 0.970447311064224, 0.978755155294224, 0.986990747099062,
    0.99515699963509, 1.00325667954467, 1.01129241744, 1.01926671746548,
    1.02718196603564, 1.03504043983344, 1.04284431314415, 1.05059566459093,
    1.05829648333067, 1.06594867476212, 1.07355406579244, 1.0811144097034,
    1.08863139065398, 1.09610662785202, 1.10354167942464, 1.11093804601357,
    1.11829717411934, 1.12562045921553, 1.13290924865253, 1.14016484436815,
    1.14738850542085, 1.15458145035993, 1.16174485944561, 1.16887987673083,
    1.17598761201545, 1.18306914268269, 1.19012551542669, 1.19715774787944,
    1.20416683014438, 1.2111537262437, 1.21811937548548, 1.22506469375653,
    1.23199057474614, 1.23889789110569, 1.24578749554863, 1.2526602218949,
    1.25951688606371, 1.26635828701823, 1.27318520766536, 1.27999841571382,
    1.28679866449324, 1.29358669373695, 1.30036323033084, 1.30712898903073,
    1.31388467315022, 1.32063097522106, 1.32736857762793, 1.33409815321936,
    1.3408203658964, 1.34753587118059, 1.35424531676263, 1.36094934303328,
    1.36764858359748, 1.37434366577317, 1.38103521107586, 1.38772383568998,
    1.39441015092814, 1.40109476367925, 1.4077782768464, 1.41446128977547,
    1.42114439867531, 1.42782819703026, 1.43451327600589, 1.44120022484872,
    1.44788963128058, 1.45458208188841, 1.46127816251028, 1.46797845861808,
    1.47468355569786, 1.48139403962819, 1.48811049705745, 1.49483351578049,
    1.50156368511546, 1.50830159628131, 1.51504784277671, 1.521803020761,
    1.52856772943771, 1.53534257144151, 1.542128153229, 1.54892508547417,
    1.55573398346918, 1.56255546753104, 1.56939016341512, 1.57623870273591,
    1.58310172339603, 1.58997987002419, 1.59687379442279, 1.60378415602609,
    1.61071162236983, 1.61765686957301, 1.62462058283303, 1.63160345693487,
    1.63860619677555, 1.64562951790478, 1.65267414708306, 1.65974082285818,
    1.66683029616166, 1.67394333092612, 1.68108070472517, 1.68824320943719,
    1.69543165193456, 1.70264685479992, 1.7098896570713, 1.71716091501782,
    1.72446150294804, 1.73179231405296, 1.73915426128591, 1.74654827828172,
    1.75397532031767, 1.76143636531891, 1.76893241491127, 1.77646449552452,
    1.78403365954944, 1.79164098655216, 1.79928758454972, 1.80697459135082,
    1.81470317596628, 1.82247454009388, 1.83028991968276, 1.83815058658281,
    1.84605785028518, 1.8540130597602, 1.86201760539967, 1.87007292107127,
    1.878180486293, 1.88634182853678, 1.8945585256707, 1.90283220855043,
    1.91116456377125, 1.91955733659319, 1.92801233405266, 1.93653142827569,
    1.94511656000868, 1.95376974238465, 1.96249306494436, 1.97128869793366,
    1.98015889690048, 1.98910600761744, 1.99813247135842, 2.00724083056053,
    2.0164337349062, 2.02571394786385, 2.03508435372962, 2.04454796521753,
    2.05410793165065, 2.06376754781173, 2.07353026351874, 2.0833996939983,
    2.09337963113879, 2.10347405571488, 2.11368715068665, 2.12402331568952,
    2.13448718284602, 2.14508363404789, 2.15581781987674, 2.16669518035431,
    2.17772146774029, 2.18890277162636, 2.20024554661128, 2.21175664288416,
    2.22344334009251, 2.23531338492992, 2.24737503294739, 2.25963709517379,
    2.27210899022838, 2.28480080272449, 2.29772334890286, 2.31088825060137,
    2.32430801887113, 2.33799614879653, 2.35196722737914, 2.36623705671729,
    2.38082279517208, 2.39574311978193, 2.41101841390112, 2.42667098493715,
    2.44272531820036, 2.4592083743347, 2.47614993967052, 2.49358304127105,
    2.51154444162669, 2.53007523215985, 2.54922155032478, 2.56903545268184,
    2.58957598670829, 2.61091051848882, 2.63311639363158, 2.65628303757674,
    2.68051464328574, 2.70593365612306, 2.73268535904401, 2.76094400527999,
    2.79092117400193, 2.82287739682644, 2.85713873087322, 2.89412105361341,
    2.93436686720889, 2.97860327988184, 3.02783779176959, 3.08352613200214,
    3.147889289518, 3.2245750520478, 3.32024473383983, 3.44927829856143,
    3.65415288536101, 3.91075795952492 };

  static const real_T tmp_0[257] = { 1.0, 0.977101701267673, 0.959879091800108,
    0.9451989534423, 0.932060075959231, 0.919991505039348, 0.908726440052131,
    0.898095921898344, 0.887984660755834, 0.878309655808918, 0.869008688036857,
    0.860033621196332, 0.851346258458678, 0.842915653112205, 0.834716292986884,
    0.826726833946222, 0.818929191603703, 0.811307874312656, 0.803849483170964,
    0.796542330422959, 0.789376143566025, 0.782341832654803, 0.775431304981187,
    0.768637315798486, 0.761953346836795, 0.755373506507096, 0.748892447219157,
    0.742505296340151, 0.736207598126863, 0.729995264561476, 0.72386453346863,
    0.717811932630722, 0.711834248878248, 0.705928501332754, 0.700091918136512,
    0.694321916126117, 0.688616083004672, 0.682972161644995, 0.677388036218774,
    0.671861719897082, 0.66639134390875, 0.660975147776663, 0.655611470579697,
    0.650298743110817, 0.645035480820822, 0.639820277453057, 0.634651799287624,
    0.629528779924837, 0.624450015547027, 0.619414360605834, 0.614420723888914,
    0.609468064925773, 0.604555390697468, 0.599681752619125, 0.594846243767987,
    0.590047996332826, 0.585286179263371, 0.580559996100791, 0.575868682972354,
    0.571211506735253, 0.566587763256165, 0.561996775814525, 0.557437893618766,
    0.552910490425833, 0.548413963255266, 0.543947731190026, 0.539511234256952,
    0.535103932380458, 0.530725304403662, 0.526374847171684, 0.522052074672322,
    0.517756517229756, 0.513487720747327, 0.509245245995748, 0.505028667943468,
    0.500837575126149, 0.49667156905249, 0.492530263643869, 0.488413284705458,
    0.484320269426683, 0.480250865909047, 0.476204732719506, 0.47218153846773,
    0.468180961405694, 0.464202689048174, 0.460246417812843, 0.456311852678716,
    0.452398706861849, 0.448506701507203, 0.444635565395739, 0.440785034665804,
    0.436954852547985, 0.433144769112652, 0.429354541029442, 0.425583931338022,
    0.421832709229496, 0.418100649837848, 0.414387534040891, 0.410693148270188,
    0.407017284329473, 0.403359739221114, 0.399720314980197, 0.396098818515832,
    0.392495061459315, 0.388908860018789, 0.385340034840077, 0.381788410873393,
    0.378253817245619, 0.374736087137891, 0.371235057668239, 0.367750569779032,
    0.364282468129004, 0.360830600989648, 0.357394820145781, 0.353974980800077,
    0.350570941481406, 0.347182563956794, 0.343809713146851, 0.340452257044522,
    0.337110066637006, 0.333783015830718, 0.330470981379163, 0.327173842813601,
    0.323891482376391, 0.320623784956905, 0.317370638029914, 0.314131931596337,
    0.310907558126286, 0.307697412504292, 0.30450139197665, 0.301319396100803,
    0.298151326696685, 0.294997087799962, 0.291856585617095, 0.288729728482183,
    0.285616426815502, 0.282516593083708, 0.279430141761638, 0.276356989295668,
    0.273297054068577, 0.270250256365875, 0.267216518343561, 0.264195763997261,
    0.261187919132721, 0.258192911337619, 0.255210669954662, 0.252241126055942,
    0.249284212418529, 0.246339863501264, 0.24340801542275, 0.240488605940501,
    0.237581574431238, 0.23468686187233, 0.231804410824339, 0.228934165414681,
    0.226076071322381, 0.223230075763918, 0.220396127480152, 0.217574176724331,
    0.214764175251174, 0.211966076307031, 0.209179834621125, 0.206405406397881,
    0.203642749310335, 0.200891822494657, 0.198152586545776, 0.195425003514135,
    0.192709036903589, 0.190004651670465, 0.187311814223801, 0.1846304924268,
    0.181960655599523, 0.179302274522848, 0.176655321443735, 0.174019770081839,
    0.171395595637506, 0.168782774801212, 0.166181285764482, 0.163591108232366,
    0.161012223437511, 0.158444614155925, 0.15588826472448, 0.153343161060263,
    0.150809290681846, 0.148286642732575, 0.145775208005994, 0.143274978973514,
    0.140785949814445, 0.138308116448551, 0.135841476571254, 0.133386029691669,
    0.130941777173644, 0.12850872228, 0.126086870220186, 0.123676228201597,
    0.12127680548479, 0.11888861344291, 0.116511665625611, 0.114145977827839,
    0.111791568163838, 0.109448457146812, 0.107116667774684, 0.104796225622487,
    0.102487158941935, 0.10018949876881, 0.0979032790388625, 0.095628536713009,
    0.093365311912691, 0.0911136480663738, 0.0888735920682759,
    0.0866451944505581, 0.0844285095703535, 0.082223595813203,
    0.0800305158146631, 0.0778493367020961, 0.0756801303589272,
    0.0735229737139814, 0.0713779490588905, 0.0692451443970068,
    0.0671246538277886, 0.065016577971243, 0.0629210244377582, 0.06083810834954,
    0.0587679529209339, 0.0567106901062031, 0.0546664613248891,
    0.0526354182767924, 0.0506177238609479, 0.0486135532158687,
    0.0466230949019305, 0.0446465522512946, 0.0426841449164746,
    0.0407361106559411, 0.0388027074045262, 0.0368842156885674,
    0.0349809414617162, 0.0330932194585786, 0.0312214171919203,
    0.0293659397581334, 0.0275272356696031, 0.0257058040085489,
    0.0239022033057959, 0.0221170627073089, 0.0203510962300445,
    0.0186051212757247, 0.0168800831525432, 0.0151770883079353,
    0.0134974506017399, 0.0118427578579079, 0.0102149714397015,
    0.00861658276939875, 0.00705087547137324, 0.00552240329925101,
    0.00403797259336304, 0.00260907274610216, 0.0012602859304986,
    0.000477467764609386 };

  int32_T exitg1;
  do {
    exitg1 = 0;
    mt19937ar_genrand_uint32_vector(obj, u32);
    i = (int32_T)((u32[1] >> 24U) + 1U);
    z = (((real_T)(u32[0] >> 3U) * 1.6777216E+7 + (real_T)((int32_T)u32[1] &
           16777215)) * 2.2204460492503131E-16 - 1.0) * tmp[i];
    if (fabs(z) <= tmp[i - 1]) {
      exitg1 = 1;
    } else if (i < 256) {
      u = UAV_Dynamics_mt19937ar_genrandu(obj);
      if ((tmp_0[i - 1] - tmp_0[i]) * u + tmp_0[i] < exp(-0.5 * z * z)) {
        exitg1 = 1;
      }
    } else {
      do {
        u = UAV_Dynamics_mt19937ar_genrandu(obj);
        x = log(u) * 0.273661237329758;
        u = UAV_Dynamics_mt19937ar_genrandu(obj);
      } while (!(-2.0 * log(u) > x * x));

      if (z < 0.0) {
        z = x - 3.65415288536101;
      } else {
        z = 3.65415288536101 - x;
      }

      exitg1 = 1;
    }
  } while (exitg1 == 0);

  return z;
}

static void GPSSensorBase_stepRandomStream(fusion_internal_simulink_gpsS_T *obj,
  real_T noise[3])
{
  b_coder_internal_RandStream_U_T *s;
  c_coder_internal_mt19937ar_UA_T *obj_0;
  coder_internal_RngNt_UAV_Dyna_T nt;
  s = obj->pStream;
  nt = s->NtMethod;

  /* Start for MATLABSystem: '<S2>/GPS' */
  if (nt == ziggurat) {
    obj_0 = s->Generator;
    noise[0] = UAV_Dynami_mt19937ar_mtziggurat(obj_0);
    noise[1] = UAV_Dynami_mt19937ar_mtziggurat(obj_0);
    noise[2] = UAV_Dynami_mt19937ar_mtziggurat(obj_0);
  } else if (s->NtMethod == ziggurat) {
    noise[0] = UAV_RandStream_zigguratGenrandn(s);
    noise[1] = UAV_RandStream_zigguratGenrandn(s);
    noise[2] = UAV_RandStream_zigguratGenrandn(s);
  } else if (s->NtMethod == polar) {
    noise[0] = UAV_Dy_RandStream_polarGenrandn(s);
    noise[1] = UAV_Dy_RandStream_polarGenrandn(s);
    noise[2] = UAV_Dy_RandStream_polarGenrandn(s);
  } else {
    noise[0] = UA_RandStream_inversionGenrandn(s);
    noise[1] = UA_RandStream_inversionGenrandn(s);
    noise[2] = UA_RandStream_inversionGenrandn(s);
  }

  /* End of Start for MATLABSystem: '<S2>/GPS' */
}

real_T rt_remd_snf(real_T u0, real_T u1)
{
  real_T y;
  if (rtIsNaN(u0) || rtIsNaN(u1) || rtIsInf(u0)) {
    y = (rtNaN);
  } else if (rtIsInf(u1)) {
    y = u0;
  } else if ((u1 != 0.0) && (u1 != trunc(u1))) {
    real_T q;
    q = fabs(u0 / u1);
    if (!(fabs(q - floor(q + 0.5)) > DBL_EPSILON * q)) {
      y = 0.0 * u0;
    } else {
      y = fmod(u0, u1);
    }
  } else {
    y = fmod(u0, u1);
  }

  return y;
}

static real_T UAV_Dynamics_cosd(real_T x)
{
  real_T absx;
  real_T b_x;

  /* Start for MATLABSystem: '<S2>/GPS' */
  if (rtIsInf(x) || rtIsNaN(x)) {
    b_x = (rtNaN);
  } else {
    b_x = rt_remd_snf(x, 360.0);
    absx = fabs(b_x);
    if (absx > 180.0) {
      if (b_x > 0.0) {
        b_x -= 360.0;
      } else {
        b_x += 360.0;
      }

      absx = fabs(b_x);
    }

    if (absx <= 45.0) {
      b_x = cos(0.017453292519943295 * b_x);
    } else if (absx <= 135.0) {
      if (b_x > 0.0) {
        b_x = -sin((b_x - 90.0) * 0.017453292519943295);
      } else {
        b_x = sin((b_x + 90.0) * 0.017453292519943295);
      }
    } else {
      if (b_x > 0.0) {
        b_x = (b_x - 180.0) * 0.017453292519943295;
      } else {
        b_x = (b_x + 180.0) * 0.017453292519943295;
      }

      b_x = -cos(b_x);
    }
  }

  /* End of Start for MATLABSystem: '<S2>/GPS' */
  return b_x;
}

static real_T UAV_Dynamics_sind(real_T x)
{
  real_T absx;
  real_T b_x;

  /* Start for MATLABSystem: '<S2>/GPS' */
  if (rtIsInf(x) || rtIsNaN(x)) {
    b_x = (rtNaN);
  } else {
    b_x = rt_remd_snf(x, 360.0);
    absx = fabs(b_x);
    if (absx > 180.0) {
      if (b_x > 0.0) {
        b_x -= 360.0;
      } else {
        b_x += 360.0;
      }

      absx = fabs(b_x);
    }

    if (absx <= 45.0) {
      b_x = sin(0.017453292519943295 * b_x);
    } else if (absx <= 135.0) {
      if (b_x > 0.0) {
        b_x = cos((b_x - 90.0) * 0.017453292519943295);
      } else {
        b_x = -cos((b_x + 90.0) * 0.017453292519943295);
      }
    } else {
      if (b_x > 0.0) {
        b_x = (b_x - 180.0) * 0.017453292519943295;
      } else {
        b_x = (b_x + 180.0) * 0.017453292519943295;
      }

      b_x = -sin(b_x);
    }
  }

  /* End of Start for MATLABSystem: '<S2>/GPS' */
  return b_x;
}

real_T rt_hypotd_snf(real_T u0, real_T u1)
{
  real_T a;
  real_T b;
  real_T y;
  a = fabs(u0);
  b = fabs(u1);
  if (a < b) {
    a /= b;
    y = sqrt(a * a + 1.0) * b;
  } else if (a > b) {
    b /= a;
    y = sqrt(b * b + 1.0) * a;
  } else if (rtIsNaN(b)) {
    y = (rtNaN);
  } else {
    y = a * 1.4142135623730951;
  }

  return y;
}

real_T rt_powd_snf(real_T u0, real_T u1)
{
  real_T y;
  if (rtIsNaN(u0) || rtIsNaN(u1)) {
    y = (rtNaN);
  } else {
    real_T tmp;
    real_T tmp_0;
    tmp = fabs(u0);
    tmp_0 = fabs(u1);
    if (rtIsInf(u1)) {
      if (tmp == 1.0) {
        y = 1.0;
      } else if (tmp > 1.0) {
        if (u1 > 0.0) {
          y = (rtInf);
        } else {
          y = 0.0;
        }
      } else if (u1 > 0.0) {
        y = 0.0;
      } else {
        y = (rtInf);
      }
    } else if (tmp_0 == 0.0) {
      y = 1.0;
    } else if (tmp_0 == 1.0) {
      if (u1 > 0.0) {
        y = u0;
      } else {
        y = 1.0 / u0;
      }
    } else if (u1 == 2.0) {
      y = u0 * u0;
    } else if ((u1 == 0.5) && (u0 >= 0.0)) {
      y = sqrt(u0);
    } else if ((u0 < 0.0) && (u1 > floor(u1))) {
      y = (rtNaN);
    } else {
      y = pow(u0, u1);
    }
  }

  return y;
}

real_T rt_urand_Upu32_Yd_f_pw_snf(uint32_T *u)
{
  uint32_T hi;
  uint32_T lo;

  /* Uniform random number generator (random number between 0 and 1)

     #define IA      16807                      magic multiplier = 7^5
     #define IM      2147483647                 modulus = 2^31-1
     #define IQ      127773                     IM div IA
     #define IR      2836                       IM modulo IA
     #define S       4.656612875245797e-10      reciprocal of 2^31-1
     test = IA * (seed % IQ) - IR * (seed/IQ)
     seed = test < 0 ? (test + IM) : test
     return (seed*S)
   */
  lo = *u % 127773U * 16807U;
  hi = *u / 127773U * 2836U;
  if (lo < hi) {
    *u = 2147483647U - (hi - lo);
  } else {
    *u = lo - hi;
  }

  return (real_T)*u * 4.6566128752457969E-10;
}

real_T rt_nrand_Upu32_Yd_f_pw_snf(uint32_T *u)
{
  real_T si;
  real_T sr;
  real_T y;

  /* Normal (Gaussian) random number generator */
  do {
    sr = 2.0 * rt_urand_Upu32_Yd_f_pw_snf(u) - 1.0;
    si = 2.0 * rt_urand_Upu32_Yd_f_pw_snf(u) - 1.0;
    si = sr * sr + si * si;
  } while (si > 1.0);

  y = sqrt(-2.0 * log(si) / si) * sr;
  return y;
}

static void UAV_Dynamics_SystemCore_setup_p(fusion_simulink_imuSensor_UAV_T *obj)
{
  g_fusion_internal_Acceleromet_T *obj_0;
  h_fusion_internal_GyroscopeSi_T *obj_1;
  i_fusion_internal_Magnetomete_T *obj_2;
  real_T ap_AxesMisalignment[9];
  real_T ap_BiasInstability[3];
  real_T ap_ConstantBias[3];
  real_T ap_NoiseDensity[3];
  real_T ap_RandomWalk[3];
  real_T ap_TemperatureBias[3];
  real_T ap_TemperatureScaleFactor[3];
  real_T gp_AccelerationBias[3];
  real_T ap_BiasInstabilityCoefficient_0[2];
  real_T ap_BiasInstabilityCoefficients_;
  real_T ap_MeasurementRange;
  real_T ap_Resolution;
  int32_T i;
  char_T ap_NoiseType_Value[12];
  boolean_T flag;
  obj->isInitialized = 1;

  /* Start for MATLABSystem: '<S3>/IMU1' */
  UAV_D_imuSensor_makeAccelParams(obj, &ap_MeasurementRange, &ap_Resolution,
    ap_ConstantBias, ap_AxesMisalignment, ap_NoiseDensity, ap_BiasInstability,
    ap_RandomWalk, &ap_BiasInstabilityCoefficients_,
    ap_BiasInstabilityCoefficient_0, ap_NoiseType_Value, ap_TemperatureBias,
    ap_TemperatureScaleFactor);
  obj->_pobj2.isInitialized = 0;
  for (i = 0; i < 12; i++) {
    /* Start for MATLABSystem: '<S3>/IMU1' */
    obj->_pobj2.tunablePropertyChanged[i] = false;
  }

  /* Start for MATLABSystem: '<S3>/IMU1' */
  IMUSensorParameters_updateSyste(ap_MeasurementRange, ap_Resolution,
    ap_ConstantBias, ap_AxesMisalignment, ap_NoiseDensity, ap_BiasInstability,
    ap_RandomWalk, ap_BiasInstabilityCoefficients_,
    ap_BiasInstabilityCoefficient_0, ap_NoiseType_Value, ap_TemperatureBias,
    ap_TemperatureScaleFactor, &obj->_pobj2);
  obj->pAccel = &obj->_pobj2;
  obj_0 = obj->pAccel;
  flag = (obj_0->isInitialized == 1);
  if (flag) {
    obj_0->TunablePropsChanged = true;
    obj_0->tunablePropertyChanged[11] = true;
  }

  /* Start for MATLABSystem: '<S3>/IMU1' */
  obj->pAccel->Temperature = obj->Temperature;
  UAV_Dy_imuSensor_makeGyroParams(obj, &ap_MeasurementRange, &ap_Resolution,
    ap_ConstantBias, ap_AxesMisalignment, ap_NoiseDensity, ap_BiasInstability,
    ap_RandomWalk, &ap_BiasInstabilityCoefficients_,
    ap_BiasInstabilityCoefficient_0, ap_NoiseType_Value, ap_TemperatureBias,
    ap_TemperatureScaleFactor, gp_AccelerationBias);
  obj->_pobj1.isInitialized = 0;
  for (i = 0; i < 13; i++) {
    /* Start for MATLABSystem: '<S3>/IMU1' */
    obj->_pobj1.tunablePropertyChanged[i] = false;
  }

  /* Start for MATLABSystem: '<S3>/IMU1' */
  IMUSensorParameters_updateSys_p(ap_MeasurementRange, ap_Resolution,
    ap_ConstantBias, ap_AxesMisalignment, ap_NoiseDensity, ap_BiasInstability,
    ap_RandomWalk, ap_BiasInstabilityCoefficients_,
    ap_BiasInstabilityCoefficient_0, ap_NoiseType_Value, ap_TemperatureBias,
    ap_TemperatureScaleFactor, gp_AccelerationBias, &obj->_pobj1);
  obj->pGyro = &obj->_pobj1;
  obj_1 = obj->pGyro;
  flag = (obj_1->isInitialized == 1);
  if (flag) {
    obj_1->TunablePropsChanged = true;
    obj_1->tunablePropertyChanged[12] = true;
  }

  /* Start for MATLABSystem: '<S3>/IMU1' */
  obj->pGyro->Temperature = obj->Temperature;
  UAV_Dyn_imuSensor_makeMagParams(obj, &ap_MeasurementRange, &ap_Resolution,
    ap_ConstantBias, ap_AxesMisalignment, ap_NoiseDensity, ap_BiasInstability,
    ap_RandomWalk, &ap_BiasInstabilityCoefficients_,
    ap_BiasInstabilityCoefficient_0, ap_NoiseType_Value, ap_TemperatureBias,
    ap_TemperatureScaleFactor);
  obj->_pobj0.isInitialized = 0;
  for (i = 0; i < 12; i++) {
    /* Start for MATLABSystem: '<S3>/IMU1' */
    obj->_pobj0.tunablePropertyChanged[i] = false;
  }

  /* Start for MATLABSystem: '<S3>/IMU1' */
  IMUSensorParameters_updateSy_ph(ap_MeasurementRange, ap_Resolution,
    ap_ConstantBias, ap_AxesMisalignment, ap_NoiseDensity, ap_BiasInstability,
    ap_RandomWalk, ap_BiasInstabilityCoefficients_,
    ap_BiasInstabilityCoefficient_0, ap_NoiseType_Value, ap_TemperatureBias,
    ap_TemperatureScaleFactor, &obj->_pobj0);
  obj->pMag = &obj->_pobj0;
  obj_2 = obj->pMag;
  flag = (obj_2->isInitialized == 1);
  if (flag) {
    obj_2->TunablePropsChanged = true;
    obj_2->tunablePropertyChanged[11] = true;
  }

  /* Start for MATLABSystem: '<S3>/IMU1' */
  obj->pMag->Temperature = obj->Temperature;
  obj->TunablePropsChanged = false;
}

static void UAV_Dyn_IMUSensorBase_resetImpl(fusion_simulink_imuSensor_UAV_T *obj)
{
  g_fusion_internal_Acceleromet_T *obj_0;
  h_fusion_internal_GyroscopeSi_T *obj_1;
  i_fusion_internal_Magnetomete_T *obj_2;
  int32_T i;
  uint32_T b_state[625];
  uint32_T r;
  boolean_T flag;
  for (i = 0; i < 625; i++) {
    /* Start for MATLABSystem: '<S3>/IMU1' */
    obj->pStreamState[i] = 0U;
  }

  for (i = 0; i < 625; i++) {
    /* Start for MATLABSystem: '<S3>/IMU1' */
    b_state[i] = obj->pStreamState[i];
  }

  r = 87254U;
  b_state[0] = 87254U;
  for (i = 0; i < 623; i++) {
    /* Start for MATLABSystem: '<S3>/IMU1' */
    r = ((r >> 30U ^ r) * 1812433253U + (uint32_T)i) + 1U;
    b_state[i + 1] = r;
  }

  b_state[624] = 624U;
  for (i = 0; i < 625; i++) {
    /* Start for MATLABSystem: '<S3>/IMU1' */
    obj->pStreamState[i] = b_state[i];
  }

  /* Start for MATLABSystem: '<S3>/IMU1' */
  flag = (obj->isInitialized == 1);
  if (flag) {
    obj_0 = obj->pAccel;
    if (obj_0->isInitialized == 1) {
      /* Start for MATLABSystem: '<S3>/IMU1' */
      obj_0->pBiasInstFilterStates[0] = 0.0;
      obj_0->pRandWalkFilterStates[0] = 0.0;
      obj_0->pBiasInstFilterStates[1] = 0.0;
      obj_0->pRandWalkFilterStates[1] = 0.0;
      obj_0->pBiasInstFilterStates[2] = 0.0;
      obj_0->pRandWalkFilterStates[2] = 0.0;
    }

    obj_1 = obj->pGyro;
    if (obj_1->isInitialized == 1) {
      /* Start for MATLABSystem: '<S3>/IMU1' */
      obj_1->pBiasInstFilterStates[0] = 0.0;
      obj_1->pRandWalkFilterStates[0] = 0.0;
      obj_1->pBiasInstFilterStates[1] = 0.0;
      obj_1->pRandWalkFilterStates[1] = 0.0;
      obj_1->pBiasInstFilterStates[2] = 0.0;
      obj_1->pRandWalkFilterStates[2] = 0.0;
    }

    obj_2 = obj->pMag;
    if (obj_2->isInitialized == 1) {
      /* Start for MATLABSystem: '<S3>/IMU1' */
      obj_2->pBiasInstFilterStates[0] = 0.0;
      obj_2->pRandWalkFilterStates[0] = 0.0;
      obj_2->pBiasInstFilterStates[1] = 0.0;
      obj_2->pRandWalkFilterStates[1] = 0.0;
      obj_2->pBiasInstFilterStates[2] = 0.0;
      obj_2->pRandWalkFilterStates[2] = 0.0;
    }
  }
}

static void UAV_Dynamics_SystemCore_setup(fusion_internal_simulink_gpsS_T *obj)
{
  int32_T b_statei;
  uint32_T r;
  obj->isInitialized = 1;

  /* Start for MATLABSystem: '<S2>/GPS' */
  obj->_pobj0.SavedPolarValue = 0.0;
  obj->_pobj0.HaveSavedPolarValue = false;
  obj->_pobj0.MtGenerator.Seed = 67U;
  r = obj->_pobj0.MtGenerator.Seed;
  obj->_pobj0.MtGenerator.State[0] = r;
  for (b_statei = 0; b_statei < 623; b_statei++) {
    /* Start for MATLABSystem: '<S2>/GPS' */
    r = ((r >> 30U ^ r) * 1812433253U + (uint32_T)b_statei) + 1U;
    obj->_pobj0.MtGenerator.State[b_statei + 1] = r;
  }

  /* Start for MATLABSystem: '<S2>/GPS' */
  obj->_pobj0.MtGenerator.State[624] = 624U;
  obj->_pobj0.Generator = &obj->_pobj0.MtGenerator;
  obj->_pobj0.NtMethod = ziggurat;
  obj->pStream = &obj->_pobj0;
  obj->pPositionErrorFilterStates[0] = 0.0;
  obj->pPositionErrorFilterStates[1] = 0.0;
  obj->pPositionErrorFilterStates[2] = 0.0;
  obj->TunablePropsChanged = false;
}

static void UAV_Dyn_GPSSensorBase_resetImpl(fusion_internal_simulink_gpsS_T *obj)
{
  b_coder_internal_RandStream_U_T *s;
  c_coder_internal_mt19937ar_UA_T *obj_0;
  int32_T b_statei;
  uint32_T nseed;

  /* Start for MATLABSystem: '<S2>/GPS' */
  s = obj->pStream;
  nseed = s->Generator->Seed;
  obj_0 = s->Generator;

  /* Start for MATLABSystem: '<S2>/GPS' */
  if (nseed == 0U) {
    obj_0->Seed = 5489U;
  } else {
    obj_0->Seed = nseed;
  }

  nseed = obj_0->Seed;
  obj_0->State[0] = nseed;
  for (b_statei = 0; b_statei < 623; b_statei++) {
    /* Start for MATLABSystem: '<S2>/GPS' */
    nseed = ((nseed >> 30U ^ nseed) * 1812433253U + (uint32_T)b_statei) + 1U;
    obj_0->State[b_statei + 1] = nseed;
  }

  real_T b_x;
  real_T decayFactor;
  real_T horzSigma;
  real_T vertSigma;
  obj_0->State[624] = 624U;

  /* Start for MATLABSystem: '<S2>/GPS' */
  decayFactor = obj->DecayFactor;
  horzSigma = obj->HorizontalPositionAccuracy;
  vertSigma = obj->VerticalPositionAccuracy;
  b_x = sqrt(0.02 / (0.01 / (1.0 - decayFactor)));
  horzSigma *= b_x;
  obj->pSigmaScaled[0] = horzSigma;
  obj->pSigmaScaled[1] = horzSigma;
  obj->pSigmaScaled[2] = vertSigma * b_x;
  obj->pPositionErrorFilterNum = 1.0;
  obj->pPositionErrorFilterDen[0] = 1.0;
  obj->pPositionErrorFilterDen[1] = -decayFactor;
  obj->pPositionErrorFilterStates[0] = 0.0;
  obj->pPositionErrorFilterStates[1] = 0.0;
  obj->pPositionErrorFilterStates[2] = 0.0;
}

/* Model step function */
void UAV_Dynamics_step(void)
{
  __m128d tmp_1;
  __m128d tmp_2;
  __m128d tmp_3;
  __m128d tmp_4;
  __m128d tmp_5;
  __m128d tmp_6;
  __m128d tmp_7;
  c_coder_internal_mt19937ar_UA_T *obj;
  real_T rtb_Transpose_tmp[9];
  real_T rtb_VectorConcatenate[9];
  real_T rtb_CoordinateTransformationCon[4];
  real_T c[3];
  real_T c_0[3];
  real_T rtb_MatrixMultiply1[3];
  real_T rtb_Sum_ha[3];
  real_T rtb_Transpose_tmp_0[3];
  real_T rtb_Transpose_tmp_1[3];
  real_T rtb_VectorConcatenate_0[3];
  real_T tmp_0[3];
  real_T au;
  real_T bv;
  real_T gndSpeed;
  real_T rtb_TransferFcn;
  real_T rtb_TransferFcn4;
  real_T rtb_VectorConcatenate_tmp;
  real_T rtb_fcn3;
  real_T rtb_ixj;
  real_T rtb_ixj_k;
  real_T rtb_ixk;
  real_T rtb_jxi;
  real_T rtb_kxi;
  real_T rtb_kxi_tmp;
  real_T tmp;
  coder_internal_RngNt_UAV_Dyna_T nt;
  int32_T count;
  boolean_T iterate;
  if (rtmIsMajorTimeStep(UAV_Dynamics_M)) {
    /* set solver stop time */
    rtsiSetSolverStopTime(&UAV_Dynamics_M->solverInfo,
                          ((UAV_Dynamics_M->Timing.clockTick0+1)*
      UAV_Dynamics_M->Timing.stepSize0));
  }                                    /* end MajorTimeStep */

  /* Update absolute time of base rate at minor time step */
  if (rtmIsMinorTimeStep(UAV_Dynamics_M)) {
    UAV_Dynamics_M->Timing.t[0] = rtsiGetT(&UAV_Dynamics_M->solverInfo);
  }

  /* Integrator: '<S10>/q0 q1 q2 q3' incorporates:
   *  SignalConversion generated from: '<S10>/q0 q1 q2 q3'
   */
  if (UAV_Dynamics_DW.q0q1q2q3_IWORK != 0) {
    UAV_Dynamics_X.q0q1q2q3_CSTATE[0] = UAV_Dynamics_ConstB.q0;
    UAV_Dynamics_X.q0q1q2q3_CSTATE[1] = UAV_Dynamics_ConstB.q1;
    UAV_Dynamics_X.q0q1q2q3_CSTATE[2] = UAV_Dynamics_ConstB.q2;
    UAV_Dynamics_X.q0q1q2q3_CSTATE[3] = UAV_Dynamics_ConstB.q3;
  }

  /* Sqrt: '<S33>/sqrt' incorporates:
   *  Integrator: '<S10>/q0 q1 q2 q3'
   *  Product: '<S34>/Product'
   *  Product: '<S34>/Product1'
   *  Product: '<S34>/Product2'
   *  Product: '<S34>/Product3'
   *  Sqrt: '<S41>/sqrt'
   *  Sum: '<S34>/Sum'
   */
  rtb_TransferFcn = sqrt(((UAV_Dynamics_X.q0q1q2q3_CSTATE[0] *
    UAV_Dynamics_X.q0q1q2q3_CSTATE[0] + UAV_Dynamics_X.q0q1q2q3_CSTATE[1] *
    UAV_Dynamics_X.q0q1q2q3_CSTATE[1]) + UAV_Dynamics_X.q0q1q2q3_CSTATE[2] *
    UAV_Dynamics_X.q0q1q2q3_CSTATE[2]) + UAV_Dynamics_X.q0q1q2q3_CSTATE[3] *
    UAV_Dynamics_X.q0q1q2q3_CSTATE[3]);

  /* Product: '<S32>/Product' incorporates:
   *  Integrator: '<S10>/q0 q1 q2 q3'
   *  Sqrt: '<S33>/sqrt'
   */
  rtb_kxi = UAV_Dynamics_X.q0q1q2q3_CSTATE[0] / rtb_TransferFcn;

  /* Product: '<S32>/Product1' incorporates:
   *  Integrator: '<S10>/q0 q1 q2 q3'
   *  Sqrt: '<S33>/sqrt'
   */
  rtb_ixk = UAV_Dynamics_X.q0q1q2q3_CSTATE[1] / rtb_TransferFcn;

  /* Product: '<S32>/Product2' incorporates:
   *  Integrator: '<S10>/q0 q1 q2 q3'
   *  Sqrt: '<S33>/sqrt'
   */
  rtb_jxi = UAV_Dynamics_X.q0q1q2q3_CSTATE[2] / rtb_TransferFcn;

  /* Product: '<S32>/Product3' incorporates:
   *  Integrator: '<S10>/q0 q1 q2 q3'
   *  Product: '<S36>/Product3'
   *  Sqrt: '<S33>/sqrt'
   */
  rtb_ixj = UAV_Dynamics_X.q0q1q2q3_CSTATE[3] / rtb_TransferFcn;

  /* Product: '<S22>/Product3' incorporates:
   *  Product: '<S26>/Product3'
   */
  rtb_fcn3 = rtb_kxi * rtb_kxi;

  /* Product: '<S22>/Product2' incorporates:
   *  Fcn: '<S19>/fcn2'
   *  Fcn: '<S19>/fcn5'
   *  Product: '<S26>/Product2'
   */
  rtb_ixj_k = rtb_ixk * rtb_ixk;

  /* Product: '<S22>/Product1' incorporates:
   *  Fcn: '<S19>/fcn2'
   *  Fcn: '<S19>/fcn5'
   *  Product: '<S26>/Product1'
   *  Product: '<S30>/Product1'
   */
  gndSpeed = rtb_jxi * rtb_jxi;

  /* Product: '<S22>/Product' incorporates:
   *  Fcn: '<S19>/fcn5'
   *  Product: '<S32>/Product3'
   */
  au = rtb_ixj * rtb_ixj;

  /* Sum: '<S22>/Sum' incorporates:
   *  Product: '<S22>/Product'
   *  Product: '<S22>/Product1'
   *  Product: '<S22>/Product2'
   *  Product: '<S22>/Product3'
   */
  rtb_VectorConcatenate[0] = ((rtb_fcn3 + rtb_ixj_k) - gndSpeed) - au;

  /* Product: '<S25>/Product3' incorporates:
   *  Product: '<S23>/Product3'
   *  Product: '<S32>/Product3'
   */
  bv = rtb_ixj * rtb_kxi;

  /* Product: '<S25>/Product2' incorporates:
   *  Fcn: '<S19>/fcn1'
   *  Product: '<S23>/Product2'
   */
  rtb_TransferFcn4 = rtb_ixk * rtb_jxi;

  /* Gain: '<S25>/Gain' incorporates:
   *  Product: '<S25>/Product2'
   *  Product: '<S25>/Product3'
   *  Sum: '<S25>/Sum'
   */
  rtb_VectorConcatenate[1] = (rtb_TransferFcn4 - bv) * 2.0;

  /* Product: '<S28>/Product2' incorporates:
   *  Fcn: '<S19>/fcn3'
   *  Product: '<S32>/Product3'
   */
  tmp = rtb_ixk * rtb_ixj;

  /* Product: '<S28>/Product1' incorporates:
   *  Product: '<S24>/Product1'
   */
  rtb_VectorConcatenate_tmp = rtb_kxi * rtb_jxi;

  /* Gain: '<S28>/Gain' incorporates:
   *  Product: '<S28>/Product1'
   *  Product: '<S28>/Product2'
   *  Sum: '<S28>/Sum'
   */
  rtb_VectorConcatenate[2] = (rtb_VectorConcatenate_tmp + tmp) * 2.0;

  /* Gain: '<S23>/Gain' incorporates:
   *  Sum: '<S23>/Sum'
   */
  rtb_VectorConcatenate[3] = (bv + rtb_TransferFcn4) * 2.0;

  /* Sum: '<S26>/Sum' incorporates:
   *  Product: '<S22>/Product'
   *  Sum: '<S30>/Sum'
   */
  rtb_fcn3 -= rtb_ixj_k;
  rtb_VectorConcatenate[4] = (rtb_fcn3 + gndSpeed) - au;

  /* Product: '<S29>/Product1' incorporates:
   *  Product: '<S27>/Product1'
   */
  bv = rtb_kxi * rtb_ixk;

  /* Product: '<S29>/Product2' incorporates:
   *  Fcn: '<S19>/fcn4'
   *  Product: '<S32>/Product3'
   */
  rtb_kxi_tmp = rtb_jxi * rtb_ixj;

  /* Gain: '<S29>/Gain' incorporates:
   *  Product: '<S29>/Product1'
   *  Product: '<S29>/Product2'
   *  Sum: '<S29>/Sum'
   */
  rtb_VectorConcatenate[5] = (rtb_kxi_tmp - bv) * 2.0;

  /* Gain: '<S24>/Gain' incorporates:
   *  Product: '<S28>/Product2'
   *  Sum: '<S24>/Sum'
   */
  rtb_VectorConcatenate[6] = (tmp - rtb_VectorConcatenate_tmp) * 2.0;

  /* Gain: '<S27>/Gain' incorporates:
   *  Product: '<S29>/Product2'
   *  Sum: '<S27>/Sum'
   */
  rtb_VectorConcatenate[7] = (bv + rtb_kxi_tmp) * 2.0;

  /* Sum: '<S30>/Sum' incorporates:
   *  Product: '<S22>/Product'
   */
  rtb_VectorConcatenate[8] = (rtb_fcn3 - gndSpeed) + au;
  for (count = 0; count < 3; count++) {
    /* Math: '<S4>/Transpose' incorporates:
     *  Concatenate: '<S31>/Vector Concatenate'
     *  Math: '<S52>/Transpose'
     *  Math: '<S7>/Transpose'
     */
    rtb_Transpose_tmp[3 * count] = rtb_VectorConcatenate[count];
    rtb_Transpose_tmp[3 * count + 1] = rtb_VectorConcatenate[count + 3];
    rtb_Transpose_tmp[3 * count + 2] = rtb_VectorConcatenate[count + 6];
  }

  /* DotProduct: '<S21>/Dot Product' incorporates:
   *  Integrator: '<S10>/q0 q1 q2 q3'
   */
  rtb_fcn3 = ((UAV_Dynamics_X.q0q1q2q3_CSTATE[0] *
               UAV_Dynamics_X.q0q1q2q3_CSTATE[0] +
               UAV_Dynamics_X.q0q1q2q3_CSTATE[1] *
               UAV_Dynamics_X.q0q1q2q3_CSTATE[1]) +
              UAV_Dynamics_X.q0q1q2q3_CSTATE[2] *
              UAV_Dynamics_X.q0q1q2q3_CSTATE[2]) +
    UAV_Dynamics_X.q0q1q2q3_CSTATE[3] * UAV_Dynamics_X.q0q1q2q3_CSTATE[3];

  /* SignalConversion generated from: '<S10>/q0 q1 q2 q3' incorporates:
   *  Constant: '<S21>/Constant'
   *  DotProduct: '<S21>/Dot Product'
   *  Fcn: '<S21>/q0dot'
   *  Fcn: '<S21>/q1dot'
   *  Fcn: '<S21>/q2dot'
   *  Fcn: '<S21>/q3dot'
   *  Integrator: '<S10>/q0 q1 q2 q3'
   *  Integrator: '<S7>/p,q,r '
   *  Sum: '<S21>/Sum'
   */
  UAV_Dynamics_B.TmpSignalConversionAtq0q1q2q3_a[0] =
    ((UAV_Dynamics_X.pqr_CSTATE[0] * UAV_Dynamics_X.q0q1q2q3_CSTATE[1] +
      UAV_Dynamics_X.pqr_CSTATE[1] * UAV_Dynamics_X.q0q1q2q3_CSTATE[2]) +
     UAV_Dynamics_X.pqr_CSTATE[2] * UAV_Dynamics_X.q0q1q2q3_CSTATE[3]) * -0.5 +
    (1.0 - rtb_fcn3) * UAV_Dynamics_X.q0q1q2q3_CSTATE[0];
  UAV_Dynamics_B.TmpSignalConversionAtq0q1q2q3_a[1] =
    ((UAV_Dynamics_X.q0q1q2q3_CSTATE[0] * UAV_Dynamics_X.pqr_CSTATE[0] +
      UAV_Dynamics_X.q0q1q2q3_CSTATE[2] * UAV_Dynamics_X.pqr_CSTATE[2]) -
     UAV_Dynamics_X.pqr_CSTATE[1] * UAV_Dynamics_X.q0q1q2q3_CSTATE[3]) * 0.5 +
    (1.0 - rtb_fcn3) * UAV_Dynamics_X.q0q1q2q3_CSTATE[1];
  UAV_Dynamics_B.TmpSignalConversionAtq0q1q2q3_a[2] =
    ((UAV_Dynamics_X.q0q1q2q3_CSTATE[0] * UAV_Dynamics_X.pqr_CSTATE[1] +
      UAV_Dynamics_X.pqr_CSTATE[0] * UAV_Dynamics_X.q0q1q2q3_CSTATE[3]) -
     UAV_Dynamics_X.q0q1q2q3_CSTATE[1] * UAV_Dynamics_X.pqr_CSTATE[2]) * 0.5 +
    (1.0 - rtb_fcn3) * UAV_Dynamics_X.q0q1q2q3_CSTATE[2];
  UAV_Dynamics_B.TmpSignalConversionAtq0q1q2q3_a[3] =
    ((UAV_Dynamics_X.q0q1q2q3_CSTATE[0] * UAV_Dynamics_X.pqr_CSTATE[2] +
      UAV_Dynamics_X.q0q1q2q3_CSTATE[1] * UAV_Dynamics_X.pqr_CSTATE[1]) -
     UAV_Dynamics_X.pqr_CSTATE[0] * UAV_Dynamics_X.q0q1q2q3_CSTATE[2]) * 0.5 +
    (1.0 - rtb_fcn3) * UAV_Dynamics_X.q0q1q2q3_CSTATE[3];

  /* Product: '<S36>/Product' incorporates:
   *  Integrator: '<S10>/q0 q1 q2 q3'
   */
  rtb_kxi = UAV_Dynamics_X.q0q1q2q3_CSTATE[0] / rtb_TransferFcn;

  /* Fcn: '<S19>/fcn3' */
  rtb_fcn3 = (tmp - rtb_kxi * rtb_jxi) * -2.0;

  /* If: '<S37>/If' */
  if (rtsiIsModeUpdateTimeStep(&UAV_Dynamics_M->solverInfo)) {
    if (rtb_fcn3 > 1.0) {
      UAV_Dynamics_DW.If_ActiveSubsystem = 0;
    } else if (rtb_fcn3 < -1.0) {
      UAV_Dynamics_DW.If_ActiveSubsystem = 1;
    } else {
      UAV_Dynamics_DW.If_ActiveSubsystem = 2;
    }
  }

  switch (UAV_Dynamics_DW.If_ActiveSubsystem) {
   case 0:
    /* Outputs for IfAction SubSystem: '<S37>/If Action Subsystem' incorporates:
     *  ActionPort: '<S38>/Action Port'
     */
    if (rtmIsMajorTimeStep(UAV_Dynamics_M)) {
      /* Merge: '<S37>/Merge' incorporates:
       *  Constant: '<S38>/Constant'
       */
      UAV_Dynamics_B.Merge = 1.0;
    }

    /* End of Outputs for SubSystem: '<S37>/If Action Subsystem' */
    break;

   case 1:
    /* Outputs for IfAction SubSystem: '<S37>/If Action Subsystem1' incorporates:
     *  ActionPort: '<S39>/Action Port'
     */
    if (rtmIsMajorTimeStep(UAV_Dynamics_M)) {
      /* Merge: '<S37>/Merge' incorporates:
       *  Constant: '<S39>/Constant'
       */
      UAV_Dynamics_B.Merge = 1.0;
    }

    /* End of Outputs for SubSystem: '<S37>/If Action Subsystem1' */
    break;

   default:
    /* Outputs for IfAction SubSystem: '<S37>/If Action Subsystem2' incorporates:
     *  ActionPort: '<S40>/Action Port'
     */
    /* Merge: '<S37>/Merge' incorporates:
     *  SignalConversion generated from: '<S40>/In'
     */
    UAV_Dynamics_B.Merge = rtb_fcn3;

    /* End of Outputs for SubSystem: '<S37>/If Action Subsystem2' */
    break;
  }

  /* End of If: '<S37>/If' */

  /* Trigonometry: '<S35>/trigFcn' incorporates:
   *  Concatenate: '<S35>/Vector Concatenate'
   */
  if (UAV_Dynamics_B.Merge > 1.0) {
    rtb_fcn3 = 1.0;
  } else if (UAV_Dynamics_B.Merge < -1.0) {
    rtb_fcn3 = -1.0;
  } else {
    rtb_fcn3 = UAV_Dynamics_B.Merge;
  }

  rtb_fcn3 = asin(rtb_fcn3);

  /* End of Trigonometry: '<S35>/trigFcn' */

  /* Fcn: '<S19>/fcn5' incorporates:
   *  Fcn: '<S19>/fcn2'
   */
  rtb_TransferFcn = rtb_kxi * rtb_kxi;

  /* Trigonometry: '<S35>/Trigonometric Function3' incorporates:
   *  Concatenate: '<S35>/Vector Concatenate'
   *  Fcn: '<S19>/fcn4'
   *  Fcn: '<S19>/fcn5'
   */
  rtb_ixk = rt_atan2d_snf((rtb_kxi * rtb_ixk + rtb_kxi_tmp) * 2.0,
    ((rtb_TransferFcn - rtb_ixj_k) - gndSpeed) + au);
  if (rtmIsMajorTimeStep(UAV_Dynamics_M)) {
    /* Start for MATLABSystem: '<S3>/Coordinate Transformation Conversion1' incorporates:
     *  Fcn: '<S19>/fcn1'
     *  Fcn: '<S19>/fcn2'
     *  Trigonometry: '<S35>/Trigonometric Function1'
     */
    rtb_ixj_k = rt_atan2d_snf((rtb_kxi * rtb_ixj + rtb_TransferFcn4) * 2.0,
      ((rtb_TransferFcn + rtb_ixj_k) - gndSpeed) - au) / 2.0;
    rtb_Sum_ha[0] = rtb_ixj_k;

    /* MATLABSystem: '<S3>/Coordinate Transformation Conversion1' */
    c[0] = rtb_ixj_k;

    /* Start for MATLABSystem: '<S3>/Coordinate Transformation Conversion1' */
    rtb_ixj_k = rtb_fcn3 / 2.0;
    rtb_Sum_ha[1] = rtb_ixj_k;

    /* MATLABSystem: '<S3>/Coordinate Transformation Conversion1' */
    c[1] = rtb_ixj_k;

    /* Start for MATLABSystem: '<S3>/Coordinate Transformation Conversion1' */
    rtb_ixj_k = rtb_ixk / 2.0;

    /* MATLABSystem: '<S3>/Coordinate Transformation Conversion1' */
    c[0] = cos(c[0]);
    rtb_Sum_ha[0] = sin(rtb_Sum_ha[0]);
    c[1] = cos(c[1]);
    rtb_Sum_ha[1] = sin(rtb_Sum_ha[1]);
    c[2] = cos(rtb_ixj_k);
    rtb_Sum_ha[2] = sin(rtb_ixj_k);
    rtb_CoordinateTransformationCon[0] = c[0] * c[1] * c[2] + rtb_Sum_ha[0] *
      rtb_Sum_ha[1] * rtb_Sum_ha[2];
    rtb_CoordinateTransformationCon[1] = c[0] * c[1] * rtb_Sum_ha[2] -
      rtb_Sum_ha[0] * rtb_Sum_ha[1] * c[2];
    rtb_CoordinateTransformationCon[2] = c[0] * rtb_Sum_ha[1] * c[2] +
      rtb_Sum_ha[0] * c[1] * rtb_Sum_ha[2];
    rtb_CoordinateTransformationCon[3] = rtb_Sum_ha[0] * c[1] * c[2] - c[0] *
      rtb_Sum_ha[1] * rtb_Sum_ha[2];
  }

  /* TransferFcn: '<S63>/Transfer Fcn4' */
  rtb_TransferFcn4 = 80.0 * UAV_Dynamics_X.TransferFcn4_CSTATE;

  /* TransferFcn: '<S63>/Transfer Fcn3' */
  rtb_kxi = 80.0 * UAV_Dynamics_X.TransferFcn3_CSTATE;

  /* TransferFcn: '<S63>/Transfer Fcn2' */
  rtb_jxi = 80.0 * UAV_Dynamics_X.TransferFcn2_CSTATE;

  /* TransferFcn: '<S63>/Transfer Fcn' */
  rtb_TransferFcn = 80.0 * UAV_Dynamics_X.TransferFcn_CSTATE;

  /* MATLAB Function: '<S53>/MATLAB Function' incorporates:
   *  Constant: '<S53>/Constant'
   *  SignalConversion generated from: '<S62>/ SFunction '
   *  TransferFcn: '<S64>/Transfer Fcn1'
   *  TransferFcn: '<S64>/Transfer Fcn2'
   *  TransferFcn: '<S64>/Transfer Fcn3'
   *  TransferFcn: '<S64>/Transfer Fcn4'
   */
  rtb_ixj = 0.11667261889578034 * -rtb_TransferFcn4;
  rtb_ixj_k = -0.11667261889578034 * -rtb_kxi;
  c[0] = ((rtb_ixj + rtb_ixj_k) + -0.11667261889578034 * -rtb_jxi) +
    0.11667261889578034 * -rtb_TransferFcn;
  c[1] = (((0.0 - rtb_ixj) + (0.0 - rtb_ixj_k)) + (0.0 - 0.11667261889578034 *
           -rtb_jxi)) + (0.0 - -0.11667261889578034 * -rtb_TransferFcn);
  c[2] = (((0.0 - (-UAV_Dynamics_X.TransferFcn1_CSTATE)) -
           (-UAV_Dynamics_X.TransferFcn2_CSTATE_i)) -
          UAV_Dynamics_X.TransferFcn3_CSTATE_o) -
    UAV_Dynamics_X.TransferFcn4_CSTATE_j;

  /* DotProduct: '<S50>/Dot Product' */
  rtb_ixj_k = 0.0;
  for (count = 0; count < 3; count++) {
    /* Product: '<S52>/Matrix Multiply1' incorporates:
     *  Integrator: '<S7>/ub,vb,wb'
     *  Math: '<S52>/Transpose'
     */
    rtb_MatrixMultiply1[count] = (rtb_Transpose_tmp[count + 3] *
      UAV_Dynamics_X.ubvbwb_CSTATE[1] + rtb_Transpose_tmp[count] *
      UAV_Dynamics_X.ubvbwb_CSTATE[0]) + rtb_Transpose_tmp[count + 6] *
      UAV_Dynamics_X.ubvbwb_CSTATE[2];

    /* Sum: '<S50>/relative air velocity (body frame)' incorporates:
     *  Concatenate: '<S31>/Vector Concatenate'
     *  Constant: '<S50>/Constant'
     *  Integrator: '<S7>/ub,vb,wb'
     *  Product: '<S50>/wind (body frame)'
     */
    gndSpeed = ((rtb_VectorConcatenate[count + 3] * 0.0 +
                 rtb_VectorConcatenate[count] * 0.0) +
                rtb_VectorConcatenate[count + 6] * 0.0) -
      UAV_Dynamics_X.ubvbwb_CSTATE[count];
    rtb_Sum_ha[count] = gndSpeed;

    /* DotProduct: '<S50>/Dot Product' */
    rtb_ixj_k += gndSpeed * gndSpeed;
  }

  /* Saturate: '<S50>/Saturation' incorporates:
   *  DotProduct: '<S50>/Dot Product'
   */
  if (rtb_ixj_k <= 0.0001) {
    rtb_ixj_k = 0.0001;
  }

  /* Sqrt: '<S50>/Square Root' incorporates:
   *  Saturate: '<S50>/Saturation'
   */
  rtb_ixj_k = sqrt(rtb_ixj_k);

  /* Switch: '<S57>/Switch' incorporates:
   *  Constant: '<S57>/Constant'
   *  Gain: '<S57>/Damper Kp'
   *  Gain: '<S57>/Spring Kp'
   *  Integrator: '<S7>/xe,ye,ze'
   *  Sum: '<S57>/Add'
   *  UnaryMinus: '<S57>/Unary Minus'
   *  UnaryMinus: '<S57>/Unary Minus1'
   */
  if (-UAV_Dynamics_X.xeyeze_CSTATE[2] > 0.0) {
    rtb_ixj = 0.0;
  } else {
    rtb_ixj = -3100.0 * -UAV_Dynamics_X.xeyeze_CSTATE[2] + -100.0 *
      -rtb_MatrixMultiply1[2];
  }

  /* End of Switch: '<S57>/Switch' */

  /* Saturate: '<S57>/Saturation' */
  if (rtb_ixj > 80.0) {
    rtb_ixj = 80.0;
  } else if (rtb_ixj < 0.0) {
    rtb_ixj = 0.0;
  }

  /* End of Saturate: '<S57>/Saturation' */
  for (count = 0; count <= 0; count += 2) {
    /* Product: '<S51>/Matrix Multiply' incorporates:
     *  Concatenate: '<S31>/Vector Concatenate'
     *  Constant: '<S51>/Constant'
     */
    tmp_3 = _mm_loadu_pd(&rtb_VectorConcatenate[count + 3]);
    tmp_6 = _mm_set1_pd(0.0);
    tmp_4 = _mm_loadu_pd(&rtb_VectorConcatenate[count]);
    tmp_5 = _mm_loadu_pd(&rtb_VectorConcatenate[count + 6]);
    _mm_storeu_pd(&rtb_VectorConcatenate_0[count], _mm_add_pd(_mm_add_pd
      (_mm_mul_pd(tmp_3, tmp_6), _mm_mul_pd(tmp_4, tmp_6)), _mm_mul_pd(tmp_5,
      _mm_set1_pd(9.81))));
  }

  /* Product: '<S51>/Matrix Multiply' incorporates:
   *  Concatenate: '<S31>/Vector Concatenate'
   *  Constant: '<S51>/Constant'
   */
  for (count = 2; count < 3; count++) {
    rtb_VectorConcatenate_0[count] = (rtb_VectorConcatenate[count + 3] * 0.0 +
      rtb_VectorConcatenate[count] * 0.0) + rtb_VectorConcatenate[count + 6] *
      9.81;
  }

  /* MATLAB Function: '<S53>/MATLAB Function' incorporates:
   *  SignalConversion generated from: '<S62>/ SFunction '
   */
  tmp_0[0] = 0.0;
  tmp_0[1] = 0.0;
  tmp_0[2] = -(((rtb_TransferFcn4 + rtb_kxi) + rtb_jxi) + rtb_TransferFcn);

  /* Saturate: '<S55>/Saturation' incorporates:
   *  Gain: '<S60>/friction coefficient'
   *  Gain: '<S60>/vd'
   *  Product: '<S55>/Product'
   *  Trigonometry: '<S60>/Tanh'
   *  UnaryMinus: '<S55>/Unary Minus'
   */
  gndSpeed = -(tanh(50.0 * rtb_MatrixMultiply1[0]) * 0.5 * rtb_ixj);
  if (gndSpeed > 20.0) {
    /* SignalConversion generated from: '<S52>/Matrix Multiply' */
    gndSpeed = 20.0;
  } else if (gndSpeed < -20.0) {
    /* SignalConversion generated from: '<S52>/Matrix Multiply' */
    gndSpeed = -20.0;
  }

  rtb_TransferFcn4 = -(tanh(50.0 * rtb_MatrixMultiply1[1]) * 0.5 * rtb_ixj);
  if (rtb_TransferFcn4 > 20.0) {
    /* SignalConversion generated from: '<S52>/Matrix Multiply' */
    rtb_TransferFcn4 = 20.0;
  } else if (rtb_TransferFcn4 < -20.0) {
    /* SignalConversion generated from: '<S52>/Matrix Multiply' */
    rtb_TransferFcn4 = -20.0;
  }

  /* End of Saturate: '<S55>/Saturation' */
  for (count = 0; count <= 0; count += 2) {
    /* Product: '<S7>/Product' incorporates:
     *  Concatenate: '<S31>/Vector Concatenate'
     *  Product: '<S52>/Matrix Multiply'
     */
    tmp_3 = _mm_loadu_pd(&rtb_VectorConcatenate[count + 3]);
    tmp_6 = _mm_loadu_pd(&rtb_VectorConcatenate[count]);
    tmp_4 = _mm_loadu_pd(&rtb_VectorConcatenate[count + 6]);

    /* Gain: '<S51>/Gain' incorporates:
     *  Product: '<S52>/Matrix Multiply'
     *  Product: '<S7>/Product'
     */
    tmp_5 = _mm_loadu_pd(&rtb_VectorConcatenate_0[count]);
    tmp_7 = _mm_set1_pd(0.8);

    /* Sum: '<S9>/Add' incorporates:
     *  Product: '<S52>/Matrix Multiply'
     *  Product: '<S7>/Product'
     */
    tmp_1 = _mm_loadu_pd(&tmp_0[count]);

    /* Product: '<S50>/Product' incorporates:
     *  Product: '<S52>/Matrix Multiply'
     *  Product: '<S7>/Product'
     */
    tmp_2 = _mm_loadu_pd(&rtb_Sum_ha[count]);

    /* Product: '<S7>/Product' incorporates:
     *  Constant: '<S50>/Constant1'
     *  Product: '<S50>/Product'
     *  Product: '<S52>/Matrix Multiply'
     *  SignalConversion generated from: '<S52>/Matrix Multiply'
     *  UnaryMinus: '<S52>/Unary Minus1'
     */
    _mm_storeu_pd(&rtb_Sum_ha[count], _mm_div_pd(_mm_add_pd(_mm_add_pd
      (_mm_add_pd(_mm_mul_pd(tmp_3, _mm_set1_pd(rtb_TransferFcn4)), _mm_mul_pd
                  (tmp_6, _mm_set1_pd(gndSpeed))), _mm_mul_pd(tmp_4, _mm_set1_pd
      (-rtb_ixj))), _mm_add_pd(_mm_add_pd(_mm_mul_pd(tmp_7, tmp_5), tmp_1),
      _mm_mul_pd(_mm_mul_pd(_mm_set1_pd(rtb_ixj_k), tmp_2), _mm_set1_pd(0.01)))),
      tmp_7));
  }

  /* Product: '<S7>/Product' incorporates:
   *  Concatenate: '<S31>/Vector Concatenate'
   *  Constant: '<S12>/Constant'
   *  Constant: '<S50>/Constant1'
   *  Gain: '<S51>/Gain'
   *  Product: '<S50>/Product'
   *  Product: '<S52>/Matrix Multiply'
   *  SignalConversion generated from: '<S52>/Matrix Multiply'
   *  Sum: '<S9>/Add'
   *  UnaryMinus: '<S52>/Unary Minus1'
   */
  for (count = 2; count < 3; count++) {
    rtb_Sum_ha[count] = (((rtb_VectorConcatenate[count + 3] * rtb_TransferFcn4 +
      rtb_VectorConcatenate[count] * gndSpeed) + rtb_VectorConcatenate[count + 6]
                          * -rtb_ixj) + ((0.8 * rtb_VectorConcatenate_0[count] +
      tmp_0[count]) + rtb_ixj_k * rtb_Sum_ha[count] * 0.01)) / 0.8;
  }

  if (rtmIsMajorTimeStep(UAV_Dynamics_M)) {
    /* MATLABSystem: '<S3>/IMU1' */
    if (UAV_Dynamics_DW.obj.Temperature != 25.0) {
      iterate = (UAV_Dynamics_DW.obj.isInitialized == 1);
      if (iterate) {
        UAV_Dynamics_DW.obj.TunablePropsChanged = true;
        UAV_Dynamics_DW.obj.tunablePropertyChanged[37] = true;
      }

      UAV_Dynamics_DW.obj.Temperature = 25.0;
    }

    if (!UAV_Dynamics_isequal_p(UAV_Dynamics_DW.obj.MagneticFieldNED,
         UAV_Dynamics_ConstP.IMU1_MagneticFieldNED)) {
      iterate = (UAV_Dynamics_DW.obj.isInitialized == 1);
      if (iterate) {
        UAV_Dynamics_DW.obj.TunablePropsChanged = true;
        UAV_Dynamics_DW.obj.tunablePropertyChanged[0] = true;
      }

      imuSensor_set_MagneticFieldNED(&UAV_Dynamics_DW.obj,
        UAV_Dynamics_ConstP.IMU1_MagneticFieldNED);
    }

    if (UAV_Dynamics_DW.obj.AccelParamsMeasurementRange != (rtInf)) {
      iterate = (UAV_Dynamics_DW.obj.isInitialized == 1);
      if (iterate) {
        UAV_Dynamics_DW.obj.TunablePropsChanged = true;
        UAV_Dynamics_DW.obj.tunablePropertyChanged[3] = true;
      }

      UAV_Dynamics_DW.obj.AccelParamsMeasurementRange = (rtInf);
    }

    if (UAV_Dynamics_DW.obj.AccelParamsResolution != 0.0) {
      iterate = (UAV_Dynamics_DW.obj.isInitialized == 1);
      if (iterate) {
        UAV_Dynamics_DW.obj.TunablePropsChanged = true;
        UAV_Dynamics_DW.obj.tunablePropertyChanged[4] = true;
      }

      UAV_Dynamics_DW.obj.AccelParamsResolution = 0.0;
    }

    if (!UAV_Dynamics_isequal_p(UAV_Dynamics_DW.obj.AccelParamsConstantBias,
         UAV_Dynamics_ConstP.pooled4)) {
      iterate = (UAV_Dynamics_DW.obj.isInitialized == 1);
      if (iterate) {
        UAV_Dynamics_DW.obj.TunablePropsChanged = true;
        UAV_Dynamics_DW.obj.tunablePropertyChanged[5] = true;
      }

      UAV_Dynamics_DW.obj.AccelParamsConstantBias[0] = 0.0;
      UAV_Dynamics_DW.obj.AccelParamsConstantBias[1] = 0.0;
      UAV_Dynamics_DW.obj.AccelParamsConstantBias[2] = 0.0;
    }

    if (!UAV_Dynamics_isequal_p(UAV_Dynamics_DW.obj.AccelParamsAxesMisalignment,
         UAV_Dynamics_ConstP.pooled4)) {
      iterate = (UAV_Dynamics_DW.obj.isInitialized == 1);
      if (iterate) {
        UAV_Dynamics_DW.obj.TunablePropsChanged = true;
        UAV_Dynamics_DW.obj.tunablePropertyChanged[6] = true;
      }

      UAV_Dynamics_DW.obj.AccelParamsAxesMisalignment[0] = 0.0;
      UAV_Dynamics_DW.obj.AccelParamsAxesMisalignment[1] = 0.0;
      UAV_Dynamics_DW.obj.AccelParamsAxesMisalignment[2] = 0.0;
    }

    if (UAV_Dynamics_DW.obj.AccelParamsNoiseDensity != 0.0003) {
      iterate = (UAV_Dynamics_DW.obj.isInitialized == 1);
      if (iterate) {
        UAV_Dynamics_DW.obj.TunablePropsChanged = true;
        UAV_Dynamics_DW.obj.tunablePropertyChanged[7] = true;
      }

      UAV_Dynamics_DW.obj.AccelParamsNoiseDensity = 0.0003;
    }

    if (!UAV_Dynamics_isequal_p(UAV_Dynamics_DW.obj.AccelParamsBiasInstability,
         UAV_Dynamics_ConstP.pooled4)) {
      iterate = (UAV_Dynamics_DW.obj.isInitialized == 1);
      if (iterate) {
        UAV_Dynamics_DW.obj.TunablePropsChanged = true;
        UAV_Dynamics_DW.obj.tunablePropertyChanged[8] = true;
      }

      UAV_Dynamics_DW.obj.AccelParamsBiasInstability[0] = 0.0;
      UAV_Dynamics_DW.obj.AccelParamsBiasInstability[1] = 0.0;
      UAV_Dynamics_DW.obj.AccelParamsBiasInstability[2] = 0.0;
    }

    if (UAV_Dynamics_DW.obj.AccelParamsBiasInstabilityNumerator != 1.0) {
      iterate = (UAV_Dynamics_DW.obj.isInitialized == 1);
      if (iterate) {
        UAV_Dynamics_DW.obj.TunablePropsChanged = true;
        UAV_Dynamics_DW.obj.tunablePropertyChanged[9] = true;
      }

      UAV_Dynamics_DW.obj.AccelParamsBiasInstabilityNumerator = 1.0;
    }

    if (!UAV_Dynamics_isequal
        (UAV_Dynamics_DW.obj.AccelParamsBiasInstabilityDenominator,
         UAV_Dynamics_ConstP.pooled6)) {
      iterate = (UAV_Dynamics_DW.obj.isInitialized == 1);
      if (iterate) {
        UAV_Dynamics_DW.obj.TunablePropsChanged = true;
        UAV_Dynamics_DW.obj.tunablePropertyChanged[10] = true;
      }

      UAV_Dynamics_DW.obj.AccelParamsBiasInstabilityDenominator[0] = 1.0;
      UAV_Dynamics_DW.obj.AccelParamsBiasInstabilityDenominator[1] = -0.5;
    }

    if (!UAV_Dynamics_isequal_p(UAV_Dynamics_DW.obj.AccelParamsRandomWalk,
         UAV_Dynamics_ConstP.pooled4)) {
      iterate = (UAV_Dynamics_DW.obj.isInitialized == 1);
      if (iterate) {
        UAV_Dynamics_DW.obj.TunablePropsChanged = true;
        UAV_Dynamics_DW.obj.tunablePropertyChanged[11] = true;
      }

      UAV_Dynamics_DW.obj.AccelParamsRandomWalk[0] = 0.0;
      UAV_Dynamics_DW.obj.AccelParamsRandomWalk[1] = 0.0;
      UAV_Dynamics_DW.obj.AccelParamsRandomWalk[2] = 0.0;
    }

    if (!UAV_Dynamics_isequal_p(UAV_Dynamics_DW.obj.AccelParamsTemperatureBias,
         UAV_Dynamics_ConstP.pooled4)) {
      iterate = (UAV_Dynamics_DW.obj.isInitialized == 1);
      if (iterate) {
        UAV_Dynamics_DW.obj.TunablePropsChanged = true;
        UAV_Dynamics_DW.obj.tunablePropertyChanged[12] = true;
      }

      UAV_Dynamics_DW.obj.AccelParamsTemperatureBias[0] = 0.0;
      UAV_Dynamics_DW.obj.AccelParamsTemperatureBias[1] = 0.0;
      UAV_Dynamics_DW.obj.AccelParamsTemperatureBias[2] = 0.0;
    }

    if (!UAV_Dynamics_isequal_p
        (UAV_Dynamics_DW.obj.AccelParamsTemperatureScaleFactor,
         UAV_Dynamics_ConstP.pooled4)) {
      iterate = (UAV_Dynamics_DW.obj.isInitialized == 1);
      if (iterate) {
        UAV_Dynamics_DW.obj.TunablePropsChanged = true;
        UAV_Dynamics_DW.obj.tunablePropertyChanged[13] = true;
      }

      UAV_Dynamics_DW.obj.AccelParamsTemperatureScaleFactor[0] = 0.0;
      UAV_Dynamics_DW.obj.AccelParamsTemperatureScaleFactor[1] = 0.0;
      UAV_Dynamics_DW.obj.AccelParamsTemperatureScaleFactor[2] = 0.0;
    }

    if (UAV_Dynamics_DW.obj.GyroParamsMeasurementRange != (rtInf)) {
      iterate = (UAV_Dynamics_DW.obj.isInitialized == 1);
      if (iterate) {
        UAV_Dynamics_DW.obj.TunablePropsChanged = true;
        UAV_Dynamics_DW.obj.tunablePropertyChanged[14] = true;
      }

      UAV_Dynamics_DW.obj.GyroParamsMeasurementRange = (rtInf);
    }

    if (UAV_Dynamics_DW.obj.GyroParamsResolution != 0.0) {
      iterate = (UAV_Dynamics_DW.obj.isInitialized == 1);
      if (iterate) {
        UAV_Dynamics_DW.obj.TunablePropsChanged = true;
        UAV_Dynamics_DW.obj.tunablePropertyChanged[15] = true;
      }

      UAV_Dynamics_DW.obj.GyroParamsResolution = 0.0;
    }

    if (!UAV_Dynamics_isequal_p(UAV_Dynamics_DW.obj.GyroParamsConstantBias,
         UAV_Dynamics_ConstP.pooled4)) {
      iterate = (UAV_Dynamics_DW.obj.isInitialized == 1);
      if (iterate) {
        UAV_Dynamics_DW.obj.TunablePropsChanged = true;
        UAV_Dynamics_DW.obj.tunablePropertyChanged[16] = true;
      }

      UAV_Dynamics_DW.obj.GyroParamsConstantBias[0] = 0.0;
      UAV_Dynamics_DW.obj.GyroParamsConstantBias[1] = 0.0;
      UAV_Dynamics_DW.obj.GyroParamsConstantBias[2] = 0.0;
    }

    if (!UAV_Dynamics_isequal_p(UAV_Dynamics_DW.obj.GyroParamsAxesMisalignment,
         UAV_Dynamics_ConstP.pooled4)) {
      iterate = (UAV_Dynamics_DW.obj.isInitialized == 1);
      if (iterate) {
        UAV_Dynamics_DW.obj.TunablePropsChanged = true;
        UAV_Dynamics_DW.obj.tunablePropertyChanged[17] = true;
      }

      UAV_Dynamics_DW.obj.GyroParamsAxesMisalignment[0] = 0.0;
      UAV_Dynamics_DW.obj.GyroParamsAxesMisalignment[1] = 0.0;
      UAV_Dynamics_DW.obj.GyroParamsAxesMisalignment[2] = 0.0;
    }

    if (UAV_Dynamics_DW.obj.GyroParamsAccelerationBias != 0.0001) {
      iterate = (UAV_Dynamics_DW.obj.isInitialized == 1);
      if (iterate) {
        UAV_Dynamics_DW.obj.TunablePropsChanged = true;
        UAV_Dynamics_DW.obj.tunablePropertyChanged[25] = true;
      }

      UAV_Dynamics_DW.obj.GyroParamsAccelerationBias = 0.0001;
    }

    if (UAV_Dynamics_DW.obj.GyroParamsNoiseDensity != 0.01) {
      iterate = (UAV_Dynamics_DW.obj.isInitialized == 1);
      if (iterate) {
        UAV_Dynamics_DW.obj.TunablePropsChanged = true;
        UAV_Dynamics_DW.obj.tunablePropertyChanged[18] = true;
      }

      UAV_Dynamics_DW.obj.GyroParamsNoiseDensity = 0.01;
    }

    if (!UAV_Dynamics_isequal_p(UAV_Dynamics_DW.obj.GyroParamsBiasInstability,
         UAV_Dynamics_ConstP.pooled4)) {
      iterate = (UAV_Dynamics_DW.obj.isInitialized == 1);
      if (iterate) {
        UAV_Dynamics_DW.obj.TunablePropsChanged = true;
        UAV_Dynamics_DW.obj.tunablePropertyChanged[19] = true;
      }

      UAV_Dynamics_DW.obj.GyroParamsBiasInstability[0] = 0.0;
      UAV_Dynamics_DW.obj.GyroParamsBiasInstability[1] = 0.0;
      UAV_Dynamics_DW.obj.GyroParamsBiasInstability[2] = 0.0;
    }

    if (UAV_Dynamics_DW.obj.GyroParamsBiasInstabilityNumerator != 1.0) {
      iterate = (UAV_Dynamics_DW.obj.isInitialized == 1);
      if (iterate) {
        UAV_Dynamics_DW.obj.TunablePropsChanged = true;
        UAV_Dynamics_DW.obj.tunablePropertyChanged[20] = true;
      }

      UAV_Dynamics_DW.obj.GyroParamsBiasInstabilityNumerator = 1.0;
    }

    if (!UAV_Dynamics_isequal
        (UAV_Dynamics_DW.obj.GyroParamsBiasInstabilityDenominator,
         UAV_Dynamics_ConstP.pooled6)) {
      iterate = (UAV_Dynamics_DW.obj.isInitialized == 1);
      if (iterate) {
        UAV_Dynamics_DW.obj.TunablePropsChanged = true;
        UAV_Dynamics_DW.obj.tunablePropertyChanged[21] = true;
      }

      UAV_Dynamics_DW.obj.GyroParamsBiasInstabilityDenominator[0] = 1.0;
      UAV_Dynamics_DW.obj.GyroParamsBiasInstabilityDenominator[1] = -0.5;
    }

    if (!UAV_Dynamics_isequal_p(UAV_Dynamics_DW.obj.GyroParamsRandomWalk,
         UAV_Dynamics_ConstP.pooled4)) {
      iterate = (UAV_Dynamics_DW.obj.isInitialized == 1);
      if (iterate) {
        UAV_Dynamics_DW.obj.TunablePropsChanged = true;
        UAV_Dynamics_DW.obj.tunablePropertyChanged[22] = true;
      }

      UAV_Dynamics_DW.obj.GyroParamsRandomWalk[0] = 0.0;
      UAV_Dynamics_DW.obj.GyroParamsRandomWalk[1] = 0.0;
      UAV_Dynamics_DW.obj.GyroParamsRandomWalk[2] = 0.0;
    }

    if (!UAV_Dynamics_isequal_p(UAV_Dynamics_DW.obj.GyroParamsTemperatureBias,
         UAV_Dynamics_ConstP.pooled4)) {
      iterate = (UAV_Dynamics_DW.obj.isInitialized == 1);
      if (iterate) {
        UAV_Dynamics_DW.obj.TunablePropsChanged = true;
        UAV_Dynamics_DW.obj.tunablePropertyChanged[23] = true;
      }

      UAV_Dynamics_DW.obj.GyroParamsTemperatureBias[0] = 0.0;
      UAV_Dynamics_DW.obj.GyroParamsTemperatureBias[1] = 0.0;
      UAV_Dynamics_DW.obj.GyroParamsTemperatureBias[2] = 0.0;
    }

    if (!UAV_Dynamics_isequal_p
        (UAV_Dynamics_DW.obj.GyroParamsTemperatureScaleFactor,
         UAV_Dynamics_ConstP.pooled4)) {
      iterate = (UAV_Dynamics_DW.obj.isInitialized == 1);
      if (iterate) {
        UAV_Dynamics_DW.obj.TunablePropsChanged = true;
        UAV_Dynamics_DW.obj.tunablePropertyChanged[24] = true;
      }

      UAV_Dynamics_DW.obj.GyroParamsTemperatureScaleFactor[0] = 0.0;
      UAV_Dynamics_DW.obj.GyroParamsTemperatureScaleFactor[1] = 0.0;
      UAV_Dynamics_DW.obj.GyroParamsTemperatureScaleFactor[2] = 0.0;
    }

    if (UAV_Dynamics_DW.obj.MagParamsMeasurementRange != (rtInf)) {
      iterate = (UAV_Dynamics_DW.obj.isInitialized == 1);
      if (iterate) {
        UAV_Dynamics_DW.obj.TunablePropsChanged = true;
        UAV_Dynamics_DW.obj.tunablePropertyChanged[26] = true;
      }

      UAV_Dynamics_DW.obj.MagParamsMeasurementRange = (rtInf);
    }

    if (UAV_Dynamics_DW.obj.MagParamsResolution != 0.0) {
      iterate = (UAV_Dynamics_DW.obj.isInitialized == 1);
      if (iterate) {
        UAV_Dynamics_DW.obj.TunablePropsChanged = true;
        UAV_Dynamics_DW.obj.tunablePropertyChanged[27] = true;
      }

      UAV_Dynamics_DW.obj.MagParamsResolution = 0.0;
    }

    if (!UAV_Dynamics_isequal_p(UAV_Dynamics_DW.obj.MagParamsConstantBias,
         UAV_Dynamics_ConstP.pooled4)) {
      iterate = (UAV_Dynamics_DW.obj.isInitialized == 1);
      if (iterate) {
        UAV_Dynamics_DW.obj.TunablePropsChanged = true;
        UAV_Dynamics_DW.obj.tunablePropertyChanged[28] = true;
      }

      UAV_Dynamics_DW.obj.MagParamsConstantBias[0] = 0.0;
      UAV_Dynamics_DW.obj.MagParamsConstantBias[1] = 0.0;
      UAV_Dynamics_DW.obj.MagParamsConstantBias[2] = 0.0;
    }

    if (!UAV_Dynamics_isequal_p(UAV_Dynamics_DW.obj.MagParamsAxesMisalignment,
         UAV_Dynamics_ConstP.pooled4)) {
      iterate = (UAV_Dynamics_DW.obj.isInitialized == 1);
      if (iterate) {
        UAV_Dynamics_DW.obj.TunablePropsChanged = true;
        UAV_Dynamics_DW.obj.tunablePropertyChanged[29] = true;
      }

      UAV_Dynamics_DW.obj.MagParamsAxesMisalignment[0] = 0.0;
      UAV_Dynamics_DW.obj.MagParamsAxesMisalignment[1] = 0.0;
      UAV_Dynamics_DW.obj.MagParamsAxesMisalignment[2] = 0.0;
    }

    if (UAV_Dynamics_DW.obj.MagParamsNoiseDensity != 0.0005) {
      iterate = (UAV_Dynamics_DW.obj.isInitialized == 1);
      if (iterate) {
        UAV_Dynamics_DW.obj.TunablePropsChanged = true;
        UAV_Dynamics_DW.obj.tunablePropertyChanged[30] = true;
      }

      UAV_Dynamics_DW.obj.MagParamsNoiseDensity = 0.0005;
    }

    if (!UAV_Dynamics_isequal_p(UAV_Dynamics_DW.obj.MagParamsBiasInstability,
         UAV_Dynamics_ConstP.pooled4)) {
      iterate = (UAV_Dynamics_DW.obj.isInitialized == 1);
      if (iterate) {
        UAV_Dynamics_DW.obj.TunablePropsChanged = true;
        UAV_Dynamics_DW.obj.tunablePropertyChanged[31] = true;
      }

      UAV_Dynamics_DW.obj.MagParamsBiasInstability[0] = 0.0;
      UAV_Dynamics_DW.obj.MagParamsBiasInstability[1] = 0.0;
      UAV_Dynamics_DW.obj.MagParamsBiasInstability[2] = 0.0;
    }

    if (UAV_Dynamics_DW.obj.MagParamsBiasInstabilityNumerator != 1.0) {
      iterate = (UAV_Dynamics_DW.obj.isInitialized == 1);
      if (iterate) {
        UAV_Dynamics_DW.obj.TunablePropsChanged = true;
        UAV_Dynamics_DW.obj.tunablePropertyChanged[32] = true;
      }

      UAV_Dynamics_DW.obj.MagParamsBiasInstabilityNumerator = 1.0;
    }

    if (!UAV_Dynamics_isequal
        (UAV_Dynamics_DW.obj.MagParamsBiasInstabilityDenominator,
         UAV_Dynamics_ConstP.pooled6)) {
      iterate = (UAV_Dynamics_DW.obj.isInitialized == 1);
      if (iterate) {
        UAV_Dynamics_DW.obj.TunablePropsChanged = true;
        UAV_Dynamics_DW.obj.tunablePropertyChanged[33] = true;
      }

      UAV_Dynamics_DW.obj.MagParamsBiasInstabilityDenominator[0] = 1.0;
      UAV_Dynamics_DW.obj.MagParamsBiasInstabilityDenominator[1] = -0.5;
    }

    if (!UAV_Dynamics_isequal_p(UAV_Dynamics_DW.obj.MagParamsRandomWalk,
         UAV_Dynamics_ConstP.pooled4)) {
      iterate = (UAV_Dynamics_DW.obj.isInitialized == 1);
      if (iterate) {
        UAV_Dynamics_DW.obj.TunablePropsChanged = true;
        UAV_Dynamics_DW.obj.tunablePropertyChanged[34] = true;
      }

      UAV_Dynamics_DW.obj.MagParamsRandomWalk[0] = 0.0;
      UAV_Dynamics_DW.obj.MagParamsRandomWalk[1] = 0.0;
      UAV_Dynamics_DW.obj.MagParamsRandomWalk[2] = 0.0;
    }

    if (!UAV_Dynamics_isequal_p(UAV_Dynamics_DW.obj.MagParamsTemperatureBias,
         UAV_Dynamics_ConstP.pooled4)) {
      iterate = (UAV_Dynamics_DW.obj.isInitialized == 1);
      if (iterate) {
        UAV_Dynamics_DW.obj.TunablePropsChanged = true;
        UAV_Dynamics_DW.obj.tunablePropertyChanged[35] = true;
      }

      UAV_Dynamics_DW.obj.MagParamsTemperatureBias[0] = 0.0;
      UAV_Dynamics_DW.obj.MagParamsTemperatureBias[1] = 0.0;
      UAV_Dynamics_DW.obj.MagParamsTemperatureBias[2] = 0.0;
    }

    if (!UAV_Dynamics_isequal_p
        (UAV_Dynamics_DW.obj.MagParamsTemperatureScaleFactor,
         UAV_Dynamics_ConstP.pooled4)) {
      iterate = (UAV_Dynamics_DW.obj.isInitialized == 1);
      if (iterate) {
        UAV_Dynamics_DW.obj.TunablePropsChanged = true;
        UAV_Dynamics_DW.obj.tunablePropertyChanged[36] = true;
      }

      UAV_Dynamics_DW.obj.MagParamsTemperatureScaleFactor[0] = 0.0;
      UAV_Dynamics_DW.obj.MagParamsTemperatureScaleFactor[1] = 0.0;
      UAV_Dynamics_DW.obj.MagParamsTemperatureScaleFactor[2] = 0.0;
    }

    /* Product: '<S4>/Matrix Multiply1' incorporates:
     *  Math: '<S4>/Transpose'
     */
    rtb_ixj_k = rtb_Sum_ha[0];
    gndSpeed = rtb_Sum_ha[1];
    rtb_TransferFcn4 = rtb_Sum_ha[2];

    /* Integrator: '<S7>/p,q,r ' incorporates:
     *  Math: '<S4>/Transpose'
     */
    rtb_kxi = UAV_Dynamics_X.pqr_CSTATE[0];
    rtb_jxi = UAV_Dynamics_X.pqr_CSTATE[1];
    rtb_TransferFcn = UAV_Dynamics_X.pqr_CSTATE[2];
    for (count = 0; count <= 0; count += 2) {
      /* Math: '<S4>/Transpose' */
      tmp_3 = _mm_loadu_pd(&rtb_Transpose_tmp[count]);
      tmp_6 = _mm_loadu_pd(&rtb_Transpose_tmp[count + 3]);
      tmp_4 = _mm_loadu_pd(&rtb_Transpose_tmp[count + 6]);

      /* Product: '<S4>/Matrix Multiply' incorporates:
       *  Integrator: '<S7>/p,q,r '
       *  Math: '<S4>/Transpose'
       */
      _mm_storeu_pd(&rtb_Transpose_tmp_1[count], _mm_add_pd(_mm_mul_pd(tmp_4,
        _mm_set1_pd(rtb_TransferFcn)), _mm_add_pd(_mm_mul_pd(tmp_6, _mm_set1_pd
        (rtb_jxi)), _mm_mul_pd(tmp_3, _mm_set1_pd(rtb_kxi)))));

      /* Product: '<S4>/Matrix Multiply1' incorporates:
       *  Math: '<S4>/Transpose'
       */
      _mm_storeu_pd(&rtb_Transpose_tmp_0[count], _mm_add_pd(_mm_mul_pd(tmp_4,
        _mm_set1_pd(rtb_TransferFcn4)), _mm_add_pd(_mm_mul_pd(tmp_6, _mm_set1_pd
        (gndSpeed)), _mm_mul_pd(tmp_3, _mm_set1_pd(rtb_ixj_k)))));
    }

    for (count = 2; count < 3; count++) {
      /* Math: '<S4>/Transpose' */
      au = rtb_Transpose_tmp[count];

      /* Product: '<S4>/Matrix Multiply1' incorporates:
       *  Math: '<S4>/Transpose'
       */
      bv = au * rtb_ixj_k;

      /* Product: '<S4>/Matrix Multiply' incorporates:
       *  Integrator: '<S7>/p,q,r '
       *  Math: '<S4>/Transpose'
       */
      tmp = au * rtb_kxi;

      /* Math: '<S4>/Transpose' */
      au = rtb_Transpose_tmp[count + 3];

      /* Product: '<S4>/Matrix Multiply1' incorporates:
       *  Math: '<S4>/Transpose'
       */
      bv += au * gndSpeed;

      /* Product: '<S4>/Matrix Multiply' incorporates:
       *  Integrator: '<S7>/p,q,r '
       *  Math: '<S4>/Transpose'
       */
      tmp += au * rtb_jxi;

      /* Math: '<S4>/Transpose' */
      au = rtb_Transpose_tmp[count + 6];

      /* Product: '<S4>/Matrix Multiply' incorporates:
       *  Integrator: '<S7>/p,q,r '
       *  Math: '<S4>/Transpose'
       */
      rtb_Transpose_tmp_1[count] = au * rtb_TransferFcn + tmp;

      /* Product: '<S4>/Matrix Multiply1' incorporates:
       *  Math: '<S4>/Transpose'
       */
      rtb_Transpose_tmp_0[count] = au * rtb_TransferFcn4 + bv;
    }

    /* MATLABSystem: '<S3>/IMU1' incorporates:
     *  MATLABSystem: '<S3>/Coordinate Transformation Conversion1'
     */
    UAV_Dynamics_SystemCore_step(&UAV_Dynamics_DW.obj, rtb_Transpose_tmp_0,
      rtb_Transpose_tmp_1, rtb_CoordinateTransformationCon, UAV_Dynamics_Y.Acc,
      UAV_Dynamics_Y.Gyro, UAV_Dynamics_Y.Mag);

    /* Outport: '<Root>/Acc' incorporates:
     *  Gain: '<S3>/Gain'
     *  MATLABSystem: '<S3>/IMU1'
     * */
    UAV_Dynamics_Y.Acc[0] = -UAV_Dynamics_Y.Acc[0];
    UAV_Dynamics_Y.Acc[1] = -UAV_Dynamics_Y.Acc[1];
    UAV_Dynamics_Y.Acc[2] = -UAV_Dynamics_Y.Acc[2];
  }

  /* Sum: '<S7>/Sum' incorporates:
   *  Integrator: '<S7>/p,q,r '
   *  Integrator: '<S7>/ub,vb,wb'
   *  Product: '<S48>/i x j'
   *  Product: '<S48>/j x k'
   *  Product: '<S48>/k x i'
   *  Product: '<S49>/i x k'
   *  Product: '<S49>/j x i'
   *  Product: '<S49>/k x j'
   *  Sum: '<S13>/Sum'
   */
  UAV_Dynamics_B.Sum[0] = (UAV_Dynamics_X.ubvbwb_CSTATE[1] *
    UAV_Dynamics_X.pqr_CSTATE[2] - UAV_Dynamics_X.pqr_CSTATE[1] *
    UAV_Dynamics_X.ubvbwb_CSTATE[2]) + rtb_Sum_ha[0];
  UAV_Dynamics_B.Sum[1] = (UAV_Dynamics_X.pqr_CSTATE[0] *
    UAV_Dynamics_X.ubvbwb_CSTATE[2] - UAV_Dynamics_X.ubvbwb_CSTATE[0] *
    UAV_Dynamics_X.pqr_CSTATE[2]) + rtb_Sum_ha[1];
  UAV_Dynamics_B.Sum[2] = (UAV_Dynamics_X.ubvbwb_CSTATE[0] *
    UAV_Dynamics_X.pqr_CSTATE[1] - UAV_Dynamics_X.pqr_CSTATE[0] *
    UAV_Dynamics_X.ubvbwb_CSTATE[1]) + rtb_Sum_ha[2];

  /* Switch: '<S56>/Switch' incorporates:
   *  Constant: '<S56>/Constant'
   */
  if (rtb_ixj > 0.0) {
    /* Saturate: '<S56>/Saturation1' */
    if (rtb_ixk > 0.3490658503988659) {
      rtb_ixk = 0.3490658503988659;
    } else if (rtb_ixk < -0.3490658503988659) {
      rtb_ixk = -0.3490658503988659;
    }

    /* Sum: '<S56>/Add' incorporates:
     *  Gain: '<S56>/Gain'
     *  Integrator: '<S7>/p,q,r '
     *  Saturate: '<S56>/Saturation1'
     */
    gndSpeed = 2.0 * rtb_ixk + UAV_Dynamics_X.pqr_CSTATE[0];

    /* Saturate: '<S56>/Saturation' incorporates:
     *  Gain: '<S56>/Gain2'
     */
    if (gndSpeed > 0.1) {
      rtb_Sum_ha[0] = -0.1;
    } else if (gndSpeed < -0.1) {
      rtb_Sum_ha[0] = 0.1;
    } else {
      rtb_Sum_ha[0] = -gndSpeed;
    }

    /* Saturate: '<S56>/Saturation1' */
    if (rtb_fcn3 > 0.3490658503988659) {
      rtb_fcn3 = 0.3490658503988659;
    } else if (rtb_fcn3 < -0.3490658503988659) {
      rtb_fcn3 = -0.3490658503988659;
    }

    /* Sum: '<S56>/Add' incorporates:
     *  Gain: '<S56>/Gain'
     *  Integrator: '<S7>/p,q,r '
     *  Saturate: '<S56>/Saturation1'
     */
    gndSpeed = 2.0 * rtb_fcn3 + UAV_Dynamics_X.pqr_CSTATE[1];

    /* Saturate: '<S56>/Saturation' incorporates:
     *  Gain: '<S56>/Gain2'
     */
    if (gndSpeed > 0.1) {
      rtb_Sum_ha[1] = -0.1;
    } else if (gndSpeed < -0.1) {
      rtb_Sum_ha[1] = 0.1;
    } else {
      rtb_Sum_ha[1] = -gndSpeed;
    }

    /* Product: '<S56>/Product' incorporates:
     *  Gain: '<S61>/friction coefficient'
     *  Gain: '<S61>/vd'
     *  Integrator: '<S7>/p,q,r '
     *  Trigonometry: '<S61>/Tanh'
     *  UnaryMinus: '<S56>/Unary Minus'
     */
    gndSpeed = -(tanh(5.0 * UAV_Dynamics_X.pqr_CSTATE[2]) * 0.025) * rtb_ixj;

    /* Saturate: '<S56>/Saturation2' */
    if (gndSpeed > 0.1) {
      rtb_Sum_ha[2] = 0.1;
    } else if (gndSpeed < -0.1) {
      rtb_Sum_ha[2] = -0.1;
    } else {
      rtb_Sum_ha[2] = gndSpeed;
    }

    /* End of Saturate: '<S56>/Saturation2' */
  } else {
    rtb_Sum_ha[0] = 0.0;
    rtb_Sum_ha[1] = 0.0;
    rtb_Sum_ha[2] = 0.0;
  }

  /* End of Switch: '<S56>/Switch' */

  /* Integrator: '<S7>/p,q,r ' incorporates:
   *  Product: '<S44>/Product'
   */
  rtb_kxi = UAV_Dynamics_X.pqr_CSTATE[1];
  rtb_jxi = UAV_Dynamics_X.pqr_CSTATE[0];
  rtb_TransferFcn = UAV_Dynamics_X.pqr_CSTATE[2];
  for (count = 0; count <= 0; count += 2) {
    /* Sum: '<S9>/Add1' */
    tmp_3 = _mm_loadu_pd(&c[count]);
    tmp_6 = _mm_loadu_pd(&rtb_Sum_ha[count]);
    _mm_storeu_pd(&c[count], _mm_add_pd(tmp_3, tmp_6));

    /* Selector: '<S11>/Selector1' incorporates:
     *  Product: '<S45>/Product'
     *  Sum: '<S9>/Add1'
     */
    tmp_3 = _mm_loadu_pd(&UAV_Dynamics_ConstB.Selector1[count + 3]);

    /* Integrator: '<S7>/p,q,r ' */
    tmp_6 = _mm_set1_pd(rtb_kxi);

    /* Selector: '<S11>/Selector1' incorporates:
     *  Sum: '<S9>/Add1'
     */
    tmp_4 = _mm_loadu_pd(&UAV_Dynamics_ConstB.Selector1[count]);

    /* Integrator: '<S7>/p,q,r ' */
    tmp_5 = _mm_set1_pd(rtb_jxi);

    /* Selector: '<S11>/Selector1' incorporates:
     *  Product: '<S45>/Product'
     *  Sum: '<S9>/Add1'
     */
    tmp_7 = _mm_loadu_pd(&UAV_Dynamics_ConstB.Selector1[count + 6]);

    /* Integrator: '<S7>/p,q,r ' */
    tmp_1 = _mm_set1_pd(rtb_TransferFcn);

    /* Product: '<S45>/Product' incorporates:
     *  Sum: '<S9>/Add1'
     */
    _mm_storeu_pd(&rtb_MatrixMultiply1[count], _mm_add_pd(_mm_add_pd(_mm_mul_pd
      (tmp_3, tmp_6), _mm_mul_pd(tmp_4, tmp_5)), _mm_mul_pd(tmp_7, tmp_1)));

    /* Selector: '<S11>/Selector' incorporates:
     *  Product: '<S44>/Product'
     *  Product: '<S45>/Product'
     *  Sum: '<S9>/Add1'
     */
    tmp_3 = _mm_loadu_pd(&UAV_Dynamics_ConstB.Selector[count + 3]);
    tmp_4 = _mm_loadu_pd(&UAV_Dynamics_ConstB.Selector[count]);
    tmp_7 = _mm_loadu_pd(&UAV_Dynamics_ConstB.Selector[count + 6]);

    /* Product: '<S44>/Product' incorporates:
     *  Sum: '<S43>/Sum'
     *  Sum: '<S9>/Add1'
     */
    _mm_storeu_pd(&rtb_Sum_ha[count], _mm_add_pd(_mm_add_pd(_mm_mul_pd(tmp_3,
      tmp_6), _mm_mul_pd(tmp_4, tmp_5)), _mm_mul_pd(tmp_7, tmp_1)));
  }

  for (count = 2; count < 3; count++) {
    /* Sum: '<S9>/Add1' */
    c[count] += rtb_Sum_ha[count];

    /* Product: '<S45>/Product' incorporates:
     *  Integrator: '<S7>/p,q,r '
     *  Selector: '<S11>/Selector1'
     */
    rtb_MatrixMultiply1[count] = (UAV_Dynamics_ConstB.Selector1[count + 3] *
      rtb_kxi + UAV_Dynamics_ConstB.Selector1[count] * rtb_jxi) +
      UAV_Dynamics_ConstB.Selector1[count + 6] * rtb_TransferFcn;

    /* Product: '<S44>/Product' incorporates:
     *  Integrator: '<S7>/p,q,r '
     *  Selector: '<S11>/Selector'
     *  Sum: '<S43>/Sum'
     */
    rtb_Sum_ha[count] = (UAV_Dynamics_ConstB.Selector[count + 3] * rtb_kxi +
                         UAV_Dynamics_ConstB.Selector[count] * rtb_jxi) +
      UAV_Dynamics_ConstB.Selector[count + 6] * rtb_TransferFcn;
  }

  /* Product: '<S11>/Product2' incorporates:
   *  Integrator: '<S7>/p,q,r '
   *  Product: '<S45>/Product'
   *  Product: '<S46>/i x j'
   *  Product: '<S46>/j x k'
   *  Product: '<S46>/k x i'
   *  Product: '<S47>/i x k'
   *  Product: '<S47>/j x i'
   *  Product: '<S47>/k x j'
   *  Selector: '<S11>/Selector2'
   *  Sum: '<S11>/Sum2'
   *  Sum: '<S43>/Sum'
   */
  c_0[0] = (c[0] - rtb_MatrixMultiply1[0]) - (UAV_Dynamics_X.pqr_CSTATE[1] *
    rtb_Sum_ha[2] - rtb_Sum_ha[1] * UAV_Dynamics_X.pqr_CSTATE[2]);
  c_0[1] = (c[1] - rtb_MatrixMultiply1[1]) - (rtb_Sum_ha[0] *
    UAV_Dynamics_X.pqr_CSTATE[2] - UAV_Dynamics_X.pqr_CSTATE[0] * rtb_Sum_ha[2]);
  c_0[2] = (c[2] - rtb_MatrixMultiply1[2]) - (UAV_Dynamics_X.pqr_CSTATE[0] *
    rtb_Sum_ha[1] - rtb_Sum_ha[0] * UAV_Dynamics_X.pqr_CSTATE[1]);
  rt_mrdivide_U1d1x3_U2d_9vOrDY9Z(c_0, UAV_Dynamics_ConstB.Selector2,
    UAV_Dynamics_B.Product2);

  /* Integrator: '<S7>/ub,vb,wb' incorporates:
   *  Math: '<S7>/Transpose'
   */
  rtb_fcn3 = UAV_Dynamics_X.ubvbwb_CSTATE[1];
  rtb_ixk = UAV_Dynamics_X.ubvbwb_CSTATE[0];
  rtb_ixj = UAV_Dynamics_X.ubvbwb_CSTATE[2];
  for (count = 0; count <= 0; count += 2) {
    /* Math: '<S7>/Transpose' incorporates:
     *  Product: '<S17>/Product'
     */
    tmp_3 = _mm_loadu_pd(&rtb_Transpose_tmp[count + 3]);
    tmp_6 = _mm_loadu_pd(&rtb_Transpose_tmp[count]);
    tmp_4 = _mm_loadu_pd(&rtb_Transpose_tmp[count + 6]);

    /* Product: '<S17>/Product' incorporates:
     *  Integrator: '<S7>/ub,vb,wb'
     *  Math: '<S7>/Transpose'
     */
    _mm_storeu_pd(&UAV_Dynamics_B.Product[count], _mm_add_pd(_mm_add_pd
      (_mm_mul_pd(tmp_3, _mm_set1_pd(rtb_fcn3)), _mm_mul_pd(tmp_6, _mm_set1_pd
      (rtb_ixk))), _mm_mul_pd(tmp_4, _mm_set1_pd(rtb_ixj))));
  }

  for (count = 2; count < 3; count++) {
    /* Product: '<S17>/Product' incorporates:
     *  Integrator: '<S7>/ub,vb,wb'
     *  Math: '<S7>/Transpose'
     */
    UAV_Dynamics_B.Product[count] = (rtb_Transpose_tmp[count + 3] * rtb_fcn3 +
      rtb_Transpose_tmp[count] * rtb_ixk) + rtb_Transpose_tmp[count + 6] *
      rtb_ixj;
  }

  if (rtmIsMajorTimeStep(UAV_Dynamics_M)) {
    /* MATLABSystem: '<S2>/GPS' incorporates:
     *  Reshape: '<S2>/Reshape1'
     *  Reshape: '<S2>/Reshape3'
     */
    if (UAV_Dynamics_DW.obj_g.HorizontalPositionAccuracy != 0.01) {
      if (UAV_Dynamics_DW.obj_g.isInitialized == 1) {
        UAV_Dynamics_DW.obj_g.TunablePropsChanged = true;
        UAV_Dynamics_DW.obj_g.tunablePropertyChanged[0] = true;
      }

      UAV_Dynamics_DW.obj_g.HorizontalPositionAccuracy = 0.01;
    }

    if (UAV_Dynamics_DW.obj_g.VerticalPositionAccuracy != 0.01) {
      if (UAV_Dynamics_DW.obj_g.isInitialized == 1) {
        UAV_Dynamics_DW.obj_g.TunablePropsChanged = true;
        UAV_Dynamics_DW.obj_g.tunablePropertyChanged[1] = true;
      }

      UAV_Dynamics_DW.obj_g.VerticalPositionAccuracy = 0.01;
    }

    if (UAV_Dynamics_DW.obj_g.VelocityAccuracy != 0.01) {
      if (UAV_Dynamics_DW.obj_g.isInitialized == 1) {
        UAV_Dynamics_DW.obj_g.TunablePropsChanged = true;
        UAV_Dynamics_DW.obj_g.tunablePropertyChanged[2] = true;
      }

      UAV_Dynamics_DW.obj_g.VelocityAccuracy = 0.01;
    }

    if (UAV_Dynamics_DW.obj_g.DecayFactor != 0.99) {
      if (UAV_Dynamics_DW.obj_g.isInitialized == 1) {
        UAV_Dynamics_DW.obj_g.TunablePropsChanged = true;
        UAV_Dynamics_DW.obj_g.tunablePropertyChanged[3] = true;
      }

      UAV_Dynamics_DW.obj_g.DecayFactor = 0.99;
    }

    if (UAV_Dynamics_DW.obj_g.TunablePropsChanged) {
      UAV_Dynamics_DW.obj_g.TunablePropsChanged = false;
      if (UAV_Dynamics_DW.obj_g.tunablePropertyChanged[0] ||
          UAV_Dynamics_DW.obj_g.tunablePropertyChanged[1] ||
          UAV_Dynamics_DW.obj_g.tunablePropertyChanged[3]) {
        UAV_Dynamics_DW.obj_g.pSigmaScaled[0] = 0.0014142135623730957;
        UAV_Dynamics_DW.obj_g.pSigmaScaled[1] = 0.0014142135623730957;
        UAV_Dynamics_DW.obj_g.pSigmaScaled[2] = 0.0014142135623730957;
        UAV_Dynamics_DW.obj_g.pPositionErrorFilterNum = 1.0;
        UAV_Dynamics_DW.obj_g.pPositionErrorFilterDen[0] = 1.0;
        UAV_Dynamics_DW.obj_g.pPositionErrorFilterDen[1] = -0.99;
      }

      UAV_Dynamics_DW.obj_g.tunablePropertyChanged[0] = false;
      UAV_Dynamics_DW.obj_g.tunablePropertyChanged[1] = false;
      UAV_Dynamics_DW.obj_g.tunablePropertyChanged[2] = false;
      UAV_Dynamics_DW.obj_g.tunablePropertyChanged[3] = false;
    }

    GPSSensorBase_stepRandomStream(&UAV_Dynamics_DW.obj_g, rtb_Sum_ha);
    c[0] = rtb_Sum_ha[0] * UAV_Dynamics_DW.obj_g.pSigmaScaled[0];
    c[1] = rtb_Sum_ha[1] * UAV_Dynamics_DW.obj_g.pSigmaScaled[1];
    c[2] = rtb_Sum_ha[2] * UAV_Dynamics_DW.obj_g.pSigmaScaled[2];
    rtb_ixj = UAV_Dynamics_DW.obj_g.pPositionErrorFilterNum;
    rtb_ixj_k = UAV_Dynamics_DW.obj_g.pPositionErrorFilterDen[1];
    if ((!rtIsInf(UAV_Dynamics_DW.obj_g.pPositionErrorFilterDen[0])) &&
        (!rtIsNaN(UAV_Dynamics_DW.obj_g.pPositionErrorFilterDen[0])) &&
        (!(UAV_Dynamics_DW.obj_g.pPositionErrorFilterDen[0] == 0.0)) &&
        (UAV_Dynamics_DW.obj_g.pPositionErrorFilterDen[0] != 1.0)) {
      rtb_ixj = UAV_Dynamics_DW.obj_g.pPositionErrorFilterNum /
        UAV_Dynamics_DW.obj_g.pPositionErrorFilterDen[0];
      rtb_ixj_k = UAV_Dynamics_DW.obj_g.pPositionErrorFilterDen[1] /
        UAV_Dynamics_DW.obj_g.pPositionErrorFilterDen[0];
    }

    rtb_kxi = UAV_Dynamics_DW.obj_g.pPositionErrorFilterStates[0];
    rtb_fcn3 = UAV_Dynamics_DW.obj_g.pPositionErrorFilterStates[1];
    rtb_ixk = UAV_Dynamics_DW.obj_g.pPositionErrorFilterStates[2];
    rtb_kxi += c[0] * rtb_ixj;
    rtb_fcn3 += c[1] * rtb_ixj;
    rtb_ixk += c[2] * rtb_ixj;
    UAV_Dynamics_DW.obj_g.pPositionErrorFilterStates[0] = -rtb_kxi * rtb_ixj_k;
    UAV_Dynamics_DW.obj_g.pPositionErrorFilterStates[1] = -rtb_fcn3 * rtb_ixj_k;
    UAV_Dynamics_DW.obj_g.pPositionErrorFilterStates[2] = -rtb_ixk * rtb_ixj_k;
    gndSpeed = sqrt(UAV_Dynamics_B.Product[0] * UAV_Dynamics_B.Product[0] +
                    UAV_Dynamics_B.Product[1] * UAV_Dynamics_B.Product[1]);
    GPSSensorBase_stepRandomStream(&UAV_Dynamics_DW.obj_g, rtb_Sum_ha);
    rtb_Sum_ha[0] *= UAV_Dynamics_DW.obj_g.VelocityAccuracy;
    rtb_Sum_ha[1] *= UAV_Dynamics_DW.obj_g.VelocityAccuracy;
    rtb_Sum_ha[2] *= UAV_Dynamics_DW.obj_g.VelocityAccuracy;
    rtb_TransferFcn = UAV_Dynamics_DW.obj_g.VelocityAccuracy / gndSpeed;
    if (!(gndSpeed > 0.0)) {
      rtb_TransferFcn = 360.0;
      rtb_ixj_k = UAV_Dynamics_RandStream_rand_p(UAV_Dynamics_DW.obj_g.pStream);
    } else {
      nt = UAV_Dynamics_DW.obj_g.pStream->NtMethod;
      if (nt == ziggurat) {
        obj = UAV_Dynamics_DW.obj_g.pStream->Generator;
        rtb_ixj_k = UAV_Dynami_mt19937ar_mtziggurat(obj);
      } else if (UAV_Dynamics_DW.obj_g.pStream->NtMethod == ziggurat) {
        rtb_ixj_k = UAV_RandStream_zigguratGenrandn
          (UAV_Dynamics_DW.obj_g.pStream);
      } else if (UAV_Dynamics_DW.obj_g.pStream->NtMethod == polar) {
        rtb_ixj_k = UAV_Dy_RandStream_polarGenrandn
          (UAV_Dynamics_DW.obj_g.pStream);
      } else {
        rtb_ixj_k = UA_RandStream_inversionGenrandn
          (UAV_Dynamics_DW.obj_g.pStream);
      }
    }

    rtb_ixj_k *= rtb_TransferFcn;
    rtb_kxi += UAV_Dynamics_X.xeyeze_CSTATE[0];
    rtb_fcn3 += UAV_Dynamics_X.xeyeze_CSTATE[1];
    rtb_ixk += UAV_Dynamics_X.xeyeze_CSTATE[2];

    /* Start for MATLABSystem: '<S2>/GPS' */
    rtb_jxi = UAV_Dynamics_cosd(47.397742);
    rtb_TransferFcn = UAV_Dynamics_sind(47.397742);
    au = UAV_Dynamics_cosd(8.545594);
    bv = UAV_Dynamics_sind(8.545594);

    /* MATLABSystem: '<S2>/GPS' */
    rtb_TransferFcn4 = 6.378137E+6 / sqrt(1.0 - rtb_TransferFcn *
      rtb_TransferFcn * 0.0066943799901413165);
    rtb_ixj = (rtb_TransferFcn4 + 488.0) * rtb_jxi;
    tmp = rtb_jxi * -rtb_ixk - rtb_TransferFcn * rtb_kxi;
    c[0] = (au * tmp - bv * rtb_fcn3) + rtb_ixj * au;
    c[1] = (bv * tmp + au * rtb_fcn3) + rtb_ixj * bv;
    c[2] = (rtb_TransferFcn4 * 0.99330562000985867 + 488.0) * rtb_TransferFcn +
      (rtb_TransferFcn * -rtb_ixk + rtb_jxi * rtb_kxi);
    rtb_ixj = rt_hypotd_snf(c[0], c[1]);
    rtb_ixk = 6.378137E+6 * rtb_ixj;
    rtb_TransferFcn4 = (42841.311513313565 / rt_hypotd_snf(rtb_ixj, c[2]) + 1.0)
      * (6.3567523142451793E+6 * c[2]);

    /* Start for MATLABSystem: '<S2>/GPS' */
    if (rtIsNaN(rtb_ixk)) {
      rtb_fcn3 = (rtNaN);
    } else {
      rtb_fcn3 = (rtb_ixk > 0.0);
    }

    /* MATLABSystem: '<S2>/GPS' */
    rtb_kxi = rtb_fcn3 / rt_hypotd_snf(1.0, rtb_TransferFcn4 / rtb_ixk);

    /* Start for MATLABSystem: '<S2>/GPS' */
    if (rtIsNaN(rtb_TransferFcn4)) {
      rtb_fcn3 = (rtNaN);
    } else if (rtb_TransferFcn4 < 0.0) {
      rtb_fcn3 = -1.0;
    } else {
      rtb_fcn3 = (rtb_TransferFcn4 > 0.0);
    }

    /* MATLABSystem: '<S2>/GPS' incorporates:
     *  Reshape: '<S2>/Reshape1'
     */
    rtb_fcn3 /= rt_hypotd_snf(1.0, rtb_ixk / rtb_TransferFcn4);
    count = 0;
    iterate = true;
    while (iterate && (count < 5)) {
      rtb_jxi = rtb_kxi;
      rtb_TransferFcn = rtb_fcn3;
      rtb_ixk = rtb_ixj - 42697.672707179969 * rt_powd_snf(rtb_kxi, 3.0);
      rtb_TransferFcn4 = 42841.311513313565 * rt_powd_snf(rtb_fcn3, 3.0) + c[2];
      au = 6.378137E+6 * rtb_ixk;
      bv = 6.3567523142451793E+6 * rtb_TransferFcn4;
      if (rtIsNaN(au)) {
        rtb_fcn3 = (rtNaN);
      } else if (au < 0.0) {
        rtb_fcn3 = -1.0;
      } else {
        rtb_fcn3 = (au > 0.0);
      }

      rtb_kxi = rtb_fcn3 / rt_hypotd_snf(1.0, bv / au);
      if (rtIsNaN(bv)) {
        rtb_fcn3 = (rtNaN);
      } else if (bv < 0.0) {
        rtb_fcn3 = -1.0;
      } else {
        rtb_fcn3 = (bv > 0.0);
      }

      rtb_fcn3 /= rt_hypotd_snf(1.0, au / bv);
      iterate = (rt_hypotd_snf(rtb_kxi - rtb_jxi, rtb_fcn3 - rtb_TransferFcn) >
                 2.2204460492503131E-16);
      count++;
    }

    rtb_fcn3 = 57.295779513082323 * rt_atan2d_snf(rtb_TransferFcn4, rtb_ixk);
    rtb_ixk = UAV_Dynamics_sind(rtb_fcn3);
    rtb_TransferFcn4 = 6.378137E+6 / sqrt(1.0 - rtb_ixk * rtb_ixk *
      0.0066943799901413165);
    UAV_Dynamics_Y.GndSpeed = sqrt(rtb_Sum_ha[0] * rtb_Sum_ha[0] + rtb_Sum_ha[1]
      * rtb_Sum_ha[1]) + gndSpeed;
    rtb_ixj_k += 57.295779513082323 * rt_atan2d_snf(UAV_Dynamics_B.Product[1],
      UAV_Dynamics_B.Product[0]);
    iterate = (rtb_ixj_k > 0.0);
    gndSpeed = rtb_ixj_k;
    if (rtIsNaN(rtb_ixj_k) || rtIsInf(rtb_ixj_k)) {
      rtb_ixj_k = (rtNaN);
    } else if (rtb_ixj_k == 0.0) {
      rtb_ixj_k = 0.0;
    } else {
      rtb_ixj_k = fmod(rtb_ixj_k, 360.0);
      if (rtb_ixj_k == 0.0) {
        rtb_ixj_k = 0.0;
      } else if (gndSpeed < 0.0) {
        rtb_ixj_k += 360.0;
      }
    }

    if ((rtb_ixj_k == 0.0) && iterate) {
      rtb_ixj_k = 360.0;
    }

    UAV_Dynamics_Y.Velocity[0] = UAV_Dynamics_Y.GndSpeed * UAV_Dynamics_cosd
      (rtb_ixj_k);
    UAV_Dynamics_Y.Velocity[1] = UAV_Dynamics_Y.GndSpeed * UAV_Dynamics_sind
      (rtb_ixj_k);
    UAV_Dynamics_Y.Velocity[2] = UAV_Dynamics_B.Product[2] + rtb_Sum_ha[2];
    UAV_Dynamics_Y.LLA[0] = rtb_fcn3;
    UAV_Dynamics_Y.LLA[1] = 57.295779513082323 * rt_atan2d_snf(c[1], c[0]);
    UAV_Dynamics_Y.LLA[2] = ((0.0066943799901413165 * rtb_TransferFcn4 * rtb_ixk
      + c[2]) * rtb_ixk + rtb_ixj * UAV_Dynamics_cosd(rtb_fcn3)) -
      rtb_TransferFcn4;

    /* Gain: '<S1>/Gain1' incorporates:
     *  Gain: '<S1>/Gain2'
     *  RandomNumber: '<S1>/Random Number1'
     *  Sum: '<S1>/Sum1'
     */
    rtb_ixk = (1000.0 * UAV_Dynamics_Y.LLA[2] + UAV_Dynamics_DW.NextOutput) *
      0.001;

    /* Saturate: '<S6>/Limit  altitude  to troposhere' */
    if (rtb_ixk > 11000.0) {
      rtb_fcn3 = 11000.0;
    } else if (rtb_ixk < 0.0) {
      rtb_fcn3 = 0.0;
    } else {
      rtb_fcn3 = rtb_ixk;
    }

    /* Sum: '<S6>/Sum1' incorporates:
     *  Constant: '<S6>/Sea Level  Temperature'
     *  Gain: '<S6>/Lapse Rate'
     *  Saturate: '<S6>/Limit  altitude  to troposhere'
     */
    rtb_ixj = 288.15 - 0.0065 * rtb_fcn3;

    /* Saturate: '<S6>/Limit  altitude  to Stratosphere' incorporates:
     *  Constant: '<S6>/Altitude of Troposphere'
     *  Sum: '<S6>/Sum'
     */
    if (11000.0 - rtb_ixk > 0.0) {
      rtb_fcn3 = 0.0;
    } else if (11000.0 - rtb_ixk < -9000.0) {
      rtb_fcn3 = -9000.0;
    } else {
      rtb_fcn3 = 11000.0 - rtb_ixk;
    }

    /* Outport: '<Root>/Pressure' incorporates:
     *  Constant: '<S6>/Constant'
     *  Gain: '<S6>/1//T0'
     *  Gain: '<S6>/P0'
     *  Gain: '<S6>/g//R'
     *  Math: '<S6>/(T//T0)^(g//LR) '
     *  Math: '<S6>/Stratosphere Model'
     *  Product: '<S6>/Product1'
     *  Product: '<S6>/Product2'
     *  Saturate: '<S6>/Limit  altitude  to Stratosphere'
     *
     * About '<S6>/Stratosphere Model':
     *  Operator: exp
     */
    UAV_Dynamics_Y.Pressure = rt_powd_snf(0.00347041471455839 * rtb_ixj,
      5.2558756014667134) * 101325.0 * exp(1.0 / rtb_ixj * (0.034163191409533639
      * rtb_fcn3));

    /* Outport: '<Root>/Course' incorporates:
     *  MATLABSystem: '<S2>/GPS'
     * */
    UAV_Dynamics_Y.Course = rtb_ixj_k;
  }

  if (rtmIsMajorTimeStep(UAV_Dynamics_M)) {
    /* Update for Integrator: '<S10>/q0 q1 q2 q3' */
    UAV_Dynamics_DW.q0q1q2q3_IWORK = 0;
    if (rtmIsMajorTimeStep(UAV_Dynamics_M)) {
      /* Update for RandomNumber: '<S1>/Random Number1' */
      UAV_Dynamics_DW.NextOutput = rt_nrand_Upu32_Yd_f_pw_snf
        (&UAV_Dynamics_DW.RandSeed) * 100.0;
    }
  }                                    /* end MajorTimeStep */

  if (rtmIsMajorTimeStep(UAV_Dynamics_M)) {
    rt_ertODEUpdateContinuousStates(&UAV_Dynamics_M->solverInfo);

    /* Update absolute time for base rate */
    /* The "clockTick0" counts the number of times the code of this task has
     * been executed. The absolute time is the multiplication of "clockTick0"
     * and "Timing.stepSize0". Size of "clockTick0" ensures timer will not
     * overflow during the application lifespan selected.
     */
    ++UAV_Dynamics_M->Timing.clockTick0;
    UAV_Dynamics_M->Timing.t[0] = rtsiGetSolverStopTime
      (&UAV_Dynamics_M->solverInfo);

    {
      /* Update absolute timer for sample time: [0.01s, 0.0s] */
      /* The "clockTick1" counts the number of times the code of this task has
       * been executed. The resolution of this integer timer is 0.01, which is the step size
       * of the task. Size of "clockTick1" ensures timer will not overflow during the
       * application lifespan selected.
       */
      UAV_Dynamics_M->Timing.clockTick1++;
    }
  }                                    /* end MajorTimeStep */
}

/* Derivatives for root system: '<Root>' */
void UAV_Dynamics_derivatives(void)
{
  XDot_UAV_Dynamics_T *_rtXdot;
  _rtXdot = ((XDot_UAV_Dynamics_T *) UAV_Dynamics_M->derivs);

  /* Derivatives for Integrator: '<S10>/q0 q1 q2 q3' */
  _rtXdot->q0q1q2q3_CSTATE[0] = UAV_Dynamics_B.TmpSignalConversionAtq0q1q2q3_a[0];
  _rtXdot->q0q1q2q3_CSTATE[1] = UAV_Dynamics_B.TmpSignalConversionAtq0q1q2q3_a[1];
  _rtXdot->q0q1q2q3_CSTATE[2] = UAV_Dynamics_B.TmpSignalConversionAtq0q1q2q3_a[2];
  _rtXdot->q0q1q2q3_CSTATE[3] = UAV_Dynamics_B.TmpSignalConversionAtq0q1q2q3_a[3];

  /* Derivatives for TransferFcn: '<S63>/Transfer Fcn4' incorporates:
   *  Inport: '<Root>/PWM Inputs'
   */
  _rtXdot->TransferFcn4_CSTATE = -20.0 * UAV_Dynamics_X.TransferFcn4_CSTATE;
  _rtXdot->TransferFcn4_CSTATE += UAV_Dynamics_U.PWMInputs[0];

  /* Derivatives for TransferFcn: '<S63>/Transfer Fcn3' incorporates:
   *  Inport: '<Root>/PWM Inputs'
   */
  _rtXdot->TransferFcn3_CSTATE = -20.0 * UAV_Dynamics_X.TransferFcn3_CSTATE;
  _rtXdot->TransferFcn3_CSTATE += UAV_Dynamics_U.PWMInputs[1];

  /* Derivatives for TransferFcn: '<S63>/Transfer Fcn2' incorporates:
   *  Inport: '<Root>/PWM Inputs'
   */
  _rtXdot->TransferFcn2_CSTATE = -20.0 * UAV_Dynamics_X.TransferFcn2_CSTATE;
  _rtXdot->TransferFcn2_CSTATE += UAV_Dynamics_U.PWMInputs[2];

  /* Derivatives for TransferFcn: '<S63>/Transfer Fcn' incorporates:
   *  Inport: '<Root>/PWM Inputs'
   */
  _rtXdot->TransferFcn_CSTATE = -20.0 * UAV_Dynamics_X.TransferFcn_CSTATE;
  _rtXdot->TransferFcn_CSTATE += UAV_Dynamics_U.PWMInputs[3];

  /* Derivatives for TransferFcn: '<S64>/Transfer Fcn1' incorporates:
   *  Inport: '<Root>/PWM Inputs'
   */
  _rtXdot->TransferFcn1_CSTATE = -20.0 * UAV_Dynamics_X.TransferFcn1_CSTATE;
  _rtXdot->TransferFcn1_CSTATE += UAV_Dynamics_U.PWMInputs[0];

  /* Derivatives for TransferFcn: '<S64>/Transfer Fcn2' incorporates:
   *  Inport: '<Root>/PWM Inputs'
   */
  _rtXdot->TransferFcn2_CSTATE_i = -20.0 * UAV_Dynamics_X.TransferFcn2_CSTATE_i;
  _rtXdot->TransferFcn2_CSTATE_i += UAV_Dynamics_U.PWMInputs[1];

  /* Derivatives for TransferFcn: '<S64>/Transfer Fcn3' incorporates:
   *  Inport: '<Root>/PWM Inputs'
   */
  _rtXdot->TransferFcn3_CSTATE_o = -20.0 * UAV_Dynamics_X.TransferFcn3_CSTATE_o;
  _rtXdot->TransferFcn3_CSTATE_o += UAV_Dynamics_U.PWMInputs[2];

  /* Derivatives for TransferFcn: '<S64>/Transfer Fcn4' incorporates:
   *  Inport: '<Root>/PWM Inputs'
   */
  _rtXdot->TransferFcn4_CSTATE_j = -20.0 * UAV_Dynamics_X.TransferFcn4_CSTATE_j;
  _rtXdot->TransferFcn4_CSTATE_j += UAV_Dynamics_U.PWMInputs[3];

  /* Derivatives for Integrator: '<S7>/p,q,r ' */
  _rtXdot->pqr_CSTATE[0] = UAV_Dynamics_B.Product2[0];

  /* Derivatives for Integrator: '<S7>/ub,vb,wb' */
  _rtXdot->ubvbwb_CSTATE[0] = UAV_Dynamics_B.Sum[0];

  /* Derivatives for Integrator: '<S7>/xe,ye,ze' */
  _rtXdot->xeyeze_CSTATE[0] = UAV_Dynamics_B.Product[0];

  /* Derivatives for Integrator: '<S7>/p,q,r ' */
  _rtXdot->pqr_CSTATE[1] = UAV_Dynamics_B.Product2[1];

  /* Derivatives for Integrator: '<S7>/ub,vb,wb' */
  _rtXdot->ubvbwb_CSTATE[1] = UAV_Dynamics_B.Sum[1];

  /* Derivatives for Integrator: '<S7>/xe,ye,ze' */
  _rtXdot->xeyeze_CSTATE[1] = UAV_Dynamics_B.Product[1];

  /* Derivatives for Integrator: '<S7>/p,q,r ' */
  _rtXdot->pqr_CSTATE[2] = UAV_Dynamics_B.Product2[2];

  /* Derivatives for Integrator: '<S7>/ub,vb,wb' */
  _rtXdot->ubvbwb_CSTATE[2] = UAV_Dynamics_B.Sum[2];

  /* Derivatives for Integrator: '<S7>/xe,ye,ze' */
  _rtXdot->xeyeze_CSTATE[2] = UAV_Dynamics_B.Product[2];
}

/* Model initialize function */
void UAV_Dynamics_initialize(void)
{
  /* Registration code */

  /* initialize non-finites */
  rt_InitInfAndNaN(sizeof(real_T));

  {
    /* Setup solver object */
    rtsiSetSimTimeStepPtr(&UAV_Dynamics_M->solverInfo,
                          &UAV_Dynamics_M->Timing.simTimeStep);
    rtsiSetTPtr(&UAV_Dynamics_M->solverInfo, &rtmGetTPtr(UAV_Dynamics_M));
    rtsiSetStepSizePtr(&UAV_Dynamics_M->solverInfo,
                       &UAV_Dynamics_M->Timing.stepSize0);
    rtsiSetdXPtr(&UAV_Dynamics_M->solverInfo, &UAV_Dynamics_M->derivs);
    rtsiSetContStatesPtr(&UAV_Dynamics_M->solverInfo, (real_T **)
                         &UAV_Dynamics_M->contStates);
    rtsiSetNumContStatesPtr(&UAV_Dynamics_M->solverInfo,
      &UAV_Dynamics_M->Sizes.numContStates);
    rtsiSetNumPeriodicContStatesPtr(&UAV_Dynamics_M->solverInfo,
      &UAV_Dynamics_M->Sizes.numPeriodicContStates);
    rtsiSetPeriodicContStateIndicesPtr(&UAV_Dynamics_M->solverInfo,
      &UAV_Dynamics_M->periodicContStateIndices);
    rtsiSetPeriodicContStateRangesPtr(&UAV_Dynamics_M->solverInfo,
      &UAV_Dynamics_M->periodicContStateRanges);
    rtsiSetContStateDisabledPtr(&UAV_Dynamics_M->solverInfo, (boolean_T**)
      &UAV_Dynamics_M->contStateDisabled);
    rtsiSetErrorStatusPtr(&UAV_Dynamics_M->solverInfo, (&rtmGetErrorStatus
      (UAV_Dynamics_M)));
    rtsiSetRTModelPtr(&UAV_Dynamics_M->solverInfo, UAV_Dynamics_M);
  }

  rtsiSetSimTimeStep(&UAV_Dynamics_M->solverInfo, MAJOR_TIME_STEP);
  UAV_Dynamics_M->intgData.y = UAV_Dynamics_M->odeY;
  UAV_Dynamics_M->intgData.f[0] = UAV_Dynamics_M->odeF[0];
  UAV_Dynamics_M->intgData.f[1] = UAV_Dynamics_M->odeF[1];
  UAV_Dynamics_M->intgData.f[2] = UAV_Dynamics_M->odeF[2];
  UAV_Dynamics_M->intgData.f[3] = UAV_Dynamics_M->odeF[3];
  UAV_Dynamics_M->contStates = ((X_UAV_Dynamics_T *) &UAV_Dynamics_X);
  UAV_Dynamics_M->contStateDisabled = ((XDis_UAV_Dynamics_T *)
    &UAV_Dynamics_XDis);
  UAV_Dynamics_M->Timing.tStart = (0.0);
  rtsiSetSolverData(&UAV_Dynamics_M->solverInfo, (void *)
                    &UAV_Dynamics_M->intgData);
  rtsiSetIsMinorTimeStepWithModeChange(&UAV_Dynamics_M->solverInfo, false);
  rtsiSetSolverName(&UAV_Dynamics_M->solverInfo,"ode4");
  rtmSetTPtr(UAV_Dynamics_M, &UAV_Dynamics_M->Timing.tArray[0]);
  UAV_Dynamics_M->Timing.stepSize0 = 0.01;
  rtmSetFirstInitCond(UAV_Dynamics_M, 1);

  {
    int32_T i;
    boolean_T flag;

    /* Start for If: '<S37>/If' */
    UAV_Dynamics_DW.If_ActiveSubsystem = -1;

    /* InitializeConditions for Integrator: '<S10>/q0 q1 q2 q3' */
    if (rtmIsFirstInitCond(UAV_Dynamics_M)) {
      UAV_Dynamics_X.q0q1q2q3_CSTATE[0] = 0.0;
      UAV_Dynamics_X.q0q1q2q3_CSTATE[1] = 0.0;
      UAV_Dynamics_X.q0q1q2q3_CSTATE[2] = 0.0;
      UAV_Dynamics_X.q0q1q2q3_CSTATE[3] = 0.0;
    }

    UAV_Dynamics_DW.q0q1q2q3_IWORK = 1;

    /* End of InitializeConditions for Integrator: '<S10>/q0 q1 q2 q3' */

    /* InitializeConditions for TransferFcn: '<S63>/Transfer Fcn4' */
    UAV_Dynamics_X.TransferFcn4_CSTATE = 0.0;

    /* InitializeConditions for TransferFcn: '<S63>/Transfer Fcn3' */
    UAV_Dynamics_X.TransferFcn3_CSTATE = 0.0;

    /* InitializeConditions for TransferFcn: '<S63>/Transfer Fcn2' */
    UAV_Dynamics_X.TransferFcn2_CSTATE = 0.0;

    /* InitializeConditions for TransferFcn: '<S63>/Transfer Fcn' */
    UAV_Dynamics_X.TransferFcn_CSTATE = 0.0;

    /* InitializeConditions for TransferFcn: '<S64>/Transfer Fcn1' */
    UAV_Dynamics_X.TransferFcn1_CSTATE = 0.0;

    /* InitializeConditions for TransferFcn: '<S64>/Transfer Fcn2' */
    UAV_Dynamics_X.TransferFcn2_CSTATE_i = 0.0;

    /* InitializeConditions for TransferFcn: '<S64>/Transfer Fcn3' */
    UAV_Dynamics_X.TransferFcn3_CSTATE_o = 0.0;

    /* InitializeConditions for TransferFcn: '<S64>/Transfer Fcn4' */
    UAV_Dynamics_X.TransferFcn4_CSTATE_j = 0.0;

    /* InitializeConditions for Integrator: '<S7>/p,q,r ' */
    UAV_Dynamics_X.pqr_CSTATE[0] = 0.0;

    /* InitializeConditions for Integrator: '<S7>/ub,vb,wb' */
    UAV_Dynamics_X.ubvbwb_CSTATE[0] = 0.0;

    /* InitializeConditions for Integrator: '<S7>/xe,ye,ze' incorporates:
     *  Reshape: '<S2>/Reshape3'
     */
    UAV_Dynamics_X.xeyeze_CSTATE[0] = 0.0;

    /* InitializeConditions for Integrator: '<S7>/p,q,r ' */
    UAV_Dynamics_X.pqr_CSTATE[1] = 0.0;

    /* InitializeConditions for Integrator: '<S7>/ub,vb,wb' */
    UAV_Dynamics_X.ubvbwb_CSTATE[1] = 0.0;

    /* InitializeConditions for Integrator: '<S7>/xe,ye,ze' incorporates:
     *  Reshape: '<S2>/Reshape3'
     */
    UAV_Dynamics_X.xeyeze_CSTATE[1] = 0.0;

    /* InitializeConditions for Integrator: '<S7>/p,q,r ' */
    UAV_Dynamics_X.pqr_CSTATE[2] = 0.0;

    /* InitializeConditions for Integrator: '<S7>/ub,vb,wb' */
    UAV_Dynamics_X.ubvbwb_CSTATE[2] = 0.0;

    /* InitializeConditions for Integrator: '<S7>/xe,ye,ze' incorporates:
     *  Reshape: '<S2>/Reshape3'
     */
    UAV_Dynamics_X.xeyeze_CSTATE[2] = 0.0025316129032258066;

    /* InitializeConditions for RandomNumber: '<S1>/Random Number1' */
    UAV_Dynamics_DW.RandSeed = 655360U;
    UAV_Dynamics_DW.NextOutput = rt_nrand_Upu32_Yd_f_pw_snf
      (&UAV_Dynamics_DW.RandSeed) * 100.0;

    /* Start for MATLABSystem: '<S3>/IMU1' */
    UAV_Dynamics_DW.obj.MagneticFieldNED[0] = 27.555;
    UAV_Dynamics_DW.obj.MagneticFieldNED[1] = -2.4169;
    UAV_Dynamics_DW.obj.MagneticFieldNED[2] = -16.0849;
    UAV_Dynamics_DW.obj.isInitialized = 0;
    for (i = 0; i < 38; i++) {
      UAV_Dynamics_DW.obj.tunablePropertyChanged[i] = false;
    }

    flag = (UAV_Dynamics_DW.obj.isInitialized == 1);
    if (flag) {
      UAV_Dynamics_DW.obj.TunablePropsChanged = true;
      UAV_Dynamics_DW.obj.tunablePropertyChanged[2] = true;
    }

    flag = (UAV_Dynamics_DW.obj.isInitialized == 1);
    if (flag) {
      UAV_Dynamics_DW.obj.TunablePropsChanged = true;
      UAV_Dynamics_DW.obj.tunablePropertyChanged[37] = true;
    }

    UAV_Dynamics_DW.obj.Temperature = 25.0;
    flag = (UAV_Dynamics_DW.obj.isInitialized == 1);
    if (flag) {
      UAV_Dynamics_DW.obj.TunablePropsChanged = true;
      UAV_Dynamics_DW.obj.tunablePropertyChanged[0] = true;
    }

    flag = (UAV_Dynamics_DW.obj.isInitialized == 1);
    if (flag) {
      UAV_Dynamics_DW.obj.TunablePropsChanged = true;
      UAV_Dynamics_DW.obj.tunablePropertyChanged[2] = true;
    }

    UAV_Dynamics_DW.obj.MagneticField[0] = 21.5;
    UAV_Dynamics_DW.obj.MagneticField[1] = 1.16;
    UAV_Dynamics_DW.obj.MagneticField[2] = 43.1;
    flag = (UAV_Dynamics_DW.obj.isInitialized == 1);
    if (flag) {
      UAV_Dynamics_DW.obj.TunablePropsChanged = true;
      UAV_Dynamics_DW.obj.tunablePropertyChanged[3] = true;
    }

    UAV_Dynamics_DW.obj.AccelParamsMeasurementRange = (rtInf);
    flag = (UAV_Dynamics_DW.obj.isInitialized == 1);
    if (flag) {
      UAV_Dynamics_DW.obj.TunablePropsChanged = true;
      UAV_Dynamics_DW.obj.tunablePropertyChanged[4] = true;
    }

    UAV_Dynamics_DW.obj.AccelParamsResolution = 0.0;
    flag = (UAV_Dynamics_DW.obj.isInitialized == 1);
    if (flag) {
      UAV_Dynamics_DW.obj.TunablePropsChanged = true;
      UAV_Dynamics_DW.obj.tunablePropertyChanged[5] = true;
    }

    UAV_Dynamics_DW.obj.AccelParamsConstantBias[0] = 0.0;
    UAV_Dynamics_DW.obj.AccelParamsConstantBias[1] = 0.0;
    UAV_Dynamics_DW.obj.AccelParamsConstantBias[2] = 0.0;
    flag = (UAV_Dynamics_DW.obj.isInitialized == 1);
    if (flag) {
      UAV_Dynamics_DW.obj.TunablePropsChanged = true;
      UAV_Dynamics_DW.obj.tunablePropertyChanged[6] = true;
    }

    UAV_Dynamics_DW.obj.AccelParamsAxesMisalignment[0] = 0.0;
    UAV_Dynamics_DW.obj.AccelParamsAxesMisalignment[1] = 0.0;
    UAV_Dynamics_DW.obj.AccelParamsAxesMisalignment[2] = 0.0;
    flag = (UAV_Dynamics_DW.obj.isInitialized == 1);
    if (flag) {
      UAV_Dynamics_DW.obj.TunablePropsChanged = true;
      UAV_Dynamics_DW.obj.tunablePropertyChanged[7] = true;
    }

    UAV_Dynamics_DW.obj.AccelParamsNoiseDensity = 0.0003;
    flag = (UAV_Dynamics_DW.obj.isInitialized == 1);
    if (flag) {
      UAV_Dynamics_DW.obj.TunablePropsChanged = true;
      UAV_Dynamics_DW.obj.tunablePropertyChanged[8] = true;
    }

    UAV_Dynamics_DW.obj.AccelParamsBiasInstability[0] = 0.0;
    UAV_Dynamics_DW.obj.AccelParamsBiasInstability[1] = 0.0;
    UAV_Dynamics_DW.obj.AccelParamsBiasInstability[2] = 0.0;
    flag = (UAV_Dynamics_DW.obj.isInitialized == 1);
    if (flag) {
      UAV_Dynamics_DW.obj.TunablePropsChanged = true;
      UAV_Dynamics_DW.obj.tunablePropertyChanged[9] = true;
    }

    UAV_Dynamics_DW.obj.AccelParamsBiasInstabilityNumerator = 1.0;
    flag = (UAV_Dynamics_DW.obj.isInitialized == 1);
    if (flag) {
      UAV_Dynamics_DW.obj.TunablePropsChanged = true;
      UAV_Dynamics_DW.obj.tunablePropertyChanged[10] = true;
    }

    UAV_Dynamics_DW.obj.AccelParamsBiasInstabilityDenominator[0] = 1.0;
    UAV_Dynamics_DW.obj.AccelParamsBiasInstabilityDenominator[1] = -0.5;
    flag = (UAV_Dynamics_DW.obj.isInitialized == 1);
    if (flag) {
      UAV_Dynamics_DW.obj.TunablePropsChanged = true;
      UAV_Dynamics_DW.obj.tunablePropertyChanged[11] = true;
    }

    UAV_Dynamics_DW.obj.AccelParamsRandomWalk[0] = 0.0;
    UAV_Dynamics_DW.obj.AccelParamsRandomWalk[1] = 0.0;
    UAV_Dynamics_DW.obj.AccelParamsRandomWalk[2] = 0.0;
    flag = (UAV_Dynamics_DW.obj.isInitialized == 1);
    if (flag) {
      UAV_Dynamics_DW.obj.TunablePropsChanged = true;
      UAV_Dynamics_DW.obj.tunablePropertyChanged[12] = true;
    }

    UAV_Dynamics_DW.obj.AccelParamsTemperatureBias[0] = 0.0;
    UAV_Dynamics_DW.obj.AccelParamsTemperatureBias[1] = 0.0;
    UAV_Dynamics_DW.obj.AccelParamsTemperatureBias[2] = 0.0;
    flag = (UAV_Dynamics_DW.obj.isInitialized == 1);
    if (flag) {
      UAV_Dynamics_DW.obj.TunablePropsChanged = true;
      UAV_Dynamics_DW.obj.tunablePropertyChanged[13] = true;
    }

    UAV_Dynamics_DW.obj.AccelParamsTemperatureScaleFactor[0] = 0.0;
    UAV_Dynamics_DW.obj.AccelParamsTemperatureScaleFactor[1] = 0.0;
    UAV_Dynamics_DW.obj.AccelParamsTemperatureScaleFactor[2] = 0.0;
    flag = (UAV_Dynamics_DW.obj.isInitialized == 1);
    if (flag) {
      UAV_Dynamics_DW.obj.TunablePropsChanged = true;
      UAV_Dynamics_DW.obj.tunablePropertyChanged[14] = true;
    }

    UAV_Dynamics_DW.obj.GyroParamsMeasurementRange = (rtInf);
    flag = (UAV_Dynamics_DW.obj.isInitialized == 1);
    if (flag) {
      UAV_Dynamics_DW.obj.TunablePropsChanged = true;
      UAV_Dynamics_DW.obj.tunablePropertyChanged[15] = true;
    }

    UAV_Dynamics_DW.obj.GyroParamsResolution = 0.0;
    flag = (UAV_Dynamics_DW.obj.isInitialized == 1);
    if (flag) {
      UAV_Dynamics_DW.obj.TunablePropsChanged = true;
      UAV_Dynamics_DW.obj.tunablePropertyChanged[16] = true;
    }

    UAV_Dynamics_DW.obj.GyroParamsConstantBias[0] = 0.0;
    UAV_Dynamics_DW.obj.GyroParamsConstantBias[1] = 0.0;
    UAV_Dynamics_DW.obj.GyroParamsConstantBias[2] = 0.0;
    flag = (UAV_Dynamics_DW.obj.isInitialized == 1);
    if (flag) {
      UAV_Dynamics_DW.obj.TunablePropsChanged = true;
      UAV_Dynamics_DW.obj.tunablePropertyChanged[17] = true;
    }

    UAV_Dynamics_DW.obj.GyroParamsAxesMisalignment[0] = 0.0;
    UAV_Dynamics_DW.obj.GyroParamsAxesMisalignment[1] = 0.0;
    UAV_Dynamics_DW.obj.GyroParamsAxesMisalignment[2] = 0.0;
    flag = (UAV_Dynamics_DW.obj.isInitialized == 1);
    if (flag) {
      UAV_Dynamics_DW.obj.TunablePropsChanged = true;
      UAV_Dynamics_DW.obj.tunablePropertyChanged[25] = true;
    }

    UAV_Dynamics_DW.obj.GyroParamsAccelerationBias = 0.0001;
    flag = (UAV_Dynamics_DW.obj.isInitialized == 1);
    if (flag) {
      UAV_Dynamics_DW.obj.TunablePropsChanged = true;
      UAV_Dynamics_DW.obj.tunablePropertyChanged[18] = true;
    }

    UAV_Dynamics_DW.obj.GyroParamsNoiseDensity = 0.01;
    flag = (UAV_Dynamics_DW.obj.isInitialized == 1);
    if (flag) {
      UAV_Dynamics_DW.obj.TunablePropsChanged = true;
      UAV_Dynamics_DW.obj.tunablePropertyChanged[19] = true;
    }

    UAV_Dynamics_DW.obj.GyroParamsBiasInstability[0] = 0.0;
    UAV_Dynamics_DW.obj.GyroParamsBiasInstability[1] = 0.0;
    UAV_Dynamics_DW.obj.GyroParamsBiasInstability[2] = 0.0;
    flag = (UAV_Dynamics_DW.obj.isInitialized == 1);
    if (flag) {
      UAV_Dynamics_DW.obj.TunablePropsChanged = true;
      UAV_Dynamics_DW.obj.tunablePropertyChanged[20] = true;
    }

    UAV_Dynamics_DW.obj.GyroParamsBiasInstabilityNumerator = 1.0;
    flag = (UAV_Dynamics_DW.obj.isInitialized == 1);
    if (flag) {
      UAV_Dynamics_DW.obj.TunablePropsChanged = true;
      UAV_Dynamics_DW.obj.tunablePropertyChanged[21] = true;
    }

    UAV_Dynamics_DW.obj.GyroParamsBiasInstabilityDenominator[0] = 1.0;
    UAV_Dynamics_DW.obj.GyroParamsBiasInstabilityDenominator[1] = -0.5;
    flag = (UAV_Dynamics_DW.obj.isInitialized == 1);
    if (flag) {
      UAV_Dynamics_DW.obj.TunablePropsChanged = true;
      UAV_Dynamics_DW.obj.tunablePropertyChanged[22] = true;
    }

    UAV_Dynamics_DW.obj.GyroParamsRandomWalk[0] = 0.0;
    UAV_Dynamics_DW.obj.GyroParamsRandomWalk[1] = 0.0;
    UAV_Dynamics_DW.obj.GyroParamsRandomWalk[2] = 0.0;
    flag = (UAV_Dynamics_DW.obj.isInitialized == 1);
    if (flag) {
      UAV_Dynamics_DW.obj.TunablePropsChanged = true;
      UAV_Dynamics_DW.obj.tunablePropertyChanged[23] = true;
    }

    UAV_Dynamics_DW.obj.GyroParamsTemperatureBias[0] = 0.0;
    UAV_Dynamics_DW.obj.GyroParamsTemperatureBias[1] = 0.0;
    UAV_Dynamics_DW.obj.GyroParamsTemperatureBias[2] = 0.0;
    flag = (UAV_Dynamics_DW.obj.isInitialized == 1);
    if (flag) {
      UAV_Dynamics_DW.obj.TunablePropsChanged = true;
      UAV_Dynamics_DW.obj.tunablePropertyChanged[24] = true;
    }

    UAV_Dynamics_DW.obj.GyroParamsTemperatureScaleFactor[0] = 0.0;
    UAV_Dynamics_DW.obj.GyroParamsTemperatureScaleFactor[1] = 0.0;
    UAV_Dynamics_DW.obj.GyroParamsTemperatureScaleFactor[2] = 0.0;
    flag = (UAV_Dynamics_DW.obj.isInitialized == 1);
    if (flag) {
      UAV_Dynamics_DW.obj.TunablePropsChanged = true;
      UAV_Dynamics_DW.obj.tunablePropertyChanged[26] = true;
    }

    UAV_Dynamics_DW.obj.MagParamsMeasurementRange = (rtInf);
    flag = (UAV_Dynamics_DW.obj.isInitialized == 1);
    if (flag) {
      UAV_Dynamics_DW.obj.TunablePropsChanged = true;
      UAV_Dynamics_DW.obj.tunablePropertyChanged[27] = true;
    }

    UAV_Dynamics_DW.obj.MagParamsResolution = 0.0;
    flag = (UAV_Dynamics_DW.obj.isInitialized == 1);
    if (flag) {
      UAV_Dynamics_DW.obj.TunablePropsChanged = true;
      UAV_Dynamics_DW.obj.tunablePropertyChanged[28] = true;
    }

    UAV_Dynamics_DW.obj.MagParamsConstantBias[0] = 0.0;
    UAV_Dynamics_DW.obj.MagParamsConstantBias[1] = 0.0;
    UAV_Dynamics_DW.obj.MagParamsConstantBias[2] = 0.0;
    flag = (UAV_Dynamics_DW.obj.isInitialized == 1);
    if (flag) {
      UAV_Dynamics_DW.obj.TunablePropsChanged = true;
      UAV_Dynamics_DW.obj.tunablePropertyChanged[29] = true;
    }

    UAV_Dynamics_DW.obj.MagParamsAxesMisalignment[0] = 0.0;
    UAV_Dynamics_DW.obj.MagParamsAxesMisalignment[1] = 0.0;
    UAV_Dynamics_DW.obj.MagParamsAxesMisalignment[2] = 0.0;
    flag = (UAV_Dynamics_DW.obj.isInitialized == 1);
    if (flag) {
      UAV_Dynamics_DW.obj.TunablePropsChanged = true;
      UAV_Dynamics_DW.obj.tunablePropertyChanged[30] = true;
    }

    UAV_Dynamics_DW.obj.MagParamsNoiseDensity = 0.0005;
    flag = (UAV_Dynamics_DW.obj.isInitialized == 1);
    if (flag) {
      UAV_Dynamics_DW.obj.TunablePropsChanged = true;
      UAV_Dynamics_DW.obj.tunablePropertyChanged[31] = true;
    }

    UAV_Dynamics_DW.obj.MagParamsBiasInstability[0] = 0.0;
    UAV_Dynamics_DW.obj.MagParamsBiasInstability[1] = 0.0;
    UAV_Dynamics_DW.obj.MagParamsBiasInstability[2] = 0.0;
    flag = (UAV_Dynamics_DW.obj.isInitialized == 1);
    if (flag) {
      UAV_Dynamics_DW.obj.TunablePropsChanged = true;
      UAV_Dynamics_DW.obj.tunablePropertyChanged[32] = true;
    }

    UAV_Dynamics_DW.obj.MagParamsBiasInstabilityNumerator = 1.0;
    flag = (UAV_Dynamics_DW.obj.isInitialized == 1);
    if (flag) {
      UAV_Dynamics_DW.obj.TunablePropsChanged = true;
      UAV_Dynamics_DW.obj.tunablePropertyChanged[33] = true;
    }

    UAV_Dynamics_DW.obj.MagParamsBiasInstabilityDenominator[0] = 1.0;
    UAV_Dynamics_DW.obj.MagParamsBiasInstabilityDenominator[1] = -0.5;
    flag = (UAV_Dynamics_DW.obj.isInitialized == 1);
    if (flag) {
      UAV_Dynamics_DW.obj.TunablePropsChanged = true;
      UAV_Dynamics_DW.obj.tunablePropertyChanged[34] = true;
    }

    UAV_Dynamics_DW.obj.MagParamsRandomWalk[0] = 0.0;
    UAV_Dynamics_DW.obj.MagParamsRandomWalk[1] = 0.0;
    UAV_Dynamics_DW.obj.MagParamsRandomWalk[2] = 0.0;
    flag = (UAV_Dynamics_DW.obj.isInitialized == 1);
    if (flag) {
      UAV_Dynamics_DW.obj.TunablePropsChanged = true;
      UAV_Dynamics_DW.obj.tunablePropertyChanged[35] = true;
    }

    UAV_Dynamics_DW.obj.MagParamsTemperatureBias[0] = 0.0;
    UAV_Dynamics_DW.obj.MagParamsTemperatureBias[1] = 0.0;
    UAV_Dynamics_DW.obj.MagParamsTemperatureBias[2] = 0.0;
    flag = (UAV_Dynamics_DW.obj.isInitialized == 1);
    if (flag) {
      UAV_Dynamics_DW.obj.TunablePropsChanged = true;
      UAV_Dynamics_DW.obj.tunablePropertyChanged[36] = true;
    }

    UAV_Dynamics_DW.obj.MagParamsTemperatureScaleFactor[0] = 0.0;
    UAV_Dynamics_DW.obj.MagParamsTemperatureScaleFactor[1] = 0.0;
    UAV_Dynamics_DW.obj.MagParamsTemperatureScaleFactor[2] = 0.0;
    UAV_Dynamics_SystemCore_setup_p(&UAV_Dynamics_DW.obj);

    /* InitializeConditions for MATLABSystem: '<S3>/IMU1' */
    UAV_Dyn_IMUSensorBase_resetImpl(&UAV_Dynamics_DW.obj);

    /* Start for MATLABSystem: '<S2>/GPS' */
    UAV_Dynamics_DW.obj_g.isInitialized = 0;
    UAV_Dynamics_DW.obj_g.tunablePropertyChanged[0] = false;
    UAV_Dynamics_DW.obj_g.tunablePropertyChanged[1] = false;
    UAV_Dynamics_DW.obj_g.tunablePropertyChanged[2] = false;
    UAV_Dynamics_DW.obj_g.tunablePropertyChanged[3] = false;
    flag = (UAV_Dynamics_DW.obj_g.isInitialized == 1);
    if (flag) {
      UAV_Dynamics_DW.obj_g.TunablePropsChanged = true;
      UAV_Dynamics_DW.obj_g.tunablePropertyChanged[0] = true;
    }

    UAV_Dynamics_DW.obj_g.HorizontalPositionAccuracy = 0.01;
    flag = (UAV_Dynamics_DW.obj_g.isInitialized == 1);
    if (flag) {
      UAV_Dynamics_DW.obj_g.TunablePropsChanged = true;
      UAV_Dynamics_DW.obj_g.tunablePropertyChanged[1] = true;
    }

    UAV_Dynamics_DW.obj_g.VerticalPositionAccuracy = 0.01;
    flag = (UAV_Dynamics_DW.obj_g.isInitialized == 1);
    if (flag) {
      UAV_Dynamics_DW.obj_g.TunablePropsChanged = true;
      UAV_Dynamics_DW.obj_g.tunablePropertyChanged[2] = true;
    }

    UAV_Dynamics_DW.obj_g.VelocityAccuracy = 0.01;
    flag = (UAV_Dynamics_DW.obj_g.isInitialized == 1);
    if (flag) {
      UAV_Dynamics_DW.obj_g.TunablePropsChanged = true;
      UAV_Dynamics_DW.obj_g.tunablePropertyChanged[3] = true;
    }

    UAV_Dynamics_DW.obj_g.DecayFactor = 0.99;
    UAV_Dynamics_SystemCore_setup(&UAV_Dynamics_DW.obj_g);

    /* InitializeConditions for MATLABSystem: '<S2>/GPS' */
    UAV_Dyn_GPSSensorBase_resetImpl(&UAV_Dynamics_DW.obj_g);
  }

  /* set "at time zero" to false */
  if (rtmIsFirstInitCond(UAV_Dynamics_M)) {
    rtmSetFirstInitCond(UAV_Dynamics_M, 0);
  }
}

/* Model terminate function */
void UAV_Dynamics_terminate(void)
{
  /* (no terminate code required) */
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */