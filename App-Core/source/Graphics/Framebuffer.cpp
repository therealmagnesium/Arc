#include "Graphics/Framebuffer.h"
#include "Graphics/Texture.h"

#include "Core/Base.h"
#include "Core/Log.h"

#include <glad/glad.h>

namespace Arc
{
    namespace Graphics
    {
        Framebuffer CreateFramebuffer(u32 numAttachments)
        {
            Framebuffer framebuffer;
            framebuffer.attachments.resize(numAttachments);

            glGenFramebuffers(1, &framebuffer.id);
            glBindFramebuffer(GL_FRAMEBUFFER, framebuffer.id);

            glBindFramebuffer(GL_FRAMEBUFFER, 0);

            INFO("Framebuffer was successfully created with id %d", framebuffer.id);
            return framebuffer;
        }

        void DestroyFramebuffer(Framebuffer& framebuffer)
        {
            INFO("Destroying framebuffer with id %d...", framebuffer.id);
            glDeleteFramebuffers(1, &framebuffer.id);
        }

        void ValidateFramebuffer(Framebuffer& framebuffer)
        {
            if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
                WARN("Failed to create framebuffer with id %d", framebuffer.id);
        }

        void Framebuffer::Bind()
        {
            glBindFramebuffer(GL_FRAMEBUFFER, id);
        }

        void Framebuffer::Unbind()
        {
            glBindFramebuffer(GL_FRAMEBUFFER, 0);
        }

        Texture Framebuffer::CreateAttachment(FramebufferAttachmentType type, u32 width, u32 height)
        {
            Texture texture;
            texture.width = width;
            texture.height = height;

            glGenTextures(1, &texture.id);
            glBindTexture(GL_TEXTURE_2D, texture.id);

            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

            switch (type)
            {
                case FB_ATTACHMENT_COLOR:
                    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, texture.width, texture.height, 0, GL_RGB, GL_UNSIGNED_BYTE,
                                 texture.data);
                    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, texture.id, 0);
                    break;
                case FB_ATTACHMENT_DEPTH:
                    glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH, texture.width, texture.height, 0, GL_DEPTH_STENCIL,
                                 GL_UNSIGNED_INT, texture.data);
                    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH, GL_TEXTURE_2D, texture.id, 0);
                    break;
                case FB_ATTACHMENT_DEPTH_STENCIL:
                    glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH24_STENCIL8, texture.width, texture.height, 0,
                                 GL_DEPTH_STENCIL, GL_UNSIGNED_INT_24_8, texture.data);
                    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_TEXTURE_2D, texture.id, 0);
                    break;
            }

            glBindTexture(GL_TEXTURE_2D, 0);

            return texture;
        }
    }
}
