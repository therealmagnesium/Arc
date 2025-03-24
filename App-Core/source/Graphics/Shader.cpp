#include "Graphics/Shader.h"
#include "Core/Base.h"
#include "Core/Log.h"
#include "Core/IO.h"

#include <glad/glad.h>

namespace Arc
{
    namespace Graphics
    {
        static u32 CompileShader(u32 target, const char* path)
        {
            s32 success;
            char log[512];

            Core::File file = Core::ReadFile(path);
            if (!file.isValid)
            {
                WARN("Failed to compile shader %s!", path);
                return 0;
            }

            u32 targetId = glCreateShader(target);
            glShaderSource(targetId, 1, (const char* const*)&file.data, NULL);
            glCompileShader(targetId);
            glGetShaderiv(targetId, GL_COMPILE_STATUS, &success);

            if (!success)
            {
                glGetShaderInfoLog(targetId, 512, NULL, log);
                ERROR("Failed to compile shader!\n%s", log);
            }

            free(file.data);
            return targetId;
        }

        Shader LoadShader(const char* vertexPath, const char* fragmentPath)
        {
            Shader shader;
            shader.id = glCreateProgram();

            u32 vertex = CompileShader(GL_VERTEX_SHADER, vertexPath);
            u32 fragment = CompileShader(GL_FRAGMENT_SHADER, fragmentPath);

            int success;
            char log[512];

            glAttachShader(shader.id, vertex);
            glAttachShader(shader.id, fragment);
            glLinkProgram(shader.id);
            glGetProgramiv(shader.id, GL_LINK_STATUS, &success);

            if (!success)
            {
                glGetProgramInfoLog(shader.id, 512, NULL, log);
                ERROR("Failed to link shader!\n%s", log);
                return (Shader){};
            }

            return shader;
        }

        void UnloadShader(Shader& shader)
        {
            shader.Unbind();
            glDeleteProgram(shader.id);
        }

        void Shader::Bind()
        {
            glUseProgram(id);
        }

        void Shader::Unbind()
        {
            glUseProgram(0);
        }

    }
}
