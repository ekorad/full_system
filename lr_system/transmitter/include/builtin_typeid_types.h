//
// File: builtin_typeid_types.h
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

#ifndef BUILTIN_TYPEID_TYPES_H
#define BUILTIN_TYPEID_TYPES_H
#include "rtwtypes.h"
#ifndef BUILTIN_TYPEID_TYPES
#define BUILTIN_TYPEID_TYPES

// Enumeration of built-in data types
typedef enum {
  SS_DOUBLE = 0,                       // real_T
  SS_SINGLE = 1,                       // real32_T
  SS_INT8 = 2,                         // int8_T
  SS_UINT8 = 3,                        // uint8_T
  SS_INT16 = 4,                        // int16_T
  SS_UINT16 = 5,                       // uint16_T
  SS_INT32 = 6,                        // int32_T
  SS_UINT32 = 7,                       // uint32_T
  SS_BOOLEAN = 8                       // boolean_T
} BuiltInDTypeId;

#define SS_NUM_BUILT_IN_DTYPE          ((int_T)SS_BOOLEAN+1)

// Enumeration for MAT-file logging code
typedef int_T DTypeId;

#endif                                 // BUILTIN_TYPEID_TYPES
#endif                                 // BUILTIN_TYPEID_TYPES_H

//
// File trailer for generated code.
//
// [EOF]
//
