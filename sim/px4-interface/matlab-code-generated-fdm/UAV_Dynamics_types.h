/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: UAV_Dynamics_types.h
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

#ifndef RTW_HEADER_UAV_Dynamics_types_h_
#define RTW_HEADER_UAV_Dynamics_types_h_
#include "rtwtypes.h"
#ifndef struct_tag_2PsGMppoK4e2vdwpogf6iH
#define struct_tag_2PsGMppoK4e2vdwpogf6iH

struct tag_2PsGMppoK4e2vdwpogf6iH
{
  int32_T isInitialized;
};

#endif                                 /* struct_tag_2PsGMppoK4e2vdwpogf6iH */

#ifndef typedef_robotics_slcore_internal_bloc_T
#define typedef_robotics_slcore_internal_bloc_T

typedef struct tag_2PsGMppoK4e2vdwpogf6iH robotics_slcore_internal_bloc_T;

#endif                             /* typedef_robotics_slcore_internal_bloc_T */

#ifndef struct_tag_2SMHDelJvNeqNrZ7Atn6QB
#define struct_tag_2SMHDelJvNeqNrZ7Atn6QB

struct tag_2SMHDelJvNeqNrZ7Atn6QB
{
  uint32_T Seed;
  uint32_T State[625];
};

#endif                                 /* struct_tag_2SMHDelJvNeqNrZ7Atn6QB */

#ifndef typedef_c_coder_internal_mt19937ar_UA_T
#define typedef_c_coder_internal_mt19937ar_UA_T

typedef struct tag_2SMHDelJvNeqNrZ7Atn6QB c_coder_internal_mt19937ar_UA_T;

#endif                             /* typedef_c_coder_internal_mt19937ar_UA_T */

#ifndef struct_tag_sI9OZ8YWn5qr2iby6yfJzBB
#define struct_tag_sI9OZ8YWn5qr2iby6yfJzBB

struct tag_sI9OZ8YWn5qr2iby6yfJzBB
{
  real_T Numerator;
  real_T Denominator[2];
};

#endif                                 /* struct_tag_sI9OZ8YWn5qr2iby6yfJzBB */

#ifndef typedef_sI9OZ8YWn5qr2iby6yfJzBB_UAV_D_T
#define typedef_sI9OZ8YWn5qr2iby6yfJzBB_UAV_D_T

typedef struct tag_sI9OZ8YWn5qr2iby6yfJzBB sI9OZ8YWn5qr2iby6yfJzBB_UAV_D_T;

#endif                             /* typedef_sI9OZ8YWn5qr2iby6yfJzBB_UAV_D_T */

#ifndef struct_tag_EDDefAxlN8L7dR1ZfMmDTH
#define struct_tag_EDDefAxlN8L7dR1ZfMmDTH

struct tag_EDDefAxlN8L7dR1ZfMmDTH
{
  char_T Value[12];
};

#endif                                 /* struct_tag_EDDefAxlN8L7dR1ZfMmDTH */

#ifndef typedef_rtString_UAV_Dynamics_T
#define typedef_rtString_UAV_Dynamics_T

typedef struct tag_EDDefAxlN8L7dR1ZfMmDTH rtString_UAV_Dynamics_T;

#endif                                 /* typedef_rtString_UAV_Dynamics_T */

#ifndef struct_tag_i6CsTCVxB9hTYdRcCjoywF
#define struct_tag_i6CsTCVxB9hTYdRcCjoywF

struct tag_i6CsTCVxB9hTYdRcCjoywF
{
  boolean_T tunablePropertyChanged[12];
  int32_T isInitialized;
  boolean_T TunablePropsChanged;
  real_T MeasurementRange;
  real_T Resolution;
  real_T ConstantBias[3];
  real_T AxesMisalignment[9];
  real_T NoiseDensity[3];
  real_T BiasInstability[3];
  real_T RandomWalk[3];
  sI9OZ8YWn5qr2iby6yfJzBB_UAV_D_T BiasInstabilityCoefficients;
  rtString_UAV_Dynamics_T NoiseType;
  real_T TemperatureBias[3];
  real_T TemperatureScaleFactor[3];
  real_T Temperature;
  real_T pBandwidth;
  real_T pCorrelationTime;
  real_T pBiasInstFilterNum;
  real_T pBiasInstFilterDen[2];
  real_T pBiasInstFilterStates[3];
  real_T pStdDevBiasInst[3];
  real_T pStdDevWhiteNoise[3];
  real_T pRandWalkFilterStates[3];
  real_T pStdDevRandWalk[3];
  real_T pGain[9];
};

#endif                                 /* struct_tag_i6CsTCVxB9hTYdRcCjoywF */

#ifndef typedef_g_fusion_internal_Acceleromet_T
#define typedef_g_fusion_internal_Acceleromet_T

