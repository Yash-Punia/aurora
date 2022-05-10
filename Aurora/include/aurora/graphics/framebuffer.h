#pragma once
#include <cstdint>

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
        inline void GetSize(uint32_t& w, uint32_t&h ) { w = mWidth; h = mHeight; }
        inline void GetClearColour(float& r, float& g, float& b, float& a) { r = mCCR; g = mCCG; b = mCCB; a = mCCA; }
        inline void SetClearColour(float r, float g, float b, float a) { mCCR = r; mCCG = g; mCCB = b; mCCA = a; }

    private:
        uint32_t mFbo;
        uint32_t mTextureId;
        uint32_t mRenderbufferId;
        uint32_t mWidth, mHeight;

        float mCCR, mCCG, mCCB, mCCA;
    };
}
