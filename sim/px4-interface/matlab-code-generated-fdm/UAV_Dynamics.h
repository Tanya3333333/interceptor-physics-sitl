/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: UAV_Dynamics.h
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

#ifndef RTW_HEADER_UAV_Dynamics_h_
#define RTW_HEADER_UAV_Dynamics_h_
#ifndef UAV_Dynamics_COMMON_INCLUDES_
#define UAV_Dynamics_COMMON_INCLUDES_
#include <string.h>
#include "rtwtypes.h"
#include "rtw_continuous.h"
#include "rtw_solver.h"
#endif                                 /* UAV_Dynamics_COMMON_INCLUDES_ */

#include "UAV_Dynamics_types.h"
#include "rt_nonfinite.h"
#include "rtGetInf.h"
#include "rtGetNaN.h"

/* Macros for accessing real-time model data structure */
#ifndef rtmGetErrorStatus
#define rtmGetErrorStatus(rtm)         ((rtm)->errorStatus)
#endif

#ifndef rtmSetErrorStatus
#define rtmSetErrorStatus(rtm, val)    ((rtm)->errorStatus = (val))
#endif

#ifndef rtmGetStopRequested
#define rtmGetStopRequested(rtm)       ((rtm)->Timing.stopRequestedFlag)
#endif

#ifndef rtmSetStopRequested
#define rtmSetStopRequested(rtm, val)  ((rtm)->Timing.stopRequestedFlag = (val))
#endif

#ifndef rtmGetStopRequestedPtr
#define rtmGetStopRequestedPtr(rtm)    (&((rtm)->Timing.stopRequestedFlag))
#endif

#ifndef rtmGetT
#define rtmGetT(rtm)                   (rtmGetTPtr((rtm))[0])
#endif

#ifndef rtmGetTPtr
#define rtmGetTPtr(rtm)                ((rtm)->Timing.t)
#endif

#ifndef rtmGetTStart
#define rtmGetTStart(rtm)              ((rtm)->Timing.tStart)
#endif

/* Block signals for system '<Root>/Coordinate Transformation Conversion1' */
typedef struct {
  real_T CoordinateTransformationConve_b[4];
                            /* '<Root>/Coordinate Transformation Conversion1' */
} B_CoordinateTransformationCon_T;

/* Block states (default storage) for system '<Root>/Coordinate Transformation Conversion1' */
typedef struct {
  robotics_slcore_internal_bloc_T obj;
                            /* '<Root>/Coordinate Transformation Conversion1' */
  boolean_T objisempty;     /* '<Root>/Coordinate Transformation Conversion1' */
} DW_CoordinateTransformationCo_T;

/* Block signals (default storage) */
typedef struct {
  real_T TmpSignalConversionAtq0q1q2q3_a[4];/* '<S10>/qdot' */
  real_T Sum[3];                       /* '<S7>/Sum' */
  real_T Product2[3];                  /* '<S11>/Product2' */
  real_T Product[3];                   /* '<S17>/Product' */
  real_T Merge;                        /* '<S37>/Merge' */
  B_CoordinateTransformationCon_T CoordinateTransformationConv_pn;
                            /* '<Root>/Coordinate Transformation Conversion1' */
  B_CoordinateTransformationCon_T CoordinateTransformationConve_p;
                            /* '<Root>/Coordinate Transformation Conversion1' */
} B_UAV_Dynamics_T;

/* Block states (default storage) for system '<Root>' */
typedef struct {
  fusion_simulink_imuSensor_UAV_T obj; /* '<S3>/IMU1' */
  fusion_internal_simulink_gpsS_T obj_g;/* '<S2>/GPS' */
  real_T Product2_DWORK4[9];           /* '<S11>/Product2' */
  real_T NextOutput;                   /* '<S1>/Random Number1' */
  uint32_T RandSeed;                   /* '<S1>/Random Number1' */
  int_T q0q1q2q3_IWORK;                /* '<S10>/q0 q1 q2 q3' */
  int8_T If_ActiveSubsystem;           /* '<S37>/If' */
  DW_CoordinateTransformationCo_T CoordinateTransformationConv_pn;
                            /* '<Root>/Coordinate Transformation Conversion1' */
  DW_CoordinateTransformationCo_T CoordinateTransformationConve_p;
                            /* '<Root>/Coordinate Transformation Conversion1' */
} DW_UAV_Dynamics_T;