typedef struct tag_i6CsTCVxB9hTYdRcCjoywF g_fusion_internal_Acceleromet_T;

#endif                             /* typedef_g_fusion_internal_Acceleromet_T */

#ifndef struct_tag_Mj47eX45769jebuqv2OytB
#define struct_tag_Mj47eX45769jebuqv2OytB

struct tag_Mj47eX45769jebuqv2OytB
{
  boolean_T tunablePropertyChanged[13];
  int32_T isInitialized;
  boolean_T TunablePropsChanged;
  real_T MeasurementRange;
  real_T Resolution;
  real_T ConstantBias[3];
  real_T AxesMisalignment[9];
  real_T NoiseDensity[3];
  real_T BiasInstability[3];
  real_T RandomWalk[3];
  sI9OZ8YWn5qr2iby6yfJzBB_UAV_D_T BiasInstabilityCoefficients;
  rtString_UAV_Dynamics_T NoiseType;
  real_T TemperatureBias[3];
  real_T TemperatureScaleFactor[3];
  real_T Temperature;
  real_T pBandwidth;
  real_T pCorrelationTime;
  real_T pBiasInstFilterNum;
  real_T pBiasInstFilterDen[2];
  real_T pBiasInstFilterStates[3];
  real_T pStdDevBiasInst[3];
  real_T pStdDevWhiteNoise[3];
  real_T pRandWalkFilterStates[3];
  real_T pStdDevRandWalk[3];
  real_T pGain[9];
  real_T AccelerationBias[3];
  real_T pAcceleration[3];
};

#endif                                 /* struct_tag_Mj47eX45769jebuqv2OytB */

#ifndef typedef_h_fusion_internal_GyroscopeSi_T
#define typedef_h_fusion_internal_GyroscopeSi_T

typedef struct tag_Mj47eX45769jebuqv2OytB h_fusion_internal_GyroscopeSi_T;

#endif                             /* typedef_h_fusion_internal_GyroscopeSi_T */

#ifndef struct_tag_dGsU1cW6xvZMdrkopsDHLC
#define struct_tag_dGsU1cW6xvZMdrkopsDHLC

struct tag_dGsU1cW6xvZMdrkopsDHLC
{
  boolean_T tunablePropertyChanged[12];
  int32_T isInitialized;
  boolean_T TunablePropsChanged;
  real_T MeasurementRange;
  real_T Resolution;
  real_T ConstantBias[3];
  real_T AxesMisalignment[9];
  real_T NoiseDensity[3];
  real_T BiasInstability[3];
  real_T RandomWalk[3];
  sI9OZ8YWn5qr2iby6yfJzBB_UAV_D_T BiasInstabilityCoefficients;
  rtString_UAV_Dynamics_T NoiseType;
  real_T TemperatureBias[3];
  real_T TemperatureScaleFactor[3];
  real_T Temperature;
  real_T pBandwidth;
  real_T pCorrelationTime;
  real_T pBiasInstFilterNum;
  real_T pBiasInstFilterDen[2];
  real_T pBiasInstFilterStates[3];
  real_T pStdDevBiasInst[3];
  real_T pStdDevWhiteNoise[3];
  real_T pRandWalkFilterStates[3];
  real_T pStdDevRandWalk[3];
  real_T pGain[9];
};

#endif                                 /* struct_tag_dGsU1cW6xvZMdrkopsDHLC */

#ifndef typedef_i_fusion_internal_Magnetomete_T
#define typedef_i_fusion_internal_Magnetomete_T

typedef struct tag_dGsU1cW6xvZMdrkopsDHLC i_fusion_internal_Magnetomete_T;

#endif                             /* typedef_i_fusion_internal_Magnetomete_T */

#ifndef struct_tag_rdZ8Dia9eKS4x42ynVbOyF
#define struct_tag_rdZ8Dia9eKS4x42ynVbOyF

