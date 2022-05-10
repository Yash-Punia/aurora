#include "graphics/framebuffer.h"
#include "graphics/helpers.h"
#include "log.h"

#include "glad/glad.h"

namespace aurora::graphics
{
    Framebuffer::Framebuffer(uint32_t width, uint32_t height)
        : mFbo(0)
        , mTextureId(0)
        , mRenderbufferId(0)
        , mWidth(width)
        , mHeight(height)
        , mCCR(1)
        , mCCG(1)
        , mCCB(1)
        , mCCA(1)
        
    
    {
        glGenBuffers(1, &mFbo); AURORA_CHECK_GL_ERROR;
        glBindBuffer(GL_FRAMEBUFFER, mFbo); AURORA_CHECK_GL_ERROR;

        /**
         * Instead of using direct colours, we are here using colours from
         * textures by and passing it onto the framebuffers 
         * 
         * Framebuffers need colours, depth and stencil buffer
         */
        glGenTextures(1, &mTextureId); AURORA_CHECK_GL_ERROR;
        glBindTexture(GL_TEXTURE_2D, mTextureId); AURORA_CHECK_GL_ERROR;
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, mWidth, mHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, nullptr); AURORA_CHECK_GL_ERROR;
        glBindTexture(GL_TEXTURE_2D, 0); AURORA_CHECK_GL_ERROR;
        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, mTextureId, 0); AURORA_CHECK_GL_ERROR;

        // Create depth/stencil renderbuffer
        // Use this link to understand more 
        // https://stackoverflow.com/questions/2213030/whats-the-concept-of-and-differences-between-framebuffer-and-renderbuffer-in-op

        glGenRenderbuffers(1, &mRenderbufferId); AURORA_CHECK_GL_ERROR;
        glBindRenderbuffer(GL_RENDERBUFFER, mRenderbufferId); AURORA_CHECK_GL_ERROR;
        glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, mWidth, mHeight); AURORA_CHECK_GL_ERROR;
        glBindRenderbuffer(GL_RENDERBUFFER, 0); AURORA_CHECK_GL_ERROR;
        glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, mRenderbufferId); AURORA_CHECK_GL_ERROR;

        // Check status for completeness
        int32_t completeStatus = glCheckFramebufferStatus(GL_FRAMEBUFFER); AURORA_CHECK_GL_ERROR;
        if(completeStatus != GL_FRAMEBUFFER_COMPLETE)
        {
            AURORA_ERROR("Failure to create framebuffer. Complete status: {}", completeStatus);
        }

        glBindFramebuffer(GL_FRAMEBUFFER, 0); AURORA_CHECK_GL_ERROR;
    }

    Framebuffer::~Framebuffer()
    {
        glDeleteFramebuffers(1, &mFbo); AURORA_CHECK_GL_ERROR;
        mFbo = 0;
        mTextureId = 0;
        mRenderbufferId = 0;
    }
} 
