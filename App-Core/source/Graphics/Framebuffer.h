#pragma once
#include "Graphics/Texture.h"

#include "Core/Base.h"

#include <vector>

namespace Arc
{
    namespace Graphics
    {
        enum FramebufferAttachmentType
        {
            FB_ATTACHMENT_COLOR = 0,
            FB_ATTACHMENT_DEPTH,
            FB_ATTACHMENT_DEPTH_STENCIL
        };

        struct Framebuffer
        {
            u32 id = 0;
            std::vector<Texture> attachments;

            void Bind();
            void Unbind();

            static Texture CreateAttachment(FramebufferAttachmentType type, u32 width, u32 height);
        };

        Framebuffer CreateFramebuffer(u32 numAttachments);
        void DestroyFramebuffer(Framebuffer& framebuffer); 
        void ValidateFramebuffer(Framebuffer& framebuffer);
    }
}
