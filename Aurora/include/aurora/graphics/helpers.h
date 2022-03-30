#pragma once

#include "log.h"

#include "glad/glad.h"
#include <string>

namespace aurora::graphics
{
    void CheckGLError();
}

#ifdef AURORA_CONFIG_RELEASE
#define AURORA_CHECK_GL_ERROR aurora::graphics::CheckGL_Error();
#else
#define AURORA_CHECK_GL_ERROR (void)0
#endif