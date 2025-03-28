#include "Graphics/Texture.h"
#include "Core/Base.h"
#include "Core/Log.h"

#include <glad/glad.h>
#include <stb_image.h>
#include <string>

namespace Arc
{
    namespace Graphics
    {
        static u32 TextureFormatToU32(TextureFormat format)
        {
            u32 value = 0;

            switch (format)
            {
                case TextureFormat::RGB:
                    value = GL_RGB;
                    break;

                case TextureFormat::RGBA:
                    value = GL_RGBA;
                    break;
            }

            return value;
        }

        Texture LoadTexture(const char* path, TextureFormat format)
        {
            Texture texture;
            texture.format = format;
            texture.path = path;

            glGenTextures(1, &texture.id);
            glBindTexture(GL_TEXTURE_2D, texture.id);

            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

            stbi_set_flip_vertically_on_load(true);
            texture.data = stbi_load(texture.path.c_str(), (s32*)&texture.width, (s32*)&texture.height,
                                     (s32*)&texture.numChannels, 0);

            if (texture.data == NULL)
            {
                WARN("Failed to load texture %s", texture.path.c_str());
                return texture;
            }

            u32 glFormat = TextureFormatToU32(texture.format);
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, texture.width, texture.height, 0, glFormat, GL_UNSIGNED_BYTE,
                         texture.data);
            glGenerateMipmap(GL_TEXTURE_2D);

            glBindTexture(GL_TEXTURE_2D, 0);

            INFO("Loaded texture %s successfully with id %d", texture.path.c_str(), texture.id);
            return texture;
        }

        void UnloadTexture(Texture& texture)
        {
            if (texture.id != 0)
            {
                INFO("Unloading texture %s...", texture.path.c_str());
                stbi_image_free(texture.data);
                glDeleteTextures(1, &texture.id);
            }
        }

        void Texture::Bind(u8 slot)
        {
            glActiveTexture(GL_TEXTURE0 + slot);
            glBindTexture(GL_TEXTURE_2D, id);
        }

        void Texture::Unbind()
        {
            glBindTexture(GL_TEXTURE_2D, 0);
        }
    }
}
