#pragma once
#include "Core/Base.h"
#include <string>

namespace Arc
{
    namespace Graphics
    {
        enum class TextureFormat
        {
            RGB = 0,
            RGBA
        };

        struct Texture
        {
            bool isValid = false;
            u32 id = 0;
            u32 width = 0;
            u32 height = 0;
            u32 numChannels = 0;
            u8* data = NULL;
            std::string path;
            TextureFormat format;

            void Bind(u8 slot);
            void Unbind();
        };

        Texture LoadTexture(const char* path, TextureFormat format = TextureFormat::RGB);
        void UnloadTexture(Texture& texture);
    }
}