/* Continuous states (default storage) */
typedef struct {
  real_T q0q1q2q3_CSTATE[4];           /* '<S10>/q0 q1 q2 q3' */
  real_T pqr_CSTATE[3];                /* '<S7>/p,q,r ' */
  real_T TransferFcn4_CSTATE;          /* '<S63>/Transfer Fcn4' */
  real_T TransferFcn3_CSTATE;          /* '<S63>/Transfer Fcn3' */
  real_T TransferFcn2_CSTATE;          /* '<S63>/Transfer Fcn2' */
  real_T TransferFcn_CSTATE;           /* '<S63>/Transfer Fcn' */
  real_T TransferFcn1_CSTATE;          /* '<S64>/Transfer Fcn1' */
  real_T TransferFcn2_CSTATE_i;        /* '<S64>/Transfer Fcn2' */
  real_T TransferFcn3_CSTATE_o;        /* '<S64>/Transfer Fcn3' */
  real_T TransferFcn4_CSTATE_j;        /* '<S64>/Transfer Fcn4' */
  real_T ubvbwb_CSTATE[3];             /* '<S7>/ub,vb,wb' */
  real_T xeyeze_CSTATE[3];             /* '<S7>/xe,ye,ze' */
} X_UAV_Dynamics_T;

/* State derivatives (default storage) */
typedef struct {
  real_T q0q1q2q3_CSTATE[4];           /* '<S10>/q0 q1 q2 q3' */
  real_T pqr_CSTATE[3];                /* '<S7>/p,q,r ' */
  real_T TransferFcn4_CSTATE;          /* '<S63>/Transfer Fcn4' */
  real_T TransferFcn3_CSTATE;          /* '<S63>/Transfer Fcn3' */
  real_T TransferFcn2_CSTATE;          /* '<S63>/Transfer Fcn2' */
  real_T TransferFcn_CSTATE;           /* '<S63>/Transfer Fcn' */
  real_T TransferFcn1_CSTATE;          /* '<S64>/Transfer Fcn1' */
  real_T TransferFcn2_CSTATE_i;        /* '<S64>/Transfer Fcn2' */
  real_T TransferFcn3_CSTATE_o;        /* '<S64>/Transfer Fcn3' */
  real_T TransferFcn4_CSTATE_j;        /* '<S64>/Transfer Fcn4' */
  real_T ubvbwb_CSTATE[3];             /* '<S7>/ub,vb,wb' */
  real_T xeyeze_CSTATE[3];             /* '<S7>/xe,ye,ze' */
} XDot_UAV_Dynamics_T;

/* State disabled  */
typedef struct {
  boolean_T q0q1q2q3_CSTATE[4];        /* '<S10>/q0 q1 q2 q3' */
  boolean_T pqr_CSTATE[3];             /* '<S7>/p,q,r ' */
  boolean_T TransferFcn4_CSTATE;       /* '<S63>/Transfer Fcn4' */
  boolean_T TransferFcn3_CSTATE;       /* '<S63>/Transfer Fcn3' */
  boolean_T TransferFcn2_CSTATE;       /* '<S63>/Transfer Fcn2' */
  boolean_T TransferFcn_CSTATE;        /* '<S63>/Transfer Fcn' */
  boolean_T TransferFcn1_CSTATE;       /* '<S64>/Transfer Fcn1' */
  boolean_T TransferFcn2_CSTATE_i;     /* '<S64>/Transfer Fcn2' */
  boolean_T TransferFcn3_CSTATE_o;     /* '<S64>/Transfer Fcn3' */
  boolean_T TransferFcn4_CSTATE_j;     /* '<S64>/Transfer Fcn4' */
  boolean_T ubvbwb_CSTATE[3];          /* '<S7>/ub,vb,wb' */
  boolean_T xeyeze_CSTATE[3];          /* '<S7>/xe,ye,ze' */
} XDis_UAV_Dynamics_T;

