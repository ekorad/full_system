//
// File: system_transmitter_private.h
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
#ifndef RTW_HEADER_system_transmitter_private_h_
#define RTW_HEADER_system_transmitter_private_h_
#include "rtwtypes.h"
#include "builtin_typeid_types.h"

// Private macros used by the generated code to access rtModel
#ifndef rtmIsMajorTimeStep
# define rtmIsMajorTimeStep(rtm)       (((rtm)->Timing.simTimeStep) == MAJOR_TIME_STEP)
#endif

#ifndef rtmIsMinorTimeStep
# define rtmIsMinorTimeStep(rtm)       (((rtm)->Timing.simTimeStep) == MINOR_TIME_STEP)
#endif

#ifndef rtmSetTPtr
# define rtmSetTPtr(rtm, val)          ((rtm)->Timing.t = (val))
#endif

// private model entry point functions
extern void system_transmitter_derivatives(void);

#endif                              // RTW_HEADER_system_transmitter_private_h_

//
// File trailer for generated code.
//
// [EOF]
//
