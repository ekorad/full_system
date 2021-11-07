#ifndef RTW_HEADER_system_transmitter_cap_host_h_
#define RTW_HEADER_system_transmitter_cap_host_h_
#ifdef HOST_CAPI_BUILD
#include "rtw_capi.h"
#include "rtw_modelmap.h"

typedef struct {
  rtwCAPI_ModelMappingInfo mmi;
} system_transmitter_host_DataMapInfo_T;

#ifdef __cplusplus

extern "C" {

#endif

  void system_transmitter_host_InitializeDataMapInfo
    (system_transmitter_host_DataMapInfo_T *dataMap, const char *path);

#ifdef __cplusplus

}
#endif
#endif                                 // HOST_CAPI_BUILD
#endif                             // RTW_HEADER_system_transmitter_cap_host_h_

// EOF: system_transmitter_capi_host.h