/* Invariant block signals (default storage) */
typedef struct {
  const real_T u2[3];                  /* '<S20>/1//2' */
  const real_T sincos_o1[3];           /* '<S20>/sincos' */
  const real_T sincos_o2[3];           /* '<S20>/sincos' */
  const real_T q0;                     /* '<S20>/q0' */
  const real_T q1;                     /* '<S20>/q1' */
  const real_T q2;                     /* '<S20>/q2' */
  const real_T q3;                     /* '<S20>/q3' */
  const real_T VectorConcatenate[18];  /* '<S12>/Vector Concatenate' */
  const real_T Selector[9];            /* '<S11>/Selector' */
  const real_T Selector1[9];           /* '<S11>/Selector1' */
  const real_T Selector2[9];           /* '<S11>/Selector2' */
} ConstB_UAV_Dynamics_T;

#ifndef ODE4_INTG
#define ODE4_INTG

/* ODE4 Integration Data */
typedef struct {
  real_T *y;                           /* output */
  real_T *f[4];                        /* derivatives */
} ODE4_IntgData;

#endif

/* Constant parameters (default storage) */
typedef struct {
  /* Expression: [21.5 1.16 43.1]
   * Referenced by: '<S3>/IMU1'
   */
  real_T IMU1_MagneticFieldNED[3];

  /* Pooled Parameter (Mixed Expressions)
   * Referenced by:
   *   '<S3>/IMU1'
   *   '<S7>/p,q,r '
   *   '<S7>/ub,vb,wb'
   *   '<S10>/Initial Euler Angles'
   *   '<S50>/Constant'
   *   '<S56>/Constant'
   */
  real_T pooled4[3];

  /* Pooled Parameter (Expression: fractalcoef().Denominator)
   * Referenced by: '<S3>/IMU1'
   */
  real_T pooled6[2];
} ConstP_UAV_Dynamics_T;

/* External inputs (root inport signals with default storage) */
typedef struct {
  real_T PWMInputs[4];                 /* '<Root>/PWM Inputs' */
} ExtU_UAV_Dynamics_T;

/* External outputs (root outports fed by signals with default storage) */
typedef struct {
  real_T Acc[3];                       /* '<Root>/Acc' */
  real_T Gyro[3];                      /* '<Root>/Gyro' */
  real_T Mag[3];                       /* '<Root>/Mag' */
  real_T Pressure;                     /* '<Root>/Pressure' */
  real_T LLA[3];                       /* '<Root>/LLA' */
  real_T Velocity[3];                  /* '<Root>/Velocity' */
  real_T GndSpeed;                     /* '<Root>/GndSpeed' */
  real_T Course;                       /* '<Root>/Course' */
  real_T quat_raw[4];                  /* '<Root>/quat_raw' */
  real_T posi_raw[3];                  /* '<Root>/posi_raw' */
} ExtY_UAV_Dynamics_T;

/* Real-time Model Data Structure */
struct tag_RTM_UAV_Dynamics_T {
  const char_T *errorStatus;
  RTWSolverInfo solverInfo;
  X_UAV_Dynamics_T *contStates;
  int_T *periodicContStateIndices;
  real_T *periodicContStateRanges;
  real_T *derivs;
  XDis_UAV_Dynamics_T *contStateDisabled;
  boolean_T zCCacheNeedsReset;
  boolean_T derivCacheNeedsReset;
  boolean_T CTOutputIncnstWithState;
  real_T odeY[21];
  real_T odeF[4][21];
  ODE4_IntgData intgData;

  /*
   * Sizes:
   * The following substructure contains sizes information
   * for many of the model attributes such as inputs, outputs,
   * dwork, sample times, etc.
   */
  struct {
    int_T numContStates;
    int_T numPeriodicContStates;
    int_T numSampTimes;
  } Sizes;

