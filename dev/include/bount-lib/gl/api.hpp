#pragma once
#include "bount-lib/standard/macros.hpp"

#if defined(BOUNT_GL_BUILD_API)
#define BOUNT_GL_API BOUNT_EXPORT
#elif defined(BOUNT_GL_USE_API)
#define BOUNT_GL_API BOUNT_IMPORT
#else
#define BOUNT_GL_API
#endif