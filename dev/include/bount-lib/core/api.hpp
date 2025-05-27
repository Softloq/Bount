#pragma once
#include "bount-lib/standard/macros.hpp"

#if defined(BOUNT_CORE_BUILD_API)
#define BOUNT_CORE_API BOUNT_EXPORT
#elif defined(BOUNT_CORE_USE_API)
#define BOUNT_CORE_API BOUNT_IMPORT
#else
#define BOUNT_CORE_API
#endif