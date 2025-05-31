#pragma once
#include "bount-lib/standard/macros.hpp"

#if defined(BOUNT_GPU_BUILD_API)
#define BOUNT_GPU_API BOUNT_EXPORT
#elif defined(BOUNT_GPU_USE_API)
#define BOUNT_GPU_API BOUNT_IMPORT
#else
#define BOUNT_GPU_API
#endif