  /*
   * Timing:
   * The following substructure contains information regarding
   * the timing information for the model.
   */
  struct {
    uint32_T clockTick0;
    time_T stepSize0;
    uint32_T clockTick1;
    boolean_T firstInitCondFlag;
    time_T tStart;
    SimTimeStep simTimeStep;
    boolean_T stopRequestedFlag;
    time_T *t;
    time_T tArray[2];
  } Timing;
};

/* Block signals (default storage) */
extern B_UAV_Dynamics_T UAV_Dynamics_B;

/* Continuous states (default storage) */
extern X_UAV_Dynamics_T UAV_Dynamics_X;

/* Disabled states (default storage) */
extern XDis_UAV_Dynamics_T UAV_Dynamics_XDis;

/* Block states (default storage) */
extern DW_UAV_Dynamics_T UAV_Dynamics_DW;

/* External inputs (root inport signals with default storage) */
extern ExtU_UAV_Dynamics_T UAV_Dynamics_U;

/* External outputs (root outports fed by signals with default storage) */
extern ExtY_UAV_Dynamics_T UAV_Dynamics_Y;
extern const ConstB_UAV_Dynamics_T UAV_Dynamics_ConstB;/* constant block i/o */

/* Constant parameters (default storage) */
extern const ConstP_UAV_Dynamics_T UAV_Dynamics_ConstP;

/* Model entry point functions */
extern void UAV_Dynamics_initialize(void);
extern void UAV_Dynamics_step(void);
extern void UAV_Dynamics_terminate(void);

/* Real-time Model object */
extern RT_MODEL_UAV_Dynamics_T *const UAV_Dynamics_M;

/*-
 * These blocks were eliminated from the model due to optimizations:
 *
 * Block '<S5>/Add' : Unused code path elimination
 * Block '<S5>/Constant' : Unused code path elimination
 * Block '<S5>/Constant1' : Unused code path elimination
 * Block '<S5>/Data Type Conversion' : Unused code path elimination
 * Block '<S5>/Data Type Conversion1' : Unused code path elimination
 * Block '<S5>/Data Type Conversion3' : Unused code path elimination
 * Block '<S5>/Divide' : Unused code path elimination
 * Block '<S5>/Divide1' : Unused code path elimination
 * Block '<S5>/Gain' : Unused code path elimination
 * Block '<S6>/Product' : Unused code path elimination
 * Block '<S6>/Product3' : Unused code path elimination
 * Block '<S6>/a' : Unused code path elimination
 * Block '<S6>/gamma*R' : Unused code path elimination
 * Block '<S6>/rho0' : Unused code path elimination
 * Block '<S5>/Power' : Unused code path elimination
 * Block '<S5>/dynVisc Conversion' : Unused code path elimination
 * Block '<S5>/kineVisc Conversion' : Unused code path elimination
 * Block '<S16>/Unit Conversion' : Unused code path elimination
 * Block '<S58>/Compare' : Unused code path elimination
 * Block '<S58>/Constant' : Unused code path elimination
 * Block '<S54>/Gain' : Unused code path elimination
 * Block '<S59>/Dot Product' : Unused code path elimination
 * Block '<S59>/Sqrt' : Unused code path elimination
 * Block '<S5>/Cast To Double' : Eliminate redundant data type conversion
 * Block '<S5>/Data Type Conversion2' : Eliminate redundant data type conversion
 * Block '<S3>/Reshape3' : Reshape block reduction
 * Block '<S31>/Reshape (9) to [3x3] column-major' : Reshape block reduction
 * Block '<S21>/High Gain Quaternion Normalization' : Eliminated nontunable gain of 1
 * Block '<S44>/Reshape1' : Reshape block reduction
 * Block '<S44>/Reshape2' : Reshape block reduction
 * Block '<S45>/Reshape1' : Reshape block reduction
 * Block '<S45>/Reshape2' : Reshape block reduction
 * Block '<S11>/Reshape' : Reshape block reduction
 * Block '<S11>/Reshape1' : Reshape block reduction
 * Block '<S14>/Unit Conversion' : Eliminated nontunable gain of 1
 * Block '<S15>/Unit Conversion' : Eliminated nontunable gain of 1
 * Block '<S17>/Reshape1' : Reshape block reduction
 * Block '<S17>/Reshape2' : Reshape block reduction
 * Block '<S56>/Gain1' : Eliminated nontunable gain of 1
 */

