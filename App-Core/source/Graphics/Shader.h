#pragma once
#include "Core/Base.h"

#include <string>
#include <unordered_map>

namespace Arc
{
    namespace Graphics
    {
        struct Shader
        {
            u32 id = 0;
            std::unordered_map<std::string, s32> uniforms;

            void Bind();
            void Unbind();
        };

        Shader LoadShader(const char* vertexPath, const char* fragmentPath);
        void UnloadShader(Shader& shader);
    }
}
