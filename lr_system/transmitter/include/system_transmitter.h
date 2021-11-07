//
// File: system_transmitter.h
//
// Code generated for Simulink model 'system_transmitter'.
//
// Model version                  : 1.38
// Simulink Coder version         : 9.3 (R2020a) 18-Nov-2019
// C/C++ source code generated on : Sun Nov  7 12:19:36 2021
//
// Target selection: ert.tlc
// Embedded hardware selection: 32-bit Generic
// Code generation objectives: Unspecified
// Validation result: Not run
//
#ifndef RTW_HEADER_system_transmitter_h_
#define RTW_HEADER_system_transmitter_h_
#include <cmath>
#include "rtw_modelmap.h"
#include "rtwtypes.h"
#include "rtw_continuous.h"
#include "rtw_solver.h"
#include "system_transmitter_types.h"
#include "rtGetInf.h"
#include "rt_nonfinite.h"

// Macros for accessing real-time model data structure
#ifndef rtmGetDataMapInfo
# define rtmGetDataMapInfo(rtm)        ((rtm)->DataMapInfo)
#endif

#ifndef rtmSetDataMapInfo
# define rtmSetDataMapInfo(rtm, val)   ((rtm)->DataMapInfo = (val))
#endif

#ifndef rtmGetErrorStatus
# define rtmGetErrorStatus(rtm)        ((rtm)->errorStatus)
#endif

#ifndef rtmSetErrorStatus
# define rtmSetErrorStatus(rtm, val)   ((rtm)->errorStatus = (val))
#endif

#ifndef rtmGetStopRequested
# define rtmGetStopRequested(rtm)      ((rtm)->Timing.stopRequestedFlag)
#endif

#ifndef rtmSetStopRequested
# define rtmSetStopRequested(rtm, val) ((rtm)->Timing.stopRequestedFlag = (val))
#endif

#ifndef rtmGetStopRequestedPtr
# define rtmGetStopRequestedPtr(rtm)   (&((rtm)->Timing.stopRequestedFlag))
#endif

#ifndef rtmGetT
# define rtmGetT(rtm)                  (rtmGetTPtr((rtm))[0])
#endif

#ifndef rtmGetTPtr
# define rtmGetTPtr(rtm)               ((rtm)->Timing.t)
#endif

// Block signals (default storage)
typedef struct {
  real_T Integrator;                   // '<Root>/Integrator'
  real_T Integrator1;                  // '<Root>/Integrator1'
  real_T Integrator2;                  // '<Root>/Integrator2'
  real_T Integrator3;                  // '<Root>/Integrator3'
  real_T Integrator4;                  // '<Root>/Integrator4'
  real_T Integrator5;                  // '<Root>/Integrator5'
  real_T U1;                           // '<Root>/U1 '
  real_T Sum;                          // '<Root>/Sum'
  real_T u2;                           // '<Root>/u2'
  real_T Fcn;                          // '<Root>/Fcn'
  real_T Fcn1;                         // '<Root>/Fcn1'
  real_T Fcn12;                        // '<Root>/Fcn12'
  real_T Fcn2;                         // '<Root>/Fcn2'
  real_T Fcn23;                        // '<Root>/Fcn23'
  real_T Fcn3;                         // '<Root>/Fcn3'
  real_T Fcn4;                         // '<Root>/Fcn4'
  real_T Fcn5;                         // '<Root>/Fcn5'
} B_system_transmitter_T;

// Continuous states (default storage)
typedef struct {
  real_T Integrator_CSTATE;            // '<Root>/Integrator'
  real_T Integrator1_CSTATE;           // '<Root>/Integrator1'
  real_T Integrator2_CSTATE;           // '<Root>/Integrator2'
  real_T Integrator3_CSTATE;           // '<Root>/Integrator3'
  real_T Integrator4_CSTATE;           // '<Root>/Integrator4'
  real_T Integrator5_CSTATE;           // '<Root>/Integrator5'
} X_system_transmitter_T;

// State derivatives (default storage)
typedef struct {
  real_T Integrator_CSTATE;            // '<Root>/Integrator'
  real_T Integrator1_CSTATE;           // '<Root>/Integrator1'
  real_T Integrator2_CSTATE;           // '<Root>/Integrator2'
  real_T Integrator3_CSTATE;           // '<Root>/Integrator3'
  real_T Integrator4_CSTATE;           // '<Root>/Integrator4'
  real_T Integrator5_CSTATE;           // '<Root>/Integrator5'
} XDot_system_transmitter_T;

