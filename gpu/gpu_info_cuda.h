#ifndef __APPLE__
#ifndef __GPU_INFO_CUDA_H__
#define __GPU_INFO_CUDA_H__
#include "gpu_info.h"

// Just enough typedef's to dlopen/dlsym for memory information
typedef enum nvmlReturn_enum {
  NVML_SUCCESS = 0,
  // Other values omitted for now...
} nvmlReturn_t;
typedef void *nvmlDevice_t;  // Opaque is sufficient
typedef struct nvmlMemory_st {
  unsigned long long total;
  unsigned long long free;
  unsigned long long used;
} nvmlMemory_t;

typedef struct cuda_handle {
  void *handle;
  nvmlReturn_t (*initFn)(void);
  nvmlReturn_t (*shutdownFn)(void);
  nvmlReturn_t (*getHandle)(unsigned int, nvmlDevice_t *);
  nvmlReturn_t (*getMemInfo)(nvmlDevice_t, nvmlMemory_t *);
  nvmlReturn_t (*getCount)(unsigned int *);
  nvmlReturn_t (*getComputeCapability)(nvmlDevice_t, int* major, int* minor);
} cuda_handle_t;

typedef struct cuda_init_resp {
  char *err;  // If err is non-null handle is invalid
  cuda_handle_t ch;
} cuda_init_resp_t;

typedef struct cuda_compute_capability {
  char *err;
  int major;
  int minor;
} cuda_compute_capability_t;

void cuda_init(char *cuda_lib_path, cuda_init_resp_t *resp);
void cuda_check_vram(cuda_handle_t ch, mem_info_t *resp);
void cuda_compute_capability(cuda_handle_t ch, cuda_compute_capability_t *cc);

#endif  // __GPU_INFO_CUDA_H__
#endif  // __APPLE__