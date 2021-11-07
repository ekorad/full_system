//
// File: system_transmitter.cpp
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
#include "system_transmitter_capi.h"
#include "system_transmitter.h"
#include "system_transmitter_private.h"

// Block signals (default storage)
B_system_transmitter_T system_transmitter_B;

// Continuous states
X_system_transmitter_T system_transmitter_X;

// External outputs (root outports fed by signals with default storage)
ExtY_system_transmitter_T system_transmitter_Y;

// Real-time model
RT_MODEL_system_transmitter_T system_transmitter_M_ =
  RT_MODEL_system_transmitter_T();
RT_MODEL_system_transmitter_T *const system_transmitter_M =
  &system_transmitter_M_;

//
// This function updates continuous states using the ODE1 fixed-step
// solver algorithm
//
static void rt_ertODEUpdateContinuousStates(RTWSolverInfo *si )
{
  time_T tnew = rtsiGetSolverStopTime(si);
  time_T h = rtsiGetStepSize(si);
  real_T *x = rtsiGetContStates(si);
  ODE1_IntgData *id = static_cast<ODE1_IntgData *>(rtsiGetSolverData(si));
  real_T *f0 = id->f[0];
  int_T i;
  int_T nXc = 6;
  rtsiSetSimTimeStep(si,MINOR_TIME_STEP);
  rtsiSetdX(si, f0);
  system_transmitter_derivatives();
  rtsiSetT(si, tnew);
  for (i = 0; i < nXc; ++i) {
    x[i] += h * f0[i];
  }

  rtsiSetSimTimeStep(si,MAJOR_TIME_STEP);
}

