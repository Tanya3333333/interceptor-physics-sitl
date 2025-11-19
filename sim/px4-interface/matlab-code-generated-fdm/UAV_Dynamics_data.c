/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: UAV_Dynamics_data.c
 *
 * Code generated for Simulink model 'UAV_Dynamics'.
 *
 * Model version                  : 4.12
 * Simulink Coder version         : 23.2 (R2023b) 01-Aug-2023
 * C/C++ source code generated on : Tue Nov 18 10:21:53 2025
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: Intel->x86-64 (Windows64)
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#include "UAV_Dynamics.h"

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

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
