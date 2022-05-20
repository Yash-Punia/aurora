#pragma once
#include <cstdint>

#include "external/glm/glm.hpp"

namespace aurora::graphics
{
    class Framebuffer
    {

    public:
        Framebuffer(uint32_t width, uint32_t height);
        ~Framebuffer();

        inline uint32_t GetFbo() { return mFbo; }
        inline uint32_t GetTextureId() { return mTextureId;}
        inline uint32_t GetRenderbufferId() { return mRenderbufferId; }
        inline const glm::ivec2& GetSize() { return mSize; }
        inline const glm::vec4& GetClearColour() { return mClearColour; }
        inline void SetClearColour(glm::vec4& cc) { mClearColour = cc; }

    private:
        uint32_t mFbo;
        uint32_t mTextureId;
        uint32_t mRenderbufferId;
        glm::ivec2 mSize;

        glm::vec4 mClearColour;
    };
}