/*-
 * The generated code includes comments that allow you to trace directly
 * back to the appropriate location in the model.  The basic format
 * is <system>/block_name, where system is the system number (uniquely
 * assigned by Simulink) and block_name is the name of the block.
 *
 * Use the MATLAB hilite_system command to trace the generated code back
 * to the model.  For example,
 *
 * hilite_system('<S3>')    - opens system 3
 * hilite_system('<S3>/Kp') - opens and selects block Kp which resides in S3
 *
 * Here is the system hierarchy for this model
 *
 * '<Root>' : 'UAV_Dynamics'
 * '<S1>'   : 'UAV_Dynamics/ '
 * '<S2>'   : 'UAV_Dynamics/GNSS//GPS Simulation'
 * '<S3>'   : 'UAV_Dynamics/IMU Simulation'
 * '<S4>'   : 'UAV_Dynamics/Quadcopter Model'
 * '<S5>'   : 'UAV_Dynamics/ /Lapse Rate Model'
 * '<S6>'   : 'UAV_Dynamics/ /Lapse Rate Model/Modelling'
 * '<S7>'   : 'UAV_Dynamics/Quadcopter Model/6DOF Rigid body dynamics '
 * '<S8>'   : 'UAV_Dynamics/Quadcopter Model/Create States Bus'
 * '<S9>'   : 'UAV_Dynamics/Quadcopter Model/Force and Moment Calculation'
 * '<S10>'  : 'UAV_Dynamics/Quadcopter Model/6DOF Rigid body dynamics /Calculate DCM & Euler Angles'
 * '<S11>'  : 'UAV_Dynamics/Quadcopter Model/6DOF Rigid body dynamics /Calculate omega_dot'
 * '<S12>'  : 'UAV_Dynamics/Quadcopter Model/6DOF Rigid body dynamics /Determine Force,  Mass & Inertia'
 * '<S13>'  : 'UAV_Dynamics/Quadcopter Model/6DOF Rigid body dynamics /Vbxw'
 * '<S14>'  : 'UAV_Dynamics/Quadcopter Model/6DOF Rigid body dynamics /Velocity Conversion'
 * '<S15>'  : 'UAV_Dynamics/Quadcopter Model/6DOF Rigid body dynamics /Velocity Conversion1'
 * '<S16>'  : 'UAV_Dynamics/Quadcopter Model/6DOF Rigid body dynamics /Velocity Conversion2'
 * '<S17>'  : 'UAV_Dynamics/Quadcopter Model/6DOF Rigid body dynamics /transform to Inertial axes '
 * '<S18>'  : 'UAV_Dynamics/Quadcopter Model/6DOF Rigid body dynamics /Calculate DCM & Euler Angles/Quaternions to  Direction Cosine Matrix'
 * '<S19>'  : 'UAV_Dynamics/Quadcopter Model/6DOF Rigid body dynamics /Calculate DCM & Euler Angles/Quaternions to Rotation Angles'
 * '<S20>'  : 'UAV_Dynamics/Quadcopter Model/6DOF Rigid body dynamics /Calculate DCM & Euler Angles/Rotation Angles to Quaternions'
 * '<S21>'  : 'UAV_Dynamics/Quadcopter Model/6DOF Rigid body dynamics /Calculate DCM & Euler Angles/qdot'
 * '<S22>'  : 'UAV_Dynamics/Quadcopter Model/6DOF Rigid body dynamics /Calculate DCM & Euler Angles/Quaternions to  Direction Cosine Matrix/A11'
 * '<S23>'  : 'UAV_Dynamics/Quadcopter Model/6DOF Rigid body dynamics /Calculate DCM & Euler Angles/Quaternions to  Direction Cosine Matrix/A12'
 * '<S24>'  : 'UAV_Dynamics/Quadcopter Model/6DOF Rigid body dynamics /Calculate DCM & Euler Angles/Quaternions to  Direction Cosine Matrix/A13'
 * '<S25>'  : 'UAV_Dynamics/Quadcopter Model/6DOF Rigid body dynamics /Calculate DCM & Euler Angles/Quaternions to  Direction Cosine Matrix/A21'
 * '<S26>'  : 'UAV_Dynamics/Quadcopter Model/6DOF Rigid body dynamics /Calculate DCM & Euler Angles/Quaternions to  Direction Cosine Matrix/A22'
 * '<S27>'  : 'UAV_Dynamics/Quadcopter Model/6DOF Rigid body dynamics /Calculate DCM & Euler Angles/Quaternions to  Direction Cosine Matrix/A23'
 * '<S28>'  : 'UAV_Dynamics/Quadcopter Model/6DOF Rigid body dynamics /Calculate DCM & Euler Angles/Quaternions to  Direction Cosine Matrix/A31'
 * '<S29>'  : 'UAV_Dynamics/Quadcopter Model/6DOF Rigid body dynamics /Calculate DCM & Euler Angles/Quaternions to  Direction Cosine Matrix/A32'
 * '<S30>'  : 'UAV_Dynamics/Quadcopter Model/6DOF Rigid body dynamics /Calculate DCM & Euler Angles/Quaternions to  Direction Cosine Matrix/A33'
 * '<S31>'  : 'UAV_Dynamics/Quadcopter Model/6DOF Rigid body dynamics /Calculate DCM & Euler Angles/Quaternions to  Direction Cosine Matrix/Create 3x3 Matrix'
 * '<S32>'  : 'UAV_Dynamics/Quadcopter Model/6DOF Rigid body dynamics /Calculate DCM & Euler Angles/Quaternions to  Direction Cosine Matrix/Quaternion Normalize'
 * '<S33>'  : 'UAV_Dynamics/Quadcopter Model/6DOF Rigid body dynamics /Calculate DCM & Euler Angles/Quaternions to  Direction Cosine Matrix/Quaternion Normalize/Quaternion Modulus'
 * '<S34>'  : 'UAV_Dynamics/Quadcopter Model/6DOF Rigid body dynamics /Calculate DCM & Euler Angles/Quaternions to  Direction Cosine Matrix/Quaternion Normalize/Quaternion Modulus/Quaternion Norm'
 * '<S35>'  : 'UAV_Dynamics/Quadcopter Model/6DOF Rigid body dynamics /Calculate DCM & Euler Angles/Quaternions to Rotation Angles/Angle Calculation'
 * '<S36>'  : 'UAV_Dynamics/Quadcopter Model/6DOF Rigid body dynamics /Calculate DCM & Euler Angles/Quaternions to Rotation Angles/Quaternion Normalize'
 * '<S37>'  : 'UAV_Dynamics/Quadcopter Model/6DOF Rigid body dynamics /Calculate DCM & Euler Angles/Quaternions to Rotation Angles/Angle Calculation/Protect asincos input'
 * '<S38>'  : 'UAV_Dynamics/Quadcopter Model/6DOF Rigid body dynamics /Calculate DCM & Euler Angles/Quaternions to Rotation Angles/Angle Calculation/Protect asincos input/If Action Subsystem'
 * '<S39>'  : 'UAV_Dynamics/Quadcopter Model/6DOF Rigid body dynamics /Calculate DCM & Euler Angles/Quaternions to Rotation Angles/Angle Calculation/Protect asincos input/If Action Subsystem1'
 * '<S40>'  : 'UAV_Dynamics/Quadcopter Model/6DOF Rigid body dynamics /Calculate DCM & Euler Angles/Quaternions to Rotation Angles/Angle Calculation/Protect asincos input/If Action Subsystem2'
 * '<S41>'  : 'UAV_Dynamics/Quadcopter Model/6DOF Rigid body dynamics /Calculate DCM & Euler Angles/Quaternions to Rotation Angles/Quaternion Normalize/Quaternion Modulus'
 * '<S42>'  : 'UAV_Dynamics/Quadcopter Model/6DOF Rigid body dynamics /Calculate DCM & Euler Angles/Quaternions to Rotation Angles/Quaternion Normalize/Quaternion Modulus/Quaternion Norm'
 * '<S43>'  : 'UAV_Dynamics/Quadcopter Model/6DOF Rigid body dynamics /Calculate omega_dot/3x3 Cross Product'
 * '<S44>'  : 'UAV_Dynamics/Quadcopter Model/6DOF Rigid body dynamics /Calculate omega_dot/I x w'
 * '<S45>'  : 'UAV_Dynamics/Quadcopter Model/6DOF Rigid body dynamics /Calculate omega_dot/I x w1'
 * '<S46>'  : 'UAV_Dynamics/Quadcopter Model/6DOF Rigid body dynamics /Calculate omega_dot/3x3 Cross Product/Subsystem'
 * '<S47>'  : 'UAV_Dynamics/Quadcopter Model/6DOF Rigid body dynamics /Calculate omega_dot/3x3 Cross Product/Subsystem1'
 * '<S48>'  : 'UAV_Dynamics/Quadcopter Model/6DOF Rigid body dynamics /Vbxw/Subsystem'
 * '<S49>'  : 'UAV_Dynamics/Quadcopter Model/6DOF Rigid body dynamics /Vbxw/Subsystem1'
 * '<S50>'  : 'UAV_Dynamics/Quadcopter Model/Force and Moment Calculation/Aerodynamic drag'
 * '<S51>'  : 'UAV_Dynamics/Quadcopter Model/Force and Moment Calculation/Gravity'
 * '<S52>'  : 'UAV_Dynamics/Quadcopter Model/Force and Moment Calculation/Ground Model'
 * '<S53>'  : 'UAV_Dynamics/Quadcopter Model/Force and Moment Calculation/Rotor Model'
 * '<S54>'  : 'UAV_Dynamics/Quadcopter Model/Force and Moment Calculation/Ground Model/Crash Detector'
 * '<S55>'  : 'UAV_Dynamics/Quadcopter Model/Force and Moment Calculation/Ground Model/Friction Force'
 * '<S56>'  : 'UAV_Dynamics/Quadcopter Model/Force and Moment Calculation/Ground Model/Ground Moment Model'
 * '<S57>'  : 'UAV_Dynamics/Quadcopter Model/Force and Moment Calculation/Ground Model/Normal Force'
 * '<S58>'  : 'UAV_Dynamics/Quadcopter Model/Force and Moment Calculation/Ground Model/Crash Detector/Compare To Constant'
 * '<S59>'  : 'UAV_Dynamics/Quadcopter Model/Force and Moment Calculation/Ground Model/Crash Detector/norm1'
 * '<S60>'  : 'UAV_Dynamics/Quadcopter Model/Force and Moment Calculation/Ground Model/Friction Force/Soft Coulomb Friction'
 * '<S61>'  : 'UAV_Dynamics/Quadcopter Model/Force and Moment Calculation/Ground Model/Ground Moment Model/Soft Coulomb Friction'
 * '<S62>'  : 'UAV_Dynamics/Quadcopter Model/Force and Moment Calculation/Rotor Model/MATLAB Function'
 * '<S63>'  : 'UAV_Dynamics/Quadcopter Model/Force and Moment Calculation/Rotor Model/Thrust model'
 * '<S64>'  : 'UAV_Dynamics/Quadcopter Model/Force and Moment Calculation/Rotor Model/Torque model'
 */
#endif                                 /* RTW_HEADER_UAV_Dynamics_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