// Model step function
void system_transmitter_step(void)
{
  real_T tmp;
  if (rtmIsMajorTimeStep(system_transmitter_M)) {
    // set solver stop time
    if (!(system_transmitter_M->Timing.clockTick0+1)) {
      rtsiSetSolverStopTime(&system_transmitter_M->solverInfo,
                            ((system_transmitter_M->Timing.clockTickH0 + 1) *
        system_transmitter_M->Timing.stepSize0 * 4294967296.0));
    } else {
      rtsiSetSolverStopTime(&system_transmitter_M->solverInfo,
                            ((system_transmitter_M->Timing.clockTick0 + 1) *
        system_transmitter_M->Timing.stepSize0 +
        system_transmitter_M->Timing.clockTickH0 *
        system_transmitter_M->Timing.stepSize0 * 4294967296.0));
    }
  }                                    // end MajorTimeStep

  // Update absolute time of base rate at minor time step
  if (rtmIsMinorTimeStep(system_transmitter_M)) {
    system_transmitter_M->Timing.t[0] = rtsiGetT
      (&system_transmitter_M->solverInfo);
  }

  // Integrator: '<Root>/Integrator'
  system_transmitter_B.Integrator = system_transmitter_X.Integrator_CSTATE;

  // Integrator: '<Root>/Integrator1'
  system_transmitter_B.Integrator1 = system_transmitter_X.Integrator1_CSTATE;
  if (rtmIsMajorTimeStep(system_transmitter_M)) {
    // Outport: '<Root>/xl_out' incorporates:
    //   ZeroOrderHold: '<Root>/Zero-Order Hold'

    system_transmitter_Y.xl_out = system_transmitter_B.Integrator;
  }

  // Integrator: '<Root>/Integrator2'
  system_transmitter_B.Integrator2 = system_transmitter_X.Integrator2_CSTATE;
  if (rtmIsMajorTimeStep(system_transmitter_M)) {
    // Outport: '<Root>/yl_out' incorporates:
    //   ZeroOrderHold: '<Root>/Zero-Order Hold1'

    system_transmitter_Y.yl_out = system_transmitter_B.Integrator1;
  }

  // Integrator: '<Root>/Integrator3'
  system_transmitter_B.Integrator3 = system_transmitter_X.Integrator3_CSTATE;
  if (rtmIsMajorTimeStep(system_transmitter_M)) {
    // Outport: '<Root>/zl_out' incorporates:
    //   ZeroOrderHold: '<Root>/Zero-Order Hold2'

    system_transmitter_Y.zl_out = system_transmitter_B.Integrator2;
  }

  // Integrator: '<Root>/Integrator4'
  system_transmitter_B.Integrator4 = system_transmitter_X.Integrator4_CSTATE;
  if (rtmIsMajorTimeStep(system_transmitter_M)) {
    // Outport: '<Root>/xr_out' incorporates:
    //   ZeroOrderHold: '<Root>/Zero-Order Hold3'

    system_transmitter_Y.xr_out = system_transmitter_B.Integrator3;
  }

  // Integrator: '<Root>/Integrator5'
  system_transmitter_B.Integrator5 = system_transmitter_X.Integrator5_CSTATE;
  if (rtmIsMajorTimeStep(system_transmitter_M)) {
    // Outport: '<Root>/yr_out' incorporates:
    //   ZeroOrderHold: '<Root>/Zero-Order Hold4'

    system_transmitter_Y.yr_out = system_transmitter_B.Integrator4;

    // Outport: '<Root>/zr_out' incorporates:
    //   ZeroOrderHold: '<Root>/Zero-Order Hold5'

    system_transmitter_Y.zr_out = system_transmitter_B.Integrator5;
  }

  // SignalGenerator: '<Root>/U1 '
  tmp = 6.2831853071795862 * system_transmitter_M->Timing.t[0];
  system_transmitter_B.U1 = std::sin(1.0 * tmp) * 1.0;

  // Sum: '<Root>/Sum' incorporates:
  //   Constant: '<Root>/Constant'

  system_transmitter_B.Sum = 5.0 + system_transmitter_B.U1;

  // SignalGenerator: '<Root>/u2'
  tmp = 6.2831853071795862 * system_transmitter_M->Timing.t[0];
  system_transmitter_B.u2 = std::sin(0.9 * tmp) * 5.0;

  // Fcn: '<Root>/Fcn'
  system_transmitter_B.Fcn = (system_transmitter_B.Integrator1 -
    system_transmitter_B.Integrator) * 10.0;

  // Fcn: '<Root>/Fcn1'
  system_transmitter_B.Fcn1 = ((-10.0 * system_transmitter_B.Integrator *
    system_transmitter_B.Integrator2 + 28.0 * system_transmitter_B.Integrator) -
    system_transmitter_B.Integrator1) + system_transmitter_B.Sum;

  // Fcn: '<Root>/Fcn12'
  system_transmitter_B.Fcn12 = ((((-10.0 * system_transmitter_B.Integrator *
    system_transmitter_B.Integrator2 + 28.0 * system_transmitter_B.Integrator) -
    system_transmitter_B.Integrator1) + system_transmitter_B.Sum) -
    (system_transmitter_B.Integrator1 - system_transmitter_B.Integrator) * 10.0)
    * 10.0;

  // Fcn: '<Root>/Fcn2'
  system_transmitter_B.Fcn2 = (10.0 * system_transmitter_B.Integrator *
    system_transmitter_B.Integrator1 - 2.6666666666666665 *
    system_transmitter_B.Integrator2) + system_transmitter_B.Integrator4 *
    system_transmitter_B.Sum;

  // Fcn: '<Root>/Fcn23'
  system_transmitter_B.Fcn23 = (((-(0.15 * system_transmitter_B.Integrator4 +
    system_transmitter_B.Integrator3) - ((system_transmitter_B.Integrator3 -
    10.0) * system_transmitter_B.Integrator5 + 0.2)) + system_transmitter_B.u2)
    + (-system_transmitter_B.Integrator4 - system_transmitter_B.Integrator5) *
    0.15) + (0.15 * system_transmitter_B.Integrator4 +
             system_transmitter_B.Integrator3) * 0.0225;

  // Fcn: '<Root>/Fcn3'
  system_transmitter_B.Fcn3 = -system_transmitter_B.Integrator4 -
    system_transmitter_B.Integrator5;

  // Fcn: '<Root>/Fcn4'
  system_transmitter_B.Fcn4 = 0.15 * system_transmitter_B.Integrator4 +
    system_transmitter_B.Integrator3;

  // Fcn: '<Root>/Fcn5'
  system_transmitter_B.Fcn5 = ((system_transmitter_B.Integrator3 - 10.0) *
    system_transmitter_B.Integrator5 + 0.2) - system_transmitter_B.u2;
  if (rtmIsMajorTimeStep(system_transmitter_M)) {
    rt_ertODEUpdateContinuousStates(&system_transmitter_M->solverInfo);

    // Update absolute time for base rate
    // The "clockTick0" counts the number of times the code of this task has
    //  been executed. The absolute time is the multiplication of "clockTick0"
    //  and "Timing.stepSize0". Size of "clockTick0" ensures timer will not
    //  overflow during the application lifespan selected.
    //  Timer of this task consists of two 32 bit unsigned integers.
    //  The two integers represent the low bits Timing.clockTick0 and the high bits
    //  Timing.clockTickH0. When the low bit overflows to 0, the high bits increment.

    if (!(++system_transmitter_M->Timing.clockTick0)) {
      ++system_transmitter_M->Timing.clockTickH0;
    }

    system_transmitter_M->Timing.t[0] = rtsiGetSolverStopTime
      (&system_transmitter_M->solverInfo);

    {
      // Update absolute timer for sample time: [1.0E-6s, 0.0s]
      // The "clockTick1" counts the number of times the code of this task has
      //  been executed. The resolution of this integer timer is 1.0E-6, which is the step size
      //  of the task. Size of "clockTick1" ensures timer will not overflow during the
      //  application lifespan selected.
      //  Timer of this task consists of two 32 bit unsigned integers.
      //  The two integers represent the low bits Timing.clockTick1 and the high bits
      //  Timing.clockTickH1. When the low bit overflows to 0, the high bits increment.

      system_transmitter_M->Timing.clockTick1++;
      if (!system_transmitter_M->Timing.clockTick1) {
        system_transmitter_M->Timing.clockTickH1++;
      }
    }
  }                                    // end MajorTimeStep
}