// State disabled
typedef struct {
  boolean_T Integrator_CSTATE;         // '<Root>/Integrator'
  boolean_T Integrator1_CSTATE;        // '<Root>/Integrator1'
  boolean_T Integrator2_CSTATE;        // '<Root>/Integrator2'
  boolean_T Integrator3_CSTATE;        // '<Root>/Integrator3'
  boolean_T Integrator4_CSTATE;        // '<Root>/Integrator4'
  boolean_T Integrator5_CSTATE;        // '<Root>/Integrator5'
} XDis_system_transmitter_T;

#ifndef ODE1_INTG
#define ODE1_INTG

// ODE1 Integration Data
typedef struct {
  real_T *f[1];                        // derivatives
} ODE1_IntgData;

#endif

// External outputs (root outports fed by signals with default storage)
typedef struct {
  real_T xl_out;                       // '<Root>/xl_out'
  real_T yl_out;                       // '<Root>/yl_out'
  real_T zl_out;                       // '<Root>/zl_out'
  real_T xr_out;                       // '<Root>/xr_out'
  real_T yr_out;                       // '<Root>/yr_out'
  real_T zr_out;                       // '<Root>/zr_out'
} ExtY_system_transmitter_T;

// Real-time Model Data Structure
struct tag_RTM_system_transmitter_T {
  const char_T *errorStatus;
  RTWSolverInfo solverInfo;
  X_system_transmitter_T *contStates;
  int_T *periodicContStateIndices;
  real_T *periodicContStateRanges;
  real_T *derivs;
  boolean_T *contStateDisabled;
  boolean_T zCCacheNeedsReset;
  boolean_T derivCacheNeedsReset;
  boolean_T CTOutputIncnstWithState;
  real_T odeF[1][6];
  ODE1_IntgData intgData;

  //
  //  DataMapInfo:
  //  The following substructure contains information regarding
  //  structures generated in the model's C API.

  struct {
    rtwCAPI_ModelMappingInfo mmi;
  } DataMapInfo;

  //
  //  Sizes:
  //  The following substructure contains sizes information
  //  for many of the model attributes such as inputs, outputs,
  //  dwork, sample times, etc.

  struct {
    int_T numContStates;
    int_T numPeriodicContStates;
    int_T numSampTimes;
  } Sizes;

  //
  //  Timing:
  //  The following substructure contains information regarding
  //  the timing information for the model.

  struct {
    uint32_T clockTick0;
    uint32_T clockTickH0;
    time_T stepSize0;
    uint32_T clockTick1;
    uint32_T clockTickH1;
    SimTimeStep simTimeStep;
    boolean_T stopRequestedFlag;
    time_T *t;
    time_T tArray[2];
  } Timing;
};

// Block signals (default storage)
#ifdef __cplusplus

extern "C" {

#endif

  extern B_system_transmitter_T system_transmitter_B;

#ifdef __cplusplus

}
#endif

// Continuous states (default storage)
extern X_system_transmitter_T system_transmitter_X;

#ifdef __cplusplus

extern "C" {

#endif

  // External outputs (root outports fed by signals with default storage)
  extern ExtY_system_transmitter_T system_transmitter_Y;

#ifdef __cplusplus

}
#endif

#ifdef __cplusplus

extern "C" {

#endif

  // Model entry point functions
  extern void system_transmitter_initialize(void);
  extern void system_transmitter_step(void);
  extern void system_transmitter_terminate(void);

#ifdef __cplusplus

}
#endif

// Function to get C API Model Mapping Static Info
extern const rtwCAPI_ModelMappingStaticInfo*
  system_transmitter_GetCAPIStaticMap(void);

// Real-time Model object
#ifdef __cplusplus

extern "C" {

#endif

  extern RT_MODEL_system_transmitter_T *const system_transmitter_M;

#ifdef __cplusplus

}
#endif

//-
//  The generated code includes comments that allow you to trace directly
//  back to the appropriate location in the model.  The basic format
//  is <system>/block_name, where system is the system number (uniquely
//  assigned by Simulink) and block_name is the name of the block.
//
//  Use the MATLAB hilite_system command to trace the generated code back
//  to the model.  For example,
//
//  hilite_system('<S3>')    - opens system 3
//  hilite_system('<S3>/Kp') - opens and selects block Kp which resides in S3
//
//  Here is the system hierarchy for this model
//
//  '<Root>' : 'system_transmitter'

#endif                                 // RTW_HEADER_system_transmitter_h_

//
// File trailer for generated code.
//
// [EOF]
//