struct tag_rdZ8Dia9eKS4x42ynVbOyF
{
  boolean_T tunablePropertyChanged[38];
  int32_T isInitialized;
  boolean_T TunablePropsChanged;
  real_T Temperature;
  uint32_T pStreamState[625];
  g_fusion_internal_Acceleromet_T *pAccel;
  h_fusion_internal_GyroscopeSi_T *pGyro;
  i_fusion_internal_Magnetomete_T *pMag;
  real_T MagneticFieldNED[3];
  real_T MagneticField[3];
  real_T AccelParamsMeasurementRange;
  real_T AccelParamsResolution;
  real_T AccelParamsConstantBias[3];
  real_T AccelParamsAxesMisalignment[3];
  real_T AccelParamsNoiseDensity;
  real_T AccelParamsBiasInstability[3];
  real_T AccelParamsBiasInstabilityNumerator;
  real_T AccelParamsBiasInstabilityDenominator[2];
  real_T AccelParamsRandomWalk[3];
  real_T AccelParamsTemperatureBias[3];
  real_T AccelParamsTemperatureScaleFactor[3];
  real_T GyroParamsMeasurementRange;
  real_T GyroParamsResolution;
  real_T GyroParamsConstantBias[3];
  real_T GyroParamsAxesMisalignment[3];
  real_T GyroParamsNoiseDensity;
  real_T GyroParamsBiasInstability[3];
  real_T GyroParamsBiasInstabilityNumerator;
  real_T GyroParamsBiasInstabilityDenominator[2];
  real_T GyroParamsRandomWalk[3];
  real_T GyroParamsTemperatureBias[3];
  real_T GyroParamsTemperatureScaleFactor[3];
  real_T GyroParamsAccelerationBias;
  real_T MagParamsMeasurementRange;
  real_T MagParamsResolution;
  real_T MagParamsConstantBias[3];
  real_T MagParamsAxesMisalignment[3];
  real_T MagParamsNoiseDensity;
  real_T MagParamsBiasInstability[3];
  real_T MagParamsBiasInstabilityNumerator;
  real_T MagParamsBiasInstabilityDenominator[2];
  real_T MagParamsRandomWalk[3];
  real_T MagParamsTemperatureBias[3];
  real_T MagParamsTemperatureScaleFactor[3];
  i_fusion_internal_Magnetomete_T _pobj0;
  h_fusion_internal_GyroscopeSi_T _pobj1;
  g_fusion_internal_Acceleromet_T _pobj2;
};

#endif                                 /* struct_tag_rdZ8Dia9eKS4x42ynVbOyF */

#ifndef typedef_fusion_simulink_imuSensor_UAV_T
#define typedef_fusion_simulink_imuSensor_UAV_T

typedef struct tag_rdZ8Dia9eKS4x42ynVbOyF fusion_simulink_imuSensor_UAV_T;

#endif                             /* typedef_fusion_simulink_imuSensor_UAV_T */

#ifndef typedef_coder_internal_RngNt_UAV_Dyna_T
#define typedef_coder_internal_RngNt_UAV_Dyna_T

typedef int32_T coder_internal_RngNt_UAV_Dyna_T;

#endif                             /* typedef_coder_internal_RngNt_UAV_Dyna_T */

#ifndef coder_internal_RngNt_constants
#define coder_internal_RngNt_constants

/* enum coder_internal_RngNt */
#define ziggurat                       (0)
#define polar                          (1)
#define inversion                      (2)
#endif                                 /* coder_internal_RngNt_constants */

#ifndef struct_tag_xA3DogVhhJHOspRusE5FCF
#define struct_tag_xA3DogVhhJHOspRusE5FCF

struct tag_xA3DogVhhJHOspRusE5FCF
{
  coder_internal_RngNt_UAV_Dyna_T NtMethod;
  real_T SavedPolarValue;
  boolean_T HaveSavedPolarValue;
  c_coder_internal_mt19937ar_UA_T *Generator;
  c_coder_internal_mt19937ar_UA_T MtGenerator;
};

#endif                                 /* struct_tag_xA3DogVhhJHOspRusE5FCF */

#ifndef typedef_b_coder_internal_RandStream_U_T
#define typedef_b_coder_internal_RandStream_U_T

typedef struct tag_xA3DogVhhJHOspRusE5FCF b_coder_internal_RandStream_U_T;

#endif                             /* typedef_b_coder_internal_RandStream_U_T */

#ifndef struct_tag_ZvCspuecuRVgwkhFU1vlJF
#define struct_tag_ZvCspuecuRVgwkhFU1vlJF

struct tag_ZvCspuecuRVgwkhFU1vlJF
{
  boolean_T tunablePropertyChanged[4];
  int32_T isInitialized;
  boolean_T TunablePropsChanged;
  real_T HorizontalPositionAccuracy;
  real_T VerticalPositionAccuracy;
  real_T VelocityAccuracy;
  real_T DecayFactor;
  b_coder_internal_RandStream_U_T *pStream;
  real_T pPositionErrorFilterNum;
  real_T pPositionErrorFilterDen[2];
  real_T pPositionErrorFilterStates[3];
  real_T pSigmaScaled[3];
  b_coder_internal_RandStream_U_T _pobj0;
};

#endif                                 /* struct_tag_ZvCspuecuRVgwkhFU1vlJF */

#ifndef typedef_fusion_internal_simulink_gpsS_T
#define typedef_fusion_internal_simulink_gpsS_T

typedef struct tag_ZvCspuecuRVgwkhFU1vlJF fusion_internal_simulink_gpsS_T;

#endif                             /* typedef_fusion_internal_simulink_gpsS_T */

/* Forward declaration for rtModel */
typedef struct tag_RTM_UAV_Dynamics_T RT_MODEL_UAV_Dynamics_T;

#endif                                 /* RTW_HEADER_UAV_Dynamics_types_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
