/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: UAV_Dynamics_private.h
 *
 * Code generated for Simulink model 'UAV_Dynamics'.
 *
 * Model version                  : 4.12
 * Simulink Coder version         : 23.2 (R2023b) 01-Aug-2023
 * C/C++ source code generated on : Mon Nov 17 17:09:33 2025
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: Intel->x86-64 (Windows64)
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#ifndef RTW_HEADER_UAV_Dynamics_private_h_
#define RTW_HEADER_UAV_Dynamics_private_h_
#include "rtwtypes.h"
#include "UAV_Dynamics.h"
#include "UAV_Dynamics_types.h"
#include "rtw_continuous.h"
#include "rtw_solver.h"

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

extern real_T rt_atan2d_snf(real_T u0, real_T u1);
extern real_T rt_roundd_snf(real_T u);
extern void rt_mrdivide_U1d1x3_U2d_9vOrDY9Z(const real_T u0[3], const real_T u1
  [9], real_T y[3]);
extern real_T rt_remd_snf(real_T u0, real_T u1);
extern real_T rt_hypotd_snf(real_T u0, real_T u1);
extern real_T rt_powd_snf(real_T u0, real_T u1);
extern real_T rt_urand_Upu32_Yd_f_pw_snf(uint32_T *u);
extern real_T rt_nrand_Upu32_Yd_f_pw_snf(uint32_T *u);
extern void CoordinateTransformationCo_Init(DW_CoordinateTransformationCo_T
  *localDW);
extern void CoordinateTransformationConvers(const real_T rtu_0[3],
  B_CoordinateTransformationCon_T *localB);

/* private model entry point functions */
extern void UAV_Dynamics_derivatives(void);

#endif                                 /* RTW_HEADER_UAV_Dynamics_private_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
