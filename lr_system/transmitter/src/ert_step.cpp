//
// File: ert_main.cpp
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
#include <stddef.h>
#include <stdio.h>                // This ert_main.c example uses printf/fflush
#include "system_transmitter.h"        // Model's header file
#include "rtwtypes.h"
#include "builtin_typeid_types.h"
#include "ert_step.h"
#include <stdexcept>

using std::size_t;
using std::to_string;
using std::runtime_error;

static constexpr size_t modelMaxSamples = 5000001;
static size_t requestedMaxSamples = modelMaxSamples;

CustomDataMessage rt_OneStep(void)
{
    static boolean_T OverrunFlag = false;
    static size_t crtSampleIndex = 0;

    // Disable interrupts here

    // Check for overrun
    if (OverrunFlag) {
        rtmSetErrorStatus(system_transmitter_M, "Overrun");
        throw runtime_error("Overrun error detected");
    }

    OverrunFlag = true;

    // Save FPU context here (if necessary)
    // Re-enable timer or interrupt here
    // Set model inputs here

    // Step the model for base rate
    system_transmitter_step();

    // Get model outputs here
    
    CustomDataMessage cdm{ system_transmitter_Y.xl_out, system_transmitter_Y.zl_out,
        system_transmitter_Y.yr_out };

    // Indicate task complete
    OverrunFlag = false;

    // Disable interrupts here
    // Restore FPU context here (if necessary)
    // Enable interrupts here

    crtSampleIndex++;
    if (crtSampleIndex == requestedMaxSamples)
    {
        rtmSetStopRequested(system_transmitter_M, true);
    }

    return cdm;
}

void setMaxSamples(const size_t maxSamples)
{
    if (maxSamples > modelMaxSamples)
    {
        throw runtime_error("Specified number of samples is too large (max ="
            + to_string(modelMaxSamples) + ")");
    }

    requestedMaxSamples = maxSamples; 
}