// Derivatives for root system: '<Root>'
void system_transmitter_derivatives(void)
{
  XDot_system_transmitter_T *_rtXdot;
  _rtXdot = ((XDot_system_transmitter_T *) system_transmitter_M->derivs);

  // Derivatives for Integrator: '<Root>/Integrator'
  _rtXdot->Integrator_CSTATE = system_transmitter_B.Fcn;

  // Derivatives for Integrator: '<Root>/Integrator1'
  _rtXdot->Integrator1_CSTATE = system_transmitter_B.Fcn1;

  // Derivatives for Integrator: '<Root>/Integrator2'
  _rtXdot->Integrator2_CSTATE = system_transmitter_B.Fcn2;

  // Derivatives for Integrator: '<Root>/Integrator3'
  _rtXdot->Integrator3_CSTATE = system_transmitter_B.Fcn3;

  // Derivatives for Integrator: '<Root>/Integrator4'
  _rtXdot->Integrator4_CSTATE = system_transmitter_B.Fcn4;

  // Derivatives for Integrator: '<Root>/Integrator5'
  _rtXdot->Integrator5_CSTATE = system_transmitter_B.Fcn5;
}

// Model initialize function
void system_transmitter_initialize(void)
{
  // Registration code

  // initialize non-finites
  rt_InitInfAndNaN(sizeof(real_T));

  {
    // Setup solver object
    rtsiSetSimTimeStepPtr(&system_transmitter_M->solverInfo,
                          &system_transmitter_M->Timing.simTimeStep);
    rtsiSetTPtr(&system_transmitter_M->solverInfo, &rtmGetTPtr
                (system_transmitter_M));
    rtsiSetStepSizePtr(&system_transmitter_M->solverInfo,
                       &system_transmitter_M->Timing.stepSize0);
    rtsiSetdXPtr(&system_transmitter_M->solverInfo,
                 &system_transmitter_M->derivs);
    rtsiSetContStatesPtr(&system_transmitter_M->solverInfo, (real_T **)
                         &system_transmitter_M->contStates);
    rtsiSetNumContStatesPtr(&system_transmitter_M->solverInfo,
      &system_transmitter_M->Sizes.numContStates);
    rtsiSetNumPeriodicContStatesPtr(&system_transmitter_M->solverInfo,
      &system_transmitter_M->Sizes.numPeriodicContStates);
    rtsiSetPeriodicContStateIndicesPtr(&system_transmitter_M->solverInfo,
      &system_transmitter_M->periodicContStateIndices);
    rtsiSetPeriodicContStateRangesPtr(&system_transmitter_M->solverInfo,
      &system_transmitter_M->periodicContStateRanges);
    rtsiSetErrorStatusPtr(&system_transmitter_M->solverInfo, (&rtmGetErrorStatus
      (system_transmitter_M)));
    rtsiSetRTModelPtr(&system_transmitter_M->solverInfo, system_transmitter_M);
  }

  rtsiSetSimTimeStep(&system_transmitter_M->solverInfo, MAJOR_TIME_STEP);
  system_transmitter_M->intgData.f[0] = system_transmitter_M->odeF[0];
  system_transmitter_M->contStates = ((X_system_transmitter_T *)
    &system_transmitter_X);
  rtsiSetSolverData(&system_transmitter_M->solverInfo, static_cast<void *>
                    (&system_transmitter_M->intgData));
  rtsiSetSolverName(&system_transmitter_M->solverInfo,"ode1");
  rtmSetTPtr(system_transmitter_M, &system_transmitter_M->Timing.tArray[0]);
  system_transmitter_M->Timing.stepSize0 = 1.0E-6;

  // Initialize DataMapInfo substructure containing ModelMap for C API
  system_transmitter_InitializeDataMapInfo();

  // InitializeConditions for Integrator: '<Root>/Integrator'
  system_transmitter_X.Integrator_CSTATE = 1.0;

  // InitializeConditions for Integrator: '<Root>/Integrator1'
  system_transmitter_X.Integrator1_CSTATE = 1.0;

  // InitializeConditions for Integrator: '<Root>/Integrator2'
  system_transmitter_X.Integrator2_CSTATE = 1.0;

  // InitializeConditions for Integrator: '<Root>/Integrator3'
  system_transmitter_X.Integrator3_CSTATE = 1.0;

  // InitializeConditions for Integrator: '<Root>/Integrator4'
  system_transmitter_X.Integrator4_CSTATE = 1.0;

  // InitializeConditions for Integrator: '<Root>/Integrator5'
  system_transmitter_X.Integrator5_CSTATE = 1.0;
}

// Model terminate function
void system_transmitter_terminate(void)
{
  // (no terminate code required)
}

//
// File trailer for generated code.
//
// [EOF]
//
